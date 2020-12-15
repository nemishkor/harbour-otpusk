#include "datesmodel.h"

SearchDatesModel::SearchDatesModel(Api *api)
    : mApi(api)
{
    connect(mApi, SIGNAL(datesLoaded(QNetworkReply*)), this, SLOT(updateFromApiReply(QNetworkReply*)));
}

int SearchDatesModel::rowCount(const QModelIndex &) const
{
    return mItems.size();
}

QVariant SearchDatesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mItems.size())
        return QVariant();

    const SearchDate &searchDate = mItems[index.row()];

    if(role == SearchDateRoles::DateRole){
        return searchDate.date();
    }
    if(role == SearchDateRoles::LengthRole){
        return searchDate.length();
    }

    return QVariant();
}

void SearchDatesModel::update(int location)
{
    networkError = QString("");
    emit networkErrorChanged();
    mApi->dates(location);
}

QString SearchDatesModel::getNetworkError() const
{
    return networkError;
}


QHash<int, QByteArray> SearchDatesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DateRole] = "date";
    roles[LengthRole] = "role";
    return roles;
}

void SearchDatesModel::updateFromApiReply(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::OperationCanceledError){
        qDebug("Request canceled");
        return;
    }
    if(reply->error() != QNetworkReply::NoError){
        qDebug("Got network error");
        networkError = reply->errorString();
        emit networkErrorChanged();
        return;
    }
    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    qDebug(qPrintable(json.toJson()));
    QJsonObject response = json.object()["response"].toObject();
//    QJsonObject::const_iterator i;
//    mItems.clear();
//    beginInsertRows(QModelIndex(), 0, response.size());
//    for (i = response.constBegin(); i != response.end(); ++i){
//        QJsonObject result = (*i).toObject();
//        qDebug("append item");
//        mItems.append(SearchDate(result["id"].toString().toInt(), result["name"].toString()));
//    }
//      qDebug("iserted " + QString::number(mItems.count()).toLatin1() + " locations");
//    endInsertRows();
}
