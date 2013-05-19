#include "product.h"

using namespace Common;

Product::Product(Component *cmp, QObject *parent) :
    QObject(parent),
    component(cmp)
{

}

Component * Product::getComponent()
{
    return component;
}

int Product::getQuantity()
{
    return quantity;
}

void Product::setQuantity(int n)
{
    quantity = n;
}
