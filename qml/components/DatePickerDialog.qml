import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog{
    id: dialog
    property var dialogAcceptDestination
    property var dialogOnAcceptPendingChanged
    property int dialogAcceptDestinationAction: PageStackAction.Push
    property date min
    property date max
    property string title
    property alias dateText: datePicker.dateText
    property alias date: datePicker.date

    Component.onCompleted: {
        console.log(min)
    }

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
                            if (model.month === model.primaryMonth) {
                                var date = new Date(model.year, model.month-1, model.day,12,0,0)
                                if(min.toString() !== "Invalid Date" && date < min){
                                    return palette.secondaryColor
                                }
                                if(max.toString() !== "Invalid Date" && date > max){
                                    return palette.secondaryColor
                                }
                                return palette.primaryColor
                            }
                            return palette.secondaryColor
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
                        var selectedDate = new Date(model.year, model.month-1, model.day,12,0,0)
                        if(min.toString() !== "Invalid Date" && selectedDate < min){
                            return
                        }
                        if(max.toString() !== "Invalid Date" && selectedDate > max){
                            return
                        }
                        datePicker.date = selectedDate
                    }
                }
            }
        }
    }

}
