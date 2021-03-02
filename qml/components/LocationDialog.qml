import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: locationDialog

    property string searchString
    property int locationId
    property string locationName
    property alias dialog: locationDialog

    canAccept: locationId !== 0

    onSearchStringChanged: locationModel.update(searchString)
    Component.onCompleted: locationModel.update(searchString)

    Text {
        visible: locationModel.networkError !== ""
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: Theme.paddingLarge
        width: parent.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        anchors.centerIn: parent
        text: locationModel.networkError
        color: Theme.errorColor
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WrapAnywhere
    }

    SilicaListView {
        model: locationModel
        anchors.fill: parent
        currentIndex: -1 // otherwise currentItem will steal focus
        header:  Column {
            width: parent.width

            PageHeader {
                title: "Виберіть місце подорожі"
            }

            SearchField {
                id: locationSearchField
                width: parent.width

                Binding {
                    target: locationDialog
                    property: "searchString"
                    value: locationSearchField.text.toLowerCase().trim()
                }
            }
        }

        delegate: BackgroundItem {
            id: backgroundItem
            highlighted: model.id === locationDialog.locationId

            ListView.onAdd: AddAnimation {
                target: backgroundItem
            }
            ListView.onRemove: RemoveAnimation {
                target: backgroundItem
            }

            onClicked: {
                locationDialog.locationId=model.id
                locationDialog.locationName=model.name
            }

            Label {
                x: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                color: searchString.length > 0 ? (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
                                               : (highlighted ? Theme.highlightColor : Theme.primaryColor)
                textFormat: Text.StyledText
                text: Theme.highlightText(model.name, searchString, Theme.highlightColor)
                truncationMode: TruncationMode.Fade
                wrapMode: "WordWrap"
                width: parent.width - 2 * Theme.horizontalPageMargin
            }
        }

        VerticalScrollDecorator {}

    }

}
