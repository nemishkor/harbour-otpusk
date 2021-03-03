#ifndef TOUR_H
#define TOUR_H

#include <QObject>
#include <QString>
#include "offersmodel.h"

class Tour
//        : public QObject
{
//    Q_OBJECT
//    Q_PROPERTY(int id READ id)
public:
    Tour(
            const int id,
            const QString &name,
            const QString &city,
            const QString &country,
            const double ratingAvarage,
            const int ratingCount,
            const double priceUah,
            const double price,
            const QString currency,
            const bool isFirst,
            const QString stars,
            const QString photo,
            const QString priceId);
//    Tour(const Tour &tour);

    int id() const;
    QString name() const;
    QString city() const;
    QString country() const;
    double ratingAvarage() const;
    int ratingCount() const;
    double priceUah() const;
    double price() const;
    QString currency() const;
    bool isFirst() const;
    QString stars() const;
    QString photo() const;
    QString priceId() const;
//    Q_INVOKABLE OffersModel* offers();

private:
    int m_id;
    QString m_name;
    QString m_city;
    QString m_country;
    double m_ratingAvarage;
    int m_ratingCount;
    double m_priceUah;
    double m_price;
    QString m_currency;
    // first item of page
    bool m_isFirst;
    QString m_stars;
    QString m_photo;
    QString m_priceId;
//    OffersModel m_offers;
};

#endif // TOUR_H
