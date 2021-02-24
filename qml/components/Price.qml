import QtQuick 2.0
import Sailfish.Silica 1.0

Row {

    id: root

    property var price
    property var priceUah
    property var currency

    spacing: Theme.paddingLarge
    Label {
        id: priceUahLabel
        font.pixelSize: Theme.fontSizeLarge
        color: Theme.primaryColor
        text: root.priceUah + "₴"
        leftPadding: Theme.horizontalPageMargin
    }
    Label {
        anchors.baseline: priceUahLabel.baseline
        font.pixelSize: Theme.fontSizeMedium
        color: Theme.secondaryColor
        text: {
            var t = root.price
            switch(root.currency){
            case "eur":
                t += "€"
                break;
            case "usd":
                t += "$"
                break;
            default:
                t += root.currency
                break;
            }
        }
    }
}
