#include "tourmodel.h"

Tour::Tour(
        const QString &name,
        const QString &city,
        const QString &country,
        const QString &size)
    : m_name(name),
      m_city(city),
      m_country(country),
      m_size(size)
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

QString Tour::size() const
{
    return m_size;
}

TourModel::TourModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void TourModel::addTour(const Tour &tour)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_tours << tour;
    endInsertRows();
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
    else if (role == SizeRole)
        return tour.size();
    return QVariant();
}
QHash<int, QByteArray> TourModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CityRole] = "city";
    roles[CountryRole] = "country";
    roles[SizeRole] = "size";
    return roles;
}
