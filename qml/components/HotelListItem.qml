import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem{
    id: root
    contentHeight: moreResultsLabel.height + mainImage.height + (isPortrait ? infoColumn.height : 0) + separator.height
    contentWidth: parent.width

    Rectangle {
        id: moreResultsLabel
        visible: index !== 0 && isFirst
        color: Theme.highlightBackgroundColor
        height: Theme.itemSizeSmall
        width: root.width
        Label {
            text: "Більше результатів"
            anchors.centerIn: parent
        }
    }

    Image {
        id: mainImage
        source: "https://newimg.otpusk.com/2/800x600/" + photo
        width: isPortrait ? parent.width : (parent.width / 2 - 2 * Theme.horizontalPageMargin)
        height: width * 600 / 800
        opacity: root.highlighted ? 0.5 : 1.0
    }

    Column {
        id: infoColumn
        spacing: Theme.paddingSmall
        anchors {
            top: isPortrait ? mainImage.bottom : mainImage.top
            topMargin: isPortrait ? Theme.paddingMedium : Theme.paddingSmall
            left: isPortrait ? parent.left : mainImage.right
            leftMargin: isPortrait ? 0 : Theme.paddingMedium
        }

        Row {
            height: Theme.fontSizeMedium + 2 * Theme.paddingSmall
            Label {
                id: starsLabel
                text: stars
                font.pixelSize: Theme.fontSizeMedium
                color: Theme.highlightColor
                leftPadding: Theme.horizontalPageMargin + Theme.paddingSmall
            }
            Icon {
                id: starsIcon
                source: "image://theme/icon-s-favorite"
                anchors.verticalCenter: starsLabel.verticalCenter
                color: Theme.highlightColor
            }
            Label {
                leftPadding: Theme.paddingMedium
                font.pixelSize: Theme.fontSizeMedium
                width: root.width - progressCircle.width - starsLabel.width - starsIcon.width - Theme.horizontalPageMargin
                color: Theme.highlightColor
                text: name
                truncationMode: TruncationMode.Fade

                ProgressCircle {
                    id: progressCircle
                    anchors.left: parent.right
                    anchors.top: parent.top
                    progressValue: ratingAvarage / 10
                    backgroundColor: "#80000000"
                    opacity: root.highlighted ? 0.5 : 1.0
                    progressColor: {
                        if(ratingAvarage === 0)
                            return "#807B7B7B"
                        if(ratingAvarage > 6)
                            return "#8051D511"
                        if(ratingAvarage > 4)
                            return "#80DEB321"
                        return "#80EC4713"
                    }
                    Label{
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: ratingCount > 0 ? ratingCount : "-"
                        font.pixelSize: ratingCount > 999 ? Theme.fontSizeSmall : Theme.fontSizeMedium
                        color: ratingCount < 10 ? "#80EC4713" : ratingAvarageLabel.color
                    }
                    Label{
                        id: ratingAvarageLabel
                        visible: ratingCount > 0
                        anchors.top: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        horizontalAlignment: Text.AlignHCenter
                        text: ratingAvarage + "/10"
                        font.pixelSize: Theme.fontSizeSmall
                    }
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
                text: country + ", " + city
                anchors.left: parent.right
                width: root.width - 2 * Theme.horizontalPageMargin - parent.width
                anchors.verticalCenter: parent.verticalCenter
                truncationMode: TruncationMode.Fade
            }
        }

        Row{
            spacing: Theme.paddingLarge
            Label {
                id: priceUahLabel
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.primaryColor
                text: priceUah + "₴"
                leftPadding: Theme.horizontalPageMargin
            }
            Label {
                anchors.baseline: priceUahLabel.baseline
                font.pixelSize: Theme.fontSizeMedium
                color: Theme.secondaryColor
                text: {
                    var t = price
                    switch(currency){
                    case "eur":
                        t += "€"
                        break;
                    case "usd":
                        t += "$"
                        break;
                    default:
                        t += currency
                        break;
                    }
                }
            }
        }

    }

    Separator {
        id: separator
        anchors {
            top: isPortrait ? infoColumn.bottom : mainImage.bottom
            topMargin: Theme.paddingMedium
        }

        width: parent.width
        color: Theme.primaryColor
        horizontalAlignment: Qt.AlignHCenter
    }

}
