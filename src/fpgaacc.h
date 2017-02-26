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

    void on_action_load_hw_triggered();
    void on_action_save_hw_triggered();

private:

    void writeToFile(const QString &fileName);

    Ui::FPGAAcc *ui;
    NocAccelerator::ptr _hwnoc;

    QAbstractItemModel *data;

};

#endif // FPGAACC_H
