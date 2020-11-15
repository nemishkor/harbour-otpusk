import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.otpusk 1.0
import "../components"

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    Api{
        id: api
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Load")
                onClicked: api.load()
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: parent.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: parent.width
            height: parent.height
            spacing: Theme.paddingMedium

            Column{
                id: pageHeader
                width: parent.width
                PageHeader {
                    title: qsTr("Otpusk")
                }
                Label{
                    x: Theme.horizontalPageMargin
                    text: "lastResult " + (api.lastResult ? "true" : "false")
                    color: Theme.secondaryHighlightColor
                    font.pixelSize: Theme.fontSizeMedium
                }
                Label{
                    x: Theme.horizontalPageMargin
                    text: "total" + api.total
                    color: Theme.secondaryHighlightColor
                    font.pixelSize: Theme.fontSizeMedium
                }
            }


            Item {
                id: toursItem
                width: parent.width
                height: parent.height - Theme.paddingMedium - pageHeader.height

                SilicaListView {
                    id: toursListView

                    anchors.fill: parent
                    clip: true

                    model: toursModel
                    delegate: ToursListViewItem {
                        nameLabel.text: model.name
                    }
                }

            }

        }

    }
}
