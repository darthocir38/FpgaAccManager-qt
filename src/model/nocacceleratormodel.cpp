#include "nocacceleratormodel.h"

NocAcceleratorModel::NocAcceleratorModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QModelIndex NocAcceleratorModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex NocAcceleratorModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int NocAcceleratorModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int NocAcceleratorModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant NocAcceleratorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
