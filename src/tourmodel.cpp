#include "tourmodel.h"

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
        const QString photo)
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
      m_offers(nullptr)
{
    qDebug("cunstruct tour");
}

Tour::Tour(const Tour &tour) : QObject(), m_offers(tour.m_offers) {
    m_id = tour.id();
    m_name = tour.name();
    m_city = tour.city();
    m_country = tour.country();
    m_ratingAvarage = tour.ratingAvarage();
    m_ratingCount = tour.ratingCount();
    m_priceUah = tour.priceUah();
    m_price = tour.price();
    m_currency = tour.currency();
    m_isFirst = tour.isFirst();
    m_stars = tour.stars();
    m_photo = tour.photo();
    qDebug("copy tour");
}

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

OffersModel* Tour::offers()
{
    return &m_offers;
}

TourModel::TourModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void TourModel::addTour(Tour &tour)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    qDebug("before append");
//    qDebug(QString("0x%1").arg((quintptr)&tour,
//                               QT_POINTER_SIZE * 2, 16, QChar('0')).toLatin1());
    m_tours << tour;

//    qDebug("in list");
//    qDebug(QString("0x%1").arg((quintptr)&m_tours.last(),
//                               QT_POINTER_SIZE * 2, 16, QChar('0')).toLatin1());

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
    if (role == PriceUahRole)
        return tour.priceUah();
    if (role == PriceRole)
        return tour.price();
    if (role == CurrencyRole)
        return tour.currency();
    if (role == IsFirstRole)
        return tour.isFirst();
    if (role == StarsRole)
        return tour.stars();
    if (role == PhotoRole)
        return tour.photo();
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
    roles[PriceUahRole] = "priceUah";
    roles[PriceRole] = "price";
    roles[CurrencyRole] = "currency";
    roles[IsFirstRole] = "isFirst";
    roles[StarsRole] = "stars";
    roles[PhotoRole] = "photo";
    return roles;
}
