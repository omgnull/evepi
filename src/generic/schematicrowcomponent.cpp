#include "schematicrowcomponent.h"

using namespace Generic;

SchematicRowComponent::SchematicRowComponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchematicRowComponent)
{
    ui->setupUi(this);
}

SchematicRowComponent::~SchematicRowComponent()
{
    delete ui;
}
