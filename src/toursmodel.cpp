#include "toursmodel.h"
#include <QString>
#include <QHash>
#include <QAbstractListModel>
#include <QVariantMap>

ToursModel::ToursModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ToursModel::addTour(Tour tour)
{
    tours.append(tour);
}

QHash<int, QByteArray> ToursModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(NameRole, "name");
    return roles;
}

int ToursModel::rowCount(const QModelIndex &) const
{
    return tours.size();
}

QVariant ToursModel::data(const QModelIndex &index, int role) const
{

    const int row = index.row();
    if (row < 0 || row > tours.size()) {
        return QVariant();
    }

    const Tour tour = tours.at(row);
    switch (role) {
    case NameRole: return tour.name;
    }

    return QVariant(QString("null"));
}
