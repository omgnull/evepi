#ifndef PRODUCT_H
#define PRODUCT_H

#include "component.h"

namespace Common {

class Product : public QObject
{
    Q_OBJECT

public:
    explicit Product(Component *, QObject *parent = 0);

    Component *getComponent();

    int getQuantity();

    void setQuantity(int);

    bool useCustomSellPrice();

    void useCustomSellPrice(bool);
    
signals:
    
public slots:


private:
    Component *component;

    double customSellPrice;

    bool useCstmSellPrice;

    int quantity;
};

}

#endif // PRODUCT_H
