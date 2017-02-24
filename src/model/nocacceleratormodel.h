#ifndef NOCACCELERATORMODEL_H
#define NOCACCELERATORMODEL_H

#include "src/hw/noc_accelerator.h"

#include <QAbstractItemModel>

class NocAcceleratorModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit NocAcceleratorModel(const NocAccelerator::ptr& accelerator, QObject *parent = 0);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    NocAccelerator::ptr _accelerator;
};

#endif // NOCACCELERATORMODEL_H
