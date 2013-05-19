#include "xmlloader.h"

using namespace Model;

XmlLoader::XmlLoader()
{

}

XmlLoader::~XmlLoader()
{

}

QDomDocument * XmlLoader::load(QString filename)
{
    QFile file(QDir::toNativeSeparators(QCoreApplication::applicationDirPath().append(filename)));
    if (!file.open(QIODevice::ReadOnly)) {
        #ifdef APP_DEBUG
        qDebug() << "Could not open file: "
                 << fName;
        #endif

        return nullptr;
    }

    QDomDocument *doc = new QDomDocument();
    if (!doc->setContent(&file)) {
        #ifdef QT_DEBUG
        qDebug() << "Load cache error. Wrong xml data.";
        #endif

        file.close();
        delete doc;

        return nullptr;
    }

    file.close();

    return doc;
}
