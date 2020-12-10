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
    }

    void search(QUrl url, QJsonObject json) {
        QUrlQuery query = QUrlQuery(url.query());
        query.addQueryItem("lang", "ukr");
        query.addQueryItem("access_token", "2bf9c-83b4a-0dac2-e0893-8cf29");
        url.setQuery(query);
        qDebug(qPrintable(url.toString()));
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0");
        searchReply = networkManager->post(request, QJsonDocument(json).toJson());
        connect(searchReply, &QNetworkReply::finished, this, &Api::searchReplyFinished);
    }

    void toursSuggest(QString text) {
        // stop previous request
        if(toursSuggestReply != NULL){
            toursSuggestReply->abort();
        }
        QUrl url = QUrl("https://export.otpusk.com/api/tours/suggests");
        QUrlQuery query = QUrlQuery(url.query());
        query.addQueryItem("text", text);
        query.addQueryItem("lang", "ukr");
        query.addQueryItem("access_token", "2bf9c-83b4a-0dac2-e0893-8cf29");
        url.setQuery(query);
        qDebug(qPrintable(url.toString()));
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0");
        toursSuggestReply = networkManager->get(request);
        connect(toursSuggestReply, &QNetworkReply::finished, this, &Api::toursSuggestReplyFinished);
    }

private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *searchReply;
    QNetworkReply *toursSuggestReply = NULL;

    void searchReplyFinished(){
        qDebug("search reply finished");
        emit searchLoaded(searchReply);
    }

    void toursSuggestReplyFinished(){
        qDebug("tours suggest reply finished");
        emit toursSuggestLoaded(toursSuggestReply);
    }

signals:
    void searchLoaded(QNetworkReply*);
    void toursSuggestLoaded(QNetworkReply*);

};

#endif // API_H
