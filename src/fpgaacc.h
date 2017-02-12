#ifndef FPGAACC_H
#define FPGAACC_H

#include <QMainWindow>

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

private:
    Ui::FPGAAcc *ui;

};

#endif // FPGAACC_H