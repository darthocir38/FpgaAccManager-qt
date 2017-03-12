#ifndef NOCELEMENT_H
#define NOCELEMENT_H

#include <QJsonObject>
#include <QXmlStreamWriter>

#include <memory>
#include <vector>

class NocElement
{
public:
    typedef std::shared_ptr<NocElement> ptr;

    enum class TileType
    {
        Empty, Process, IO
    };

    static std::string typeToString(TileType type)
    {
        switch (type)
        {
            case TileType::Empty: return "E";
            case TileType::Process: return "P";
            case TileType::IO: return "IO";
        }
        return "Error";
    }

    static TileType stringToType(std::string const& str)
    {
        if(str == "E") return TileType::Empty;
        else if (str == "P") return TileType::Process;
        else if (str == "IO") return TileType::IO;

        return TileType::Empty;
    }

    static std::string typeToLongString(TileType type)
    {
        switch (type)
        {
            case TileType::Empty: return "Empty";
            case TileType::Process: return "ProcessTile";
            case TileType::IO: return "IOTile";
        }
        return "Error";
    }

    static std::vector<std::string> getListOfTypes()
    {
        return {"E", "P", "IO"};
    }
    NocElement(unsigned col, unsigned row, TileType type);
    NocElement(NocElement::ptr oldElement);
    NocElement();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    virtual void exportIpxactComponents(QXmlStreamWriter &xmlWriter, const QString &uri);
    virtual void exportIpxactConnections(QXmlStreamWriter &xmlWriter, const QString &uri);



    std::string to_string();
    TileType type() const;
    void type(const TileType &type);

    unsigned col() const;
    unsigned row() const;

protected:
    unsigned _col;
    unsigned _row;
    TileType _type;

    /*
    out_north_ready
    out_north_data
    out_north_vc
    out_north_valid

    in_north_ready
    in_north_data
    in_north_vc
    in_north_valid
*/
};

#endif // NOCELEMENT_H
