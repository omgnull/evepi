#ifndef XMLCACHE_H
#define XMLCACHE_H

#include "src/main.h"
#include "src/model/xmlloader.h"

#include <QObject>
#include <QFile>

namespace Model {

class XmlCache : public XmlLoader
{
public:
    XmlCache();

    ~XmlCache();

    QDomDocument* load(QString);

    bool save(QString, QByteArray &);

    bool clear();

private:
    QString prepareFilename(QString);
};

}

#endif // XMLCACHE_H
