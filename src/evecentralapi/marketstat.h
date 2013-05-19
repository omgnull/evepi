#ifndef EVECENTRALAPI_MARKETSTAT_H
#define EVECENTRALAPI_MARKETSTAT_H

#include "query.h"
#include "src/common/component.h"

namespace EVECentralAPI {

class MarketStat : public Query
{
    Q_OBJECT

public:
    MarketStat(QObject *parent = 0);
    MarketStat(QString, QObject *parent = 0);

    ~MarketStat();

    void addComponent(Common::Component *);

    void setRegoin(int);

    void setSolarSysetm(int);

    void setQuantityLimit(int);

    void setHours(int);

    void clear();


protected:
    QString buildQuery(QString);

private:
    QString *hours;

    QString *region;

    QString *solarSystem;

    QString *quantityLimit;
};

}

#endif // EVECENTRALAPI_MARKETSTAT_H
