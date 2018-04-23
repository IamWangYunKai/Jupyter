import QtQuick 2.0

Rectangle{
    width:200;
    height:200;
    x:0;
    y:0;
    radius: height/2;
    color:"grey";
    MultiPointTouchArea {
        anchors.fill: parent
        minimumTouchPoints: 1
        maximumTouchPoints: 1
        touchPoints: [
            TouchPoint { id: touch }
        ]
    }
    Rectangle{
        id:rocker
        width:50;
        height:50;
        radius: height/2;
        x:Math.min(Math.max(0,touch.x - width/2),parent.width - width);
        y:Math.min(Math.max(0,touch.y - height/2),parent.height - height);
        color:"red";
    }
}
