import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {

    id: page
    property var id

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    Component.onCompleted: hotelLoader.load(page.id)

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: pageHeader.height + infoColumn.height + photos.height + ratingsSection.height + ratingsList.height

        Label {
            id: pageHeader
            y: (isLandscape ? Theme.itemSizeSmall : Theme.itemSizeLarge) / 4
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

        Label{
            visible: hotelLoader.replyFailed
            x: Theme.horizontalPageMargin
            anchors.top: pageHeader.bottom
            width: parent.width - 2 * Theme.horizontalPageMargin
            text: hotelLoader.replyErrorText
            color: Theme.errorColor
            font.pixelSize: Theme.fontSizeMedium
            wrapMode: "WordWrap"
        }

        Photos {
            id: photos
            photos: hotel.photos
            anchors.top: pageHeader.bottom
            anchors.topMargin: (isLandscape ? Theme.itemSizeSmall : Theme.itemSizeLarge) / 4
        }

        ProgressCircle {
            id: progressCircle
            anchors {
                top: photos.bottom
                right: photos.right
                rightMargin: Theme.horizontalPageMargin
            }

            progressValue: hotel.ratingAvarage / 10
            backgroundColor: "#80000000"
            opacity: root.highlighted ? 0.5 : 1.0
            progressColor: {
                if(hotel.ratingAvarage === 0)
                    return "#807B7B7B"
                if(hotel.ratingAvarage > 6)
                    return "#8051D511"
                if(hotel.ratingAvarage > 4)
                    return "#80DEB321"
                return "#80EC4713"
            }
            Label{
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: hotel.ratingCount > 999 ? Theme.fontSizeSmall : Theme.fontSizeMedium
                color: hotel.ratingCount < 10 ? "#80EC4713" : ratingAvarageLabel.color
                text: hotel.ratingCount > 0 ? hotel.ratingCount : "-"
            }
            Label{
                id: ratingAvarageLabel
                visible: hotel.ratingCount > 0
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                horizontalAlignment: Text.AlignHCenter
                text: hotel.ratingAvarage + "/10"
                font.pixelSize: Theme.fontSizeSmall
            }
        }

        SectionHeader {
            id: ratingsSection
            text: "Оцінки"
        }

        ListView {
            id: ratingsList
            width: parent.width
            model: hotel.hotelRatings
            delegate: ListItem {
                Slider {
                    value: model.vote
                    minimumValue: 0
                    maximumValue: 10
                    enabled: false
                    width: parent.width
                    valueText : model.vote
                    label: model.name
                }
                Component.onCompleted: {
                    console.log(model.name)
                }
            }
        }

        Column {
            id: infoColumn
            width: parent.width

            spacing: Theme.paddingSmall
            anchors {
                top: isPortrait ? photos.bottom : photos.top
                topMargin: isPortrait ? Theme.paddingMedium : Theme.paddingSmall
                left: isPortrait ? parent.left : photos.right
                leftMargin: isPortrait ? 0 : Theme.paddingMedium
            }

            Icon {
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                source: "image://theme/icon-m-whereami"
                Label {
                    anchors {
                        left: parent.right
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                    width: root.width - 2 * Theme.horizontalPageMargin - parent.width
                    truncationMode: TruncationMode.Fade
                    text: hotel.country + ", " + hotel.city
                }
            }

            SectionHeader {
                text: "Послуги та зручності"
            }

            ButtonLayout {
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

        }

        VerticalScrollDecorator {}

    }

}
