#include "locationmodel.h"

LocationModel::LocationModel(Api *api): m_api(api){
    connect(m_api, SIGNAL(toursSuggestLoaded(QNetworkReply*)), this, SLOT(updateFromApiReply(QNetworkReply*)));
}

int LocationModel::rowCount(const QModelIndex &) const{
    return mItems.size();
}

QVariant LocationModel::data(const QModelIndex &index, int role) const{
    if (index.row() < 0 || index.row() >= mItems.count())
        return QVariant();
    const Location &location = mItems[index.row()];
    if(role == IdRole)
        return location.id();
    if(role == NameRole)
        return location.name();
    if(role == BoldRole)
        return location.bold();
    if(role == UahRole)
        return location.uah();
    return QVariant();
}

void LocationModel::update(QString name) {
    setNetworkError(QString(""));
    m_api->toursSuggest(name);
}

QString LocationModel::getNetworkError() const{
    return networkError;
}

QHash<int, QByteArray> LocationModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[BoldRole] = "bold";
    roles[UahRole] = "uah";
    return roles;
}

Qt::ItemFlags LocationModel::flags(const QModelIndex &) const{
    return Qt::ItemIsEditable;
}

void LocationModel::setNetworkError(QString networkError)
{
    if(QString::compare(this->networkError, networkError) == 0){
        return;
    }
    this->networkError = networkError;
    emit networkErrorChanged();
}

void LocationModel::updateFromApiReply(QNetworkReply *reply){
    if(reply->error() == QNetworkReply::OperationCanceledError){
        qDebug("Request canceled");
        return;
    }
    if(reply->error() != QNetworkReply::NoError){
        qDebug("Got network error");
        setNetworkError(reply->errorString());
        return;
    }

    beginRemoveRows(QModelIndex(), 0, mItems.size() - 1);
    mItems.clear();
    endRemoveRows();

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    //qDebug(qPrintable(json.toJson()));
    QJsonObject response = json.object()["response"].toObject();
    QJsonObject::const_iterator i;
    QList<Location>::iterator listIterator;
    bool added;
    beginInsertRows(QModelIndex(), 0, response.size() - 1);
    for (i = response.constBegin(); i != response.end(); ++i){
        added = false;
        QJsonObject result = (*i).toObject();
        const Location location(
            result["id"].toString().toInt(),
            result["name"].toString(),
            result["bold"].toString() == "1",
            result["weight"].toInt(),
            QString::number((int)result["uah"].toString().toFloat() / 1000)
        );
        if(location.weight() > 0){
            for (listIterator = mItems.begin(); listIterator != mItems.end(); ++listIterator){
                if(location.weight() > (*listIterator).weight()){
                    mItems.insert(listIterator, location);
                    added = true;
                    break;
                }
            }
        }
        if(!added){
            mItems.append(location);
        }
    }
    //      qDebug("iserted " + QString::number(mItems.count()).toLatin1() + " locations");
    endInsertRows();
}
