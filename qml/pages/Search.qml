import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: root

    property int locationId
    property string locationName
    property int fromCityId
    property string fromCityName
    property date startDate
    property date endDate
    property bool selectedDates
    property int length

    Component.onCompleted: {
        fromCityId = 1544 // kyiv
        startDate = new Date()
        startDate.setDate(startDate.getDate() + 30)
        startDate.setHours(0)
        startDate.setMinutes(0)
        startDate.setSeconds(0)
        endDate = new Date()
        endDate.setDate(endDate.getDate() + 37)
        endDate.setHours(0)
        endDate.setMinutes(0)
        endDate.setSeconds(0)
        selectedDates = false
        length = 0
    }

    onStatusChanged: {
        if (status == PageStatus.Active && locationId === 0) {
            pageStack.animatorPush(locationDialogPage)
        }
    }

    onLocationIdChanged: {
        searchDatesModel.update(locationId)
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        VerticalScrollDecorator {}

        PullDownMenu {
            MenuItem {
                text: "Новий пошук"
                onClicked: pageStack.animatorPush(locationDialogPage)
            }
        }

        Column {
            id: column
            width: parent.width

            PageHeader { title: "Пошук турів" }

            Column {
                width: parent.width
                spacing: -Theme.paddingSmall

                ValueButton{
                    label: "Куди"
                    value: root.locationName
                    onClicked: pageStack.animatorPush(locationDialogPage)
                }

                Component {
                    id: locationDialogPage

                    LocationDialog{
                        id: locationDialog
                        dialog.acceptDestination: root
                        dialog.acceptDestinationAction: PageStackAction.Pop
                        dialog.onAcceptPendingChanged: {
                            if (acceptPending) {
                                root.locationId = locationDialog.locationId
                                root.locationName = locationDialog.locationName
                            }
                        }
                    }

                }

                ComboBox {
                    currentIndex: 4
                    label: "Місто відправлення"
                    menu: ContextMenu {
                        MenuItem { text: "Івано-Франківськ"; onClicked: root.fromCityId = 1760 }
                        MenuItem { text: "Вінниця"; onClicked: root.fromCityId = 1934 }
                        MenuItem { text: "Дніпро"; onClicked: root.fromCityId = 1874 }
                        MenuItem { text: "Запоріжжя"; onClicked: root.fromCityId = 1875 }
                        MenuItem { text: "Київ"; onClicked: root.fromCityId = 1544 }
                        MenuItem { text: "Кривий Ріг"; onClicked: root.fromCityId = 1883 }
                        MenuItem { text: "Луцьк"; onClicked: root.fromCityId = 2024 }
                        MenuItem { text: "Львів"; onClicked: root.fromCityId = 1397 }
                        MenuItem { text: "Миколаїв"; onClicked: root.fromCityId = 1963 }
                        MenuItem { text: "Одеса"; onClicked: root.fromCityId = 1358 }
                        MenuItem { text: "Полтава"; onClicked: root.fromCityId = 1952 }
                        MenuItem { text: "Рівне"; onClicked: root.fromCityId = 1981 }
                        MenuItem { text: "Суми"; onClicked: root.fromCityId = 1962 }
                        MenuItem { text: "Ужгород"; onClicked: root.fromCityId = 1398 }
                        MenuItem { text: "Харків"; onClicked: root.fromCityId = 1880 }
                        MenuItem { text: "Херсон"; onClicked: root.fromCityId = 2012 }
                        MenuItem { text: "Чернівці"; onClicked: root.fromCityId = 1708 }
                    }
                }

                ValueButton {
                    id: datesButton
                    width: parent.width
                    visible: searchDatesModel.count > 0
                    label: "Дати туру"
                    value: "вкажіть"
                    onClicked: {
                        pageStack.animatorPush(startDatePickerDialogPage, { date: root.startDate, min: root.startDate })
                    }
                }

                Label{
                    visible: searchDatesModel.count === 0
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2 * Theme.horizontalPageMargin
                    text: "Не знайдено доступних дат для вибраної локації"
                    color: Theme.errorColor
                    wrapMode: "WordWrap"
                }

                Component{
                    id: startDatePickerDialogPage

                    DatePickerDialog{
                        id: startDatePicker
                        dialogAcceptDestination: endDatePickerDialogPage
                        onAcceptPendingChanged: {
                            if (acceptPending) {
                                // Tell the destination page what the selected category is
                                acceptDestinationInstance.dateStart = startDatePicker.date
                                acceptDestinationInstance.dateStartText = startDatePicker.dateText
                                acceptDestinationInstance.min = startDatePicker.date
                                acceptDestinationInstance.date = startDatePicker.date
                                acceptDestinationInstance.title = "Дата повернення"
                                var max = startDatePicker.date
                                max.setDate(max.getDate() + 14)
                                acceptDestinationInstance.max = max
                            }
                        }
                        title: "Дата вильоту"
                    }
                }

                Component{
                    id: endDatePickerDialogPage

                    DatePickerDialog{
                        id: endDatePicker
                        property date dateStart
                        property string dateStartText
                        dialogAcceptDestination: root
                        dialogAcceptDestinationAction: PageStackAction.Pop
                        onAcceptPendingChanged: {
                            console.log(acceptPending)
                            if (acceptPending) {

//                                console.log(dateStartText)
//                                console.log(endDatePicker.dateText)
                                datesButton.value = dateStartText + " - " + endDatePicker.dateText
                                root.startDate = dateStart
                                root.endDate = endDatePicker.date
                                root.selectedDates = true

                                var day = dateStart.getDate()
                                if(day < 10)
                                    day = "0" + day
                                var month = startDate.getMonth() + 1
                                if(month < 10)
                                    month = "0" + month
                                searchDatesModel.selectDate(dateStart.getFullYear() + "-" + month + "-" + day)

                            }
                        }
                        min: new Date()
                        date: new Date()
                    }
                }

                ValueButton{
                    label: "Тривалість подорожі"
                    value: length === 0 ? "вкажіть" : (length + " днів / " + (length - 1) + " ночей")
                    onClicked: pageStack.animatorPush(lengthDialogPage)
                }

                Component{
                    id: lengthDialogPage

                    Dialog{
                        id: lengthDialog
                        property int length
                        onAcceptPendingChanged: {
                            if (acceptPending) {
                                root.length = lengthDialog.length
                            }
                        }
                        DialogHeader {
                            id: lengthDialogHeader
                            title: "Тривалість туру"
                        }
                        SilicaListView{
                            anchors.top: lengthDialogHeader.bottom
                            anchors.bottom: parent.bottom
                            width: parent.width
                            model: searchDatesModel.lengths
                            delegate: BackgroundItem {
                                highlighted: Number(modelData) === lengthDialog.length
                                onClicked: {
                                    console.log("clicked")
                                    lengthDialog.length=Number(modelData)
                                    console.log(modelData)
                                    console.log(searchDatesModel.lengths)
                                }
                                Label{
                                    anchors.verticalCenter: parent.verticalCenter
                                    x: Theme.pageStackIndicatorWidth
                                    text: modelData + " днів / " + (modelData - 1) + " ночей"
                                }
                            }
                        }
                    }
                }

            }

        }

    }

}
