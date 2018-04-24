import QtQuick 2.0

Rectangle{
    width:200;
    height:200;
    x:0;
    y:0;
    radius: height/2;
    color:"#888888";
    //opacity:0.9;
    signal valueChanged(int x, int y)
    MultiPointTouchArea {
        anchors.fill: parent
        minimumTouchPoints: 1
        maximumTouchPoints: 1
        touchPoints: [
            TouchPoint { id: touch }
        ]
        onReleased:{
            valueChanged(0, 0)
        }
        onUpdated: {
            valueChanged(touch.x - parent.width/2, touch.y - parent.height/2)
        }
        onPressed: {
            valueChanged(touch.x - parent.width/2, touch.y - parent.height/2)
        }
        states: State {
            name: "reset"; when: touch.pressed
            PropertyChanges {
                target: rocker;
                color: "blue";
                opacity:0.9;
                //x:Math.min(Math.max(0,touch.x - width/2),parent.width - width);
                //y:Math.min(Math.max(0,touch.y - height/2),parent.height - height);
                x:_r * Math.cos(theta) + parent.width/2 - width/2;
                y:_r * Math.sin(theta) + parent.height/2 - height/2;
            }
        }
    }
    Rectangle{
        id:rocker
        width:50;
        height:50;
        radius: height/2;
        x:parent.width/2 - width/2;
        y:parent.height/2 - height/2;
        color:"red";
        opacity:0.6;
        property int _x:touch.x - parent.width/2;
        property int _y:touch.y - parent.height/2;
        property real _r: Math.min(Math.sqrt(_x*_x + _y*_y), parent.width/2);
        property real theta: Math.atan2(_y,_x);
    }
}
