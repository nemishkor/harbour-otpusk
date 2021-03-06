#include "tour.h"

Tour::Tour(
        const int id,
        const QString &name,
        const QString &city,
        const QString &country,
        const double ratingAvarage,
        const int ratingCount,
        const bool isFirst,
        const QString stars,
        const QString photo,
        const Offer offer)
    : m_id(id),
      m_name(name),
      m_city(city),
      m_country(country),
      m_ratingAvarage(ratingAvarage),
      m_ratingCount(ratingCount),
      m_isFirst(isFirst),
      m_stars(stars),
      m_photo(photo),
      m_offer(offer)
{
    qDebug("cunstruct tour");
}

int Tour::id() const
{
    return m_id;
}

QString Tour::name() const
{
    return m_name;
}

QString Tour::city() const
{
    return m_city;
}

QString Tour::country() const
{
    return m_country;
}

double Tour::ratingAvarage() const
{
    return m_ratingAvarage;
}

int Tour::ratingCount() const
{
    return m_ratingCount;
}

bool Tour::isFirst() const
{
    return m_isFirst;
}

QString Tour::stars() const
{
    return m_stars;
}

QString Tour::photo() const
{
    return m_photo;
}

const Offer *Tour::offer() const
{
    return &m_offer;
}
