QT       += core gui network xml sql
#QTPLUGIN += qico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = evepi
TEMPLATE = app
CONFIG += static


SOURCES         += \
    src/common/component.cpp \
    src/common/product.cpp \
    src/common/consumable.cpp \
    src/dbal/connection.cpp \
    src/dbal/driver/sqllite.cpp \
    src/model/datacontainer.cpp \
    src/evecentralapi/marketstat.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/evecentralapi/query.cpp \
    src/generic/splashscreen.cpp \
    src/common/schematic.cpp \
    src/model/xmlloader.cpp \
    src/util/comboboxhelper.cpp \
    src/model/xmlcache.cpp \
    src/generic/schematicrow.cpp \
    src/util/schematiccalculator.cpp \
    src/generic/schematicrowcomponent.cpp


HEADERS         += \
    src/common/component.h \
    src/common/product.h \
    src/common/consumable.h \
    src/dbal/connection.h \
    src/dbal/driver/sqllite.h \
    src/model/datacontainer.h \
    src/evecentralapi/marketstat.h \
    src/mainwindow.h \
    src/main.h \
    src/evecentralapi/query.h \
    src/generic/splashscreen.h \
    src/common/schematic.h \
    src/model/xmlloader.h \
    src/util/comboboxhelper.h \
    src/model/xmlcache.h \
    src/generic/schematicrow.h \
    src/util/schematiccalculator.h \
    src/generic/schematicrowcomponent.h



FORMS           += \
    src/view/mainwindow.ui \
    src/view/schematicrow.ui \
    src/view/schematicrowcomponent.ui

TRANSLATIONS    += \
    src/translations/en_US.ts

RESOURCES       += \
    src/resources.qrc

#win32 {
#    RC_FILE = src/win32res.rc
#}


CONFIG(release, debug|release) {
    DESTDIR = release
} else {
    DESTDIR = debug
}

#ress.path = $$OUT_PWD/$${DESTDIR}/
#ress.files += res/*

#INSTALLS += ress
