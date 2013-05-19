#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include "src/main.h"
#include "src/common/component.h"
#include "src/common/schematic.h"
#include "src/common/product.h"
#include "src/common/consumable.h"
#include "src/model/xmlloader.h"
#include "src/generic/splashscreen.h"
#include "src/evecentralapi/marketstat.h"

#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QProgressBar>

namespace Model {

class DataContainer : public QObject
{
    Q_OBJECT

public:
    explicit DataContainer(QObject *parent = 0);

    ~DataContainer();

    QString getGroup(int);

    const Common::Component & getComponent(int);

    const QMap<int, Common::Component*> & getComponents();

    const Common::Schematic & getSchematic(int);

    const QMap<int, Common::Schematic*> & getSchematics();

    const QMap<int, Common::Schematic*> & getRequiredSchematics(Common::Schematic *);

    const QMap<QString, int> & getRegions() const;

    const QMap<int, QString> & getGroups() const;

    const QMap<double, QString> & getTaxes() const;

    QList<Common::Schematic *> getSchematicsByGroup(int) const;

    const QMap<int, QString> &getTradeHubs() const;

    void loadPrices(int, int);

    void setSplashScreen(Generic::SplashScreen *);

    static double getGlobalTax();

    static void setGlobalTax(double);

    static void setProgressBar(QProgressBar *);

    void setProgressBarValue(int);

public slots:


signals:
    void dataLoaded(bool);

    void pricesLoaded(int);

private:
    double determineComponentBasePrice(int);

    void loadGroups();

    void loadBasePrices();

    void loadTradeHubs();

    void loadSchematics();

    void loadComponents();

    void loadRegions();

    void loadTaxes();

    void addSchematicsGroup(int, QString);

    void loadPrices(EVECentralAPI::MarketStat *, QString);

    int priceType;

    static double tax;

    EVECentralAPI::MarketStat *apiQuery;

    Generic::SplashScreen *splashScreen;

    static QProgressBar *pb;

    // Components ( id : Component )
    static QMap<int, Common::Component*> components;

    // Schematics ( id : Schematic )
    static QMap<int, Common::Schematic*> schematics;

    // Groups ( group id : group name )
    static QMap<int, QString> groups;

    // Groups ( group id : group name )
    static QMap<double, QString> taxes;

    // Regions ( region name : region id )
    static QMap<QString, int> regions;

    // Map groups to schematics ( group id : Schematic id )
    static QMultiMap<int, Common::Schematic*> mapGroupsToSch;

    // Map components base prices to group ( group id : price )
    static QMap<int, double> basePrices;

    // Map trade hubs ( solar system id : solar system/hub name )
    static QMap<int, QString> tradeHubs;


private slots:
    void autoload();

    void unload();

    void loadPricesResponse(QDomDocument *);
};

}

#endif // DATACONTAINER_H
