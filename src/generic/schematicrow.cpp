#include "schematicrow.h"

using namespace Generic;

SchemaitRow::SchemaitRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchemaitRow),
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
    delete ui;
    delete imageItem;
    delete imageScene;
}

void SchemaitRow::setSchematic(Common::Schematic *sch)
{
    schematic = sch;
    Common::Component *component = schematic
            ->getProduct()->getComponent();

    ui->iconSchematic->setScene(imageScene);
    imageScene->addItem(imageItem);
    imageItem->setPixmap(component->getIcon());
    ui->labelSchematicName->setText(schematic->getName());

    updateView();

}

void SchemaitRow::updateView()
{
    QString styleSheet = "#labelProfitIsk, #labelProfitPercentage { color: white; };";

    double profitIsk = schematic->getProfitIsk(),
           profitPercentage = schematic->getProfitPercentage();

    if (profitIsk > 0) {
        styleSheet = "#labelProfitIsk, #labelProfitPercentage { color: green; }";
    } else if (profitIsk < 0) {
        styleSheet = "#labelProfitIsk, #labelProfitPercentage { color: red; };";
    }

    ui->labelProfitIsk->setStyleSheet(styleSheet);
    ui->labelProfitIsk->setText(QLocale().toString(profitIsk, 'f', 2).append(" Isk"));

    ui->labelProfitPercentage->setStyleSheet(styleSheet);
    ui->labelProfitPercentage->setText(QLocale().toString(profitPercentage, 'f', 0).append(" %"));

}

void SchemaitRow::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }
