import QtQuick 2.12

Rectangle {
  id: root;

  width: frameless ? row.width + 6 : row.width + 24;
  height: label.height + 6;

  property alias label: label;
  property alias iconSize: icon.font.pointSize;
  property alias icon: icon.icon;
  property alias icons: icon.icons;
  property bool highlight: false;
  property bool frameless: false;
  property bool use_toggle: false;
  property bool toggle_on_click: true;
  property bool toggle: false;
  property bool highlighted: use_toggle ? toggle : highlight;

  color: frameless ? "#00000000" : highlighted ? "#2B68A4" : ma.pressed ? "#181A1F" : ma.containsMouse ? "#363C46" : "#333842"
  border.color: frameless ? "#00000000" : "#181A1F"

  radius: 2;

  signal clicked;
  signal doubleClicked;

  Row {
    id: row;

    anchors.centerIn: parent;

    spacing: 4;

    Icon {
      id: icon;

      anchors.verticalCenter: parent.verticalCenter;

      color: label.color;
    }

    Label {
      id: label;

      anchors.verticalCenter: parent.verticalCenter;

      font.weight: Font.Medium;
      color: enabled ? ma.pressed ? "#1D9FF2" : highlighted || ma.containsMouse ? "#fff" : "#9DA5B4" : "#6E7582";
    }
  }

  MouseArea {
    id: ma;

    anchors.fill: parent;

    propagateComposedEvents: true;
    hoverEnabled: true;

    onClicked: {
      if (root.use_toggle && root.toggle_on_click) {
        root.toggle = !root.toggle;
      }

      root.forceActiveFocus();
      root.clicked();
    }

    onDoubleClicked: {
      root.doubleClicked();
    }
  }
}
