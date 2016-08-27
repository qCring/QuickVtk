import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ScrollView {

    style: ScrollViewStyle {
        transientScrollBars: false;
        handleOverlap: 0

        handle: Rectangle {
            Rectangle {
                width: 7;
                height: control.viewport.height * control.viewport.height / control.contentItem.height - 4;
                color: "#353B45";
                radius: 4;
            }
        }

        decrementControl: Item {}

        incrementControl: Item {}

        scrollBarBackground: Item{
            width: 10
            height: 10
        }

        corner: Item {}
    }
}
