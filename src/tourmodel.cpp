#include "tourmodel.h"

Tour::Tour(
        const QString &name,
        const QString &city,
        const QString &country,
        const double ratingAvarage,
        const int ratingCount,
        const double priceUah,
        const double price,
        const QString currency,
        const bool isFirst)
    : m_name(name),
      m_city(city),
      m_country(country),
      m_ratingAvarage(ratingAvarage),
      m_ratingCount(ratingCount),
      m_priceUah(priceUah),
      m_price(price),
      m_currency(currency),
      m_isFirst(isFirst)
{
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

TourModel::TourModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void TourModel::addTour(const Tour &tour)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_tours << tour;
    if(tour.isFirst()){
        qDebug("is first");
        m_firstItemIndexOfLastPage = m_tours.count() - 1;
    }
    endInsertRows();
    emit countChanged();
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
    if (role == PriceUahRole)
        return tour.priceUah();
    if (role == PriceRole)
        return tour.price();
    if (role == CurrencyRole)
        return tour.currency();
    if (role == IsFirstRole)
        return tour.isFirst();
    return QVariant();
}
QHash<int, QByteArray> TourModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CityRole] = "city";
    roles[CountryRole] = "country";
    roles[RatingAvarageRole] = "ratingAvarage";
    roles[RatingCountRole] = "ratingCount";
    roles[PriceUahRole] = "priceUah";
    roles[PriceRole] = "price";
    roles[CurrencyRole] = "currency";
    roles[IsFirstRole] = "isFirst";
    return roles;
}
