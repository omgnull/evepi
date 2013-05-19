#ifndef COMBOBOXHELPER_H
#define COMBOBOXHELPER_H

#include "src/main.h"

#include <QSettings>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QListView>

namespace Util {

class ComboBoxHelper
{
public:
    ComboBoxHelper();

    void setPlaceHolder(QString, QComboBox *, bool visible = false);

    void fillComboBox(QComboBox *, QMap<QString, int>, bool keyFirst = true);

    void fillComboBox(QComboBox *, QMap<int, QString>, bool keyFirst = true);

    void fillComboBox(QComboBox *, QMap<double, QString>, bool keyFirst = true);

private:
    void addItem(QComboBox *, QString, int);

    void addItem(QComboBox *, int, QString);
};

}

#endif // COMBOBOXHELPER_H
