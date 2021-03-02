#ifndef OFFERSMODEL_H
#define OFFERSMODEL_H

#include <QAbstractListModel>
#include "offer.h"

class OffersModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum OfferRoles {
        IdRole = Qt::UserRole + 1,
        LastRole,
        TourIdRole,
        IncludedRole,
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
    OffersModel(QObject *parent = nullptr);
    OffersModel(const OffersModel &offersModel);

    void addOffer(Offer offer);
    void clear();
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Offer> m_items;
};

#endif // OFFERSMODEL_H
