#ifndef TOURSMODEL_H
#define TOURSMODEL_H

#include <QAbstractListModel>
#include "tour.h"

class ToursModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        NameRole = Qt::UserRole
    };

    explicit ToursModel(QObject *parent = nullptr);

    void addTour(Tour tour);

    virtual QHash<int,QByteArray> roleNames() const override;
    // Basic functionality:
    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<Tour> tours;
};

#endif // TOURSMODEL_H
