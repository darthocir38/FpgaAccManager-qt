#include "nocacceleratormodel.h"

NocAcceleratorModel::NocAcceleratorModel(const NocAccelerator::ptr &accelerator, QObject *parent)
    : QAbstractItemModel(parent)
    , _accelerator(accelerator)
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

    _accelerator->rows();
}

int NocAcceleratorModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    _accelerator->cols();

}

QVariant NocAcceleratorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
