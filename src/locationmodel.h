#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H

#include <QAbstractListModel>
#include <QNetworkReply>
#include "api.h"

class Location
{
public:
    Location(const int id, const QString &name): m_id(id), m_name(name){}
    QString name() const{
        return m_name;
    }
    int id() const{
        return m_id;
    }

private:
    int m_id;
    QString m_name;

};

class LocationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString networkError READ getNetworkError NOTIFY networkErrorChanged)

public:
    enum LocationRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    LocationModel(Api *api);

    int rowCount(const QModelIndex & = QModelIndex()) const override{
        return mItems.size();
    }

    QVariant data(const QModelIndex &index, int role) const override{
        if (index.row() < 0 || index.row() >= mItems.count())
            return QVariant();
        const Location &location = mItems[index.row()];
        if(role == IdRole)
            return location.id();
        if(role == NameRole)
            return location.name();
        return QVariant();
    }

    Q_INVOKABLE void update(QString name) {
        setNetworkError(QString(""));
        m_api->toursSuggest(name);
    }

    QString getNetworkError() const{
        return networkError;
    }

public slots:
//  void insert(const Location &item){
//    beginInsertRows(QModelIndex(), 0, 0);
//    mItems << item;
//    endInsertRows();
//  }

//  void remove(Location *item){
//    for (int i = 0; i < mItems.size(); ++i) {
//      if (&mItems.at(i) == item) {
//        beginRemoveRows(QModelIndex(), i, i);
//        mItems.removeAt(i);
//        endRemoveRows();
//        break;
//      }
//    }
//  }

protected:
  QHash<int, QByteArray> roleNames() const override{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
  }

  Qt::ItemFlags flags(const QModelIndex &) const override{
      return Qt::ItemIsEditable;
  }

private:
  QList<Location> mItems;
  Api *m_api;
  QString networkError;
  void setNetworkError(QString networkError);

private slots:

  void updateFromApiReply(QNetworkReply *reply){
      if(reply->error() == QNetworkReply::OperationCanceledError){
          qDebug("Request canceled");
          return;
      }
      if(reply->error() != QNetworkReply::NoError){
          qDebug("Got network error");
          setNetworkError(reply->errorString());
          return;
      }
      QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
//      qDebug(qPrintable(json.toJson()));
      QJsonObject response = json.object()["response"].toObject();
      QJsonObject::const_iterator i;
      mItems.clear();
      beginInsertRows(QModelIndex(), 0, response.size());
      for (i = response.constBegin(); i != response.end(); ++i){
          QJsonObject result = (*i).toObject();
          mItems.append(Location(result["id"].toString().toInt(), result["name"].toString()));
      }
//      qDebug("iserted " + QString::number(mItems.count()).toLatin1() + " locations");
      endInsertRows();
  }

signals:
  void networkErrorChanged();

};

#endif // LOCATIONMODEL_H
