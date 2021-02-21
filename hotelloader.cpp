#include "hotelloader.h"

HotelLoader::HotelLoader(Api* api, Hotel* hotel)
{
    this->api = api;
    this->hotel = hotel;
    connect(api, SIGNAL(hotelLoaded(QNetworkReply*)), this, SLOT(handleReply(QNetworkReply*)));
}

Q_INVOKABLE void HotelLoader::load(int id){
    api->hotel(id);
}

bool HotelLoader::getLoading() const {
    return loading;
}

void HotelLoader::setLoading(bool loading) {
    if(loading != this->loading){
        this->loading = loading;
        emit loadingChanged();
    }
}

bool HotelLoader::isReplyFailed() const{
    return replyFailed;
}

void HotelLoader::setReplyFailed(bool isReplyFailed) {
    if(this->replyFailed != isReplyFailed){
        this->replyFailed = isReplyFailed;
        emit isReplyFailedChanged();
    }
}

QString HotelLoader::getReplyErrorText() const {
    return replyErrorText;
}

void HotelLoader::setReplyErrorText(QString replyErrorText) {
    if(this->replyErrorText != replyErrorText){
        this->replyErrorText = replyErrorText;
        emit replyErrorTextChanged();
    }
}

void HotelLoader::handleReply(QNetworkReply *reply){
    if(reply->isFinished()){
        setReplyFailed(reply->error() != QNetworkReply::NoError);
        setReplyErrorText(reply->errorString());
        if(replyFailed){
            return;
        }

        qDebug("Request successfully finished");
        QByteArray responseData = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(responseData);
//        qDebug(qPrintable(json.toJson()));
        QJsonObject responseObj = json.object();
        if(responseObj.contains(QString("error")) && responseObj.take(QString("error")).toBool() && responseObj.contains(QString("message"))){
            setReplyFailed(true);
            setReplyErrorText(responseObj.take(QString("message")).toString().prepend("response contains error: "));
            return;
        }
        QJsonObject responseHotel = responseObj["hotel"].toObject();

        hotel->setName(responseHotel["nm"].toString());
        hotel->setCity(responseHotel["c"].toObject()["n"].toString());
        hotel->setCountry(responseHotel["t"].toObject()["n"].toString());
        hotel->setRatingAvarage(responseHotel["r"].toDouble());
        hotel->setRatingCount(responseHotel["v"].toInt());
        hotel->setStars(responseHotel["s"].toObject()["n"].toString().remove('*'));

        QStringList photosList;
        QJsonArray jsonPhotos = responseHotel.take("f").toArray();
        QJsonArray::const_iterator i;
        for(i = jsonPhotos.constBegin(); i != jsonPhotos.end(); i++){
            photosList.append(i->toString());
        }
        hotel->setPhotos(photosList);

    }
    qDebug("Request not finished yet");
}
