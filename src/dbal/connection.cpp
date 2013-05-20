#include "src/dbal/connection.h"
#include "src/dbal/driver/sqllite.h"

using namespace DBAL;

Connection::Connection()
{

}

Connection::~Connection()
{
    QSqlDatabase sdb;
    sdb.close();
}

void Connection::connect(QString dbtype, QString dbname)
{
    QSqlDatabase sdb;

    if ("QSQLITE" == dbtype) {
        #ifdef APP_DEBUG
        qDebug("Trying to connect to %s using driver %s.", qPrintable(dbname), qPrintable(dbtype));
        #endif

        sdb = QSqlDatabase::addDatabase(dbtype);
        SQLLite driver;
        driver.connect(&sdb, dbname);

        return;
    }

    qFatal("Database driver type %s not defined.", qPrintable(dbtype));
}
