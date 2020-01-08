import QtQuick 2.12

Rectangle {
  id: root;

  width: label.width;
  height: label.height;

  property alias label: label;

  color: "#1B1D23";

  radius: 2;

  Label {
    id: label;

    anchors.centerIn: parent;
    leftPadding: 8;
    rightPadding: 8;
    font.weight: Font.Medium;
    font.pointSize: 11;

    padding: 1;
  }
}
