import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    property bool _loading: toursLoader.loading
    property bool _replyFailed: toursLoader.replyFailed
    property bool _total: toursLoader.total

    onStatusChanged: {
        if (status == PageStatus.Active) {
            toursLoader.load(searchParameters)
        }
    }

    on_LoadingChanged: checkLoading()
    on_ReplyFailedChanged: checkLoading()
    on_TotalChanged: checkLoading()

    function checkLoading(){
        hintLabel.visible = false
        hint.stop()
        if(status == PageStatus.Active && !_loading && !_replyFailed){
            if(_total > 0){
                console.log("Loaded and results not empty")
                pageStack.replace(Qt.resolvedUrl("SearchResults.qml"), {},
                                  PageStackAction.Immediate)
            } else {
                hintLabel.visible = true
                hint.start()
            }
        }

    }

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    InteractionHintLabel {
        id: hintLabel
        visible: false
        anchors.bottom: parent.bottom
        opacity: 1.0
        Behavior on opacity { FadeAnimation {} }
        text: "За вашим запитом турів не знайдено. Спробуйте змінити дату початку туру чи вибрати інший напрямок"
    }

    TouchInteractionHint {
        id: hint
        interactionMode: TouchInteraction.Swipe
        direction: TouchInteraction.Right
        loops: Animation.Infinite
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: parent.height

        Column{
            width: parent.width
            spacing: Theme.paddingMedium
            PageHeader {
                title: qsTr("Опитування туроператорів")
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
            ProgressBar{
                id: progressBar
                visible: toursLoader.loading
                width: parent.width
                maximumValue: 100
                value: toursLoader.progress
                label: toursLoader.progress + " %"
            }
        }

        VerticalScrollDecorator {}
    }

}
