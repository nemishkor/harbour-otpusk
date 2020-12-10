#ifndef TOURSLOADER_H
#define TOURSLOADER_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QString>
#include <QTimer>
#include <QList>
#include "api.h"
#include "tourmodel.h"

class ToursLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)
    Q_PROPERTY(int total READ getTotal NOTIFY totalChanged)
    Q_PROPERTY(TourModel* tourModel READ getTourModel NOTIFY tourModelChanged)
    Q_PROPERTY(bool loading READ getLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool replyFailed READ isReplyFailed NOTIFY isReplyFailedChanged)
    Q_PROPERTY(QString replyErrorText READ getReplyErrorText NOTIFY replyErrorTextChanged)

public:
    explicit ToursLoader(Api *api){
        this->api = api;
        connect(api, SIGNAL(searchLoaded(QNetworkReply*)), this, SLOT(handleSearchReply(QNetworkReply*)));
    }

    Q_INVOKABLE void load(){
        requestNumber = 0;
        setLoading(true);
        sendSearchRequest();
    }

    void continueSearch(){
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
        query.addQueryItem("to", "43");
        query.addQueryItem("checkIn", "2021-03-20");
        query.addQueryItem("checkOut", "2021-03-30");
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

private:
    Api *api;
    int requestNumber = 0;
    int progress = 0;
    int total = 0;
    TourModel tourModel;
    bool loading = false;
    bool replyFailed = false;
    QString replyErrorText;

private slots:
    void handleSearchReply(QNetworkReply *reply){
        if(reply->isFinished()){
            setReplyFailed(reply->error() != QNetworkReply::NoError);
            setReplyErrorText(reply->errorString());
            if(!replyFailed){

                qDebug("Request successfully finished");
                    QByteArray responseData = reply->readAll();
                    QJsonDocument json = QJsonDocument::fromJson(responseData);
//                qDebug(qPrintable(json.toJson()));

                setTotal((int) json.object()["total"].toInt());

                QJsonObject progressList = json.object()["progress"].toObject();
                int operatorsSearchProgressDone = 0;
                QJsonObject::const_iterator i;
                for (i = progressList.constBegin(); i != progressList.end(); ++i){
                    if((*i).toBool())
                        operatorsSearchProgressDone++;
                }

                setProgress((int) (100 * operatorsSearchProgressDone / progressList.size()));

                bool lastResult = json.object()["lastResult"].toBool();
                if(lastResult){
                    setLoading(false);

                    QJsonObject::const_iterator hotelsIterator;
                    QJsonObject hotels = json.object()["hotels"].toObject()["1"].toObject();
                    for (hotelsIterator = hotels.constBegin(); hotelsIterator != hotels.end(); ++hotelsIterator){
                        QJsonObject hotel = (*hotelsIterator).toObject();
                        tourModel.addTour(Tour(
                                hotel["n"].toString(),
                                hotel["c"].toObject()["n"].toString(),
                                hotel["t"].toObject()["n"].toString(),
                                hotel["r"].toDouble(),
                                hotel["v"].toString().toInt(),
                                hotel["p"].toDouble(),
                                hotel["po"].toDouble(),
                                hotel["pu"].toString()));
                    }

                    emit tourModelChanged();
                } else {
                    continueSearch();
                }

                return;
            }
        }
        qDebug("Request not finished yet");
    }

signals:
    void tourModelChanged();
    void progressChanged();
    void totalChanged();
    void loadingChanged();
    void isReplyFailedChanged();
    void replyErrorTextChanged();
};

#endif // TOURSLOADER_H
