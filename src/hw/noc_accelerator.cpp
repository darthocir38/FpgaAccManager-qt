#include "noc_accelerator.h"
#include <QJsonArray>


NocAccelerator::NocAccelerator(unsigned row, unsigned col) : _rc(row), _cc(col)
{
    for(unsigned i = 0; i < row; i++)
        for (unsigned j = 0; j< col; j++)
        {
            NocElement::ptr elem(new NocElement(i,j, NocElement::TileType::Empty));
            _tiles.push_back(elem);
        }
}

void NocAccelerator::read(const QJsonObject &json)
{
    _tiles.clear();
    QJsonArray elemArray = json["elems"].toArray();
    for (int elemIndex = 0; elemIndex < elemArray.size(); ++elemIndex)
    {
        QJsonObject elemObject = elemArray[elemIndex].toObject();
        NocElement::ptr elem;
        elem->read(elemObject);
        _tiles.push_back(elem);
    }
}

void NocAccelerator::write(QJsonObject &json) const
{
    QJsonArray elemArray;
    for(const NocElement::ptr elem : _tiles)
    {
        QJsonObject elemObject;
        elem->write(elemObject);
        elemArray.append(elemObject);
    }
    json["elems"] = elemArray;
}

unsigned NocAccelerator::rows() const
{
    return _rc;
}

unsigned NocAccelerator::columns() const
{
    return _cc;
}

NocElement::ptr NocAccelerator::get_element(unsigned row, unsigned column)
{
    return _tiles.at((row*_cc)+column);
}
