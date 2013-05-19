#ifndef SCHEMA_H
#define SCHEMA_H

#include "src/main.h"
#include "product.h"
#include "consumable.h"

#include <QObject>

namespace Common {

class Schematic : public QObject
{
    Q_OBJECT

public:
    explicit Schematic(QObject *parent = 0);

    ~Schematic();


    int getId();

    QString getName();

    int getCycleTime();

    bool isDisabled();

    Schematic* getParentSchematic();

    Product *getProduct();

    double getCost();

    double getProfitIsk();

    double getProfitPercentage();

    bool isMainSchematic();

    bool hasChildren();

    QMap<int, Consumable*> getConsumables();


    void setId(int);

    void setName(QString);

    void setCycleTime(int);

    void setProduct(Product *);

    bool disable(bool);

    void setParentSchematic(Schematic *);

    void addChildSchematic(Schematic *);

    void setSchematicAsMain(bool);

    void addConsumable(Consumable *);


    Schematic clone();
    
signals:
    
public slots:

private:
    int id;

    QString name;

    int cycleTime;

    bool disabled;

    Schematic *parentSchematic;

    QList<Schematic*> children;

    Product *product;

    QMap<int, Consumable*> consumables;
};

}

#endif // SCHEMA_H
