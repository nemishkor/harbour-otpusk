import QtQuick 2.0
import Sailfish.Silica 1.0

Column {

    property string offerId
    property string dateFrom
    property string dateTo
    property string roomType
    property int adults
    property var childrenCount
    property var childrenAges
    property int nights
    property var foodType
    property string roomName
    property double price
    property double priceUah
    property string currency
    property string transport

    property bool hideSeparator: false

    id: root
    width: parent.width - 2 * Theme.horizontalPageMargin
    anchors.left: parent.left
    anchors.leftMargin: Theme.horizontalPageMargin
    spacing: Theme.paddingSmall

    Label {
        text: "ID: " + root.offerId
        font.pixelSize: Theme.fontSizeLarge
    }

    Icon {
        source: "image://theme/icon-m-date"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
                verticalCenter: parent.verticalCenter
            }
            width: root.width - parent.width - anchors.leftMargin
            text: root.dateFrom + "   " + root.dateTo
        }
    }

    Icon {
        source: "image://theme/icon-m-moon"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
                verticalCenter: parent.verticalCenter
            }
            width: root.width - parent.width - anchors.leftMargin
            text: {
                var text = root.nights + " "
                if(root.nights === 1){
                    text += "ніч"
                } else if(root.nights > 1 && root.nights < 5){
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
                verticalCenter: parent.verticalCenter
            }
            width: root.width - parent.width - anchors.leftMargin
            text: root.transport
        }
    }

    Icon {
        source: "image://theme/icon-m-people"
        color: Theme.highlightColor
        Label {
            anchors {
                left: parent.right
                leftMargin: Theme.paddingMedium
                verticalCenter: parent.verticalCenter
            }
            width: root.width - parent.width - anchors.leftMargin
            text: {
                var text = root.adults + " " + (root.adults === 1 ? "дорослий" : "дорослих") + " + " + root.childrenCount + " "
                if(root.childrenCount === 1)
                    text += "дитина"
                else if(root.childrenCount > 1 && root.childrenCount < 5)
                    text += "дитини"
                else
                    text += "дітей"
                if(root.childrenAges !== "")
                    text += " (" + root.childrenAges + ")"
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
                verticalCenter: parent.verticalCenter
            }
            width: root.width - parent.width - anchors.leftMargin
            text: root.roomType + " (" + root.roomName + ") | " + root.foodType
        }
    }

    Price {
        price: root.price
        priceUah: root.priceUah
        currency: root.currency
    }

    Item {
        width: parent.width
        height: Theme.paddingSmall
    }

    ButtonLayout {
        Button {
            text: "Замовити на Otpusk.com"
            onClicked: Qt.openUrlExternally("https://www.otpusk.com/hotel/" + hotel.id + "-" + hotel.alias + "/" + root.offerId + "/")
        }
    }

    Item {
        width: parent.width
        height: Theme.paddingSmall
    }

    Separator {
        id: separator
        visible: !root.hideSeparator
        width: parent.width
        color: Theme.primaryColor
        horizontalAlignment: Qt.AlignHCenter
    }
}
