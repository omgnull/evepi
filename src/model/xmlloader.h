#ifndef XMLLOADER_H
#define XMLLOADER_H

#include "src/main.h"
#include <QtXml>

namespace Model {

class XmlLoader
{
public:
    XmlLoader();

    ~XmlLoader();

    QDomDocument* load(QString);
};

}

#endif // XMLLOADER_H
