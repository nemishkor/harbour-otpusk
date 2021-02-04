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
            const QString currency,
            const bool isFirst,
            const QString stars,
            const QString photo);

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

private:
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
};

class TourModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum TourRoles {
        NameRole = Qt::UserRole + 1,
        CityRole,
        CountryRole,
        RatingAvarageRole,
        RatingCountRole,
        PriceUahRole,
        PriceRole,
        CurrencyRole,
        IsFirstRole,
        StarsRole,
        PhotoRole
    };

    TourModel(QObject *parent = 0);

    void addTour(const Tour &tour);

    Q_INVOKABLE void clear();
    Q_INVOKABLE int firstItemIndexOfLastPage();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Tour> m_tours;
    int m_firstItemIndexOfLastPage = 0;

signals:
    void countChanged();
};


#endif // ANIMALMODEL_H


