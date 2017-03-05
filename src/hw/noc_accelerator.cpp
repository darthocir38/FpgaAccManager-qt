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


    xmlWriter.writeStartDocument();

    xmlWriter.writeNamespace("test1","test2");
    xmlWriter.writeStartElement("t1"",test3");

    xmlWriter.writeAttribute("test4", "test5", "test6");


    //<bd:repository xmlns:bd="http://www.xilinx.com/bd" bd:BoundaryCRC="0x0" bd:device="xc7vx690tffg1761-2" bd:synthFlowMode="Hierarchical" bd:tool_version="2016.4" bd:top="design_1" bd:version="1.00.a">


    xmlWriter.writeEndElement();

    /*
    <spirit:component xmlns:spirit="http://www.spiritconsortium.org/XMLSchema/SPIRIT/1685-2009">
      <spirit:vendor>xilinx.com</spirit:vendor>
      <spirit:library>BlockDiagram</spirit:library>
      <spirit:name>design_1</spirit:name>
      <spirit:version>1.00.a</spirit:version>
      <spirit:parameters>
        <spirit:parameter>
          <spirit:name>isTop</spirit:name>
          <spirit:value spirit:format="bool" spirit:resolve="immediate">true</spirit:value>
        </spirit:parameter>
      </spirit:parameters>
      <spirit:model>
        <spirit:views>
          <spirit:view>
            <spirit:name>BlockDiagram</spirit:name>
            <spirit:envIdentifier>:vivado.xilinx.com:</spirit:envIdentifier>
            <spirit:hierarchyRef spirit:library="BlockDiagram" spirit:name="design_1_imp" spirit:vendor="xilinx.com" spirit:version="1.00.a"/>
          </spirit:view>
        </spirit:views>
      </spirit:model>
    </spirit:component>

*/

    xmlWriter.writeEndDocument();
   }

}
