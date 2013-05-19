#include "xmlcache.h"

using namespace Model;

XmlCache::XmlCache()
{

}

XmlCache::~XmlCache()
{

}

QDomDocument* XmlCache::load(QString filename)
{
    QString path = QCoreApplication::applicationDirPath()
            .append(APPC::XML_CACHE_DIR).append("/");

    QFile file(QDir::toNativeSeparators(path.append(prepareFilename(filename))));

    if (!file.exists()) {
        #ifdef APP_DEBUG
        qDebug() << "Cache file not exists or cache has expired. "
                 << fName;
        #endif

        return nullptr;
    }


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

bool XmlCache::save(QString filename, QByteArray &data)
{
    QString path = QCoreApplication::applicationDirPath()
            .append(APPC::XML_CACHE_DIR).append("/");
    QFile file(QDir::toNativeSeparators(path.append(prepareFilename(filename))));

    if (!file.open(QIODevice::WriteOnly)) {
        #ifdef QT_DEBUG
        qDebug() << "Cannot write cache file.";
        #endif

        return false;
    }

    int result = file.write(data);
    file.close();

    if (-1 == result) {
        #ifdef QT_DEBUG
        qDebug() << "Error while writing cache data.";
        #endif

        return false;
    }

    return true;
}

bool XmlCache::clear()
{
    QDir cacheDir(QCoreApplication::applicationDirPath()
                  .append(APPC::XML_CACHE_DIR));

    if(cacheDir.exists()){
        QFileInfoList list = cacheDir.entryInfoList(QDir::Hidden | QDir::Files);
        Q_FOREACH(QFileInfo info, list){
            if(info.isFile()){
                QFile::remove(info.absoluteFilePath());
            }
        }
    }

    return false;
}

QString XmlCache::prepareFilename(QString filename)
{
    QDateTime now(QDateTime::currentDateTime());
    filename.prepend(now.toString("ddMMyyyyhh").append("-"));

    return filename;
}
