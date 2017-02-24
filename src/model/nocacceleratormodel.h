#ifndef NOCACCELERATORMODEL_H
#define NOCACCELERATORMODEL_H

#include <QAbstractItemModel>

class NocAcceleratorModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit NocAcceleratorModel(QObject *parent = 0);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // NOCACCELERATORMODEL_H