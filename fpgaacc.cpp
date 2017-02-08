#include "fpgaacc.h"
#include "ui_fpgaacc.h"
#include "generategriddialog.h"

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

void FPGAAcc::on_createDesign_clicked()
{
    GenerateGridDialog grid;
    grid.setModal(true);
    grid.exec();
}
