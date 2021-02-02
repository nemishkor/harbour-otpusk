import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog{
    id: dialog
    property var dialogAcceptDestination
    property var dialogOnAcceptPendingChanged
    property int dialogAcceptDestinationAction: PageStackAction.Push
    property var allowedDates: searchDatesModel.dates
    property date min
    property date max
    property string title
    property alias dateText: datePicker.dateText
    property alias date: datePicker.date

    acceptDestination: dialogAcceptDestination
    onAcceptPendingChanged: dialogOnAcceptPendingChanged
    acceptDestinationAction: dialogAcceptDestinationAction

    Column {
        width: parent.width

        DialogHeader {
            title: dialog.title
        }
        DatePicker {
            id: datePicker
            daysVisible: true
            monthYearVisible: true
            weeksVisible: true
            delegate: Component {
                MouseArea {
                    width: datePicker.cellWidth
                    height: datePicker.cellHeight

                    function isAllowedDateToSelect(date){
                        if(
                                min.toString() !== "Invalid Date" && date < min ||
                                max.toString() !== "Invalid Date" && date > max
                        ){
                            return false
                        }
                        var month = date.getMonth() + 1
                        if(month < 10){
                            month = '0' + month
                        }
                        var day = date.getDate()
                        if(day < 10){
                            day = '0' + day
                        }
                        var dateString = date.getFullYear() + '-' + month + '-' + day
                        if(allowedDates.indexOf(dateString) === -1){
                            return false;
                        }
                        return true;
                    }

                    Label {
                        anchors.centerIn: parent
                        text: model.day.toLocaleString()
                        font.bold: model.day === datePicker._today.getDate()
                                    && model.month === datePicker._today.getMonth()+1
                                    && model.year === datePicker._today.getFullYear()
                        color: {
                            if (pressed && containsMouse) {
                                return palette.highlightColor
                            }
                            if (model.month !== model.primaryMonth) {
                                return palette.secondaryColor
                            }
                            var date = new Date(model.year, model.month-1, model.day,12,0,0)
                            if(isAllowedDateToSelect(date)){
                                return palette.highlightColor
                            }
                            return palette.primaryColor
                        }
                    }

                    function updateHighlight() {
                        datePicker._highlightedDate = pressed && containsMouse
                                ? new Date(model.year, model.month-1, model.day,12,0,0)
                                : undefined
                    }

                    onPressedChanged: updateHighlight()
                    onContainsMouseChanged: updateHighlight()
                    onClicked: {
                        console.log(allowedDates)
                        var selectedDate = new Date(model.year, model.month-1, model.day,12,0,0)
                        var allowed = isAllowedDateToSelect(selectedDate)
                        if(allowed){
                            datePicker.date = selectedDate
                        }
                    }
                }
            }
        }
    }

}
