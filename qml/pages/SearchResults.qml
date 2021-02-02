import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    onStatusChanged: {
        if (status == PageStatus.Active) {
            toursLoader.load(searchParameters)
        }
    }

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    InteractionHintLabel {
        id: hintLabel
        visible: !toursLoader.loading && !toursLoader.replyFailed && toursLoader.total === 0
        anchors.bottom: parent.bottom
        opacity: 1.0
        Behavior on opacity { FadeAnimation {} }
        text: "За вашим запитом турів не знайдено. Спробуйте змінити дату початку туру чи вибрати інший напрямок"
        onVisibleChanged: {
            if(visible){
                hint.start()
            } else {
                hint.stop()
            }
        }
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
            height: parent.height - Theme.paddingMedium - pageHeader.height
            anchors.top: pageHeader.bottom

            SilicaListView {
                anchors.fill: parent
                clip: true
                model: toursLoader.tourModel
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
                                progressColor: ratingAvarage > 6 ? "#8051D511" : (ratingAvarage > 4 ? "#80DEB321" : "#80EC4713")
                                Label{
                                    anchors.fill: parent
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignHCenter
                                    text: ratingCount
                                    font.pixelSize: ratingCount > 999 ? Theme.fontSizeSmall : Theme.fontSizeMedium
                                }
                                Label{
                                    anchors.top: parent.bottom
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    horizontalAlignment: Text.AlignHCenter
                                    text: ratingAvarage + "/10"
                                    font.pixelSize: Theme.fontSizeSmall
                                }
                            }
                        }

                        Text {
                            font.pixelSize: Theme.fontSizeSmall
                            color: Theme.secondaryColor
                            text: country + ", " + city
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
                                text: price + currency
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
