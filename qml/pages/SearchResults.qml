import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All


    // Begin loader part

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
                // TourModel::firstItemIndexOfLastPage()
                var index = toursLoader.tourModel.firstItemIndexOfLastPage();
                console.log("Loaded hotels/tours and results not empty. Focus at " + index + " item")
                toursList.positionViewAtIndex(index, ListView.Beginning)
            } else {
                hintLabel.visible = true
                hint.start()
            }
        }

    }

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

    // End loader part


    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        id: fl
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: parent.height

        Column{
            id: pageHeader
            width: parent.width
            spacing: Theme.paddingMedium
            PageHeader {
                title: toursLoader.loading ? qsTr("Опитування туроператорів") : qsTr("Результати")
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

        Item {
            id: toursItem
            width: parent.width
            height: parent.height - pageHeader.height
            anchors.top: pageHeader.bottom

            SilicaListView {
                id: toursList
                anchors.fill: parent
                clip: true
                model: toursLoader.tourModel
                opacity: {
                    if(_loading){
                        return 0.5
                    }
                    if(_total === 0){
                        return 0.0
                    }

                    return 1.0
                }

                delegate: ListItem{
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

            }

        }

        VerticalScrollDecorator {}

        PushUpMenu{
            visible: !toursLoader.loading && toursLoader.total > 0 && toursLoader.tourModel.count < toursLoader.total
            MenuItem {
                text: "Завантажити більше"

                onClicked: {
                    toursLoader.page = toursLoader.page + 1
                    toursLoader.load(searchParameters)
                }
            }
        }

    }

    Rectangle{
        // pagination info
        visible: toursLoader.total !== 0
        color: Theme.highlightDimmerColor
        radius: 10 * Theme.pixelRatio
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: Theme.paddingLarge
        width: 280
        height: Theme.fontSizeMedium * 1.1
        Text {
            anchors.centerIn: parent
            text: String(toursLoader.tourModel.count) + " / " + String(toursLoader.total)
            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall
        }
    }

}
