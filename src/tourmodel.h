#ifndef ANIMALMODEL_H
#define ANIMALMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include "offersmodel.h"
#include "tour.h"

class TourModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum TourRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CityRole,
        CountryRole,
        RatingAvarageRole,
        RatingCountRole,
        IsFirstRole,
        StarsRole,
        PhotoRole,

        OfferIdRole,
        DateFromRole,
        DateToRole,
        RoomTypeRole,
        AdultsRole,
        ChildrenCountRole,
        ChildrenAgesRole,
        NightsRole,
        FoodTypeRole,
        RoomNameRole,
        PriceUahRole,
        PriceRole,
        CurrencyRole,
        TransportRole
    };

    TourModel(QObject *parent = 0);

    void addTour(Tour &tour);
    Q_INVOKABLE Tour *get(int index);
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


