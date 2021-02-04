import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem{
    contentHeight: mainColumn.height + separator.height + 2 * Theme.paddingMedium
    contentWidth: parent.width

    Column {
        id: mainColumn
        width: parent.width - ( 2 * Theme.horizontalPageMargin )
        spacing: Theme.paddingSmall
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        Rectangle {
            visible: index !== 0 && isFirst
            color: Theme.highlightBackgroundColor
            anchors.horizontalCenter: parent.horizontalCenter
            height: Theme.itemSizeSmall
            width: page.width
            Label {
                text: "Більше результатів"
                anchors.centerIn: parent
            }
        }

        Text {
            font.pixelSize: Theme.fontSizeMedium
            width: parent.width - progressCircle.width
            color: Theme.highlightColor
            text: name

            ProgressCircle {
                id: progressCircle
                anchors.left: parent.right
                anchors.top: parent.top
                progressValue: ratingAvarage / 10
                backgroundColor: "#80000000"
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

        Icon{
            source: "image://theme/icon-m-whereami"
            Label {
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.secondaryColor
                text: country + ", " + city
                anchors.left: parent.right
                width: page.width - 2 * Theme.horizontalPageMargin - parent.width
                anchors.verticalCenter: parent.verticalCenter
                truncationMode: TruncationMode.Fade
            }
        }


        Row{
            spacing: Theme.paddingLarge
            Text {
                id: priceUahLabel
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.primaryColor
                text: priceUah + "₴"
            }
            Text {
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
            top: mainColumn.bottom
            topMargin: Theme.paddingMedium
        }

        width: parent.width
        color: Theme.primaryColor
        horizontalAlignment: Qt.AlignHCenter
    }

}
