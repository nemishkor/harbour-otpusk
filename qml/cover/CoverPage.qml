import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

CoverBackground {
    Label {
        id: title
        anchors.top: parent.top
        anchors.topMargin: Theme.paddingMedium
        width: parent.width
        text: "Otpusk"
        horizontalAlignment: "AlignHCenter"
        font.pixelSize: Theme.fontSizeExtraLarge
        color: Theme.highlightColor
    }
    Label {
        id: hotelName
        anchors.top: title.bottom
        text: hotel.name
        width: parent.width
        horizontalAlignment: "AlignHCenter"
        color: Theme.secondaryHighlightColor
        wrapMode: "WordWrap"
    }
    Image {
        id: hotelPhoto
        anchors.top: hotelName.bottom
        anchors.topMargin: Theme.paddingSmall
        anchors.left: parent.left
        anchors.leftMargin: Theme.horizontalPageMargin
        width: parent.width - Theme.horizontalPageMargin * 2
        height: hotel.photos[0] === undefined ? width : Math.floor(600 * width / 800)
        source: hotel.photos[0] === undefined ? "qrc:///assets/around.svg" : "https://newimg.otpusk.com/2/800x600/" + hotel.photos[0]
    }
    ColorOverlay {
        visible: hotel.photos[0] === undefined
        anchors.fill: hotelPhoto
        source: hotelPhoto
        color: Theme.secondaryHighlightColor
    }
}
