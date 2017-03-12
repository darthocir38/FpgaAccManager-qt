#include "noc_entry.h"

NocEntry::NocEntry()
{

}

NocEntry::NocEntry(NocElement::ptr oldElement)
    :NocElement(oldElement->col(),oldElement->row(), NocElement::TileType::IO)
{

}

void NocEntry::exportIpxactComponents(QXmlStreamWriter &xmlWriter, const QString &uri)
{
    NocElement::exportIpxactComponents(xmlWriter, uri);

    QString name = QString("NocEntry_%1_%2").arg(_col).arg(_row);
    //<spirit:componentInstance>
    xmlWriter.writeStartElement(uri,"componentInstance");
    //<spirit:instanceName>NocEntry_0</spirit:instanceName>
    xmlWriter.writeTextElement(uri,"InstanceName",name);

    //<spirit:componentRef spirit:library="user" spirit:name="NocEntry" spirit:vendor="Fabmatics.com" spirit:version="1.0"/>
    xmlWriter.writeStartElement(uri,"componentRef");
    xmlWriter.writeAttribute(uri,"library","user");
    xmlWriter.writeAttribute(uri,"name","NocEntry");
    xmlWriter.writeAttribute(uri,"vendor","Fabmatics.com");
    xmlWriter.writeAttribute(uri,"version","1.0");
    xmlWriter.writeEndElement(); //componentRef

    //<spirit:configurableElementValues>
    xmlWriter.writeStartElement(uri,"configurableElementValues");
        //<spirit:configurableElementValue spirit:referenceId="bd:xciName">design_1_NocEntry_0_0</spirit:configurableElementValue>
        xmlWriter.writeStartElement(uri,"configurableElementValue");
        QString attr_value = QString("design_1_%1").arg(name);
        xmlWriter.writeAttribute(uri,"referenceId","bd:xciName");
        xmlWriter.writeCharacters(attr_value);
        xmlWriter.writeEndElement(); //configurableElementValue
    xmlWriter.writeEndElement(); //configurableElementValues
    xmlWriter.writeEndElement(); //componentInstance
}

void NocEntry::exportIpxactConnections(QXmlStreamWriter &xmlWriter, const QString &uri)
{

}
