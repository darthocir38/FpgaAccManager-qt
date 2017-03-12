#ifndef NOCTILE_H
#define NOCTILE_H

#include "noc_element.h"

#include <map>
class NocTile : public NocElement
{
public:
    NocTile();
    NocTile(NocElement::ptr oldElement);
    void exportIpxactComponents(QXmlStreamWriter &xmlWriter, const QString &uri) override;
    void exportIpxactConnections(QXmlStreamWriter &xmlWriter, const QString &uri) override;

    static std::map<QString, QString> connections;
};
#endif // NOCTILE_H
