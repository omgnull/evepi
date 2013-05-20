#include "component.h"

using namespace Common;

#ifdef QT_DEBUG
#include <QFileInfo>
#endif

double Component::tax = 10;

Component::Component(QObject *parent) :
    QObject(parent),
    id(0),
    name(""),
    icon(QPixmap()),
    basePrice(0.00),
    buyPrice(0.00),
    sellPrice(0.00)
{

}

Component::~Component()
{
    //delete icon;
}

int Component::getId()
{
    return id;
}

QString Component::getName()
{
    return name;
}

QPixmap & Component::getIcon()
{
    return icon;
}

double Component::getVolume()
{
    return volume;
}

double Component::getBasePrice()
{
    return basePrice;
}

double Component::getBuyPrice()
{
    return buyPrice;
}

double Component::getSellPrice()
{
    return sellPrice;
}

double Component::getExportCost()
{
    return (basePrice / 100) * Component::tax;
}

double Component::getImportCost()
{
    return (basePrice / 100) * (Component::tax / 2);
}

void Component::setId(int n)
{
    id = n;
    icon.load(QCoreApplication::applicationDirPath()
              .append(APPC::DATA_COMPONENT_GENERIC_ICON).arg(n));

    /*
    QPixmap *img = new QPixmap(
        QCoreApplication::applicationDirPath()
            .append(APPC::DATA_COMPONENT_GENERIC_ICON).arg(n));

    if (img->isNull()) {
        #ifdef QT_DEBUG
        qDebug() << "Icon not exists for component " << id;

        QString source = QCoreApplication::applicationDirPath()
                .append("/Types/%1_64.png").arg(id);

        QFileInfo finfo(source);

        if (finfo.isFile()) {
            QString dest = QCoreApplication::applicationDirPath()
                    .append("/icons/%1").arg(finfo.fileName());
            QFile::copy(source, dest);
        }
        #endif

        img->load(APPC::DATA_COMPONENT_DEFAULT_ICON);
    }

    */
}

void Component::setName(QString str)
{
    name = str;
}

void Component::setVolume(double v)
{
    volume = v;
}

void Component::setBasePrice(double price)
{
    basePrice = price;
}

void Component::setBuyPrice(double price)
{
    buyPrice = price;
}

void Component::setSellPrice(double price)
{
    sellPrice = price;
}
