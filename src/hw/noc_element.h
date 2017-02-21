#ifndef NOCELEMENT_H
#define NOCELEMENT_H

#include <QJsonObject>

class NocElement
{
public:
    enum TileType
    {
        Empty, Process, IO
    };

    NocElement(unsigned col, unsigned row, TileType type);
    NocElement();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    unsigned col;
    unsigned row;
    TileType type;
};

#endif // NOCELEMENT_H
