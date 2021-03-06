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
        qDebug() << url.toString();
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
        query.addQueryItem("with", "price");
        query.addQueryItem("access_token", "2bf9c-83b4a-0dac2-e0893-8cf29");
        url.setQuery(query);
        qDebug() << url.toString();
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0");
        toursSuggestReply = networkManager->get(request);
        connect(toursSuggestReply, &QNetworkReply::finished, this, &Api::toursSuggestReplyFinished);
    }

    void dates(int locationId) {
        // stop previous request
        if(datesReply != NULL){
            datesReply->abort();
        }
        QUrl url = QUrl("https://export.otpusk.com/api/tours/dates");
        QUrlQuery query = QUrlQuery(url.query());
        query.addQueryItem("to", QString::number(locationId));
        query.addQueryItem("access_token", "2bf9c-83b4a-0dac2-e0893-8cf29");
        url.setQuery(query);
        qDebug() << url.toString();
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0");
        datesReply = networkManager->get(request);
        connect(datesReply, &QNetworkReply::finished, this, &Api::datesReplyFinished);
    }

    void hotel(int id) {
        // stop previous request
        if(hotelReply != NULL){
            hotelReply->abort();
        }
        QUrl url = QUrl("https://export.otpusk.com/api/tours/hotel");
        QUrlQuery query = QUrlQuery(url.query());
        query.addQueryItem("hotelId", QString::number(id));
        query.addQueryItem("lang", QString("ukr"));
        query.addQueryItem("access_token", "2bf9c-83b4a-0dac2-e0893-8cf29");
        url.setQuery(query);
        qDebug() << url.toString();
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64; rv:83.0) Gecko/20100101 Firefox/83.0");
        hotelReply = networkManager->get(request);
        connect(hotelReply, &QNetworkReply::finished, this, &Api::hotelReplyFinished);
    }

private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *searchReply;
    QNetworkReply *toursSuggestReply = NULL;
    QNetworkReply *datesReply = NULL;
    QNetworkReply *hotelReply = NULL;

    void searchReplyFinished(){
        qDebug("search reply finished");
        emit searchLoaded(searchReply);
    }

    void toursSuggestReplyFinished(){
        qDebug("tours suggest reply finished");
        emit toursSuggestLoaded(toursSuggestReply);
    }

    void datesReplyFinished(){
        qDebug("dates reply finished");
        emit datesLoaded(datesReply);
    }

    void hotelReplyFinished(){
        qDebug("hotel reply finished");
        emit hotelLoaded(hotelReply);
    }

signals:
    void searchLoaded(QNetworkReply*);
    void toursSuggestLoaded(QNetworkReply*);
    void datesLoaded(QNetworkReply*);
    void hotelLoaded(QNetworkReply*);

};

#endif // API_H
