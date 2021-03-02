#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <QObject>

class SearchParameters : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int locationId READ getLocationId WRITE setLocationId)
    Q_PROPERTY(int fromCityId READ getFromCityId WRITE setFromCityId)
    Q_PROPERTY(QString startDate READ getStartDate WRITE setStartDate)
    Q_PROPERTY(QString endDate READ getEndDate WRITE setEndDate)
    Q_PROPERTY(int length READ getLength WRITE setLength)
    Q_PROPERTY(int adults READ getAdults WRITE setAdults)
    Q_PROPERTY(QStringList children READ getChildren WRITE setChildren)
public:
    explicit SearchParameters(QObject *parent = nullptr);

    int getLocationId() const;
    void setLocationId(int value);
    int getFromCityId() const;
    void setFromCityId(int value);
    QString getStartDate() const;
    void setStartDate(const QString &value);
    QString getEndDate() const;
    void setEndDate(const QString &value);
    int getLength() const;
    void setLength(int value);
    int getAdults() const;
    void setAdults(int value);
    QStringList getChildren() const;
    void setChildren(const QStringList &value);

private:
    int locationId;
    int fromCityId;
    QString startDate;
    QString endDate;
    int length;
    int adults;
    QStringList children;

signals:

};

#endif // SEARCHPARAMETERS_H
