#include "main.h"
#include "mainwindow.h"
#include "src/generic/splashscreen.h"
#include "src/dbal/connection.h"
#include "src/model/datacontainer.h"

//#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Omgnull");
    QCoreApplication::setApplicationName("EVE Online planetary industry profitability");

    QSettings::setPath(
        QSettings::IniFormat,
        QSettings::UserScope,
        QCoreApplication::applicationDirPath().append(APPC::SETTINGS_FILE)
    );

    QTranslator translator;
    QSettings settings(APPC::SETTINGS_FILE, QSettings::IniFormat);
    QString trFilePath = settings.value("locale", QLocale::system().name())
            .toString().append(QString(".qm"));

    if (!translator.load(trFilePath, QString(":/translations"))) {
        translator.load("en_US.qm", ":/translations");
    }

    app.installTranslator(&translator);

    DBAL::Connection conn;
    conn.connect("QSQLITE", "eve.db");

    MainWindow mw;
    Generic::SplashScreen *splash = new Generic::SplashScreen();
    splash->setPixmap(QPixmap(APPC::DATA_SPLASHSCREEN_BG));
    splash->show();

    splash->showMessage(QApplication::tr("Loading ..."),
        Qt::AlignBottom | Qt::AlignHCenter, Qt::white);

    Model::DataContainer dc;
    dc.setSplashScreen(splash);

    //QTimer::singleShot(2000, &dc, SLOT(init()));
    QTimer::singleShot(300, &dc, SLOT(autoload()));
    QObject::connect(&dc, SIGNAL(dataLoaded(bool)), &mw, SLOT(setupLayout()));

    QObject::connect(&mw, SIGNAL(setupComplete()), &mw, SLOT(show()));
    QObject::connect(&mw, SIGNAL(setupComplete()), splash, SLOT(close()));
    QObject::connect(&app, SIGNAL(lastWindowClosed()), &dc, SLOT(unload()));

    return app.exec();
}
