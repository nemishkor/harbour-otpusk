#include "locationmodel.h"

LocationModel::LocationModel(Api *api): m_api(api){
    connect(m_api, SIGNAL(toursSuggestLoaded(QNetworkReply*)), this, SLOT(updateFromApiReply(QNetworkReply*)));
}
