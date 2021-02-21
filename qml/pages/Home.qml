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
                text: "Новий пошук"
                onClicked: pageStack.animatorPush(Qt.resolvedUrl("SearchForm.qml"), {},
                                                  PageStackAction.Immediate)
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: parent.height

        Column {
            id: column
            width: parent.width

            PageHeader { title: "Пошук турів" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * x
                text: "Історія та збережені пошуки в розробці"
                wrapMode: "WordWrap"
                font.pixelSize: Theme.fontSizeExtraLarge
            }

        }

        VerticalScrollDecorator {}
    }

    InteractionHintLabel {
        anchors.bottom: parent.bottom
        text: "Потягни вниз для пошуку турів"
    }

}
