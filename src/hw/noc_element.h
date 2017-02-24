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

    static std::string typeToString(TileType type)
    {
        switch (type)
        {
            case Empty: return "Empty";
            case Process: return "Process";
            case IO: return "IO";
        }
        return "Error";
    }

    NocElement(unsigned col, unsigned row, TileType type);
    NocElement();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    std::string to_string();
private:
    unsigned _col;
    unsigned _row;
    TileType _type;
};

#endif // NOCELEMENT_H
