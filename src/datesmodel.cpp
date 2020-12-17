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
    if(role == SearchDateRoles::LengthsRole){
        return searchDate.lengths();
    }

    return QVariant();
}

void SearchDatesModel::update(int location)
{

    mDates.clear();
    mItems.clear();

    beginInsertRows(QModelIndex(), 0, 2);

    mItems.append(SearchDate("2020-12-18", QString("3,5").split(QChar(','))));
    mDates.append("2020-12-18");

    mItems.append(SearchDate("2020-12-20", QString("8,9").split(QChar(','))));
    mDates.append("2020-12-20");

    endInsertRows();
    qDebug(QString::number(mItems.size()).append(" dates appended").toLatin1());
    emit countChanged();
    emit datesChanged();

    return;
    networkError = QString("");
    emit networkErrorChanged();
    mApi->dates(location);
}

void SearchDatesModel::selectDate(QString date)
{
    qDebug(QString(date).prepend("selected date ").toLatin1());
    QList<SearchDate>::iterator i;
    for (i = mItems.begin(); i != mItems.end(); ++i){
        qDebug(QString(i->date()).prepend("iterator ").toLatin1());
        if(i->date() == date){
            mLengths = i->lengths();
            qDebug("found lengths items: " + QString::number(mLengths.size()).toLatin1());
            qDebug(mLengths.join(", ").toLatin1());
            emit lengthsChanged();
            return;
        }
    }
}

QString SearchDatesModel::getNetworkError() const
{
    return networkError;
}

QStringList SearchDatesModel::dates()
{
    return mDates;
}

QStringList SearchDatesModel::lengths() const
{
    return mLengths;
}


QHash<int, QByteArray> SearchDatesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DateRole] = "date";
    roles[LengthsRole] = "length";
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
        mItems.append(SearchDate(i.key(), i.value().toString().split(QChar(','))));
        mDates.append(i.key());
    }
    endInsertRows();
    qDebug(QString::number(mItems.size()).append(" dates appended").toLatin1());
    emit countChanged();
    emit datesChanged();
}
