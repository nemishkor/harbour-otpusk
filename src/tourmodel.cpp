#include "tourmodel.h"

TourModel::TourModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void TourModel::addTour(Tour &tour)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_tours << tour;

    if(tour.isFirst()){
//        qDebug("is first");
        m_firstItemIndexOfLastPage = m_tours.count() - 1;
    }
    endInsertRows();
    emit countChanged();
}

Tour *TourModel::get(int index)
{
    Tour &tour = m_tours[index];
    return &tour;
}

void TourModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_tours.clear();
    m_firstItemIndexOfLastPage = 0;
    endRemoveRows();
    emit countChanged();
}

int TourModel::firstItemIndexOfLastPage()
{
    return m_firstItemIndexOfLastPage;
}

int TourModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_tours.count();
}

QVariant TourModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_tours.count())
        return QVariant();

    const Tour &tour = m_tours[index.row()];
    if (role == IdRole)
        return tour.id();
    if (role == NameRole)
        return tour.name();
    if (role == CityRole)
        return tour.city();
    if (role == CountryRole)
        return tour.country();
    if (role == RatingAvarageRole)
        return tour.ratingAvarage();
    if (role == RatingCountRole)
        return tour.ratingCount();
    if (role == IsFirstRole)
        return tour.isFirst();
    if (role == StarsRole)
        return tour.stars();
    if (role == PhotoRole)
        return tour.photo();

    if (role == OfferIdRole)
        return tour.offer()->id();
    if (role == DateFromRole)
        return tour.offer()->dateFrom();
    if (role == DateToRole)
        return tour.offer()->dateTo();
    if (role == RoomTypeRole)
        return tour.offer()->roomType();
    if (role == AdultsRole)
        return tour.offer()->adults();
    if (role == ChildrenCountRole)
        return tour.offer()->childrenCount();
    if (role == ChildrenAgesRole)
        return tour.offer()->childrenAges();
    if (role == NightsRole)
        return tour.offer()->nights();
    if (role == FoodTypeRole)
        return tour.offer()->foodType();
    if (role == RoomNameRole)
        return tour.offer()->roomName();
    if (role == PriceUahRole)
        return tour.offer()->priceUah();
    if (role == PriceRole)
        return tour.offer()->price();
    if (role == CurrencyRole)
        return tour.offer()->currency();
    if (role == TransportRole)
        return tour.offer()->transport();

    return QVariant();
}
QHash<int, QByteArray> TourModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[CityRole] = "city";
    roles[CountryRole] = "country";
    roles[RatingAvarageRole] = "ratingAvarage";
    roles[RatingCountRole] = "ratingCount";
    roles[IsFirstRole] = "isFirst";
    roles[StarsRole] = "stars";
    roles[PhotoRole] = "photo";

    roles[OfferIdRole] = "offerId";
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
