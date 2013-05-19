#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dc(new Model::DataContainer),
    overviewRows(new QList<Generic::SchemaitRow*>),
    overviewLayout(new QVBoxLayout())
{
    ui->setupUi(this);
    loadSettings();

    Model::DataContainer::setProgressBar(ui->progressBar);
    connect(dc, SIGNAL(pricesLoaded(int)), this, SLOT(pricesLoaded(int)));

    pricesType = pricesId = priceSource = 0;

}

MainWindow::~MainWindow()
{
    qDeleteAll(*overviewRows);

    delete overviewLayout;
    delete ui;
    delete dc;
}


void MainWindow::loadSettings()
{
    QSettings settings(APPC::SETTINGS_FILE, QSettings::IniFormat);

    setMinimumSize(APPC::MIN_WINNDOW_WIDTH, APPC::MIN_WINDOW_HEIGHT);
    int firstRun = settings.value("firstRun", 1).toInt();

    if (1 == firstRun) {
        return;
    }

    settings.beginGroup(APPC::SETTINGS_MAIN_WINDOW);
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    restoreState(settings.value("state", saveState()).toByteArray());

    if (settings.value("maximized", false).toBool()) {
        showMaximized();
    } else if (settings.value("fullscreen", false).toBool()) {
        showFullScreen();
    } else {
        QPoint winPos = settings.value("pos", pos()).toPoint();

        if (!winPos.isNull()) {
            move(winPos);
        }

        resize(settings.value("size", size()).toSize());
    }
    settings.endGroup();


    settings.beginGroup(APPC::SETTINGS_USER);
    Model::DataContainer::setGlobalTax(
                settings.value("tax", size()).toDouble());

    pricesId = settings.value("pricesId", 0).toInt();
    pricesType = settings.value("pricesType", 0).toInt();
    priceSource = settings.value("priceSource", 0).toInt();

    if (2 == priceSource) {

    }

    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings(APPC::SETTINGS_FILE, QSettings::IniFormat);
    settings.setValue("firstRun", 0);
    settings.beginGroup(APPC::SETTINGS_MAIN_WINDOW);

    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.setValue("fullscreen", isFullScreen());
    settings.setValue("maximized", isMaximized());

    if (!isMaximized() && !isFullScreen()) {
        settings.setValue("pos", pos());
        settings.setValue("size", size());
    }

    settings.endGroup();

    settings.beginGroup(APPC::SETTINGS_USER);
    settings.setValue("tax", Model::DataContainer::getGlobalTax());

    if (pricesId != 0 && pricesType != 0) {
        settings.setValue("pricesType", pricesType);
        settings.setValue("pricesId", pricesId);
        settings.setValue("priceSource", priceSource);
    }

    settings.endGroup();
}

void MainWindow::about()
{
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(tr("EVEPIP_ABOUT_HEADER"));
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(tr("EVEPIP_ABOUT_CONTENT"));
    msgBox.exec();
}

void MainWindow::setupLayout()
{
    Util::ComboBoxHelper cbHelper;

    cbHelper.setPlaceHolder(tr("select region ..."), ui->regionBox);
    cbHelper.fillComboBox(ui->regionBox, dc->getRegions());

    cbHelper.setPlaceHolder(tr("select hub ..."), ui->tradeHubBox);
    cbHelper.fillComboBox(ui->tradeHubBox, dc->getTradeHubs());

    cbHelper.fillComboBox(ui->taxBox, dc->getTaxes());


    double tax = Model::DataContainer::getGlobalTax();
    int idx = ui->taxBox->findData(tax);

    if (-1 != idx) {
       ui->taxBox->setCurrentIndex(idx);
    }

    overviewLayout->setSpacing(3);
    ui->overviewScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->overviewContents->setLayout(overviewLayout);
    Generic::SchemaitRow *schematicRow;
    QMap<int, QString> groups = dc->getGroups();
    QList<Common::Schematic *> schematics;

    //qDebug() << ui->overviewContents->layout()->

    for (auto it = groups.begin(),
         end = groups.end(); it != end; it++)
    {
        schematics = dc->getSchematicsByGroup(it.key());
        qDebug() << "Start adding " << schematics.size()
                 << " schematics to overview from goup " << it.value();

        for (int i = 0; i < schematics.size(); ++i) {
            schematicRow = new Generic::SchemaitRow(ui->overviewContents);
            overviewRows->append(schematicRow);
            schematicRow->setSchematic(schematics.at(i));


            overviewLayout->addWidget(schematicRow);
            schematicRow->show();
        }
    }

    priceSourceChanged(priceSource);
    // [TODO] Need refactor
    if (0 != pricesId  && 0 != pricesType) {
        if (1 == pricesType) {
            idx = ui->regionBox->findData(tax);
            if (-1 != idx) {
                ui->regionBox->setCurrentIndex(idx);
                regionChanged(pricesId);
            }
        } else if (2 == pricesType) {
            idx = ui->tradeHubBox->findData(tax);
            if (-1 != idx) {
                ui->tradeHubBox->setCurrentIndex(idx);
                tradeHubChanged(pricesId);
            }
        }
    }

    emit setupComplete();
}

void MainWindow::priceSourceChanged(int n)
{
    priceSource = n;

    if (2 == n) {
        ui->regionBox->setDisabled(true);
        ui->tradeHubBox->setDisabled(false);

        return;
    }

    ui->regionBox->setDisabled(false);
    ui->tradeHubBox->setDisabled(true);
}

void MainWindow::regionChanged(int n)
{
    diasbleControl(true);

    pricesType = 1;
    pricesId = ui->regionBox->itemData(n).toInt();
    dc->loadPrices(pricesId, 0);
}

void MainWindow::tradeHubChanged(int n)
{
    diasbleControl(true);

    pricesType = 2;
    pricesId = ui->tradeHubBox->itemData(n).toInt();
    dc->loadPrices(pricesId, 1);
}

void MainWindow::taxChanged(int n)
{
    diasbleControl(true);
    Model::DataContainer::setGlobalTax(ui->taxBox->itemData(n).toInt());
    dc->setProgressBarValue(40);

    for (int i = 0, end = overviewRows->size(); i < end; i++) {
        overviewRows->at(i)->updateView();
    }

    dc->setProgressBarValue(100);
    diasbleControl(false);
}

void MainWindow::pricesLoaded(int)
{
    for (int i = 0, end = overviewRows->size(); i < end; i++) {
        overviewRows->at(i)->updateView();
    }

    dc->setProgressBarValue(100);
    diasbleControl(false);
}

void MainWindow::diasbleControl(bool condition)
{
    ui->selectPriceWidget->setDisabled(condition);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    saveSettings();
}

