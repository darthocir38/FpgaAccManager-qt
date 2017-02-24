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
    NocAccelerator(unsigned _rows, unsigned _cols);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    unsigned rows() const;
    void rows(const unsigned &rows);

    unsigned cols() const;
    void cols(const unsigned &cols);

private:
    QVector<NocElement> _tiles;
    unsigned _rows;
    unsigned _cols;
};

#endif // NOC_ACCELERATOR_H
