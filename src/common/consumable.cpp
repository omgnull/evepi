#include "consumable.h"

using namespace Common;

Consumable::Consumable(Component *cmp, QObject *parent) :
    QObject(parent),
    component(cmp)
{

}

Component * Consumable::getComponent()
{
    return component;
}

int Consumable::getQuantity()
{
    return quantity;
}

void Consumable::setQuantity(int n)
{
    quantity = n;
}
