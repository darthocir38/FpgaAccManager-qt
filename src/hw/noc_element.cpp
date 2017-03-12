#include "noc_element.h"

NocElement::NocElement(unsigned col, unsigned row, TileType type)
    : _col(col)
    , _row(row)
    , _type(type)
{
}

NocElement::NocElement(NocElement::ptr oldElement)
    :_col(oldElement->col())
    ,_row(oldElement->row())
    ,_type(TileType::Empty)
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

void NocElement::exportIpxactComponents(QXmlStreamWriter &xmlWriter, QString const& uri)
{
    QString name = QString("NocSwitch_%1_%2").arg(_col).arg(_row);
    //<spirit:componentInstance>
    xmlWriter.writeStartElement(uri,"componentInstance");
    //<spirit:instanceName>NocSwitch_0</spirit:instanceName>
    xmlWriter.writeTextElement(uri,"InstanceName",name);

    //<spirit:componentRef spirit:library="user" spirit:name="NocSwitch" spirit:vendor="Fabmatics.com" spirit:version="1.0"/>
    xmlWriter.writeStartElement(uri,"componentRef");
    xmlWriter.writeAttribute(uri,"library","user");
    xmlWriter.writeAttribute(uri,"name","NocSwitch");
    xmlWriter.writeAttribute(uri,"vendor","Fabmatics.com");
    xmlWriter.writeAttribute(uri,"version","1.0");
    xmlWriter.writeEndElement(); //componentRef

    //<spirit:configurableElementValues>
    xmlWriter.writeStartElement(uri,"configurableElementValues");
        //<spirit:configurableElementValue spirit:referenceId="bd:xciName">design_1_NocSwitch_0_0</spirit:configurableElementValue>
        xmlWriter.writeStartElement(uri,"configurableElementValue");
        QString attr_value = QString("design_1_%1").arg(name);
        xmlWriter.writeAttribute(uri,"referenceId","bd:xciName");
        xmlWriter.writeCharacters(attr_value);
        xmlWriter.writeEndElement(); //configurableElementValue
    xmlWriter.writeEndElement(); //configurableElementValues
    xmlWriter.writeEndElement(); //componentInstance
}

void NocElement::exportIpxactConnections(QXmlStreamWriter &xmlWriter, QString const& uri)
{

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

unsigned NocElement::row() const
{
    return _row;
}

unsigned NocElement::col() const
{
    return _col;
}
