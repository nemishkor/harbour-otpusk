#ifndef TOUR_H
#define TOUR_H

#include <QObject>
#include <QString>
#include "offersmodel.h"

/**
 * Contains main information about hotel and one price (offer)
 */
class Tour
{
public:
    Tour(
            const int id,
            const QString &name,
            const QString &city,
            const QString &country,
            const double ratingAvarage,
            const int ratingCount,
            const bool isFirst,
            const QString stars,
            const QString photo,
            const Offer offer);

    int id() const;
    QString name() const;
    QString city() const;
    QString country() const;
    double ratingAvarage() const;
    int ratingCount() const;
    bool isFirst() const;
    QString stars() const;
    QString photo() const;
    const Offer *offer() const;

private:
    int m_id;
    QString m_name;
    QString m_city;
    QString m_country;
    double m_ratingAvarage;
    int m_ratingCount;
    // first item of page
    bool m_isFirst;
    QString m_stars;
    QString m_photo;
    const Offer m_offer;
};

#endif // TOUR_H
