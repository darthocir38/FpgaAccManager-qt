#ifndef NOCTILE_H
#define NOCTILE_H

#include "noc_element.h"

class NocTile : public NocElement
{
public:
    NocTile();
    NocTile(NocElement::ptr oldElement);
    void exportIpxactComponents(QXmlStreamWriter &xmlWriter, const QString &uri) override;
};

#endif // NOCTILE_H
