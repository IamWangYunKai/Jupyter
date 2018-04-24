import QtQuick 2.0

Rectangle{
    width:200;
    height:200;
    x:0;
    y:0;
    radius: height/2;
    color:"#808080"
    signal valueChanged(int x, int y)
    MultiPointTouchArea {
        anchors.fill: parent
        minimumTouchPoints: 1
        maximumTouchPoints: 1
        touchPoints: [
            TouchPoint { id: touch }
        ]
        onUpdated: {
            valueChanged(touch.x - parent.width/2, touch.y - parent.height/2)
        }
        onPressed: {
            //rocker.x = Math.min(Math.max(0,touch.x - rocker.width/2),parent.width - rocker.width);;
            //rocker.y = Math.min(Math.max(0,touch.y - rocker.height/2),parent.height - rocker.height);;
        }

        onReleased: {
            //rocker.x = 0;
            //rocker.y = 0;
        }
        states: State {
            name: "resized"; when: touch.pressed
            PropertyChanges { target: rocker; color: "blue"; x:0; y:0}
        }
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
