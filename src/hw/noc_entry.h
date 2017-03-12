#ifndef NOCENTRY_H
#define NOCENTRY_H

#include "noc_element.h"

class NocEntry : public NocElement
{
public:
    NocEntry();
    NocEntry(NocElement::ptr oldElement);
    void exportIpxactComponents(QXmlStreamWriter &xmlWriter, const QString &uri) override;
    void exportIpxactConnections(QXmlStreamWriter &xmlWriter, const QString &uri) override;
    static std::map<QString, QString> connections;
};




#endif // NOCENTRY_H
