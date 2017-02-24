#include "fpgaacc.h"
#include "ui_fpgaacc.h"
#include "ui/generategriddialog.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

// include headers that implement a archive in simple text format


FPGAAcc::FPGAAcc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPGAAcc),
    _hwnoc(new NocAccelerator(5,4))
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
