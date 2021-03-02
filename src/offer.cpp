#include "offer.h"

Offer::Offer(
        const QString id,
        const QString &last,
        const int tourId,
        const QStringList &included,
        const QString &dateFrom,
        const QString &dateTo,
        const QString &roomType,
        const int adults,
        const int childrenCount,
        const QString &childrenAges,
        const int nights,
        const QString &foodType,
        const QString &roomName,
        const double price,
        const double priceUah,
        const QString &currency,
        const QString &transport)
    : m_id(id),
      m_last(last),
      m_tourId(tourId),
      m_included(included),
      m_dateFrom(dateFrom),
      m_dateTo(dateTo),
      m_roomType(roomType),
      m_adults(adults),
      m_childrenCount(childrenCount),
      m_childrenAges(childrenAges),
      m_nights(nights),
      m_foodType(foodType),
      m_roomName(roomName),
      m_price(price),
      m_priceUah(priceUah),
      m_currency(currency),
      m_transport(transport){

}

QString Offer::id() const{
    return m_id;
}

QString Offer::last() const{
    return m_last;
}

int Offer::tourId() const{
    return m_tourId;
}

QStringList Offer::included() const{
    return m_included;
}

QString Offer::dateFrom() const{
    return m_dateFrom;
}

QString Offer::dateTo() const{
    return m_dateTo;
}

QString Offer::roomType() const{
    return m_roomType;
}

int Offer::adults() const{
    return m_adults;
}

int Offer::childrenCount() const{
    return m_childrenCount;
}

QString Offer::childrenAges() const{
    return m_childrenAges;
}

int Offer::nights() const{
    return m_nights;
}

QString Offer::foodType() const{
    return m_foodType;
}

QString Offer::roomName() const{
    return m_roomName;
}

double Offer::price() const{
    return m_price;
}

double Offer::priceUah() const{
    return m_priceUah;
}

QString Offer::currency() const{
    return m_currency;
}

QString Offer::transport() const{
    return m_transport;
}
