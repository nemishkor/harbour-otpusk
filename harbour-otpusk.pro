# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-otpusk

CONFIG += sailfishapp

SOURCES += \
    src/datesmodel.cpp \
    src/harbour-otpusk.cpp \
    src/hotelloader.cpp \
    src/locationmodel.cpp \
    src/offer.cpp \
    src/offersmodel.cpp \
    src/searchparameters.cpp \
    src/tour.cpp \
    src/tourmodel.cpp \
    src/toursloader.cpp

DISTFILES += \
    assets/around.svg \
    assets/icon.png \
    assets/icon.svg \
    harbour-otpusk.desktop \
    icons/108x108/harbour-otpusk.png \
    icons/128x128/harbour-otpusk.png \
    icons/172x172/harbour-otpusk.png \
    icons/86x86/harbour-otpusk.png \
    qml/components/DatePickerDialog.qml \
    qml/components/LocationDialog.qml \
    qml/components/OfferListItem.qml \
    qml/components/Photos.qml \
    qml/components/Price.qml \
    qml/components/TourListItem.qml \
    qml/cover/CoverPage.qml \
    qml/harbour-otpusk.qml \
    qml/pages/Home.qml \
    qml/pages/Offers.qml \
    qml/pages/SearchForm.qml \
    qml/pages/SearchResults.qml \
    qml/pages/Tour.qml \
    rpm/harbour-otpusk.changes.in \
    rpm/harbour-otpusk.changes.run.in \
    rpm/harbour-otpusk.spec \
    rpm/harbour-otpusk.yaml \
    translations/*.ts

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
#CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-otpusk-de.ts

QT += network

HEADERS += \
    src/api.h \
    src/datesmodel.h \
    src/hotelloader.h \
    src/locationmodel.h \
    src/offer.h \
    src/offersmodel.h \
    src/searchparameters.h \
    src/tour.h \
    src/tourmodel.h \
    src/toursloader.h

RESOURCES += \
    assets.qrc
