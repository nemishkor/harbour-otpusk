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

QStringList SearchDatesModel::dates()
{
    return mDates;
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
    QJsonObject dates = json.object()["dates"].toObject();
    mDates.clear();
    mItems.clear();
    QJsonObject::const_iterator i;
    beginInsertRows(QModelIndex(), 0, dates.size());
    for (i = dates.constBegin(); i != dates.end(); ++i){
        QJsonObject result = (*i).toObject();
//        qDebug(date.toLatin1());
        mItems.append(SearchDate(i.key(), i.value().toString()));
        mDates.append(i.key());
    }
    endInsertRows();
    qDebug(QString::number(mItems.size()).append(" dates appended").toLatin1());
    emit countChanged();
    emit datesChanged();
}
