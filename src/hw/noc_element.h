#ifndef NOCELEMENT_H
#define NOCELEMENT_H

#include <QJsonObject>
#include <memory>

class NocElement
{
public:
    typedef std::shared_ptr<NocElement> ptr;

    enum TileType
    {
        Empty, Process, IO
    };

    static std::string typeToString(TileType type)
    {
        switch (type)
        {
            case Empty: return "E";
            case Process: return "P";
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
