#include "schematic.h"

using namespace Common;

Schematic::Schematic(QObject *parent) :
    QObject(parent),
    parentSchematic(nullptr),
    product(nullptr)
{
    QList<Schematic*> list;
    children = list;

    QMap<int, Consumable*> map;
    consumables = map;
}

Schematic::~Schematic()
{
    delete product;
    qDeleteAll(children);
    qDeleteAll(consumables.values());

    children.clear();
    consumables.clear();
}

int Schematic::getId()
{
    return id;
}

QString Schematic::getName()
{
    return name;
}

int Schematic::getCycleTime()
{
    return cycleTime;
}

bool Schematic::isDisabled()
{
    return disabled;
}

Product* Schematic::getProduct()
{
    return product;
}

double Schematic::getProfitIsk()
{
    double profit;
    int consumableQuatity;
    double buyPrice;
    double importCost;
    int productQuatity = product->getQuantity();
    double sellPrice = product->getComponent()->getSellPrice();
    double exportCost = product->getComponent()->getExportCost();

    if (0 == sellPrice) {
        return 0;
    }

    profit = (productQuatity * sellPrice) - (productQuatity * exportCost);

    Consumable *consumable;

    for (auto it = consumables.begin(),
         end = consumables.end(); it != end; ++it)
    {
        consumable = it.value();
        consumableQuatity = consumable->getQuantity();
        buyPrice = consumable->getComponent()->getBuyPrice();
        importCost = consumable->getComponent()->getImportCost();

        profit -= (consumableQuatity * buyPrice) + (consumableQuatity * importCost);
    }

    if (cycleTime == 1800) {
        profit *= 2;
    }

    return profit;
}

double Schematic::getProfitPercentage()
{
    double negative = 0;
    double positive= 0;

    int consumableQuatity;
    double buyPrice;
    double importCost;
    int productQuatity = product->getQuantity();
    double sellPrice = product->getComponent()->getSellPrice();
    double exportCost = product->getComponent()->getExportCost();

    if (0 == sellPrice) {
        return 0;
    }

    positive = (productQuatity * sellPrice) - (productQuatity * exportCost);

    Consumable *consumable;

    for (auto it = consumables.begin(),
         end = consumables.end(); it != end; ++it)
    {
        consumable = it.value();
        consumableQuatity = consumable->getQuantity();
        buyPrice = consumable->getComponent()->getBuyPrice();
        importCost = consumable->getComponent()->getImportCost();

        consumable = it.value();
        negative += (consumableQuatity * buyPrice) + (consumableQuatity * importCost);
    }

    if (0 == positive || 0 == negative) {
        return 0;
    }

    double profit = (positive - negative) * 100 / positive;

    if (cycleTime == 1800) {
        profit *= 2;
    }

    return profit;
}

void Schematic::setId(int n)
{
    id = n;
}

void Schematic::setName(QString str)
{
    name = str;
}

void Schematic::setCycleTime(int n)
{
    cycleTime = n;
}

void Schematic::setProduct(Product *p)
{
    if (product) {
        delete product;
    }

    product = p;
}

void Schematic::addConsumable(Consumable *consumable)
{
    consumables.insert(consumable->getComponent()->getId(), consumable);
}
