#include "schematicrow.h"

using namespace Generic;

QPalette SchemaitRow::pal;

SchemaitRow::SchemaitRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchemaitRow),
    components(new QList<SchematicRowComponent*>),
    schematic(nullptr),
    imageItem(new QGraphicsPixmapItem),
    imageScene(new QGraphicsScene)
{
    ui->setupUi(this);

    ui->iconSchematic->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->iconSchematic->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

SchemaitRow::~SchemaitRow()
{
    qDeleteAll(*components);

    delete ui;
    delete imageItem;
    delete imageScene;
    delete components;
}

void SchemaitRow::setSchematic(Common::Schematic *sch, QString group)
{
    schematic = sch;
    int quantity = 0;
    int quantityPerHour = 0;

    Common::Component *component = schematic
            ->getProduct()->getComponent();

    ui->groupName->setText(group);
    ui->iconSchematic->setScene(imageScene);
    imageScene->addItem(imageItem);
    imageItem->setPixmap(component->getIcon());
    ui->schematicName->setText(schematic->getName());
    ui->productCycleTime->setText(QString::number(schematic->getCycleTime() / 60));

    quantity = schematic->getProduct()->getQuantity();
    quantityPerHour = quantity * (schematic->getCycleTime() == 1800 ? 2 : 1);

    ui->productQuantityPerCycle->setText(
                QString::number(quantity));

    ui->productQuantityPerHour->setText(QString::number(quantityPerHour));

    Common::Consumable *cmp;
    SchematicRowComponent *schRowComponent;
    QMap<int, Common::Consumable*> cnsm = schematic->getConsumables();

    for (auto it = cnsm.begin(), end = cnsm.end(); it != end; it++) {
        cmp = it.value();

        schRowComponent = new SchematicRowComponent(ui->componentsInfo);
        schRowComponent->consumable = cmp;
        components->append(schRowComponent);

        quantity = cmp->getQuantity();
        schRowComponent->quantityPerHour = quantity *
                (schematic->getCycleTime() == 1800 ? 2 : 1);

        schRowComponent->ui->componentName->setText(cmp->getComponent()->getName());

        schRowComponent->ui->quantityPerCycle->setText(
                    QString::number(quantity));

        schRowComponent->ui->quantityPerHour->setText(
                    QString::number(schRowComponent->quantityPerHour));

        ui->componentsInfo->layout()->addWidget(schRowComponent);
    }

    updateView();
}

void SchemaitRow::updateView()
{
    double profitIsk = schematic->getProfitIsk(true);
    double profitPercentage = schematic->getProfitPercentage(true);

    QLocale locale;
    double buyPrice;
    double sellPrice = schematic->getProduct()->getComponent()->getSellPrice();

    int quantity = schematic->getProduct()->getQuantity();
    int quantityPerHour = quantity * (schematic->getCycleTime() == 1800 ? 2 : 1);

    ui->productSellPrice->setText(locale.toString(sellPrice, 'f', 0));
    ui->productSellPriceTotal->setText(
                locale.toString((quantityPerHour * sellPrice), 'f', 0));

    if (profitIsk > 0) {
        ui->profitIsk->setStyleSheet("#profitIsk{color:green;}");
        ui->profitPercentage->setStyleSheet("#profitPercentage{color:green;}");
    } else if (profitIsk < 0) {
        ui->profitIsk->setStyleSheet("#profitIsk{color: red;}");
        ui->profitPercentage->setStyleSheet("#profitPercentage{color: red;}");
    }

    if (profitIsk != 0) {
        ui->profitIsk->setText(
                    locale.toString(profitIsk, 'f', 2).append(" Isk"));
        ui->profitPercentage->setText(
                    locale.toString(profitPercentage, 'f', 0).append(" %"));
    } else {
        ui->profitIsk->clear();
        ui->profitPercentage->clear();
    }

    ui->productExportCost->setText(
                QLocale().toString(
                    quantityPerHour * schematic->getProduct()->getComponent()->getExportCost(), 'f', 2));


    SchematicRowComponent *sch;

    for (int i = 0, size = components->size(); i < size; i++) {
        sch = components->at(i);

        int quantity = sch->consumable->getQuantity();
        int quantityPerHour = quantity * (schematic->getCycleTime() == 1800 ? 2 : 1);

        sch->ui->importCost->setText(
            QLocale().toString(
                sch->quantityPerHour * sch->consumable
                    ->getComponent()->getImportCost(), 'f', 2));

        buyPrice = sch->consumable->getComponent()->getBuyPrice();

        sch->ui->componentBuyPrice->setText(locale.toString(buyPrice, 'f', 2));
        sch->ui->componentBuyPriceTotal->setText(
                    locale.toString(quantityPerHour * buyPrice, 'f', 2));

    }

}



void SchemaitRow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SchemaitRow::setupDefaultPalette()
{
    //pal.
}
