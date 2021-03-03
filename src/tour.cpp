#include "tour.h"

Tour::Tour(
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
        const QString priceId)
    : m_id(id),
      m_name(name),
      m_city(city),
      m_country(country),
      m_ratingAvarage(ratingAvarage),
      m_ratingCount(ratingCount),
      m_priceUah(priceUah),
      m_price(price),
      m_currency(currency),
      m_isFirst(isFirst),
      m_stars(stars),
      m_photo(photo),
      m_priceId(priceId)
//    ,
//      m_offers(nullptr)
{
    qDebug("cunstruct tour");
}

//Tour::Tour(const Tour &tour) : QObject(), m_offers(tour.m_offers) {
//    m_id = tour.id();
//    m_name = tour.name();
//    m_city = tour.city();
//    m_country = tour.country();
//    m_ratingAvarage = tour.ratingAvarage();
//    m_ratingCount = tour.ratingCount();
//    m_priceUah = tour.priceUah();
//    m_price = tour.price();
//    m_currency = tour.currency();
//    m_isFirst = tour.isFirst();
//    m_stars = tour.stars();
//    m_photo = tour.photo();
//    qDebug("copy tour");
//}

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

double Tour::priceUah() const
{
    return m_priceUah;
}

double Tour::price() const
{
    return m_price;
}

QString Tour::currency() const
{
    return m_currency;
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

QString Tour::priceId() const
{
    return m_priceId;
}

//OffersModel* Tour::offers()
//{
//    return &m_offers;
//}
