#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtQml>
#include <QtQuick>
#include <sailfishapp.h>
#include "api.h"
#include <QString>
#include "toursloader.h"
#include "tourmodel.h"
#include "locationmodel.h"
#include "datesmodel.h"
#include "searchparameters.h"
#include "hotelloader.h"

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/Otpusk.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    // Set up QML engine.
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QQmlContext *context = view.data()->rootContext();

    Api api;
    context->setContextProperty("api", &api);

    LocationModel locationModel(&api);
    context->setContextProperty("locationModel", &locationModel);

    SearchDatesModel searchDatesModel(&api);
//    QObject *rootObject = view->rootObject();
//    QObject::connect(rootObject, SIGNAL(qmlSignal(QString)), &searchDatesModel, SLOT(cppSlot(QString)));
    context->setContextProperty("searchDatesModel", &searchDatesModel);

    SearchParameters searchParameters(nullptr);
    context->setContextProperty("searchParameters", &searchParameters);

    ToursLoader toursLoader(&api);
    context->setContextProperty("toursLoader", &toursLoader);

    Hotel hotel;
    context->setContextProperty("hotel", &hotel);
    HotelLoader hotelLoader(&api, &hotel);
    context->setContextProperty("hotelLoader", &hotelLoader);

//    qmlRegisterUncreatableType<Tour>("harbour.otpusk", 1, 0, "TourType", "Pass tour c++ object from list view to separated page");
//    qmlRegisterUncreatableType<OffersModel>("harbour.otpusk", 1, 0, "OffersModel", "To expose offersModel of c++ Tour object to qml");

    // If you wish to publish your app on the Jolla harbour, it is recommended
    // that you prefix your internal namespaces with "harbour.".
    //
    // For details see:
    // https://harbour.jolla.com/faq#1.5.0
//    qmlRegisterType<ToursLoader>("harbour.otpusk", 1, 0, "ToursLoader");


    // Start the application.
    view->setSource(SailfishApp::pathTo("qml/harbour-otpusk.qml"));
    view->show();
    return app->exec();
}
