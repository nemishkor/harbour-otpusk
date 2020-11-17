#ifndef API_H
#define API_H

#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

class Api : public QObject
{
    Q_OBJECT

public:
    Api(){
        networkManager = new QNetworkAccessManager(this);
        connect(networkManager, &QNetworkAccessManager::finished, this, &Api::replyFinished);
    }

    void search(QUrl url, QJsonObject json) {
        QUrlQuery query = QUrlQuery(url.query());
        query.addQueryItem("lang", "ukr");
        query.addQueryItem("access_token", "");
        url.setQuery(query);
        qDebug(qPrintable(url.toString()));
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0");
        networkManager->post(request, QJsonDocument(json).toJson());
    }

    void replyFinished(QNetworkReply *reply){
        emit searchFinished(reply);
    }

private:
    QNetworkAccessManager *networkManager;

signals:
    void searchFinished(QNetworkReply*);

};

#endif // API_H
