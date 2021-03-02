import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {

    property var offers

    SilicaListView {
        spacing: Theme.paddingMedium
        delegate: OfferListItem {}
        model: offers
        header: PageHeader {
            title: "Інші ціни туру"
            width: parent.width
        }

        VerticalScrollDecorator {}
    }

}
