#ifndef FPGAACC_H
#define FPGAACC_H

#include "hw/noc_accelerator.h"

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QStringListModel>

namespace Ui {
class FPGAAcc;
}

class FPGAAcc : public QMainWindow
{
    Q_OBJECT

public:
    explicit FPGAAcc(QWidget *parent = 0);
    ~FPGAAcc();

private slots:

    void on_action_load_hw_triggered();
    void on_action_save_hw_triggered();

    void on_pb_c_inc_clicked();

    void on_pb_c_dec_clicked();

    void on_pb_r_inc_clicked();

    void on_pb_r_dec_clicked();

    void on_hwtable_activated(const QModelIndex &index);

    void on_hwtable_clicked(const QModelIndex &index);

    void on_pb_update_tile_clicked();

private:

    void writeToFile(const QString &fileName);

    Ui::FPGAAcc *ui;
    NocAccelerator::ptr _hwnoc;

    QAbstractItemModel *_data;
    QStringListModel *_typeModel;

};

#endif // FPGAACC_H
