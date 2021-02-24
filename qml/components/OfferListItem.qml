import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: offerItem
    width: parent.width - 2 * Theme.horizontalPageMargin
    anchors.left: parent.left
    anchors.leftMargin: Theme.horizontalPageMargin
    spacing: Theme.paddingSmall

    Icon {
        source: "image://theme/icon-m-date"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
            }
            verticalAlignment: parent.verticalAlignment
            width: offerItem.width - parent.width - anchors.leftMargin
            text: dateFrom + "   " + dateTo
        }
    }

    Icon {
        source: "image://theme/icon-m-moon"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
            }
            verticalAlignment: parent.verticalAlignment
            width: offerItem.width - parent.width - anchors.leftMargin
            text: {
                var text = nights + " "
                if(nights === 1){
                    text += "ніч"
                } else if(nights > 1 && nights < 5){
                    text += "ночі"
                } else {
                    text += "ночей"
                }
                return text
            }
        }
    }

    Icon {
        source: "image://theme/icon-m-airplane-mode"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
            }
            verticalAlignment: parent.verticalAlignment
            width: offerItem.width - parent.width - anchors.leftMargin
            text: transport
        }
    }

    Icon {
        source: "image://theme/icon-m-people"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
            }
            verticalAlignment: parent.verticalAlignment
            width: offerItem.width - parent.width - anchors.leftMargin
            text: {
                var text = adults + " " + (adults === 1 ? "дорослий" : "дорослих") + " + " + childrenCount + " "
                if(childrenCount === 1)
                    text += "дитина"
                else if(childrenCount > 1 && childrenCount < 5)
                    text += "дитини"
                else
                    text += "дітей"
                if(childrenAges !== "")
                    text += " (" + childrenAges + ")"
                return text
            }
        }
    }

    Icon {
        source: "image://theme/icon-m-home"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
            }
            verticalAlignment: parent.verticalAlignment
            width: offerItem.width - parent.width - anchors.leftMargin
            text: roomType + " (" + roomName + ") | " + foodType
        }
    }

    Price {
        price: model.price
        priceUah: model.priceUah
        currency: model.currency
    }

    Separator {
        id: separator
        width: parent.width
        color: Theme.primaryColor
        horizontalAlignment: Qt.AlignHCenter
    }
}
