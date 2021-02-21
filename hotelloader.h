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
#include "api.h"

class Hotel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString city READ city NOTIFY cityChanged)
    Q_PROPERTY(QString country READ country NOTIFY countryChanged)
    Q_PROPERTY(double ratingAvarage READ ratingAvarage NOTIFY ratingAvarageChanged)
    Q_PROPERTY(int ratingCount READ ratingCount NOTIFY ratingCountChanged)
    Q_PROPERTY(QString stars READ stars NOTIFY starsChanged)
    Q_PROPERTY(QStringList photos READ photos NOTIFY photosChanged)
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

private:
    QString m_name;
    QString m_city;
    QString m_country;
    double m_ratingAvarage;
    int m_ratingCount;
    QString m_stars;
    QStringList m_photos;

signals:
    void nameChanged();
    void cityChanged();
    void countryChanged();
    void ratingAvarageChanged();
    void ratingCountChanged();
    void priceUahChanged();
    void priceChanged();
    void currencyChanged();
    void starsChanged();
    void photosChanged();
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
