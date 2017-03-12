#include "noc_tile.h"

std::map<QString,QString> NocTile::connections = {
{"noc_in_ready", "out_center_ready"},
{"noc_in_valid", "out_center_valid"},
{"noc_in_data",  "out_center_data"},
{"noc_in_vc",    "out_center_vc"},
{"noc_out_ready","in_center_ready"},
{"noc_out_data", "in_center_data"},
{"noc_out_vc",   "in_center_vc"},
{"noc_out_valid","in_center_valid"}
};

NocTile::NocTile()
{
}
NocTile::NocTile(NocElement::ptr oldElement)
    :NocElement(oldElement->col(),oldElement->row(), NocElement::TileType::Process)
{

}

void NocTile::exportIpxactComponents(QXmlStreamWriter &xmlWriter, const QString &uri)
{
    NocElement::exportIpxactComponents(xmlWriter, uri);

    QString name = QString("NocTile_%1_%2").arg(_col).arg(_row);
    //<spirit:componentInstance>
    xmlWriter.writeStartElement(uri,"componentInstance");
    //<spirit:instanceName>NocTile_0</spirit:instanceName>
    xmlWriter.writeTextElement(uri,"InstanceName",name);

    //<spirit:componentRef spirit:library="user" spirit:name="NocTile" spirit:vendor="Fabmatics.com" spirit:version="1.0"/>
    xmlWriter.writeStartElement(uri,"componentRef");
    xmlWriter.writeAttribute(uri,"library","user");
    xmlWriter.writeAttribute(uri,"name","NocTile");
    xmlWriter.writeAttribute(uri,"vendor","Fabmatics.com");
    xmlWriter.writeAttribute(uri,"version","1.0");
    xmlWriter.writeEndElement(); //componentRef

    //<spirit:configurableElementValues>
    xmlWriter.writeStartElement(uri,"configurableElementValues");
        //<spirit:configurableElementValue spirit:referenceId="bd:xciName">design_1_NocTile_0_0</spirit:configurableElementValue>
        xmlWriter.writeStartElement(uri,"configurableElementValue");
        QString attr_value = QString("design_1_%1").arg(name);
        xmlWriter.writeAttribute(uri,"referenceId","bd:xciName");
        xmlWriter.writeCharacters(attr_value);
        xmlWriter.writeEndElement(); //configurableElementValue
    xmlWriter.writeEndElement(); //configurableElementValues
    xmlWriter.writeEndElement(); //componentInstance
}

void NocTile::exportIpxactConnections(QXmlStreamWriter &xmlWriter, const QString &uri)
{
    for(auto const &connection : connections)
    {
        auto const &source = connection.first;
        auto const &destination = connection.second;

        //<spirit:adHocConnection>
        xmlWriter.writeStartElement(uri,"adHocConnection");
            //<spirit:name>NocTile_0_noc_in_ready</spirit:name>
            QString name = QString("Conn_%1_%2_%3_%4").arg(_col).arg(_row).arg(source).arg(destination);
            QString comp_src_name = QString("NocEntry_%1_%2").arg(_col).arg(_row);
            QString comp_dst_name = QString("NocSwitch_%1_%2").arg(_col).arg(_row);
            xmlWriter.writeTextElement(uri,"name",name);
            //<spirit:internalPortReference spirit:componentRef="NocTile_0" spirit:portRef="noc_in_ready"/>
            xmlWriter.writeStartElement(uri,"internalPortReference");
                xmlWriter.writeAttribute(uri,"componentRef",comp_src_name);
                xmlWriter.writeAttribute(uri,"portRef",source);
            xmlWriter.writeEndElement(); //internalPortReference
            //<spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="out_north_ready"/>
            xmlWriter.writeStartElement(uri,"internalPortReference");
                xmlWriter.writeAttribute(uri,"componentRef",comp_dst_name);
                xmlWriter.writeAttribute(uri,"portRef",destination);
            xmlWriter.writeEndElement(); //internalPortReference

        xmlWriter.writeEndElement(); //adHocConnection
    }
}
