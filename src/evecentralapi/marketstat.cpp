#include "marketstat.h"

using namespace EVECentralAPI;

MarketStat::MarketStat(QObject *parent) :
    Query(QString(APPC::EVECENTRAL_API_MARKETSTAT_URL), parent),
    hours(new QString),
    region(new QString),
    solarSystem(new QString),
    quantityLimit(new QString)
{

}

MarketStat::MarketStat(QString url, QObject *parent) :
    Query(url, parent),
    hours(new QString),
    region(new QString),
    solarSystem(new QString),
    quantityLimit(new QString)
{

}

MarketStat::~MarketStat()
{
    delete region;
    delete solarSystem;
    delete quantityLimit;
    delete hours;
}

void MarketStat::addComponent(Common::Component *component)
{
    addParameter("typeid", QString::number(component->getId()));
}

QString MarketStat::buildQuery(QString url)
{
    if (region->isEmpty() && solarSystem->isEmpty()) {
        qFatal("dasdas asdas");
    }

    if (!region->isEmpty() && solarSystem->isEmpty()) {
        addParameter("regionlimit", *region);
    }

    if (!solarSystem->isEmpty()) {
        addParameter("usesystem", *solarSystem);
    }

    if (!hours->isEmpty()) {
        addParameter("hours", *hours);
    }

    if (!quantityLimit->isEmpty()) {
        addParameter("minQ", *quantityLimit);
    }

    return Query::buildQuery(url);
}

void MarketStat::setHours(int n)
{
    updateParameter(hours, n);
}

void MarketStat::setQuantityLimit(int n)
{
    updateParameter(quantityLimit, n);
}

void MarketStat::setRegoin(int n)
{
    updateParameter(region, n);
}

void MarketStat::setSolarSysetm(int n)
{
    updateParameter(solarSystem, n);
}

void MarketStat::clear()
{
    region->clear();
    solarSystem->clear();
    quantityLimit->clear();
    hours->clear();

    Query::clear();
}

