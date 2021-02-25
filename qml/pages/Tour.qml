import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.otpusk 1.0
import "../components"

Page {

    id: page

    // already loaded tour data with offers
    property var tour
    property var hotelId

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.Portrait

    Component.onCompleted: hotelLoader.load(hotelId)

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaListView {
        anchors.fill: parent        
        spacing: Theme.paddingMedium
        delegate: OfferListItem {}
        model: tour.offers()

        header: Column {
            width: parent.width
            height: Theme.paddingMedium * 11 + gap1.height + gap2.height + pageHeader.height + failedMessage.height + photos.height + description.height + location.height + distance.height + ratingsSection.height + ratingGrid.height + servicesHeader.height + servicesButtons.height + servicesButtons2.height + pricesHeader.height
            spacing: Theme.paddingMedium

            Rectangle {
                id: gap1
                color: "#00000000"
                height: Theme.itemSizeLarge / 4 - Theme.paddingMedium
                width: parent.width
            }

            Label {
                id: pageHeader
                width: parent.width - 4 * Theme.horizontalPageMargin - starsIcon.width
                color: Theme.highlightColor
                anchors {
                    right: parent.right
                    rightMargin: Theme.horizontalPageMargin
                }
                horizontalAlignment: Text.AlignRight
                font {
                    pixelSize: Theme.fontSizeLarge
                    family: Theme.fontFamilyHeading
                }
                wrapMode: "WordWrap"
                text: hotel.name + " " + hotel.stars

                BusyIndicator {
                    running: hotelLoader.loading
                    size: BusyIndicatorSize.Large
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Icon {
                    id: starsIcon
                    source: "image://theme/icon-s-favorite"
                    anchors {
                        left: pageHeader.right
                        verticalCenter: pageHeader.verticalCenter
                    }
                    color: Theme.highlightColor
                }
            }

            Rectangle {
                id: gap2
                color: "#00000000"
                height: Theme.itemSizeLarge / 4 - Theme.paddingMedium - Theme.paddingMedium
                width: parent.width
            }

            Label{
                id: failedMessage
                visible: hotelLoader.replyFailed
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                text: hotelLoader.replyErrorText
                color: Theme.errorColor
                font.pixelSize: Theme.fontSizeMedium
                wrapMode: "WordWrap"
            }

            Photos {
                id: photos
                photos: hotel.photos
            }

            Label {
                id: description
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                text: hotel.description
                wrapMode: "WordWrap"
            }

            Icon {
                id: location
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                source: "image://theme/icon-m-whereami"
                Label {
                    anchors {
                        left: parent.right
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: Theme.fontSizeSmall
                    width: parent.width - 2 * Theme.horizontalPageMargin
                    truncationMode: TruncationMode.Fade
                    text: hotel.country + ", " + hotel.city
                }
            }

            Label {
                id: distance
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: "WordWrap"
                text: hotel.distance
            }

            SectionHeader {
                id: ratingsSection
                text: "Оцінки"
            }

            GridView {
                id: ratingGrid
                width: parent.width
                cellWidth: parent.width / 3
                cellHeight: Theme.itemSizeSmall + 2 * Theme.fontSizeSmall + Theme.paddingLarge
                height: Math.ceil(count / Math.floor(width / cellWidth)) * cellHeight
                interactive: false
                model: hotel.hotelRatings
                delegate: Column {
                    width: parent.width / 3
                    Label {
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        text: model.name === "_total" ? "середній бал" : model.name
                        font.pixelSize: Theme.fontSizeSmall
                        font.weight: model.name === "_total" ? Font.Bold : Font.Normal
                    }
                    ProgressCircle {
                        id: ratingCircle
                        progressValue: model.vote / 10
                        backgroundColor: "#80000000"
                        anchors.horizontalCenter: parent.horizontalCenter
                        progressColor: {
                            if(model.vote === 0)
                                return "#807B7B7B"
                            if(model.vote > 6)
                                return "#8051D511"
                            if(model.vote > 4)
                                return "#80DEB321"
                            return "#80EC4713"
                        }
                        Label{
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: model.count > 999 ? Theme.fontSizeSmall : Theme.fontSizeMedium
                            color: model.count < 10 ? "#80EC4713" : ratingLabel.color
                            text: model.count > 0 ? model.count : "-"
                            font.weight: model.name === "_total" ? Font.Bold : Font.Normal
                        }
                    }
                    Label{
                        id: ratingLabel
                        visible: model.count > 0
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        text: model.vote + "/10"
                        font.pixelSize: Theme.fontSizeSmall
                        font.weight: model.name === "_total" ? Font.Bold : Font.Normal
                    }
                }
            }

            SectionHeader {
                id: servicesHeader
                text: "Послуги та зручності"
            }

            ButtonLayout {
                id: servicesButtons
                preferredWidth: Theme.buttonWidthExtraSmall
                rowSpacing: Theme.paddingSmall
                Button {
                    text: "В номері"
                    onClicked: pageStack.animatorPush(roomServicesPage)
                }
                Button {
                    text: "В готелі"
                    onClicked: pageStack.animatorPush(hotelServicesPage)
                }
                Button {
                    text: "Пляж"
                    onClicked: pageStack.animatorPush(beachServicesPage)
                }
                Button {
                    text: "Для дітей"
                    onClicked: pageStack.animatorPush(forChildrenServicesPage)
                }
            }
            ButtonLayout {
                id: servicesButtons2
                preferredWidth: Theme.buttonWidthExtraSmall
                Button {
                    text: "Активності та спорт"
                    onClicked: pageStack.animatorPush(activitiesServicesPage)
                }
            }

            Page {
                id: roomServicesPage
                SilicaListView {
                    anchors.fill: parent
                    model: hotel.roomServices
                    header: Column {
                        width: parent.width
                        PageHeader { title: "В номері" }
                    }
                    delegate: Label {
                        width: roomServicesPage.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name + (model.title ? " | " + model.title : "") + (model.all ? "" : " | не всюди")
                        wrapMode: "WordWrap"
                    }
                }
            }

            Page {
                id: hotelServicesPage
                SilicaListView {
                    anchors.fill: parent
                    model: hotel.hotelServices
                    header: Column {
                        width: parent.width
                        PageHeader { title: "В готелі" }
                    }
                    delegate: Label {
                        width: hotelServicesPage.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name + (model.title ? " | " + model.title : "") + (model.all ? "" : " | не всюди")
                        wrapMode: "WordWrap"
                    }
                }
            }

            Page {
                id: forChildrenServicesPage
                SilicaListView {
                    anchors.fill: parent
                    model: hotel.forChildrenServices
                    header: Column {
                        width: parent.width
                        PageHeader { title: "Для дітей" }
                    }
                    delegate: Label {
                        width: forChildrenServicesPage.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name + (model.title ? " | " + model.title : "") + (model.all ? "" : " | не всюди")
                        wrapMode: "WordWrap"
                    }
                }
            }

            Page {
                id: beachServicesPage
                SilicaListView {
                    anchors.fill: parent
                    model: hotel.beachServices
                    header: Column {
                        width: parent.width
                        PageHeader { title: "Пляж" }
                    }
                    delegate: Label {
                        width: beachServicesPage.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name + (model.title ? " | " + model.title : "") + (model.all ? "" : " | не всюди")
                        wrapMode: "WordWrap"
                    }
                }
            }

            Page {
                id: activitiesServicesPage
                SilicaListView {
                    anchors.fill: parent
                    model: hotel.activiesServices
                    header: Column {
                        width: parent.width
                        PageHeader { title: "Активності та спорт" }
                    }
                    delegate: Label {
                        width: activitiesServicesPage.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name + (model.title ? " | " + model.title : "") + (model.all ? "" : " | не всюди")
                        wrapMode: "WordWrap"
                    }
                }
            }

            SectionHeader {
                id: pricesHeader
                text: "Ціни та варіанти туру"
            }

        }

        VerticalScrollDecorator {}

    }

}
