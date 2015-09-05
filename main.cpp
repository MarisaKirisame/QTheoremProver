#include "MainWindow.hpp"
#include <QApplication>
#include <first_order_logic_prover/first_order_logic.hpp>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    MainWindow w;
    w.show();
    return a.exec();
}

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QSignalMapper>
#include <first_order_logic_prover/sentence/parser.hpp>
#include "QProofModel.hpp"
#include <QtCore>
#include <first_order_logic_prover/FOL/gentzen_system.hpp>
#include <QMessageBox>
#include <first_order_logic_prover/first_order_logic.hpp>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttons =
    {
        ui->pushButton_2,
        ui->pushButton_3,
        ui->pushButton_4,
        ui->pushButton_5,
        ui->pushButton_6,
        ui->pushButton_7,
        ui->pushButton_8,
        ui->pushButton_9,
        ui->pushButton_10
    };
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped( const QString & )), ui->lineEdit, SLOT(AppendString( const QString & )));
    for ( auto i : buttons )
    {
        signalMapper->setMapping( i, i->text( ) );
        connect( i, SIGNAL(pressed()), signalMapper, SLOT(map()));
        connect( i, SIGNAL(released()), this, SLOT(GiveFocus()) );
    }
    setFocusPolicy( Qt::StrongFocus );
    setFocusProxy( ui->lineEdit );
    connect( ui->pushButton, SIGNAL(released()), this, SLOT(GiveFocus()) );
    ui->lineEdit->setFocus( Qt::OtherFocusReason );
}

MainWindow::~MainWindow( ) { delete ui; }

void MainWindow::GiveFocus( ) { ui->lineEdit->setFocus( Qt::OtherFocusReason ); }

void MainWindow::on_lineEdit_returnPressed( ) { on_pushButton_clicked( ); }

void MainWindow::on_pushButton_clicked()
{
    auto res = first_order_logic::parse( ui->lineEdit->text( ).toStdString( ) );
    if ( ! res )
    {
        QMessageBox msgBox( this );
        msgBox.setText( "Error in parsing formula. Please check input or file an issue." );
        msgBox.exec( );
        return;
    }
    auto ret = first_order_logic::gentzen_system::is_valid( * res );
    ui->label->setText( ret.second == first_order_logic::validity::valid ? "valid" : "falsible" );
    QProofModel * pm = new QProofModel( ret.first, nullptr );
    ui->treeView->setModel( pm );
    ui->lineEdit->setText( "" );
}

#include "QProofModel.hpp"
#include <first_order_logic_prover/FOL/proof_tree.hpp>
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

#include "QRememberPositionLineEdit.hpp"
QRememberPositionLineEdit::QRememberPositionLineEdit(QWidget *parent) : QLineEdit(parent), position( 0 ) { }

void QRememberPositionLineEdit::focusOutEvent(QFocusEvent *) { position = cursorPosition( ); }

void QRememberPositionLineEdit::focusInEvent(QFocusEvent *) { setCursorPosition( position ); }

void QRememberPositionLineEdit::AppendString( const QString & str )
{
    QString new_str( text( ) );
    new_str.insert( position, str );
    position += str.size( );
    setText( new_str );
}
