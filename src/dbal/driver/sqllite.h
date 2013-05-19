#ifndef DBAL_DRIVER_SQLLITE_H
#define DBAL_DRIVER_SQLLITE_H

#include <QtSql>

namespace DBAL {

class SQLLite
{
public:
    void connect(QSqlDatabase *, QString);
};

}

#endif // DBAL_DRIVER_SQLLITE_H
