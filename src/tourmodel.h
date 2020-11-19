#ifndef ANIMALMODEL_H
#define ANIMALMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class Tour
{
public:
    Tour(
            const QString &name,
            const QString &city,
            const QString &country,
            const double ratingAvarage,
            const int ratingCount,
            const double priceUah,
            const double price,
            const QString currency);

    QString name() const;
    QString city() const;
    QString country() const;
    double ratingAvarage() const;
    int ratingCount() const;
    double priceUah() const;
    double price() const;
    QString currency() const;

private:
    QString m_name;
    QString m_city;
    QString m_country;
    double m_ratingAvarage;
    int m_ratingCount;
    double m_priceUah;
    double m_price;
    QString m_currency;
};

class TourModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TourRoles {
        NameRole = Qt::UserRole + 1,
        CityRole,
        CountryRole,
        RatingAvarageRole,
        RatingCountRole,
        PriceUahRole,
        PriceRole,
        CurrencyRole
    };

    TourModel(QObject *parent = 0);

    void addTour(const Tour &tour);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Tour> m_tours;
};


#endif // ANIMALMODEL_H


