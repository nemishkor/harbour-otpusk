#include "toursloader.h"

ToursLoader::ToursLoader(Api *api){
    this->api = api;
    connect(api, SIGNAL(searchLoaded(QNetworkReply*)), this, SLOT(handleSearchReply(QNetworkReply*)));
}

void ToursLoader::load(SearchParameters *searchParameters){
    requestNumber = 0;
    setLoading(true);
    currentSearchParameters = searchParameters;
    sendSearchRequest();
}

void ToursLoader::continueSearch(){
    qDebug("Continue search");
    if(requestNumber == 9){
        setLoading(false);
        setReplyFailed(true);

        return;
    }
    requestNumber++;
    QTimer::singleShot(requestNumber < 3 ? 2500 : 6000, this, &ToursLoader::sendSearchRequest);
}

void ToursLoader::sendSearchRequest(){
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

int ToursLoader::getProgress() {
    return progress;
}

void ToursLoader::setProgress(int progress){
    if(this->progress != progress){
        this->progress = progress;
        emit progressChanged();
    }
}

int ToursLoader::getTotal() {
    return total;
}

void ToursLoader::setTotal(int total){
    if(this->total != total){
        this->total = total;
        emit totalChanged();
    }
}

TourModel* ToursLoader::getTourModel() {
    return &tourModel;
}

bool ToursLoader::getLoading() const {
    return loading;
}

void ToursLoader::setLoading(bool loading) {
    if(loading != this->loading){
        this->loading = loading;
        emit loadingChanged();
    }
}

bool ToursLoader::isReplyFailed() const{
    return replyFailed;
}

void ToursLoader::setReplyFailed(bool isReplyFailed) {
    if(this->replyFailed != isReplyFailed){
        this->replyFailed = isReplyFailed;
        emit isReplyFailedChanged();
    }
}

QString ToursLoader::getReplyErrorText() const {
    return replyErrorText;
}

void ToursLoader::setReplyErrorText(QString replyErrorText) {
    if(this->replyErrorText != replyErrorText){
        this->replyErrorText = replyErrorText;
        emit replyErrorTextChanged();
    }
}

int ToursLoader::getPage(){
    return page;
}

void ToursLoader::setPage(int _page){
    page = _page;
    emit pageChanged();
}

int ToursLoader::calculateProgress(QJsonDocument *json) {
    QJsonObject progressList = json->object()["progress"].toObject();
    int operatorsSearchProgressDone = 0;
    QJsonObject::const_iterator i;
    for (i = progressList.constBegin(); i != progressList.end(); ++i){
        if((*i).toBool())
            operatorsSearchProgressDone++;
    }

    return (int) (100 * operatorsSearchProgressDone / progressList.size());
}

void ToursLoader::fillOffersModelFromResponse(int hotelId, OffersModel *offersModel)
{
    offersModel->clear();
    QJsonObject::const_iterator i;
    for(i = lastToursReply.constBegin(); i != lastToursReply.constEnd(); i++){
        if(i.key().toInt() == hotelId){
            qDebug() << "found tour in json by hotelId";

            QJsonObject::const_iterator offersIterator;
            QJsonObject jsonOffers = (*i).toObject()["offers"].toObject();
            for (offersIterator = jsonOffers.constBegin(); offersIterator != jsonOffers.constEnd(); offersIterator++){
                QJsonObject jsonOffer = (*offersIterator).toObject();

                QJsonArray jsonIncluded = jsonOffer["o"].toArray();
                QJsonArray::const_iterator offersIncludedIterator;
                QStringList included;
                for (offersIncludedIterator = jsonIncluded.begin(); offersIncludedIterator != jsonIncluded.end(); offersIncludedIterator++){
                    included.append(offersIncludedIterator->toString());
                }

                offersModel->addOffer(Offer(
                                jsonOffer["i"].toVariant().toString(),
                                jsonOffer["last"].toString(),
                                jsonOffer["ti"].toInt(),
                                included,
                                jsonOffer["d"].toString(),
                                jsonOffer["dt"].toString(),
                                jsonOffer["y"].toString().toUpper(),
                                jsonOffer["a"].toInt(),
                                jsonOffer["h"].toInt(),
                                jsonOffer["ha"].toString(),
                                jsonOffer["n"].toInt(),
                                jsonOffer["f"].toString().toUpper(),
                                jsonOffer["r"].toString(),
                                jsonOffer["p"].toDouble(),
                                jsonOffer["pl"].toDouble(),
                                jsonOffer["u"].toString(),
                                jsonOffer["t"].toString()));
            }

        }
    }
}

void ToursLoader::addTour(QJsonObject hotel, bool isFirst)
{

    Tour tour(hotel["i"].toInt(),
            hotel["n"].toString(),
            hotel["c"].toObject()["n"].toString(),
            hotel["t"].toObject()["n"].toString(),
            hotel["r"].toDouble(),
            hotel["v"].toInt(),
            isFirst,
            hotel["s"].toString(),
            hotel["f"].toString(),
            getFirstOfferOfTour(&hotel));

    tourModel.addTour(tour);
}

Offer ToursLoader::getFirstOfferOfTour(QJsonObject *tour)
{
    QJsonObject::const_iterator offersIterator;
    QJsonObject jsonOffers = (*tour)["offers"].toObject();
    for (offersIterator = jsonOffers.constBegin(); true; offersIterator++){
        QJsonObject jsonOffer = (*offersIterator).toObject();

        QJsonArray jsonIncluded = jsonOffer["o"].toArray();
        QJsonArray::const_iterator offersIncludedIterator;
        QStringList included;
        for (offersIncludedIterator = jsonIncluded.begin(); offersIncludedIterator != jsonIncluded.end(); offersIncludedIterator++){
            included.append(offersIncludedIterator->toString());
        }

        return Offer(
                    jsonOffer["i"].toVariant().toString(),
                    jsonOffer["last"].toString(),
                    jsonOffer["ti"].toInt(),
                    included,
                    jsonOffer["d"].toString(),
                    jsonOffer["dt"].toString(),
                    jsonOffer["y"].toString().toUpper(),
                    jsonOffer["a"].toInt(),
                    jsonOffer["h"].toInt(),
                    jsonOffer["ha"].toString(),
                    jsonOffer["n"].toInt(),
                    jsonOffer["f"].toString().toUpper(),
                    jsonOffer["r"].toString(),
                    jsonOffer["p"].toDouble(),
                    jsonOffer["pl"].toDouble(),
                    jsonOffer["u"].toString(),
                    jsonOffer["t"].toString());
    }
}

void ToursLoader::handleSearchReply(QNetworkReply *reply){
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
    QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
//        qDebug(qPrintable(json.toJson()));
    setTotal((int) response.object()["total"].toInt());
    setProgress(calculateProgress(&response));

    if(!response.object()["lastResult"].toBool()){
        continueSearch();
        return;
    }

    qDebug("Last result of search request");

    QJsonObject::const_iterator i;
    lastToursReply = response.object()["hotels"].toObject()[QString::number(page)].toObject();
    bool isFirst = true;
    for (i = lastToursReply.constBegin(); i != lastToursReply.end(); ++i){
        addTour((*i).toObject(), isFirst);
        isFirst = false;
    }

    emit tourModelChanged();
    setLoading(false);

}
