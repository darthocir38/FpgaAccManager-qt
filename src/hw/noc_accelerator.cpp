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
