import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Search")
                onClicked: toursLoader.load()
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: pageHeader.height

        Column{
            id: pageHeader
            width: parent.width
            spacing: Theme.paddingMedium
            PageHeader {
                title: qsTr("Otpusk")
                BusyIndicator {
                    running: toursLoader.loading
                    size: BusyIndicatorSize.Medium
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: Theme.paddingLarge
                    anchors.leftMargin: Theme.horizontalPageMargin
                }
            }
            Label{
                visible: toursLoader.replyFailed
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                text: toursLoader.replyErrorText
                color: Theme.errorColor
                font.pixelSize: Theme.fontSizeMedium
                wrapMode: "WordWrap"
            }
            Label{
                visible: !toursLoader.loading && !toursLoader.replyFailed && toursLoader.total === 0
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                text: "Nothing found. Change search parameters"
                wrapMode: "WordWrap"
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeLarge
            }
            ProgressBar{
                id: progressBar
                visible: toursLoader.loading
                width: parent.width
                maximumValue: 100
                value: toursLoader.progress
                label: toursLoader.progress + " %"
            }
        }


//            Item {
//                id: toursItem
//                width: parent.width
//                height: parent.height - Theme.paddingMedium - pageHeader.height

//                SilicaListView {
//                    id: toursListView

//                    anchors.fill: parent
//                    clip: true

//                    model: toursLoader.toursModel
//                    delegate: ToursListViewItem {
//                        nameLabel.text: model.name
//                    }
//                }

//            }

    }

    Rectangle{
        visible: toursLoader.total !== 0
        color: Theme.highlightDimmerColor
        radius: 10 * Theme.pixelRatio
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: Theme.paddingLarge
        width: 140
        height: Theme.fontSizeMedium * 1.1
        Text {
            anchors.centerIn: parent
            text: String(toursLoader.total)
            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall
        }
    }

}
