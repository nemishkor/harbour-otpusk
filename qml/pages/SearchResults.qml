import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.Portrait


    // Begin loader part

    property bool _loading: toursLoader.loading
    property bool _replyFailed: toursLoader.replyFailed
    property bool _total: toursLoader.total

    onStatusChanged: {
        if (status == PageStatus.Active && toursLoader.tourModel.count === 0) {
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

                delegate: TourListItem {
                    hotelId: model.id
                    photo: model.photo
                    stars: model.stars
                    name: model.name
                    ratingAvarage: model.ratingAvarage
                    ratingCount: model.ratingCount
                    country: model.country
                    city: model.city

                    offerId: model.offerId
                    dateFrom: model.dateFrom
                    dateTo: model.dateTo
                    roomType: model.roomType
                    adults: model.adults
                    childrenCount: model.childrenCount
                    childrenAges: model.childrenAges
                    nights: model.nights
                    foodType: model.foodType
                    roomName: model.roomName
                    price: model.price
                    priceUah: model.priceUah
                    currency: model.currency
                    transport: model.transport
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
