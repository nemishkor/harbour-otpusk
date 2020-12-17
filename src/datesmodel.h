#ifndef DATESMODEL_H
#define DATESMODEL_H

#include <QAbstractItemModel>
#include "api.h"

class SearchDate{
public:
    SearchDate(QString date, QStringList lengths): mDate(date), mLengths(lengths){}

    QString date() const{
        return mDate;
    }

    QStringList lengths() const{
        return mLengths;
    }

private:
    QString mDate;
    QStringList mLengths;

};

class SearchDatesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString networkError READ getNetworkError NOTIFY networkErrorChanged)
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(QStringList dates READ dates NOTIFY datesChanged)
    Q_PROPERTY(QStringList lengths READ lengths NOTIFY lengthsChanged)

public:
    enum SearchDateRoles {
        DateRole = Qt::UserRole + 1,
        LengthsRole
    };
    SearchDatesModel(QObject *parent = nullptr);
    SearchDatesModel(Api *api);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void update(int location);
    Q_INVOKABLE void selectDate(QString date);
    QString getNetworkError() const;
    QStringList dates();
    QStringList lengths() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    Api *mApi;
    QList<SearchDate> mItems;
    QStringList mDates;
    QStringList mLengths;
    QString networkError;

private slots:
    void updateFromApiReply(QNetworkReply *reply);
    void cppSlot(const QString &msg) {
        qDebug() << "Called the C++ slot with message:" << msg;
    }

signals:
  void networkErrorChanged();
  void countChanged();
  void datesChanged();
  void lengthsChanged();
};

#endif // DATESMODEL_H
