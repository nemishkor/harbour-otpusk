#ifndef TOURSLOADER_H
#define TOURSLOADER_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QString>
#include <QTimer>
#include <QList>
#include <QJsonArray>
#include "api.h"
#include "tourmodel.h"
#include "searchparameters.h"

class ToursLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)
    Q_PROPERTY(int total READ getTotal NOTIFY totalChanged)
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(TourModel* tourModel READ getTourModel NOTIFY tourModelChanged)
    Q_PROPERTY(bool loading READ getLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool replyFailed READ isReplyFailed NOTIFY isReplyFailedChanged)
    Q_PROPERTY(QString replyErrorText READ getReplyErrorText NOTIFY replyErrorTextChanged)

public:
    explicit ToursLoader(Api *api){
        this->api = api;
        connect(api, SIGNAL(searchLoaded(QNetworkReply*)), this, SLOT(handleSearchReply(QNetworkReply*)));
    }

    Q_INVOKABLE void load(SearchParameters *searchParameters){
        requestNumber = 0;
        setLoading(true);
        currentSearchParameters = searchParameters;
        sendSearchRequest();
    }

    void continueSearch(){
        qDebug("Continue search");
        if(requestNumber == 9){
            setLoading(false);
            setReplyFailed(true);

            return;
        }
        requestNumber++;
        QTimer::singleShot(requestNumber < 3 ? 2500 : 6000, this, &ToursLoader::sendSearchRequest);
    }

    void sendSearchRequest(){
        QUrl url = QUrl("https://export.otpusk.com/api/tours/search");
        QUrlQuery query = QUrlQuery(url.query());
        query.addQueryItem("to", QString::number(currentSearchParameters->getLocationId()));
        query.addQueryItem("checkIn", currentSearchParameters->getStartDate());
        query.addQueryItem("checkOut", currentSearchParameters->getEndDate());
        query.addQueryItem("page", QString::number(page));
        if(currentSearchParameters->getFromCityId() > 0){

        }
        query.addQueryItem("number", QString::number(requestNumber));
        url.setQuery(query);
        api->search(url, QJsonObject());
    }

    int getProgress() {
        return progress;
    }

    void setProgress(int progress){
        if(this->progress != progress){
            this->progress = progress;
            emit progressChanged();
        }
    }

    int getTotal() {
        return total;
    }

    void setTotal(int total){
        if(this->total != total){
            this->total = total;
            emit totalChanged();
        }
    }

    TourModel* getTourModel() {
        return &tourModel;
    }

    bool getLoading() const {
        return loading;
    }

    void setLoading(bool loading) {
        if(loading != this->loading){
            this->loading = loading;
            emit loadingChanged();
        }
    }

    bool isReplyFailed() const{
        return replyFailed;
    }

    void setReplyFailed(bool isReplyFailed) {
        if(this->replyFailed != isReplyFailed){
            this->replyFailed = isReplyFailed;
            emit isReplyFailedChanged();
        }
    }

    QString getReplyErrorText() const {
        return replyErrorText;
    }

    void setReplyErrorText(QString replyErrorText) {
        if(this->replyErrorText != replyErrorText){
            this->replyErrorText = replyErrorText;
            emit replyErrorTextChanged();
        }
    }

    int getPage(){
        return page;
    }

    void setPage(int _page){
        page = _page;
        emit pageChanged();
    }

    int calculateProgress(QJsonDocument *json) {
        QJsonObject progressList = json->object()["progress"].toObject();
        int operatorsSearchProgressDone = 0;
        QJsonObject::const_iterator i;
        for (i = progressList.constBegin(); i != progressList.end(); ++i){
            if((*i).toBool())
                operatorsSearchProgressDone++;
        }

        return (int) (100 * operatorsSearchProgressDone / progressList.size());
    }

private:
    Api *api;
    int requestNumber = 0;
    int progress = 0;
    int total = 0;
    TourModel tourModel;
    bool loading = false;
    bool replyFailed = false;
    QString replyErrorText;
    int page = 1;
    SearchParameters *currentSearchParameters;


    void addTour(QJsonObject hotel, bool isFirst)
    {
        Tour tour(hotel["i"].toInt(),
                hotel["n"].toString(),
                hotel["c"].toObject()["n"].toString(),
                hotel["t"].toObject()["n"].toString(),
                hotel["r"].toDouble(),
                hotel["v"].toInt(),
                hotel["p"].toDouble(),
                hotel["po"].toDouble(),
                hotel["pu"].toString(),
                isFirst,
                hotel["s"].toString(),
                hotel["f"].toString());

//        qDebug("creating");
//        qDebug(tour.name().toLatin1());
//        qDebug(QString("0x%1").arg((quintptr)&tour,
//                                   QT_POINTER_SIZE * 2, 16, QChar('0')).toLatin1());
//        qDebug(QString("0x%1").arg((quintptr)tour.offers(),
//                                   QT_POINTER_SIZE * 2, 16, QChar('0')).toLatin1());

        QJsonObject::const_iterator offersIterator;
        QJsonObject jsonOffers = hotel["offers"].toObject();
        for (offersIterator = jsonOffers.constBegin(); offersIterator != jsonOffers.constEnd(); offersIterator++){
            QJsonObject jsonOffer = (*offersIterator).toObject();

            QJsonArray jsonIncluded = jsonOffer["o"].toArray();
            QJsonArray::const_iterator offersIncludedIterator;
            QStringList included;
            for (offersIncludedIterator = jsonIncluded.begin(); offersIncludedIterator != jsonIncluded.end(); offersIncludedIterator++){
                included.append(offersIncludedIterator->toString());
            }

            tour.offers()->addOffer(Offer(
                            jsonOffer["i"].toVariant().toString(),
                            jsonOffer["last"].toString(),
                            jsonOffer["ti"].toInt(),
                            included,
                            jsonOffer["d"].toString(),
                            jsonOffer["dt"].toString(),
                            jsonOffer["y"].toString(),
                            jsonOffer["a"].toInt(),
                            jsonOffer["h"].toInt(),
                            jsonOffer["ha"].toString(),
                            jsonOffer["n"].toInt(),
                            jsonOffer["f"].toString(),
                            jsonOffer["r"].toString(),
                            jsonOffer["p"].toDouble(),
                            jsonOffer["pl"].toDouble(),
                            jsonOffer["u"].toString(),
                            jsonOffer["t"].toString()));
        }

//        qDebug(QString("Added offers to tour: ").append(QString::number(tour.offers()->rowCount())).toLatin1());

        tourModel.addTour(tour);
    }

private slots:

    void handleSearchReply(QNetworkReply *reply){
        if(!reply->isFinished()){
            qDebug("Request not finished yet");
            return;
        }

        setReplyFailed(reply->error() != QNetworkReply::NoError);
        setReplyErrorText(reply->errorString());

        if(replyFailed){
            return;
        }

        qDebug("Request successfully finished");
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
//        qDebug(qPrintable(json.toJson()));
        setTotal((int) json.object()["total"].toInt());
        setProgress(calculateProgress(&json));

        if(!json.object()["lastResult"].toBool()){
            continueSearch();
            return;
        }

        qDebug("Last result of search request");

        QJsonObject::const_iterator jsonHotelsIterator;
        QJsonObject hotels = json.object()["hotels"].toObject()[QString::number(page)].toObject();
        bool isFirst = true;
        for (jsonHotelsIterator = hotels.constBegin(); jsonHotelsIterator != hotels.end(); ++jsonHotelsIterator){
            addTour((*jsonHotelsIterator).toObject(), isFirst);
            isFirst = false;
        }

        emit tourModelChanged();
        setLoading(false);

    }

signals:
    void tourModelChanged();
    void progressChanged();
    void totalChanged();
    void loadingChanged();
    void isReplyFailedChanged();
    void replyErrorTextChanged();
    void pageChanged();
};

#endif // TOURSLOADER_H
