#ifndef NOCENTRY_H
#define NOCENTRY_H

#include "noc_element.h"

class NocEntry : public NocElement
{
public:
    NocEntry();
    NocEntry(NocElement::ptr oldElement);
    void exportIpxactComponents(QXmlStreamWriter &xmlWriter, const QString &uri) override;
};

#endif // NOCENTRY_H
