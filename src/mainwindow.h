#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/main.h"
#include "src/model/datacontainer.h"
#include "src/util/comboboxhelper.h"
#include "ui_mainwindow.h"
#include "src/generic/schematicrow.h"

#include <QMainWindow>
#include <QSettings>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void setupComplete();

private:
    void loadSettings();

    void saveSettings();

    void comboBoxFill(QComboBox*, QString, QMap<QString, int>);

    void diasbleControl(bool);

    void closeEvent(QCloseEvent *);


    Ui::MainWindow *ui;

    Model::DataContainer *dc;

    QList<Generic::SchemaitRow*> *overviewRows;

    QVBoxLayout *overviewLayout;

    int pricesType;

    int pricesId;

    int priceSource;

private slots:
    void about();

    void setupLayout();

    void priceSourceChanged(int);

    void regionChanged(int);

    void tradeHubChanged(int);

    void pricesLoaded(int);

    void taxChanged(int);

};

#endif // MAINWINDOW_H
