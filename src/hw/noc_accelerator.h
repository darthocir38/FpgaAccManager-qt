#ifndef NOC_ACCELERATOR_H
#define NOC_ACCELERATOR_H

#include "noc_element.h"
#include <QJsonObject>
#include <QVector>
#include <memory>

class NocAccelerator
{
public:
    typedef std::shared_ptr<NocAccelerator> ptr;
    NocAccelerator(unsigned _rc, unsigned _cc);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    unsigned rows() const;
    unsigned columns() const;

    NocElement::ptr get_element(unsigned row, unsigned column);
    void add_column();
    void remove_column();
    void add_row();
    void remove_row();

    void change_tile_type(unsigned row, unsigned column, NocElement::TileType type);

    void generate_hw_design(QString const& filename);

private:
    QVector<NocElement::ptr> _tiles;
    unsigned _rc;
    unsigned _cc;
};

#endif // NOC_ACCELERATOR_H
