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

class Api : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastResult READ getLastResult NOTIFY lastResultChanged)
    Q_PROPERTY(QString total READ getTotal NOTIFY totalChanged)

public:
    Api(QObject *parent = nullptr){
        networkManager = new QNetworkAccessManager(this);
        connect(networkManager, &QNetworkAccessManager::finished, this, &Api::replyFinished);
    }

    bool getLastResult() {
        return lastResult;
    }

    int getTotal() {
        return total;
    }

    Q_INVOKABLE void load() {
        QNetworkRequest request(QUrl("http://example.com/exampleapi"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0");
        QJsonObject json;
        json.insert("lang", "ukr");
        json.insert("access_token", "2bf9c-83b4a-0dac2-e0893-8cf29");
        networkManager->post(request, QJsonDocument(json).toJson());
    }

    void replyFinished(QNetworkReply *reply){
        if(reply->isFinished()){
            QByteArray responseData = reply->readAll();
            QJsonDocument json = QJsonDocument::fromJson(responseData);
        }
        qDebug("Request not finished yet");
    }

private:
    bool lastResult;
    int total;
    QNetworkAccessManager *networkManager;



signals:
    void lastResultChanged();
    void totalChanged();

};

#endif // API_H
