#include "datacontainer.h"

using namespace Model;

QMap<int, Common::Component*> DataContainer::components;

QMap<int, Common::Schematic*> DataContainer::schematics;

QMap<int, QString> DataContainer::groups;

QMap<QString, int> DataContainer::regions;

QMap<double, QString> DataContainer::taxes;

QMultiMap<int, Common::Schematic*> DataContainer::mapGroupsToSch;

QMap<int, double> DataContainer::basePrices;

QMap<int, QString> DataContainer::tradeHubs;

QProgressBar *DataContainer::pb = nullptr;


DataContainer::DataContainer(QObject *parent) :
    QObject(parent),
    apiQuery(nullptr),
    splashScreen(nullptr)
{

}

DataContainer::~DataContainer()
{

}

void DataContainer::autoload()
{
    static bool initialized = false;

    if (initialized) {
        return;
    }

    QDir dir;
    dir.mkpath(QCoreApplication::applicationDirPath()
                 .append(APPC::XML_CACHE_DIR));

    splashScreen->showMessage(tr("Loading base prices"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    loadBasePrices();

    splashScreen->showMessage(tr("Loading trade hubs"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    loadTradeHubs();

    splashScreen->showMessage(tr("Loading taxes"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    loadTaxes();

    splashScreen->showMessage(tr("Loading schematics groups"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    loadGroups();

    splashScreen->showMessage(tr("Loading schematics"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    loadSchematics();

    splashScreen->showMessage(tr("Loading components"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    loadComponents();

    splashScreen->showMessage(tr("Loading regions"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    loadRegions();

    initialized = true;

    #ifdef APP_DEBUG
    qDebug("[EMIT] Data loaded.");
    #endif

    splashScreen->showMessage(tr("Data loaded"),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);

    emit dataLoaded(true);
}

void DataContainer::unload()
{
    Model::XmlCache cache;
    cache.clear();

    delete splashScreen;
    delete apiQuery;

    qDeleteAll(DataContainer::schematics.values());
    qDeleteAll(DataContainer::components.values());
}

QString DataContainer::getGroup(int id)
{
    if (!DataContainer::groups.contains(id)) {
        return nullptr;
    }

    return DataContainer::groups.find(id).value();
}

const QMap<QString, int> & DataContainer::getRegions() const
{
    return DataContainer::regions;
}

const QMap<int, QString> & DataContainer::getGroups() const
{
    return DataContainer::groups;
}

const QMap<double, QString> & DataContainer::getTaxes() const
{
    return DataContainer::taxes;
}

double DataContainer::getGlobalTax()
{
    return Common::Component::tax;
}

void DataContainer::setGlobalTax(double n)
{
    Common::Component::tax = n;
}

QList<Common::Schematic *> DataContainer::getSchematicsByGroup(int id) const
{
    QList<Common::Schematic*> list;
    auto it = DataContainer::mapGroupsToSch.begin(),
         end = DataContainer::mapGroupsToSch.end();

    while (it != end) {
        if (it.key() == id) {
            list.append(it.value());
        }
        ++it;
    }

    return list;
}

const QMap<int, QString> & DataContainer::getTradeHubs() const
{
    return DataContainer::tradeHubs;
}

void DataContainer::loadGroups()
{
    #ifdef APP_DEBUG
    qDebug("========== Start loading groups ... ==========");
    #endif

    QString sql = "SELECT marketGroupID, marketGroupName "
            "FROM invMarketGroups "
            "WHERE parentGroupID = 1332 "
            "ORDER BY marketGroupID ASC";

    QSqlQuery query;

    if (!query.exec(sql)) {
        qFatal(qPrintable(tr("SQL error: %s").arg(query.lastError().text())));
    }

    while (query.next()) {
        addSchematicsGroup(
            query.record().value(0).toInt(),
            query.record().value(1).toString());
    }

    #ifdef APP_DEBUG
    qDebug("========== End loading groups ==========");
    #endif
}

void DataContainer::loadBasePrices()
{
    #ifdef APP_DEBUG
    qDebug("========== Start loading base prices ... ==========");
    #endif

    XmlLoader xmlLoader;
    QDomDocument *doc = xmlLoader.load(APPC::XML_BASE_PRICES);

    if (!doc) {
        qFatal("Could not load base prices.");
    }

    QDomNodeList groups = doc->elementsByTagName("group");
    for (int i =0; i < groups.size(); i++) {
        QDomElement group = groups.at(i).toElement();

        int id = group.elementsByTagName("id").at(0).firstChild().nodeValue().toInt();
        double basePrice = group.elementsByTagName("basePrice").at(0).firstChild().nodeValue().toDouble();

        DataContainer::basePrices.insert(id, basePrice);

        #ifdef APP_DEBUG
        qDebug() << "Loading group " << id << " base price: " << QLocale().toString(basePrice, 'f', 2);
        #endif
    }

    #ifdef APP_DEBUG
    qDebug() << "========== End loading base prices ==========";
    #endif
}

void DataContainer::loadTradeHubs()
{
    #ifdef APP_DEBUG
    qDebug("========== Start loading trade hubs ... ==========");
    #endif

    XmlLoader xmlLoader;
    QDomDocument *doc = xmlLoader.load(APPC::XML_TRADE_HUBS);

    if (!doc) {
        qFatal("Could not load trade hubs.");
    }

    QDomNodeList groups = doc->elementsByTagName("hub");
    for (int i =0; i < groups.size(); i++) {
        QDomElement group = groups.at(i).toElement();

        int id = group.elementsByTagName("solarSystemId").at(0).firstChild().nodeValue().toInt();
        QString name = group.elementsByTagName("name").at(0).firstChild().nodeValue();

        DataContainer::tradeHubs.insert(id, name);

        #ifdef APP_DEBUG
        qDebug() << "Loading trade huub " << id << " with name: " << name;
        #endif
    }

    #ifdef APP_DEBUG
    qDebug() << "========== End loading trade hubs ==========";
    #endif
}

void DataContainer::loadTaxes()
{
    #ifdef APP_DEBUG
    qDebug("========== Start loading taxes ... ==========");
    #endif

    XmlLoader xmlLoader;
    QDomDocument *doc = xmlLoader.load(APPC::XML_TAXES);

    if (!doc) {
        qFatal("Could not load taxes.");
    }

    QDomNodeList tx = doc->elementsByTagName("tax");
    for (int i =0; i < tx.size(); i++) {
        QString tax = tx.at(i).firstChild().nodeValue();
        QString strTax(tax);
        DataContainer::taxes.insert(tax.toDouble(), strTax.append("%"));

        #ifdef APP_DEBUG
        qDebug() << "Loading tax " << tax;
        #endif
    }

    #ifdef APP_DEBUG
    qDebug() << "========== End loading taxes ==========";
    #endif
}

void DataContainer::loadSchematics()
{
    #ifdef APP_DEBUG
    qDebug("========== Start loading schematics ... ==========");
    #endif

    QString sql = "SELECT "
            "ps.schematicID , ps.schematicName, "
            "ps.cycleTime, it.marketGroupID "
            "FROM planetSchematics ps "
            "INNER JOIN planetSchematicsTypeMap pstm "
            "ON (ps.schematicID = pstm.schematicID) "
            "INNER JOIN invTypes it "
            "ON (pstm.typeID = it.typeID) "
            "WHERE pstm.isInput = 0 "
            "ORDER BY it.marketGroupID ASC";

    QSqlQuery query;

    if (!query.exec(sql)) {
        qFatal(qPrintable(tr("SQL error: %s").arg(query.lastError().text())));
    }

    while (query.next()) {
        QSqlRecord rec = query.record();
        Common::Schematic *schematic = new Common::Schematic();

        schematic->setId(query.value(rec.indexOf("schematicID")).toInt());
        schematic->setName(query.value(rec.indexOf("schematicName")).toString());
        schematic->setCycleTime(query.value(rec.indexOf("cycleTime")).toInt());

        DataContainer::schematics.insert(schematic->getId(), schematic);
        DataContainer::mapGroupsToSch.insert(
            query.value(rec.indexOf("marketGroupID")).toInt(), schematic);

        #ifdef APP_DEBUG
        qDebug() << "Loaded schematic " << schematic->getName()
                 << " with group " << query.value(rec.indexOf("marketGroupID")).toInt();
        #endif
    }

    #ifdef APP_DEBUG
    qDebug() << "========== End loading schematics ==========";
    #endif
}

void DataContainer::loadComponents()
{
    #ifdef APP_DEBUG
    qDebug("========== Start loading components ... ==========");
    #endif

    QString sql = "SELECT "
            "pstm.typeId, pstm.schematicID, pstm.quantity, "
            "pstm.isInput, it.typeName, it.volume, "
            "it.marketGroupID "
            "FROM planetSchematicsTypeMap pstm "
            "INNER JOIN invTypes it "
            "ON (pstm.typeID = it.typeID) "
            "ORDER BY pstm.schematicID  ASC";

    QSqlQuery query;

    if (!query.exec(sql)) {
        qFatal(qPrintable(tr("SQL error: %s").arg(query.lastError().text())));
    }

    while (query.next()) {
        QSqlRecord rec = query.record();

        int id = query.value(rec.indexOf("typeId")).toInt();
        int groupId = query.value(rec.indexOf("marketGroupID")).toInt();
        int schematicId = query.value(rec.indexOf("schematicID")).toInt();
        int isInput = query.value(rec.indexOf("isInput")).toInt();
        int quantity = query.value(rec.indexOf("quantity")).toInt();

        Common::Component *component;

        if (!DataContainer::components.contains(id)) {
            component = new Common::Component();

            component->setId(id);
            component->setName(query.value(rec.indexOf("typeName")).toString());
            component->setBasePrice(determineComponentBasePrice(groupId));
            component->setVolume(query.value(rec.indexOf("volume")).toInt());

            DataContainer::components.insert(id, component);

            #ifdef APP_DEBUG
            qDebug() << "Loading new component: "
                     << query.value(rec.indexOf("typeName")).toString();
            #endif
        } else {
            component = DataContainer::components.find(id).value();

            #ifdef APP_DEBUG
            qDebug() << "Component exists: " << component->getName();
            #endif
        }

        if (!DataContainer::schematics.contains(schematicId)) {
            continue;
        }

        Common::Product *product;
        Common::Consumable *consumable;
        Common::Schematic *schematic = DataContainer::schematics.find(schematicId).value();

        if (0 == isInput) {
            product = new Common::Product(component);
            product->setQuantity(quantity);
            schematic->setProduct(product);

            #ifdef APP_DEBUG
            qDebug() << "Create product " << product->getComponent()->getName()
                     << " for schemaic " << schematic->getName();
            #endif
        } else {
            consumable = new Common::Consumable(component);
            consumable->setQuantity(quantity);
            schematic->addConsumable(consumable);

            #ifdef APP_DEBUG
            qDebug() << "Create consumable " << consumable->getComponent()->getName()
                     << " for schemaic " << schematic->getName();
            #endif
        }
    }

    #ifdef APP_DEBUG
    qDebug() << "========== End loading components ==========";
    #endif
}

void Model::DataContainer::loadRegions()
{
    #ifdef APP_DEBUG
    qDebug() << "========== Start loading regions ... ==========";
    #endif

    QString sql = "SELECT "
            "regionID, regionName "
            "FROM mapRegions "
            "ORDER BY regionName ASC";

    QSqlQuery query;

    if (!query.exec(sql)) {
        qFatal(qPrintable(tr("SQL error: %s").arg(query.lastError().text())));
    }

    while (query.next()) {
        QSqlRecord rec = query.record();

        DataContainer::regions.insert(
            query.value(rec.indexOf("regionName")).toString(),
            query.value(rec.indexOf("regionID")).toInt());

        #ifdef APP_DEBUG
        qDebug() << "Loaded region: " << query.value(rec.indexOf("regionName")).toString();
        #endif
    }

    #ifdef APP_DEBUG
    qDebug() << "========== End loading regions ==========";
    #endif
}

void Model::DataContainer::addSchematicsGroup(int id, QString name)
{
    if (!DataContainer::groups.contains(id)) {
        DataContainer::groups.insert(id, name);

        #ifdef APP_DEBUG
        qDebug() << "Add scematics group " << id << ":" << name;
        #endif
    }
}

double Model::DataContainer::determineComponentBasePrice(int groupId)
{
    if (!DataContainer::basePrices.contains(groupId)) {
        return 0.00;
    }

    return DataContainer::basePrices.find(groupId).value();
}

void Model::DataContainer::setSplashScreen(Generic::SplashScreen *splash)
{
    splashScreen = splash;
}

void Model::DataContainer::loadPrices(int id, int type)
{
    priceType = type;
    apiQuery = new EVECentralAPI::MarketStat;
    QString query;

    switch (priceType) {
        case 0:
            apiQuery->setRegoin(id);
            query.append("r");
            break;
        case 1:
            apiQuery->setSolarSysetm(id);
            query.append("s");
            break;
    }

    loadPrices(apiQuery, query.append("_%1.xml").arg(id));
}

void Model::DataContainer::loadPrices(EVECentralAPI::MarketStat *query, QString filename)
{
    setProgressBarValue(10);

    for (auto it = DataContainer::components.begin(),
         end = DataContainer::components.end(); it != end; it++)
    {
        query->addComponent(it.value());
    }

    connect(query, SIGNAL(dataLoaded(QDomDocument *)),
            this, SLOT(loadPricesResponse(QDomDocument *)));

    setProgressBarValue(20);
    query->exec(filename);
}

void Model::DataContainer::loadPricesResponse(QDomDocument *doc)
{
    if (apiQuery) {
        //delete apiQuery;
        //apiQuery = nullptr;
    }

    setProgressBarValue(40);
    QDomNodeList list = doc->elementsByTagName("type");

    for (int i = 0, size = list.size(); i < size; i++) {
        QDomElement cmp = list.at(i).toElement();
        int id = cmp.attribute("id").toInt();

        #ifdef APP_DEBUG
        qDebug() << "Parse component prices: " << id;
        #endif

        // Not queried element?
        if (!DataContainer::components.contains(id)) {
            #ifdef APP_DEBUG
            qDebug() << "Component not exeists: " << id;
            #endif

            continue;
        }

        Common::Component *component = DataContainer::components.find(id).value();
        QDomNodeList types = cmp.childNodes();

        for (int it = 0, typesSize = types.size(); it < typesSize; it++) {
            QDomElement el = types.at(it).toElement();

            /*
             * For buy price set min sell price,
             * for sell price set max buy price
             */
            if ("buy" == el.tagName()) {
                double sellPrice = el.childNodes().at(2).firstChild().nodeValue().toDouble();
                component->setSellPrice(sellPrice);
            } else if ("sell" == el.tagName()) {
                double buyPrice = el.childNodes().at(3).firstChild().nodeValue().toDouble();
                component->setBuyPrice(buyPrice);
            }
        }
    }

    setProgressBarValue(20);
    delete doc;

    #ifdef APP_DEBUG
    qDebug() << "[EMIT] Prices loaded.";
    #endif

    emit pricesLoaded(priceType);
}

void Model::DataContainer::setProgressBar(QProgressBar *bar)
{
    DataContainer::pb = bar;
    DataContainer::pb->setValue(0);
    DataContainer::pb->hide();
}

void Model::DataContainer::setProgressBarValue(int val)
{
    int newVal = DataContainer::pb->value() + val;

    if (100 <= newVal) {
        DataContainer::pb->setValue(0);
        DataContainer::pb->hide();
    } else if (0 == DataContainer::pb->value()) {
        DataContainer::pb->show();
        DataContainer::pb->setValue(newVal);
    } else {
        DataContainer::pb->setValue(newVal);
    }
}
