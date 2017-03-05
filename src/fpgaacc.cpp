#include "fpgaacc.h"
#include "hw/noc_element.h"
#include "ui_fpgaacc.h"

#include "model/noc_accelerator_model.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include <QAbstractItemModel>
#include <QFileDialog>

#include <QDebug>
// include headers that implement a archive in simple text format


FPGAAcc::FPGAAcc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPGAAcc),
    _hwnoc(new NocAccelerator(1,1)),
    _data(new Model(_hwnoc)),
    _typeModel(new QStringListModel())
{
    ui->setupUi(this);
    ui->hwtable->setModel(_data);

    QStringList typelist;
    for(auto const& i : NocElement::getListOfTypes())
    {
        typelist << QString::fromStdString(i);
    }
    _typeModel->setStringList(typelist);
    ui->cb_type->setModel(_typeModel);

    if(_hwnoc->rows()<=1) ui->pb_r_dec->setDisabled(true);
    if(_hwnoc->columns()<=1) ui->pb_c_dec->setDisabled(true);

    ui->hwtable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->hwtable->setCurrentIndex(_data->index(0, 0));

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
    QString filePath = QFileDialog::getSaveFileName(
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

void FPGAAcc::on_pb_c_inc_clicked()
{
    qWarning("1");
    if(_data->insertColumn(_hwnoc->columns()))
        qWarning("1+");
    ui->pb_c_dec->setDisabled(false);
}

void FPGAAcc::on_pb_c_dec_clicked()
{
    qWarning("2");
    if(_data->removeColumn(_hwnoc->columns()))
    qWarning("2+");
    if(_hwnoc->columns()<=1) ui->pb_c_dec->setDisabled(true);
}

void FPGAAcc::on_pb_r_inc_clicked()
{
    qWarning("3");
    if(_data->insertRow(_hwnoc->rows()))
    qWarning("3+");
    ui->pb_r_dec->setDisabled(false);

}
void FPGAAcc::on_pb_r_dec_clicked()
{
    if(_data->removeRow(_hwnoc->rows()))
    qWarning("4+");
    if(_hwnoc->rows()<=1) ui->pb_r_dec->setDisabled(true);

}

void FPGAAcc::on_hwtable_activated(const QModelIndex &index)
{
    ui->le_name->setText(QString::fromStdString(_hwnoc->get_element(index.row(),index.column())->to_string()));
}

void FPGAAcc::on_hwtable_clicked(const QModelIndex &index)
{
    ui->le_name->setText(QString::fromStdString(_hwnoc->get_element(index.row(),index.column())->to_string()));
    QString type = QString::fromStdString(NocElement::typeToString(_hwnoc->get_element(index.row(),index.column())->type()));
    int idx = ui->cb_type->findText(type);
    if (idx != -1) ui->cb_type->setCurrentIndex(idx);
}

void FPGAAcc::on_pb_update_tile_clicked()
{
    QModelIndex index = ui->hwtable->currentIndex();
    auto elem = _hwnoc->get_element(index.row(),index.column());
    elem->type(NocElement::stringToType(ui->cb_type->currentText().toStdString()));
    _data->setData(index, QVariant(), Qt::EditRole);
}
