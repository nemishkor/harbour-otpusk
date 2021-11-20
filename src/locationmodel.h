#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H

#include <QAbstractListModel>
#include <QNetworkReply>
#include "api.h"

class Location
{
public:
    Location(const int id, const QString &name, const bool bold, const int weight):
        m_id(id),
        m_name(name),
        m_bold(bold),
        m_weight(weight){}
    QString name() const{
        return m_name;
    }
    int id() const{
        return m_id;
    }
    bool bold() const{
        return m_bold;
    }
    int weight() const{
        return m_weight;
    }

private:
    int m_id;
    QString m_name;
    bool m_bold;
    int m_weight;

};

class LocationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString networkError READ getNetworkError NOTIFY networkErrorChanged)

public:
    enum LocationRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        BoldRole
    };

    LocationModel(Api *api);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE void update(QString name);
    QString getNetworkError() const;

protected:
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &) const override;

private:
    QList<Location> mItems;
    Api *m_api;
    QString networkError;
    void setNetworkError(QString networkError);

private slots:
    void updateFromApiReply(QNetworkReply *reply);

signals:
    void networkErrorChanged();

};

#endif // LOCATIONMODEL_H
