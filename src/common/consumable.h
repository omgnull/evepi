#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "component.h"

namespace Common {

class Consumable : public QObject
{
    Q_OBJECT

public:
    explicit Consumable(Component *, QObject *parent = 0);

    Component * getComponent();

    int getQuantity();

    bool isBuy() const;

    void setCustomBuyPrice(double);

    void setQuantity(int);

    void isBuy(bool);
    
signals:
    
public slots:

private:
    Component *component;

    int quantity;

    bool buy;

    double customBuyPrice;
};

}

#endif // CONSUMABLE_H
