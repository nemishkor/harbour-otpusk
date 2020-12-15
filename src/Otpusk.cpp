#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "api.h"
#include <QString>
#include "toursloader.h"
#include "tourmodel.h"
#include "locationmodel.h"
#include "datesmodel.h"

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
    context->setContextProperty("searchDatesModel", &searchDatesModel);
    ToursLoader toursLoader(&api);
    context->setContextProperty("toursLoader", &toursLoader);

    // If you wish to publish your app on the Jolla harbour, it is recommended
    // that you prefix your internal namespaces with "harbour.".
    //
    // For details see:
    // https://harbour.jolla.com/faq#1.5.0
//    qmlRegisterType<ToursLoader>("harbour.otpusk", 1, 0, "ToursLoader");


    // Start the application.
    view->setSource(SailfishApp::pathTo("qml/Otpusk.qml"));
    view->show();
    return app->exec();
}
