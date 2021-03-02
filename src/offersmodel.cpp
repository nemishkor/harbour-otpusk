#include "offersmodel.h"

OffersModel::OffersModel(QObject *parent) : QAbstractListModel(parent), m_items()
{
}

OffersModel::OffersModel(const OffersModel &offersModel)
    : QAbstractListModel(), m_items()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << offersModel.m_items;
    endInsertRows();
}

void OffersModel::addOffer(Offer offer)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << offer;
    endInsertRows();
}

void OffersModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_items.clear();
    endRemoveRows();
}

int OffersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant OffersModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return QVariant();

    const Offer &item = m_items[index.row()];
    if (role == IdRole)
        return item.id();
    if (role == LastRole)
        return item.last();
    if (role == TourIdRole)
        return item.tourId();
    if (role == IncludedRole)
        return item.included();
    if (role == DateFromRole)
        return item.dateFrom();
    if (role == DateToRole)
        return item.dateTo();
    if (role == RoomTypeRole)
        return item.roomType();
    if (role == AdultsRole)
        return item.adults();
    if (role == ChildrenCountRole)
        return item.childrenCount();
    if (role == ChildrenAgesRole)
        return item.childrenAges();
    if (role == NightsRole)
        return item.nights();
    if (role == FoodTypeRole)
        return item.foodType();
    if (role == RoomNameRole)
        return item.roomName();
    if (role == PriceRole)
        return item.price();
    if (role == PriceUahRole)
        return item.priceUah();
    if (role == CurrencyRole)
        return item.currency();
    if (role == TransportRole)
        return item.transport();
    return QVariant();
}

QHash<int, QByteArray> OffersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LastRole] = "last";
    roles[TourIdRole] = "tourId";
    roles[IncludedRole] = "included";
    roles[DateFromRole] = "dateFrom";
    roles[DateToRole] = "dateTo";
    roles[RoomTypeRole] = "roomType";
    roles[AdultsRole] = "adults";
    roles[ChildrenCountRole] = "childrenCount";
    roles[ChildrenAgesRole] = "childrenAges";
    roles[NightsRole] = "nights";
    roles[FoodTypeRole] = "foodType";
    roles[RoomNameRole] = "roomName";
    roles[PriceUahRole] = "priceUah";
    roles[PriceRole] = "price";
    roles[CurrencyRole] = "currency";
    roles[TransportRole] = "transport";
    return roles;
}
