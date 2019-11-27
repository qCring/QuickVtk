import QtQuick 2.6

Row {
  spacing: 4

  Repeater {
    id: repeater;
    model: Controllers.menu.items

    FocusScope {
      id: item

      width: label.width + 12
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;

      Text {
        id: label

        anchors.centerIn: parent
        text: model.name
        color: item.focus ? "#fff" : "#a0a0a0";
      }

      MouseArea {
        anchors.fill: parent

        onClicked: {
          item.focus = !item.focus;
        }
      }

      Rectangle {
        visible: item.focus;

        anchors.top: parent.bottom;

        width: col.width;
        height: col.height;
        color: "#aa111111"
        radius: 4;

        Column {
          id: col;
          anchors.left: parent.left;

          Repeater {
            model: repeater.model[index].items;

            Item {
              width: Math.max(label.width + 20, col.width);
              height: label.height + 8;

              Text {
                id: label
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: 9;

                text: model.name;
                color: ma_item.containsMouse ? "#fff" : "#a0a0a0";
              }

              MouseArea {
                id: ma_item;

                anchors.fill: parent;
                hoverEnabled: true;

                onClicked: {
                  Controllers.menu.select(modelData);
                  item.focus = false;
                }
              }
            }
          }
        }
      }
    }
  }
}
