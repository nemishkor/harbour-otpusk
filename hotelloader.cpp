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
        QJsonArray jsonPhotos = responseHotel["f"].toArray();
        QJsonArray::const_iterator json_array_iterator;
        for(json_array_iterator = jsonPhotos.constBegin(); json_array_iterator != jsonPhotos.end(); json_array_iterator++){
            photosList.append(json_array_iterator->toString());
        }
        hotel->setPhotos(photosList);

        QJsonObject::const_iterator json_object_iterator;

        hotel->roomServices()->clear();
        QJsonObject services = responseHotel["e"].toObject()["r"].toObject();
        for(json_object_iterator = services.constBegin(); json_object_iterator != services.end(); json_object_iterator++){
            QJsonObject service = json_object_iterator->toObject();
            hotel->roomServices()->addRoomService(RoomService(
                    service["name"].toString(),
                    service["all"].toBool(),
                    service["id"].toString(),
                    service["title"].toString()));
        }
        emit hotel->roomServicesChanged();

        hotel->hotelServices()->clear();
        services = responseHotel["e"].toObject()["h"].toObject();
        for(json_object_iterator = services.constBegin(); json_object_iterator != services.end(); json_object_iterator++){
            QJsonObject service = json_object_iterator->toObject();
            hotel->hotelServices()->addHotelService(HotelService(
                    service["name"].toString(),
                    service["value"].toString(),
                    service["id"].toString(),
                    service["title"].toString()));
        }
        emit hotel->hotelServicesChanged();

        hotel->forChildrenServices()->clear();
        services = responseHotel["e"].toObject()["c"].toObject();
        for(json_object_iterator = services.constBegin(); json_object_iterator != services.end(); json_object_iterator++){
            QJsonObject service = json_object_iterator->toObject();
            hotel->forChildrenServices()->addHotelService(HotelService(
                    service["name"].toString(),
                    service["value"].toString(),
                    service["id"].toString(),
                    service["title"].toString()));
        }
        emit hotel->forChildrenServicesChanged();

        hotel->beachServices()->clear();
        services = responseHotel["e"].toObject()["b"].toObject();
        for(json_object_iterator = services.constBegin(); json_object_iterator != services.end(); json_object_iterator++){
            QJsonObject service = json_object_iterator->toObject();
            hotel->beachServices()->addHotelService(HotelService(
                    service["name"].toString(),
                    service["value"].toString(),
                    service["id"].toString(),
                    service["title"].toString()));
        }
        emit hotel->beachServicesChanged();

        hotel->activitiesServices()->clear();
        services = responseHotel["e"].toObject()["s"].toObject();
        for(json_object_iterator = services.constBegin(); json_object_iterator != services.end(); json_object_iterator++){
            QJsonObject service = json_object_iterator->toObject();
            hotel->activitiesServices()->addHotelService(HotelService(
                    service["name"].toString(),
                    service["value"].toString(),
                    service["id"].toString(),
                    service["title"].toString()));
        }
        emit hotel->activitiesServices();

        hotel->hotelRatings()->clear();
        QJsonObject ratings = responseHotel["vs"].toObject();
        for(json_object_iterator = ratings.constBegin(); json_object_iterator != ratings.end(); json_object_iterator++){
            QJsonObject rating = json_object_iterator->toObject();
            hotel->hotelRatings()->addHotelRating(HotelRating(
                    rating["name"].toString(),
                    rating["vote"].toDouble(),
                    rating["count"].toInt()));
        }
        emit hotel->hotelRatingsChanged();



    }
    qDebug("Request not finished yet");
}
