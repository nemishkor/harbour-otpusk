import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {

    property int hotelId
    property double price
    property double priceUah
    property string currency
    property string priceId
    property string photo
    property string stars
    property string name
    property double ratingAvarage
    property int ratingCount
    property string country
    property string city

    id: root
    contentHeight: moreResultsLabel.height + mainImage.height + (isPortrait ? infoColumn.height : 0) + separator.height + 2 * Theme.paddingLarge
    contentWidth: parent.width

    onClicked: {
        pageStack.animatorPush(
            Qt.resolvedUrl("../pages/Tour.qml"),
            {
//                tour: toursLoader.tourModel.get(index),
                price: root.price,
                priceUah: root.priceUah,
                currency: root.currency,
                priceId: root.priceId,
                hotelId: root.hotelId
            }
        )
    }

    Rectangle {
        id: moreResultsLabel
        visible: index !== 0 && isFirst
        color: Theme.highlightBackgroundColor
        height: visible ? Theme.itemSizeSmall : 0
        width: root.width
        Label {
            text: "Більше результатів"
            anchors.centerIn: parent
        }
    }

    Image {
        id: mainImage
        anchors.top: moreResultsLabel.bottom
        anchors.topMargin: moreResultsLabel.visible ? Theme.paddingMedium : 0
        source: "https://newimg.otpusk.com/2/800x600/" + root.photo
        width: isPortrait ? parent.width : (parent.width / 2 - 2 * Theme.horizontalPageMargin)
        height: width * 600 / 800
        opacity: root.highlighted ? 0.5 : 1.0
    }

    Column {
        id: infoColumn
        spacing: Theme.paddingSmall
        width: parent.width - anchors.leftMargin
        anchors {
            top: isPortrait ? mainImage.bottom : mainImage.top
            topMargin: isPortrait ? Theme.paddingMedium : Theme.paddingSmall
            left: isPortrait ? parent.left : mainImage.right
            leftMargin: isPortrait ? 0 : Theme.paddingMedium
        }

        Item {
            height: Theme.fontSizeMedium + 2 * Theme.paddingSmall
            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin

            Row {
                height: parent.height
                width: parent.width - progressCircle.width
                Label {
                    id: starsLabel
                    text: root.stars
                    font.pixelSize: Theme.fontSizeMedium
                    color: Theme.highlightColor
                }
                Icon {
                    id: starsIcon
                    source: "image://theme/icon-s-favorite"
                    anchors.verticalCenter: starsLabel.verticalCenter
                    color: Theme.highlightColor
                }
                Label {
                    font.pixelSize: Theme.fontSizeMedium
                    width: parent.width - starsLabel.width - starsIcon.width - Theme.paddingSmall
                    color: Theme.highlightColor
                    text: root.name
                    truncationMode: TruncationMode.Fade
                }
            }

            ProgressCircle {
                id: progressCircle
                anchors.right: parent.right
                anchors.top: parent.top
                progressValue: root.ratingAvarage / 10
                backgroundColor: "#80000000"
                opacity: root.highlighted ? 0.5 : 1.0
                progressColor: {
                    if(root.ratingAvarage === 0)
                        return "#807B7B7B"
                    if(root.ratingAvarage > 6)
                        return "#8051D511"
                    if(root.ratingAvarage > 4)
                        return "#80DEB321"
                    return "#80EC4713"
                }
                Label{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: root.ratingCount > 0 ? ratingCount : "-"
                    font.pixelSize: ratingCount > 999 ? Theme.fontSizeSmall : Theme.fontSizeMedium
                    color: root.ratingCount < 10 ? "#80EC4713" : ratingAvarageLabel.color
                }
                Label{
                    id: ratingAvarageLabel
                    visible: root.ratingCount > 0
                    anchors.top: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignHCenter
                    text: root.ratingAvarage + "/10"
                    font.pixelSize: Theme.fontSizeSmall
                }
            }

        }

        Icon {
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
            source: "image://theme/icon-m-whereami"
            Label {
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.secondaryColor
                text: root.country + ", " + root.city
                anchors.left: parent.right
                width: root.width - 2 * Theme.horizontalPageMargin - parent.width
                anchors.verticalCenter: parent.verticalCenter
                truncationMode: TruncationMode.Fade
            }
        }

        Price {
            price: root.price
            priceUah: root.priceUah
            currency: root.currency
        }

    }

    Separator {
        id: separator
        anchors {
            top: infoColumn.bottom
            topMargin: Theme.paddingMedium
        }

        width: parent.width
        color: Theme.primaryColor
        horizontalAlignment: Qt.AlignHCenter
    }

}
