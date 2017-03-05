#include "noc_element.h"

NocElement::NocElement(unsigned col, unsigned row, TileType type)
    : _col(col)
    , _row(row)
    , _type(type)
{
}
NocElement::NocElement() : _col(0), _row(0), _type(TileType::Empty)
{
}

void NocElement::read(const QJsonObject &json)
{
    _row = json["row"].toDouble();
    _col = json["col"].toDouble();
    _type = TileType(stringToType(json["tileType"].toString().toStdString()));
}

void NocElement::write(QJsonObject &json) const
{
    json["row"] = (double)_row;
    json["col"] = (double)_col;
    json["tileType"] = QString::fromStdString(typeToString(_type));
}

std::string NocElement::to_string()
{
    return typeToString(_type)+"_"+std::to_string(_col)+"_"+std::to_string(_row);
}

NocElement::TileType NocElement::type() const
{
    return _type;
}

void NocElement::type(const TileType &type)
{
    _type = type;
}
