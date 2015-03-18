#include "QProofModel.hpp"
#include "first_order_logic_prover/proof_tree.hpp"
QProofModel::QProofModel( const first_order_logic::proof_tree & pt, QObject * parent ) :
    QAbstractItemModel( parent ), pt( pt ) { assert( pt->parent == nullptr ); }

QModelIndex QProofModel::index( int row, int column, const QModelIndex & parent ) const
{
    if ( ! hasIndex( row, column, parent ) ) { return QModelIndex( ); }
    first_order_logic::proof_tree::internal & parent_pt =
            parent.isValid( ) ? ( * static_cast< first_order_logic::proof_tree::internal * >( parent.internalPointer( ) ) ) : * pt;
    first_order_logic::proof_tree & res = parent_pt.child[row];
    assert( res.data );
    return createIndex( row, column, static_cast< void * >( res.data.get( ) ) );
}

QModelIndex QProofModel::parent( const QModelIndex & child ) const
{
    if ( ! child.isValid( ) ) { return QModelIndex( ); }
    first_order_logic::proof_tree::internal * child_pt = static_cast< first_order_logic::proof_tree::internal * >( child.internalPointer( ) );
    if ( child_pt->parent->has_parent( ) )
    {
        first_order_logic::proof_tree::internal * parent_pt = child_pt->parent;
        return createIndex( [&]( )->int
        {
            if ( parent_pt->has_parent( ) )
            {
                first_order_logic::proof_tree::internal & pt = * ( parent_pt->parent );
                for ( size_t i = 0; i < pt.child.size( ); ++i ) { if ( pt.child[i] == * parent_pt ) { return i; } }
                throw;
            }
            else { return 0; }
        }( ), 0, parent_pt );
    }
    else { return QModelIndex( ); }
}

int QProofModel::rowCount(const QModelIndex & parent) const
{
    const first_order_logic::proof_tree::internal & parent_pt =
            parent.isValid( ) ? * static_cast< first_order_logic::proof_tree::internal * >( parent.internalPointer( ) ) : * pt.data.get( );
    return parent_pt.child.size( );
}

int QProofModel::columnCount( const QModelIndex & ) const { return 1; }

QVariant QProofModel::data(const QModelIndex & index, int role) const
{
    if ( ! index.isValid( ) ) { return QVariant( ); }
    if ( role != Qt::DisplayRole ) { return QVariant( ); }
    return QString( (static_cast< first_order_logic::proof_tree::internal * >( index.internalPointer( ) ) )->str.c_str( ) );
}

QVariant QProofModel::headerData( int, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole ) { return QString( pt->str.c_str( ) ); }
    return QVariant( );
}

#include "QProofModel.hpp"
