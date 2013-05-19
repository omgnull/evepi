#ifndef FORM_H
#define FORM_H

#include "src/main.h"
#include "ui_schematicrow.h"
#include "src/model/datacontainer.h"
#include "src/common/component.h"
#include "src/common/schematic.h"
#include "src/common/product.h"
#include "src/common/consumable.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

namespace Ui {
    class SchemaitRow;
}

namespace Generic {

class SchemaitRow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SchemaitRow(QWidget *parent = 0);

    ~SchemaitRow();

    void setSchematic(Common::Schematic *);

    void updateView();
    
protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::SchemaitRow *ui;

    Common::Schematic *schematic;

    QGraphicsPixmapItem *imageItem;

    QGraphicsScene *imageScene;
};

}

#endif // FORM_H
