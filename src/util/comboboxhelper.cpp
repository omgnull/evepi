#include "comboboxhelper.h"

using namespace Util;

ComboBoxHelper::ComboBoxHelper()
{

}

void ComboBoxHelper::setPlaceHolder(QString plh, QComboBox *box, bool visible)
{
    box->addItem(plh);
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(box->model());
    QModelIndex firstIndex = model->index(0, box->modelColumn(),
            box->rootModelIndex());

    QStandardItem* firstItem = model->itemFromIndex(firstIndex);
    firstItem->setSelectable(false);

    if (!visible) {
        QListView* listView = qobject_cast<QListView*>(box->view());
        Q_CHECK_PTR(listView);
        listView->setRowHidden(0, true);
    }
}

void ComboBoxHelper::fillComboBox(QComboBox *box, QMap<QString, int> items, bool keyFirst)
{
    for (auto it = items.begin(), end = items.end(); it != end; it++) {
        if (keyFirst) {
            addItem(box, it.key(), it.value());
        } else {
            addItem(box, it.value(), it.key());
        }
    }
}

void ComboBoxHelper::fillComboBox(QComboBox *box, QMap<int, QString> items, bool keyFirst)
{
    for (auto it = items.begin(), end = items.end(); it != end; it++) {
        if (keyFirst) {
            addItem(box, it.value(), it.key());
        } else {
            addItem(box, it.key(), it.value());
        }
    }
}

void ComboBoxHelper::fillComboBox(QComboBox *box, QMap<double, QString> items, bool keyFirst)
{
    for (auto it = items.begin(), end = items.end(); it != end; it++) {
        if (keyFirst) {
            addItem(box, it.value(), it.key());
        } else {
            addItem(box, it.key(), it.value());
        }
    }
}

void ComboBoxHelper::addItem(QComboBox *box, QString key, int val)
{
    box->addItem(key, val);
}

void ComboBoxHelper::addItem(QComboBox *box, int key, QString val)
{
    box->addItem(QString::number(key), val);
}
