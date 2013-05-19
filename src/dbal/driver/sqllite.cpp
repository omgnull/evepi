#include "src/dbal/driver/sqllite.h"
#include <QSqlDatabase>

using namespace DBAL;

void SQLLite::connect(QSqlDatabase *sdb, QString dbname)
{
    QString path(QCoreApplication::applicationDirPath());
    path.append(QDir::separator())
            .append("data")
            .append(QDir::separator())
            .append(dbname);
    path = QDir::toNativeSeparators(path);

    sdb->setHostName("localhost");
    sdb->setDatabaseName(path);

    if (!sdb->open()) {
        qDebug() << sdb->lastError();
        qFatal("Could not open %s database.", qPrintable(path));
    }

    qDebug("Connected to %s.", qPrintable(path));
}
