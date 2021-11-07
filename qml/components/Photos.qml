import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    property var photos: []

    id: photosComponent
    width: parent.width
    height: list.heightImage + photoFrame.height + Theme.paddingMedium
    z: 1

    Rectangle {
        id: photoFrame
        width: photosComponent.width
        height: Math.floor(photosComponent.width * list.heightImage / list.widthImage)
        Behavior on scale { NumberAnimation { duration: 400; easing.type: Easing.OutCubic } }
        Behavior on x { NumberAnimation { duration: 400; easing.type: Easing.OutCubic } }
        Behavior on y { NumberAnimation { duration: 400; easing.type: Easing.OutCubic } }
        smooth: true
        antialiasing: true
        z: 2
        Image{
            id: bigImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            antialiasing: true
            clip: true
        }
        PinchArea {
            anchors.fill: parent
            pinch.target: photoFrame
            pinch.minimumRotation: 0
            pinch.maximumRotation: 0
            pinch.minimumScale: 0.8
            pinch.maximumScale: 10
            pinch.dragAxis: Pinch.XAndYAxis
            onPinchFinished: function(){
                photoFrame.scale = 1.0
                photoFrame.y = 0.0
                photoFrame.x = 0.0
            }
        }
    }

    Flickable {
        id: thumbs
        z: 0
        height: list.heightImage
        width: parent.width
        contentWidth: list.width
        y: photoFrame.height + Theme.paddingMedium

        ListView {
            id: list
            property int selected: 0
            property int widthImage: 160
            property int heightImage: 120
            width: widthImage * count
            orientation: Qt.Horizontal
            model: photos

            delegate: MouseArea{
                width: list.widthImage
                height: list.heightImage
                onClicked: {
                    list.selected = index
                    bigImage.source = "https://newimg.otpusk.com/2/800x600/" + modelData
                }
                Component.onCompleted: {
                    if(index === 0){
                        list.selected = index
                        bigImage.source = "https://newimg.otpusk.com/2/800x600/" + modelData
                    }
                }

                Rectangle {
                    id: border
                    visible: list.selected === index
                    color: Theme.highlightColor
                    anchors.centerIn: parent
                    width: thumb.width
                    height: thumb.height
                    z: 0
                }
                Image {
                    id: thumb
                    source: "https://newimg.otpusk.com/2/" + list.widthImage + "x" + list.heightImage + "/" + modelData
                    states: [
                        State {
                            name: "faded"
                            when: !thumbs.atXEnd && (index + 1) * list.widthImage > thumbs.contentX + thumbs.width - prevBtn.width - Theme.horizontalPageMargin || !thumbs.atXBeginning && index * list.widthImage < thumbs.contentX + prevBtn.width + Theme.horizontalPageMargin
                            PropertyChanges { target: thumb; opacity: 0.4 }
                        },
                        State {
                            name: "selected"
                            when: list.selected === index
                            PropertyChanges { target: thumb; scale: 0.8 }
                        }
                    ]
                    transitions: Transition {
                        NumberAnimation { properties: "opacity,scale"; duration: 200 }
                    }
                }
            }
        }
    }
    IconButton {
        id: prevBtn
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: thumbs.verticalCenter
        }
        z: 1
        visible: !thumbs.atXBeginning
        icon.source: "image://theme/icon-m-left"
        onClicked: {
            thumbs.flick(1500.0, 0)
        }
    }
    IconButton {
        id: nextBtn
        anchors {
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: thumbs.verticalCenter
        }
        z: 1
        visible: !thumbs.atXEnd
        icon.source: "image://theme/icon-m-right"
        onClicked: {
            thumbs.flick(-1500.0, 0)
        }
    }

}
