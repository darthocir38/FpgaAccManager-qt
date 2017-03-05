/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "noc_accelerator_model.h"

#include <QIcon>
#include <QPixmap>

Model::Model(std::shared_ptr<NocAccelerator> hw_noc, QObject *parent)
    : QAbstractItemModel(parent),
      services(QPixmap(":/images/services.png")),
      _hw_noc(hw_noc)
{

}

Model::~Model()
{
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (row < _hw_noc->rows() && row >= 0 && column < _hw_noc->columns() && column >= 0) {
        //Node *parentNode = static_cast<Node*>(parent.internalPointer());
        NocElement::ptr elem = _hw_noc->get_element(row,column);
        if (elem)
            return createIndex(row, column, elem.get());
    }
    return QModelIndex();
}

QModelIndex Model::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _hw_noc->rows();
}

int Model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _hw_noc->columns();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
        return QVariant(QString::fromStdString(_hw_noc->get_element(index.row(),index.column())->to_string()));
    if (role == Qt::DecorationRole) {
        if (index.column() == 0)
            return iconProvider.icon(QFileIconProvider::Folder);
        return iconProvider.icon(QFileIconProvider::File);
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        return QString::number(section);
    if (role == Qt::DecorationRole)
        return QVariant::fromValue(services);
    return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return Qt::ItemIsDragEnabled|QAbstractItemModel::flags(index);
}

bool Model::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(rows);
    beginInsertRows(QModelIndex(), position, position);

    _hw_noc->add_row();

    endInsertRows();
    return true;
}

bool Model::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(rows);
    beginRemoveRows(QModelIndex(), position-1, position-1);
    _hw_noc->remove_row();
    endRemoveRows();
    return true;
}
bool Model::insertColumns(int position, int count, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(count);
    beginInsertColumns(QModelIndex(), position, position);
    _hw_noc->add_column();
    endInsertColumns();
    return true;
}

bool Model::removeColumns(int position, int count, const QModelIndex &index)
{
    Q_UNUSED(index);
    Q_UNUSED(count);
    beginRemoveColumns(QModelIndex(), position-1, position-1);
    _hw_noc->remove_column();
    endRemoveColumns();
    return true;
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
 {
    Q_UNUSED(value);
    if (index.isValid() && role == Qt::EditRole)
    {
        emit(dataChanged(index, index));
        return true;
    }
    return false;
 }
