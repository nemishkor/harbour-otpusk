#include "locationmodel.h"

LocationModel::LocationModel(Api *api): m_api(api){
    connect(m_api, SIGNAL(toursSuggestLoaded(QNetworkReply*)), this, SLOT(updateFromApiReply(QNetworkReply*)));
}

void LocationModel::setNetworkError(QString networkError)
{
    if(QString::compare(this->networkError, networkError) == 0){
        return;
    }
    this->networkError = networkError;
    emit networkErrorChanged();
}
