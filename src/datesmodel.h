#ifndef DATESMODEL_H
#define DATESMODEL_H

#include <QAbstractItemModel>
#include "api.h"

class SearchDate{
public:
    SearchDate(QString date, QString length): mDate(date), mLength(length){}

    QString date() const{
        return mDate;
    }

    QString length() const{
        return mLength;
    }

private:
    QString mDate;
    QString mLength;

};

class SearchDatesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString networkError READ getNetworkError NOTIFY networkErrorChanged)

public:
    enum SearchDateRoles {
        DateRole = Qt::UserRole + 1,
        LengthRole
    };
    SearchDatesModel(QObject *parent = nullptr);
    SearchDatesModel(Api *api);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void update(int location);
    QString getNetworkError() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    Api *mApi;
    QList<SearchDate> mItems;
    QString networkError;

private slots:
    void updateFromApiReply(QNetworkReply *reply);

signals:
  void networkErrorChanged();
};

#endif // DATESMODEL_H
