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
    property int adults
    property var children

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

            PageHeader { title: "Новий пошук" }

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
                    label: "Початок туру"
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

                Row{
                    width: parent.width

                    ComboBox {
                        currentIndex: 1
                        label: "Дорослі"
                        width: parent.width / 2
                        menu: ContextMenu {
                            MenuItem { text: "1"; onClicked: root.adults = 1 }
                            MenuItem { text: "2"; onClicked: root.adults = 2 }
                            MenuItem { text: "3"; onClicked: root.adults = 3 }
                            MenuItem { text: "4"; onClicked: root.adults = 4 }
                            MenuItem { text: "5"; onClicked: root.adults = 5 }
                            MenuItem { text: "6"; onClicked: root.adults = 6 }
                            MenuItem { text: "7"; onClicked: root.adults = 7 }
                            MenuItem { text: "8"; onClicked: root.adults = 8 }
                        }
                    }
                    ValueButton {
                        id: childrenButton
                        width: parent.width
                        label: "Діти"
                        value: "вкажіть"
                        onClicked: {
                            pageStack.animatorPush(childrenDialogComponent)
                        }
                    }
                    Component{
                        id: childrenDialogComponent

                        Dialog{
                            id: childrenDialog
                            property int child1: 2
                            property int child2: 4
                            property int child3: 0
                            property int child4: 0
                            onAcceptPendingChanged: {
                                if (acceptPending) {
                                    var ages = []
                                    if(child1 > 0)
                                        ages.push(child1)
                                    if(child2 > 0)
                                        ages.push(child2)
                                    if(child3 > 0)
                                        ages.push(child3)
                                    if(child4 > 0)
                                        ages.push(child4)
                                    root.children = childrenDialog.ages
                                    childrenButton.value = ages.length > 0 ? ( ages.length + " (" + ages.join(', ') + ")" ) : '-'
                                }
                            }

                            DialogHeader {
                                id: childrenDialogHeader
                                title: "Вік дітей"
                            }

                            function yearsSuffix(age){
                                if(age === 1)
                                    return " рік"
                                if(age > 1 && age < 5)
                                    return " роки"
                                return " років"
                            }

                            function addChild(age){
                                if(child1 === 0){
                                    child1 = age
                                    return
                                }
                                if(child2 === 0){
                                    child2 = age
                                    return
                                }
                                if(child3 === 0){
                                    child3 = age
                                    return
                                }
                                if(child4 === 0){
                                    child4 = age
                                    return
                                }
                            }

                            Column{
                                id: childrenDialogColumn
                                anchors.top: childrenDialogHeader.bottom
                                anchors.bottom: parent.bottom
                                width: parent.width
                                spacing: Theme.paddingLarge

                                IconButton {
                                    id: removeChild1
                                    icon.source: "image://theme/icon-m-cancel"
                                    onClicked: childrenDialog.child1 = 0
                                    visible: childrenDialog.child1 > 0
                                    Label{
                                        anchors.left: removeChild1.right
                                        anchors.verticalCenter: removeChild1.verticalCenter
                                        text: childrenDialog.child1 + childrenDialog.yearsSuffix(childrenDialog.child1)
                                    }
                                }

                                IconButton {
                                    id: removeChild2
                                    icon.source: "image://theme/icon-m-cancel"
                                    onClicked: childrenDialog.child2 = 0
                                    visible: childrenDialog.child2 > 0
                                    Label{
                                        anchors.left: removeChild2.right
                                        anchors.verticalCenter: removeChild2.verticalCenter
                                        text: childrenDialog.child2 + childrenDialog.yearsSuffix(childrenDialog.child2)
                                    }
                                }

                                IconButton {
                                    id: removeChild3
                                    icon.source: "image://theme/icon-m-cancel"
                                    onClicked: childrenDialog.child3 = 0
                                    visible: childrenDialog.child3 > 0
                                    Label{
                                        anchors.left: removeChild3.right
                                        anchors.verticalCenter: removeChild3.verticalCenter
                                        text: childrenDialog.child3 + childrenDialog.yearsSuffix(childrenDialog.child3)
                                    }
                                }

                                IconButton {
                                    id: removeChild4
                                    icon.source: "image://theme/icon-m-cancel"
                                    onClicked: childrenDialog.child4 = 0
                                    visible: childrenDialog.child4 > 0
                                    Label{
                                        anchors.left: removeChild4.right
                                        anchors.verticalCenter: removeChild4.verticalCenter
                                        text: childrenDialog.child4 + childrenDialog.yearsSuffix(childrenDialog.child4)
                                    }
                                }

                                ButtonLayout {
                                    preferredWidth: Theme.buttonWidthMedium
                                    Button {
                                        visible: childrenDialog.child1 === 0 || childrenDialog.child2 === 0 || childrenDialog.child3 === 0 || childrenDialog.child4 === 0
                                        text: "Додати"
                                        onClicked: pageStack.push(addChildDialogComponent)
                                    }
                                    Component {
                                        id: addChildDialogComponent

                                        Page {

                                            SilicaListView {
                                                anchors.fill: parent
                                                model: ListModel{
                                                    ListElement{ age: 1 }
                                                    ListElement{ age: 2 }
                                                    ListElement{ age: 3 }
                                                    ListElement{ age: 4 }
                                                    ListElement{ age: 5 }
                                                    ListElement{ age: 6 }
                                                    ListElement{ age: 7 }
                                                    ListElement{ age: 8 }
                                                    ListElement{ age: 9 }
                                                    ListElement{ age: 10 }
                                                    ListElement{ age: 11 }
                                                    ListElement{ age: 12 }
                                                    ListElement{ age: 13 }
                                                    ListElement{ age: 14 }
                                                    ListElement{ age: 15 }
                                                    ListElement{ age: 16 }
                                                }

                                                header: PageHeader {
                                                    title: "Додати дитину"
                                                }

                                                delegate: BackgroundItem {
                                                    id: delegateItem

                                                    onClicked: {
                                                        childrenDialog.addChild(age)
                                                        pageStack.pop()
                                                    }

                                                    Label {
                                                        x: Theme.horizontalPageMargin
                                                        anchors.verticalCenter: parent.verticalCenter
                                                        width: parent.width - x*2
                                                        wrapMode: Text.Wrap
                                                        text: model.age + childrenDialog.yearsSuffix(model.age)
                                                        highlighted: delegateItem.highlighted
                                                    }
                                                }
                                                VerticalScrollDecorator {}
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }

                }

            }

        }

    }

}
