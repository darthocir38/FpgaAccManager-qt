#ifndef NOC_ACCELERATOR_H
#define NOC_ACCELERATOR_H

#include "noc_element.h"
#include <QJsonObject>
#include <QVector>

class NocAccelerator
{
public:
    NocAccelerator(unsigned row, unsigned col);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QVector<NocElement> tiles;
    unsigned row;
    unsigned col;
};

#endif // NOC_ACCELERATOR_H
