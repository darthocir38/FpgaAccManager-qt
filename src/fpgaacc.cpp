#include "fpgaacc.h"
#include "ui_fpgaacc.h"

#include "model/noc_accelerator_model.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include <QAbstractItemModel>

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


void FPGAAcc::on_createDesign_clicked()
{

}

void FPGAAcc::on_saveDesign_clicked()
{
    QFile file(QStringLiteral("/tmp/save.json"));

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

