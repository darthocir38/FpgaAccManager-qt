#include "noc_accelerator.h"
#include <QJsonArray>


NocAccelerator::NocAccelerator(unsigned row, unsigned col) : _rows(row), _cols(col)
{
    for(unsigned i = 0; i < row; i++)
        for (unsigned j = 0; j< col; j++)
        {
            NocElement elem(i,j, NocElement::TileType::Process);
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
        NocElement elem;
        elem.read(elemObject);
        _tiles.push_back(elem);
    }
}

void NocAccelerator::write(QJsonObject &json) const
{
    QJsonArray elemArray;
    for(const NocElement elem : _tiles)
    {
        QJsonObject elemObject;
        elem.write(elemObject);
        elemArray.append(elemObject);
    }
    json["elems"] = elemArray;
}

unsigned NocAccelerator::rows() const
{
    return _rows;
}

void NocAccelerator::rows(const unsigned &rows)
{
    _rows = rows;
}

unsigned NocAccelerator::cols() const
{
    return _cols;
}

void NocAccelerator::cols(const unsigned &cols)
{
    _cols = cols;
}
