#ifndef SCHEMAITROWCOMPONENT_H
#define SCHEMAITROWCOMPONENT_H

#include "src/main.h"
#include "ui_schematicrowcomponent.h"
#include "src/common/consumable.h"

#include <QWidget>

namespace Generic
{

class SchematicRowComponent : public QWidget
{
    Q_OBJECT
public:
    explicit SchematicRowComponent(QWidget *parent = 0);

    ~SchematicRowComponent();

    Ui::SchematicRowComponent *ui;

    Common::Consumable *consumable;

    int quantityPerHour;
    
signals:
    
public slots:
    
};

}

#endif // SCHEMAITROWCOMPONENT_H
