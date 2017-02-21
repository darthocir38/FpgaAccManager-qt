#include "noc_element.h"

NocElement::NocElement(unsigned col, unsigned row, TileType type) : col(col), row(row), type(type)
{
}
NocElement::NocElement() : col(0), row(0), type(TileType::Empty)
{
}

void NocElement::read(const QJsonObject &json)
{
    row = json["row"].toDouble();
    col = json["col"].toDouble();
    type = TileType(qRound(json["classType"].toDouble()));
}

void NocElement::write(QJsonObject &json) const
{
    json["row"] = (double)row;
    json["col"] = (double)col;
    json["tileType"] = type;
}
