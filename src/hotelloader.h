#ifndef HOTELLOADER_H
#define HOTELLOADER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QJsonDocument>
#include <QAbstractListModel>
#include "api.h"

class RoomService
{
public:
    RoomService(QString name, bool all, QString id, QString title)
        :m_name(name), m_all(all), m_id(id), m_title(title){}
    QString name() const{ return m_name; }
    bool all() const{ return m_all; }
    QString id() const{ return m_id; }
    QString title() const{ return m_title; }
private:
    QString m_name;
    bool m_all;
    QString m_id;
    QString m_title;
};

class RoomServicesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RoomServiceRoles {
        NameRole = Qt::UserRole + 1,
        IdRole,
        AllRole,
        TitleRole
    };
    RoomServicesModel(QObject *parent = 0){
        Q_UNUSED(parent);
    }
    void addRoomService(const RoomService &roomService){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_items << roomService;
        endInsertRows();
    }
    int rowCount(const QModelIndex & parent = QModelIndex()) const{
        Q_UNUSED(parent);
        return m_items.count();
    }
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const{
        if (index.row() < 0 || index.row() >= m_items.count())
            return QVariant();

        const RoomService &roomService = m_items[index.row()];
        if (role == NameRole)
            return roomService.name();
        if (role == IdRole)
            return roomService.id();
        if (role == AllRole)
            return roomService.all();
        if (role == TitleRole)
            return roomService.title();
        return QVariant();
    }
    void clear() {
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        m_items.clear();
        endRemoveRows();
    }

protected:
    QHash<int, QByteArray> roleNames() const{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[IdRole] = "id";
        roles[AllRole] = "all";
        roles[TitleRole] = "title";
        return roles;
    }
private:
    QList<RoomService> m_items;
};


class HotelService
{
public:
    HotelService(QString name, QString value, QString id, QString title)
        :m_name(name), m_value(value), m_id(id), m_title(title){}
    QString name() const{ return m_name; }
    QString value() const{ return m_value; }
    QString id() const{ return m_id; }
    QString title() const{ return m_title; }
private:
    QString m_name;
    QString m_value;
    QString m_id;
    QString m_title;
};

class HotelServicesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RoomServiceRoles {
        NameRole = Qt::UserRole + 1,
        IdRole,
        ValueRole,
        TitleRole
    };
    HotelServicesModel(QObject *parent = 0){
        Q_UNUSED(parent);
    }
    void addHotelService(const HotelService &hotelService){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_items << hotelService;
        endInsertRows();
    }
    int rowCount(const QModelIndex & parent = QModelIndex()) const{
        Q_UNUSED(parent);
        return m_items.count();
    }
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const{
        if (index.row() < 0 || index.row() >= m_items.count())
            return QVariant();

        const HotelService &hotelService = m_items[index.row()];
        if (role == NameRole)
            return hotelService.name();
        if (role == IdRole)
            return hotelService.id();
        if (role == ValueRole)
            return hotelService.value();
        if (role == TitleRole)
            return hotelService.title();
        return QVariant();
    }
    void clear() {
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        m_items.clear();
        endRemoveRows();
    }

protected:
    QHash<int, QByteArray> roleNames() const{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[IdRole] = "id";
        roles[ValueRole] = "value";
        roles[TitleRole] = "title";
        return roles;
    }
private:
    QList<HotelService> m_items;
};


class HotelRating
{
public:
    HotelRating(QString name, double vote, int count)
        :m_name(name), m_vote(vote), m_count(count){}
    QString name() const{ return m_name; }
    double vote() const{ return m_vote; }
    int count() const{ return m_count; }
private:
    QString m_name;
    double m_vote;
    int m_count;
};

class HotelRatingsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RoomServiceRoles {
        NameRole = Qt::UserRole + 1,
        VoteRole,
        CountRole
    };
    HotelRatingsModel(QObject *parent = 0){
        Q_UNUSED(parent);
    }
    void addHotelRating(const HotelRating &hotelRating){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_items << hotelRating;
        endInsertRows();
    }
    int rowCount(const QModelIndex & parent = QModelIndex()) const{
        Q_UNUSED(parent);
        return m_items.count();
    }
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const{
        if (index.row() < 0 || index.row() >= m_items.count())
            return QVariant();

        const HotelRating &hotelRating = m_items[index.row()];
        if (role == NameRole)
            return hotelRating.name();
        if (role == VoteRole)
            return hotelRating.vote();
        if (role == CountRole)
            return hotelRating.count();
        return QVariant();
    }
    void clear() {
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        m_items.clear();
        endRemoveRows();
    }
protected:
    QHash<int, QByteArray> roleNames() const{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[VoteRole] = "vote";
        roles[CountRole] = "count";
        return roles;
    }
private:
    QList<HotelRating> m_items;
};

class Hotel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QString distance READ distance NOTIFY distanceChanged)
    Q_PROPERTY(QString city READ city NOTIFY cityChanged)
    Q_PROPERTY(QString country READ country NOTIFY countryChanged)
    Q_PROPERTY(double ratingAvarage READ ratingAvarage NOTIFY ratingAvarageChanged)
    Q_PROPERTY(int ratingCount READ ratingCount NOTIFY ratingCountChanged)
    Q_PROPERTY(QString stars READ stars NOTIFY starsChanged)
    Q_PROPERTY(QStringList photos READ photos NOTIFY photosChanged)
    Q_PROPERTY(RoomServicesModel* roomServices READ roomServices NOTIFY roomServicesChanged)
    Q_PROPERTY(HotelServicesModel* hotelServices READ hotelServices NOTIFY hotelServicesChanged)
    Q_PROPERTY(HotelServicesModel* forChildrenServices READ forChildrenServices NOTIFY forChildrenServicesChanged)
    Q_PROPERTY(HotelServicesModel* beachServices READ beachServices NOTIFY beachServicesChanged)
    Q_PROPERTY(HotelServicesModel* activitiesServices READ activitiesServices NOTIFY activitiesServicesChanged)
    Q_PROPERTY(HotelRatingsModel* hotelRatings READ hotelRatings NOTIFY hotelRatingsChanged)
public:
    Hotel(){}

    QString name() const{
        return m_name;
    }
    void setName(QString name){
        if(name != m_name){
            m_name = name;
            emit nameChanged();
        }
    }
    QString description() const{
        return m_description;
    }
    void setDescription(QString description){
        if(description != m_description){
            m_description = description;
            emit descriptionChanged();
        }
    }
    QString distance() const{
        return m_distance;
    }
    void setDistance(QString distance){
        if(distance != m_distance){
            m_distance = distance;
            emit distanceChanged();
        }
    }
    QString city() const{
        return m_city;
    }
    void setCity(QString city){
        if(city != m_city){
            m_city = city;
            emit cityChanged();
        }
    }
    QString country() const{
        return m_country;
    }
    void setCountry(QString country){
        if(country != m_country){
            m_country = country;
            emit countryChanged();
        }
    }
    double ratingAvarage() const{
        return m_ratingAvarage;
    }
    void setRatingAvarage(double ratingAvarage){
        if(ratingAvarage != m_ratingAvarage){
            m_ratingAvarage = ratingAvarage;
            emit ratingAvarageChanged();
        }
    }
    int ratingCount() const{
        return m_ratingCount;
    }
    void setRatingCount(int ratingCount){
        if(ratingCount != m_ratingCount){
            m_ratingCount = ratingCount;
            emit ratingCountChanged();
        }
    }
    QString stars() const{
        return m_stars;
    }
    void setStars(QString stars){
        if(m_stars != stars){
            m_stars = stars;
            emit starsChanged();
        }
    }
    QStringList photos() const{
        return m_photos;
    }
    void setPhotos(QStringList photos){
        m_photos = photos;
        emit photosChanged();
    }
    RoomServicesModel *roomServices(){
        return &m_roomServices;
    }
    HotelServicesModel *hotelServices(){
        return &m_hotelServices;
    }
    HotelServicesModel *forChildrenServices(){
        return &m_forChildrenServices;
    }
    HotelServicesModel *beachServices(){
        return &m_beachServices;
    }
    HotelServicesModel *activitiesServices(){
        return &m_activitiesServices;
    }
    HotelRatingsModel *hotelRatings(){
        return &m_hotelRatings;
    }

private:
    QString m_name;
    QString m_description;
    QString m_distance;
    QString m_city;
    QString m_country;
    double m_ratingAvarage;
    int m_ratingCount;
    QString m_stars;
    QStringList m_photos;
    RoomServicesModel m_roomServices;
    HotelServicesModel m_hotelServices;
    HotelServicesModel m_forChildrenServices;
    HotelServicesModel m_beachServices;
    HotelServicesModel m_activitiesServices;
    HotelRatingsModel m_hotelRatings;

signals:
    void nameChanged();
    void descriptionChanged();
    void distanceChanged();
    void cityChanged();
    void countryChanged();
    void ratingAvarageChanged();
    void ratingCountChanged();
    void priceUahChanged();
    void priceChanged();
    void currencyChanged();
    void starsChanged();
    void photosChanged();
    void roomServicesChanged();
    void hotelServicesChanged();
    void forChildrenServicesChanged();
    void beachServicesChanged();
    void activitiesServicesChanged();
    void hotelRatingsChanged();
};

class HotelLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ getLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool replyFailed READ isReplyFailed NOTIFY isReplyFailedChanged)
    Q_PROPERTY(QString replyErrorText READ getReplyErrorText NOTIFY replyErrorTextChanged)
public:
    explicit HotelLoader(Api* api, Hotel* hotel);

    Q_INVOKABLE void load(int id);
    bool getLoading() const;
    void setLoading(bool loading);
    bool isReplyFailed() const;
    void setReplyFailed(bool isReplyFailed);
    QString getReplyErrorText() const;
    void setReplyErrorText(QString replyErrorText);

private:
    Api* api;
    Hotel* hotel;
    bool loading = false;
    bool replyFailed = false;
    QString replyErrorText;

private slots:
    void handleReply(QNetworkReply *reply);

signals:
    void loadingChanged();
    void isReplyFailedChanged();
    void replyErrorTextChanged();

};

#endif // HOTELLOADER_H
