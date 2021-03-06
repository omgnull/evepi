#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <typeinfo>

#include <QtGlobal>
#include <QDebug>
#include <QApplication>
#include <QString>
#include <QProgressbar>

#include <QtPlugin>
//Q_IMPORT_PLUGIN(qico)

#ifdef QT_DEBUG
//#define APP_DEBUG
#endif

namespace APPC {

    const int MIN_WINDOW_HEIGHT                     = 480;
    const int MIN_WINNDOW_WIDTH                     = 900;

    const QString SETTINGS_FILE                     = "settings";

    const QString SETTINGS_GENERAL                  = "General";
    const QString SETTINGS_MAIN_WINDOW              = "MainWindow";
    const QString SETTINGS_USER                     = "User";

    const QString XML_BASE_PRICES                   = "/xml/components_base_prices.xml";
    const QString XML_TRADE_HUBS                    = "/xml/trade_hubs.xml";
    const QString XML_TAXES                         = "/xml/taxes.xml";

    const QString XML_CACHE_DIR                     = "/xml/cache";

    const QString NETWORK_MANAGER_USER_AGENT        = "EVE PI profitability tool";
    const QString EVECENTRAL_API_MARKETSTAT_URL     = "http://api.eve-central.com/api/marketstat?";

    const QString DATA_COMPONENT_DEFAULT_ICON       = ":/images/default_64.png";
    const QString DATA_COMPONENT_GENERIC_ICON       = "/icons/%1_64.png";

    const QString DATA_SPLASHSCREEN_BG              = ":/images/splash.jpg";

    const QString TITLE_MAIN_WINDOW                 = "EVE PI";
    const QString TITLE_GENERIC                     = "EVE PI %1";
    const QString TITLE_TAB_OVERVIEW                = "EVE PI Overview";
    const QString TITLE_ABOUT_WINDOW                = "EVE PI About";

    const QString ICON_MAIN_WINDOW_WIN32            = ":/images/win32icon.ico";
}

#endif // MAIN_H
