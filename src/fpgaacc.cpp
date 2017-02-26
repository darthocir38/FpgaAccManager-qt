#include "fpgaacc.h"
#include "ui_fpgaacc.h"

#include "model/noc_accelerator_model.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include <QAbstractItemModel>
#include <QFileDialog>

// include headers that implement a archive in simple text format


FPGAAcc::FPGAAcc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPGAAcc),
    _hwnoc(new NocAccelerator(1,1)),
    data(new Model(_hwnoc))
{
    ui->setupUi(this);
    ui->hwtable->setModel(data);
}

FPGAAcc::~FPGAAcc()
{
    delete ui;
}


void FPGAAcc::on_action_load_hw_triggered()
{

}

void FPGAAcc::on_action_save_hw_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(
                          this, tr("Save File"), "",
                          tr("Config (*.json)"));
    writeToFile(filePath);
}

void FPGAAcc::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonObject acclObject;
    _hwnoc->write(acclObject);
    QJsonDocument saveDoc(acclObject);
    file.write(saveDoc.toJson());
}
