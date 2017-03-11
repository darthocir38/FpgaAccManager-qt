#include "noc_accelerator.h"
#include <QJsonArray>
#include <QXmlStreamWriter>
#include <QFile>

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

void NocAccelerator::add_column()
{
    QVector<NocElement::ptr> new_tiles;
    for(unsigned i = 0; i < _rc; i++)
        for (unsigned j = 0; j < _cc+1; j++)
        {
            if(j<_cc)
                new_tiles.push_back(get_element(i,j));
            else
            {
                NocElement::ptr elem(new NocElement(i,j, NocElement::TileType::Empty));
                new_tiles.push_back(elem);
            }
        }
    _cc++;
    _tiles.clear();
    _tiles = new_tiles;
}

void NocAccelerator::remove_column()
{
    QVector<NocElement::ptr> new_tiles;
    for(unsigned i = 0; i < _rc; i++)
        for (unsigned j = 0; j < _cc-1; j++)
        {
            new_tiles.push_back(get_element(i,j));
        }
    _cc--;
    _tiles.clear();
    _tiles = new_tiles;
}


void NocAccelerator::add_row()
{
    QVector<NocElement::ptr> new_tiles;
    for(unsigned i = 0; i < _rc+1; i++)
        for (unsigned j = 0; j< _cc; j++)
        {
            if(i<_rc)
                new_tiles.push_back(get_element(i,j));
            else
            {
                NocElement::ptr elem(new NocElement(i,j, NocElement::TileType::Empty));
                new_tiles.push_back(elem);
            }
        }
    _rc++;
    _tiles.clear();
    _tiles = new_tiles;

}
void NocAccelerator::remove_row()
{
    QVector<NocElement::ptr> new_tiles;
    for(unsigned i = 0; i < _rc-1; i++)
        for (unsigned j = 0; j< _cc; j++)
        {
            if(i<_rc)
                new_tiles.push_back(get_element(i,j));
        }
    _rc--;
    _tiles.clear();
    _tiles = new_tiles;

}

void NocAccelerator::generate_hw_design(const QString &filename)
{
    QXmlStreamWriter xmlWriter;
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly))
    {
      return;
    }
    else
    {
    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(4);

    QString xuri("http://www.xilinx.com/bd");
    QString spirituri("http://www.spiritconsortium.org/XMLSchema/SPIRIT/1685-2009");

    xmlWriter.writeStartDocument();

    xmlWriter.writeNamespace(xuri,"bd");
    xmlWriter.writeStartElement(xuri,"repository");

    xmlWriter.writeAttribute(xuri,"BoundaryCRC", "0x0");
    xmlWriter.writeAttribute(xuri,"device","xc7vx690tffg1761-2");
    xmlWriter.writeAttribute(xuri,"synthFlowMode","Hierarchical");
    xmlWriter.writeAttribute(xuri,"tool_version","2016.4");
    xmlWriter.writeAttribute(xuri,"top","design_1");
    xmlWriter.writeAttribute(xuri,"version","1.00.a");

    xmlWriter.writeStartElement("spirit:component");
    xmlWriter.writeNamespace(spirituri,"spirit");

    xmlWriter.writeTextElement(spirituri,"vendor","xilinx.com");
    xmlWriter.writeTextElement(spirituri,"library","BlockDiagram");
    xmlWriter.writeTextElement(spirituri,"name","design_1");
    xmlWriter.writeTextElement(spirituri,"version","1.00.a");

    xmlWriter.writeStartElement(spirituri,"parameters");
    xmlWriter.writeStartElement(spirituri,"parameter");

    xmlWriter.writeTextElement(spirituri,"name","isTop");
    xmlWriter.writeStartElement(spirituri,"value");
    xmlWriter.writeAttribute(spirituri, "format","bool");
    xmlWriter.writeAttribute(spirituri,"resolve","immediate");
    xmlWriter.writeCharacters("true");

    xmlWriter.writeEndElement(); //value

    xmlWriter.writeEndElement(); //parameter
    xmlWriter.writeEndElement(); //parameters


    xmlWriter.writeStartElement(spirituri,"model");
    xmlWriter.writeStartElement(spirituri,"views");
    xmlWriter.writeStartElement(spirituri,"view");
    xmlWriter.writeTextElement(spirituri,"name","BlockDiagram");
    xmlWriter.writeTextElement(spirituri,"envIdentifier",":vivado.xilinx.com:");

    xmlWriter.writeStartElement(spirituri,"hierarchyRef");
    xmlWriter.writeAttribute(spirituri, "library","BlockDiagram");
    xmlWriter.writeAttribute(spirituri, "name","design_1_imp");
    xmlWriter.writeAttribute(spirituri, "vendor","xilinx.com");
    xmlWriter.writeAttribute(spirituri, "version","1.00.a");
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement(); //component


    xmlWriter.writeStartElement(spirituri,"design");
    xmlWriter.writeTextElement(spirituri,"vendor","xilinx.com");
    xmlWriter.writeTextElement(spirituri,"library","BlockDiagram");
    xmlWriter.writeTextElement(spirituri,"name","design_1_imp");
    xmlWriter.writeTextElement(spirituri,"version","1.00.a");

    xmlWriter.writeStartElement(spirituri,"componentInstances");

    for (auto const& element : _tiles)
    {
        QString name = QString("NocSwitch_%1_%2").arg(element->col()).arg(element->row());
        //<spirit:componentInstance>
        xmlWriter.writeStartElement(spirituri,"componentInstance");
        //<spirit:instanceName>NocSwitch_0</spirit:instanceName>
        xmlWriter.writeTextElement(spirituri,"InstanceName",name);

        //<spirit:componentRef spirit:library="user" spirit:name="NocSwitch" spirit:vendor="Fabmatics.com" spirit:version="1.0"/>
        xmlWriter.writeStartElement(spirituri,"componentRef");
        xmlWriter.writeAttribute(spirituri,"library","user");
        xmlWriter.writeAttribute(spirituri,"name","NocSwitch");
        xmlWriter.writeAttribute(spirituri,"vendor","Fabmatics.com");
        xmlWriter.writeAttribute(spirituri,"version","1.0");
        xmlWriter.writeEndElement(); //componentRef

        //<spirit:configurableElementValues>
        xmlWriter.writeStartElement(spirituri,"configurableElementValues");
            //<spirit:configurableElementValue spirit:referenceId="bd:xciName">design_1_NocSwitch_0_0</spirit:configurableElementValue>
            xmlWriter.writeStartElement(spirituri,"configurableElementValue");
            QString attr_value = QString("design_1_%1").arg(name);
            xmlWriter.writeAttribute(spirituri,"referenceId","bd:xciName");
            xmlWriter.writeCharacters(attr_value);
            xmlWriter.writeEndElement(); //configurableElementValue
        xmlWriter.writeEndElement(); //configurableElementValues
        xmlWriter.writeEndElement(); //componentInstance
    }


    /*




<spirit:componentInstance>
            <spirit:instanceName>noc_connector_dpr_0</spirit:instanceName>
            <spirit:componentRef spirit:library="user" spirit:name="noc_connector_dpr" spirit:vendor="Fabmatics.com" spirit:version="1.0"/>
            <spirit:configurableElementValues>
              <spirit:configurableElementValue spirit:referenceId="bd:xciName">design_1_noc_connector_dpr_0_0</spirit:configurableElementValue>
            </spirit:configurableElementValues>
          </spirit:componentInstance>
          <spirit:componentInstance>
            <spirit:instanceName>noc_connector_dpr_2</spirit:instanceName>
            <spirit:componentRef spirit:library="user" spirit:name="noc_connector_dpr" spirit:vendor="Fabmatics.com" spirit:version="1.0"/>
            <spirit:configurableElementValues>
              <spirit:configurableElementValue spirit:referenceId="bd:xciName">design_1_noc_connector_dpr_2_0</spirit:configurableElementValue>
            </spirit:configurableElementValues>
          </spirit:componentInstance>
        */
    xmlWriter.writeEndElement(); //componentInstances
    xmlWriter.writeStartElement(spirituri,"adHocConnections");


        /*
          <spirit:adHocConnection>
            <spirit:name>noc_connector_dpr_0_noc_in_ready</spirit:name>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_in_ready"/>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="out_center_ready"/>
          </spirit:adHocConnection>
          <spirit:adHocConnection>
            <spirit:name>noc_connector_dpr_0_noc_out_valid</spirit:name>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_out_valid"/>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="in_center_valid"/>
          </spirit:adHocConnection>
          <spirit:adHocConnection>
            <spirit:name>noc_connector_dpr_0_noc_out_vc</spirit:name>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_out_vc"/>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="in_center_vc"/>
          </spirit:adHocConnection>
          <spirit:adHocConnection>
            <spirit:name>noc_connector_dpr_0_noc_out_data</spirit:name>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_out_data"/>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="in_center_data"/>
          </spirit:adHocConnection>
          <spirit:adHocConnection>
            <spirit:name>NocSwitch_0_in_center_ready</spirit:name>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="in_center_ready"/>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_out_ready"/>
          </spirit:adHocConnection>
          <spirit:adHocConnection>
            <spirit:name>NocSwitch_0_out_center_valid</spirit:name>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="out_center_valid"/>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_in_valid"/>
          </spirit:adHocConnection>
          <spirit:adHocConnection>
            <spirit:name>NocSwitch_0_out_center_vc</spirit:name>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="out_center_vc"/>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_in_vc"/>
          </spirit:adHocConnection>
          <spirit:adHocConnection>
            <spirit:name>NocSwitch_0_out_center_data</spirit:name>
            <spirit:internalPortReference spirit:componentRef="NocSwitch_0" spirit:portRef="out_center_data"/>
            <spirit:internalPortReference spirit:componentRef="noc_connector_dpr_0" spirit:portRef="noc_in_data"/>
          </spirit:adHocConnection>
    */

    xmlWriter.writeEndElement(); //adHocConnections
    xmlWriter.writeEndElement(); //design
    xmlWriter.writeEndElement(); //repository
    xmlWriter.writeEndDocument();
   }

}
