#include "searchparameters.h"

SearchParameters::SearchParameters(QObject *parent) : QObject(parent)
{

}

int SearchParameters::getLocationId() const
{
    return locationId;
}

int SearchParameters::getFromCityId() const
{
    return fromCityId;
}

QString SearchParameters::getStartDate() const
{
    return startDate;
}

QString SearchParameters::getEndDate() const
{
    return endDate;
}

int SearchParameters::getLength() const
{
    return length;
}

int SearchParameters::getAdults() const
{
    return adults;
}

QStringList SearchParameters::getChildren() const
{
    return children;
}

void SearchParameters::setLocationId(int value)
{
    locationId = value;
}

void SearchParameters::setFromCityId(int value)
{
    fromCityId = value;
}

void SearchParameters::setStartDate(const QString &value)
{
    startDate = value;
}

void SearchParameters::setEndDate(const QString &value)
{
    endDate = value;
}

void SearchParameters::setLength(int value)
{
    length = value;
}

void SearchParameters::setAdults(int value)
{
    adults = value;
}

void SearchParameters::setChildren(const QStringList &value)
{
    children = value;
}
