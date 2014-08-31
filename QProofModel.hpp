#ifndef QPROOFMODEL_HPP
#define QPROOFMODEL_HPP

#include <QAbstractItemModel>
#include "first_order_logic_prover/term.hpp"
class QProofModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	std::shared_ptr< first_order_logic::proof_tree > pt;
	explicit QProofModel( const first_order_logic::term & term, QObject *parent = 0);
	QModelIndex index(int row, int column, const QModelIndex &parent) const override;
	QModelIndex parent(const QModelIndex &child) const override;
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // QPROOFMODEL_HPP
