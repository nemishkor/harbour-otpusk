#ifndef TOURSLOADER_H
#define TOURSLOADER_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QString>
#include <QTimer>
#include <QList>
#include <QJsonArray>
#include "api.h"
#include "tourmodel.h"
#include "searchparameters.h"

class ToursLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)
    Q_PROPERTY(int total READ getTotal NOTIFY totalChanged)
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(TourModel* tourModel READ getTourModel NOTIFY tourModelChanged)
    Q_PROPERTY(bool loading READ getLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool replyFailed READ isReplyFailed NOTIFY isReplyFailedChanged)
    Q_PROPERTY(QString replyErrorText READ getReplyErrorText NOTIFY replyErrorTextChanged)

public:
    explicit ToursLoader(Api *api);
    Q_INVOKABLE void load(SearchParameters *searchParameters);
    void continueSearch();
    void sendSearchRequest();
    int getProgress();
    void setProgress(int progress);
    int getTotal();
    void setTotal(int total);
    TourModel* getTourModel();
    bool getLoading() const;
    void setLoading(bool loading);
    bool isReplyFailed() const;
    void setReplyFailed(bool isReplyFailed);
    QString getReplyErrorText() const;
    void setReplyErrorText(QString replyErrorText);
    int getPage();
    void setPage(int _page);
    int calculateProgress(QJsonDocument *json);
    Q_INVOKABLE void fillOffersModelFromResponse(int hotelId, OffersModel *offersModel);

private:
    Api *api;
    int requestNumber = 0;
    int progress = 0;
    int total = 0;
    TourModel tourModel;
    bool loading = false;
    bool replyFailed = false;
    QString replyErrorText;
    int page = 1;
    SearchParameters *currentSearchParameters;
    QJsonObject lastToursReply;
    void addTour(QJsonObject hotel, bool isFirst);
    Offer getFirstOfferOfTour(QJsonObject *tour);

private slots:
    void handleSearchReply(QNetworkReply *reply);

signals:
    void tourModelChanged();
    void progressChanged();
    void totalChanged();
    void loadingChanged();
    void isReplyFailedChanged();
    void replyErrorTextChanged();
    void pageChanged();
};

#endif // TOURSLOADER_H
