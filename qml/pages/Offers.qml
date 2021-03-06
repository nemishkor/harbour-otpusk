import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {

    SilicaListView {
        anchors.fill: parent
        spacing: Theme.paddingMedium
        delegate: OfferListItem {
            offerId: model.id
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
        model: offersModel
        header: PageHeader {
            title: "Інші ціни туру (" + offersModel.rowCount() + ")"
            width: parent.width
        }

        VerticalScrollDecorator {}
    }

}
