#ifndef COMPONENT_H
#define COMPONENT_H

#include "src/main.h"

#include <QObject>
#include <QPixmap>

namespace Common {

class Component : public QObject
{
    Q_OBJECT

public:
    explicit Component(QObject *parent = nullptr);
    ~Component();

    int getId();

    QString getName();

    QPixmap & getIcon();

    double getVolume();

    double getBasePrice();

    double getBuyPrice();

    double getSellPrice();

    double getExportCost();

    double getImportCost();


    void setId(int);

    void setName(QString);

    void setVolume(double);

    void setBasePrice(double);

    void setBuyPrice(double);

    void setSellPrice(double);

    static double tax;
    
signals:
    
public slots:

private:
    void setIcon();

    int id;

    QString name;

    QPixmap icon;

    double volume;

    double basePrice;

    double buyPrice;

    double sellPrice;
};

}

#endif // COMPONENT_H
