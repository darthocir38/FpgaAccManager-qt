#include "generategriddialog.h"
#include "ui_generategriddialog.h"

GenerateGridDialog::GenerateGridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateGridDialog)
{
    ui->setupUi(this);
}

GenerateGridDialog::~GenerateGridDialog()
{
    delete ui;
}
