#ifndef DBAL_CONNECTION_H
#define DBAL_CONNECTION_H

#include "src/main.h"

#include <QtSql>
#include <QSqlDatabase>

namespace DBAL {

class Connection
{
public:
    Connection();

    ~Connection();

    void connect(QString, QString);
};

}

#endif // DBAL_CONNECTION_H
