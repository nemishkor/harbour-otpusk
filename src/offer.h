#ifndef OFFER_H
#define OFFER_H

#include <QString>
#include <QStringList>

class Offer
{
public:
    Offer(
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
            const QString &transport);

    QString id() const;
    QString last() const;
    int tourId() const;
    QStringList included() const;
    QString dateFrom() const;
    QString dateTo() const;
    QString roomType() const;
    int adults() const;
    int childrenCount() const;
    QString childrenAges() const;
    int nights() const;
    QString foodType() const;
    QString roomName() const;
    double price() const;
    double priceUah() const;
    QString currency() const;
    QString transport() const;

private:
    QString m_id;
    QString m_last;
    int m_tourId;
    QStringList m_included;
    QString m_dateFrom;
    QString m_dateTo;
    QString m_roomType;
    int m_adults;
    int m_childrenCount;
    QString m_childrenAges;
    int m_nights;
    QString m_foodType;
    QString m_roomName;
    double m_price;
    double m_priceUah;
    QString m_currency;
    QString m_transport;

};

#endif // OFFER_H
