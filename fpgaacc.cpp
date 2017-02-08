#include "fpgaacc.h"
#include "ui_fpgaacc.h"

FPGAAcc::FPGAAcc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPGAAcc)
{
    ui->setupUi(this);
}

FPGAAcc::~FPGAAcc()
{
    delete ui;
}
