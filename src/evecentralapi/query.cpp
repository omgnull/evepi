#include "query.h"

using namespace EVECentralAPI;

Query::Query(QString url, QObject *parent) :
    QObject(parent),
    baseUrl(url),
    manager(new QNetworkAccessManager(this)),
    query(new QList<QString>)
{
    connect(manager, SIGNAL(finished(QNetworkReply*)),
        SLOT(netReplyFinished(QNetworkReply*)));
}

Query::~Query()
{
    delete manager;
    delete query;
}

void Query::addParameter(QString name, QString value)
{
    query->append(QString("&%1=%2").arg(name, value));
}

void Query::clear()
{
    query->clear();
}

void Query::exec(QString fName)
{
    filename = fName;
    Model::XmlCache cache;
    QDomDocument *doc = cache.load(filename);

    if (doc) {
        #ifdef APP_DEBUG
        qDebug() << "Data loaded from cache.";
        #endif

        emit dataLoaded(doc);

        return;
    }

    QNetworkRequest request;
    QUrl url = QUrl(buildQuery(baseUrl));

    #ifdef APP_DEBUG
    qDebug() << "Request url: " << url.isValid();
    #endif


    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader,
        APPC::NETWORK_MANAGER_USER_AGENT);

    #ifdef QT_DEBUG
    qDebug() << "Net request start";
    #endif

    manager->get(request);
}

void Query::updateParameter(QString *param, int val)
{
    param->clear();
    param->append(QString::number(val));
}

QString Query::buildQuery(QString url)
{
    for (int i = 0; i < query->size(); i++) {
        url.append(query->at(i));
    }

    return url;
}

void Query::netReplyFinished(QNetworkReply *reply)
{
    if (QNetworkReply::NoError != reply->error()) {
        #ifdef QT_DEBUG
        qDebug() << "Network error occurred: "
                 << reply->errorString();
        #endif

        // [TODO] Need to handle this error

        emit dataLoaded(nullptr);
    }

    QDomDocument *doc = new QDomDocument(filename);
    QByteArray contents = reply->readAll();

    if (!doc->setContent(contents)) {
        #ifdef QT_DEBUG
        qDebug() << "Error reading xml data from response.";
        #endif

        // [TODO] Need to handle this error

        delete doc;
        emit dataLoaded(nullptr);
    }

    Model::XmlCache cache;
    // Not critical
    if (!cache.save(filename, contents)) {
        #ifdef QT_DEBUG
        qDebug() << "Could not save cache file: " << filename;
        #endif
    }

    emit dataLoaded(doc);
}
