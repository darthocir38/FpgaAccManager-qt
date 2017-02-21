#include "noc_accelerator.h"
#include <QJsonArray>


NocAccelerator::NocAccelerator(unsigned row, unsigned col) : row(row), col(col)
{
    for(unsigned i = 0; i < row; i++)
        for (unsigned j = 0; j< col; j++)
        {
            NocElement elem(i,j, NocElement::TileType::Process);
            tiles.push_back(elem);
        }
}

void NocAccelerator::read(const QJsonObject &json)
{
    tiles.clear();
    QJsonArray elemArray = json["elems"].toArray();
    for (int elemIndex = 0; elemIndex < elemArray.size(); ++elemIndex)
    {
        QJsonObject elemObject = elemArray[elemIndex].toObject();
        NocElement elem;
        elem.read(elemObject);
        tiles.push_back(elem);
    }
}

void NocAccelerator::write(QJsonObject &json) const
{
    QJsonArray elemArray;
    for(const NocElement elem : tiles)
    {
        QJsonObject elemObject;
        elem.write(elemObject);
        elemArray.append(elemObject);
    }
    json["elems"] = elemArray;
}
