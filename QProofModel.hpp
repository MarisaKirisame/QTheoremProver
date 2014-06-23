#ifndef QPROOFMODEL_HPP
#define QPROOFMODEL_HPP

#include <QAbstractItemModel>
#include "theorem_prover/first_order_logic/term.hpp"
class QProofModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit QProofModel( const std::shared_ptr< theorem_prover::first_order_logic::term > & ptr, QObject *parent = 0);
	QModelIndex index(int row, int column, const QModelIndex &parent) const override;
	QModelIndex parent(const QModelIndex &child) const override;
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
};

#endif // QPROOFMODEL_HPP
