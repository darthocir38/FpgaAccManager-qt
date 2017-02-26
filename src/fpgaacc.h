#ifndef FPGAACC_H
#define FPGAACC_H

#include "hw/noc_accelerator.h"

#include <QMainWindow>
#include <QAbstractItemModel>

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
    void on_createDesign_clicked();

    void on_saveDesign_clicked();

private:
    Ui::FPGAAcc *ui;
    NocAccelerator::ptr _hwnoc;

    QAbstractItemModel *data;

};

#endif // FPGAACC_H
