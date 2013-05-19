#ifndef EVECENTRALAPI_QUERY_H
#define EVECENTRALAPI_QUERY_H

#include "src/main.h"
#include "src/common/component.h"
#include "src/model/xmlcache.h"

#include <string>

#include <QObject>
#include <QFile>
#include <QtNetwork>
#include <QDomDocument>

#include <QFile>

namespace EVECentralAPI {

class Query : public QObject
{
    Q_OBJECT

public:
    Query(QString, QObject *parent = nullptr);

    ~Query();

    void exec(QString);

    void addParameter(QString, QString);

signals:
    void dataLoaded(QDomDocument *);

protected:
    virtual QString buildQuery(QString);

    void updateParameter(QString *param, int val);

    void clear();

    QString filename;

private:
    void checkErrors(QDomDocument *);

    QString baseUrl;

    QNetworkAccessManager *manager;

    QList<QString> *query;

private slots:
    void netReplyFinished(QNetworkReply *);
};

}

#endif // EVECENTRALAPI_QUERY_H
