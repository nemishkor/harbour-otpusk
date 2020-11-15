import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {

    id: toursListViewItem

    property alias nameLabel: nameLabel

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

        Text {
            id: nameLabel
            font.pixelSize: Theme.fontSizeMedium
            color: Theme.primaryColor
            elide: Text.ElideRight
            width: parent.width
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
