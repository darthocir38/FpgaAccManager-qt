#include "editgriddialog.h"
#include "ui_editgriddialog.h"

EditGridDialog::EditGridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGridDialog)
{
    ui->setupUi(this);
}

EditGridDialog::~EditGridDialog()
{
    delete ui;
}
