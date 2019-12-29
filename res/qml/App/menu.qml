import QtQuick 2.12

import Lib 1.0 as Lib

Row {
  spacing: 4

  Repeater {
    id: repeater;
    model: App.menu.items

    FocusScope {
      id: item

      width: label.width + 12
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;

      Lib.Label {
        id: label

        anchors.centerIn: parent
        text: model.label
        color: item.focus ? "#fff" : "#9DA5B4";
        font.pointSize: 14;
      }

      MouseArea {
        anchors.fill: parent
        enabled: modelData.items.length > 0;

        onClicked: {
          item.focus = !item.focus;
        }
      }

      Rectangle {
        visible: item.focus;

        anchors.top: parent.bottom;

        width: col.width;
        height: col.height;
        color: "#ee181A1F"
        border.color: "#333842"
        radius: 4;

        Column {
          id: col;
          anchors.left: parent.left;

          Repeater {
            model: modelData.items;

            Item {
              width: Math.max(content.width + 50, col.width);
              height: content.height + 8;

              Row {
                id: content;

                spacing: 8;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: 8;

                property string color: model.enabled ? ma_item.containsMouse ? "#fff" : "#9DA5B4" : "#6E7582";

                Lib.Icon {
                  icon: icons[model.icon] != undefined ? icons[model.icon] : "";
                  anchors.verticalCenter: parent.verticalCenter;
                  width: 20;
                  color: content.color;
                }

                Lib.Label {
                  text: model.label;
                  color: content.color;
                  anchors.verticalCenter: parent.verticalCenter;
                  font.pointSize: 14;
                }
              }

              Rectangle {
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;
                height: 1;
                color: "#333842";
                visible: model.separator;
              }

              MouseArea {
                id: ma_item;

                anchors.fill: parent;
                hoverEnabled: true;

                onClicked: {
                  if (!model.enabled) {
                    return;
                  }

                  if (model.items.length > 0) {
                    inner.visible = true;
                  } else {
                    item.focus = false;
                    App.menu.select(modelData);
                  }
                }

                onEntered: {
                  if (model.items.length > 0) {
                    inner.retain();
                    openTimer.restart();
                  }
                }

                onExited: {
                  if (model.items.length > 0) {
                    openTimer.stop();
                    inner.hide();
                  }
                }

                Timer {
                  id: openTimer;
                  interval: 500;

                  onTriggered: {
                    inner.visible = true;
                  }
                }
              }

              Lib.Icon {
                visible: model.items.length > 0;
                icon: icons.fa_caret_right;

                anchors.verticalCenter: parent.verticalCenter;
                anchors.right: parent.right;

                width: 20;
                color: content.color;
              }

              Rectangle {
                id: inner;
                visible: false;

                anchors.leftMargin: -4;
                anchors.left: parent.right;
                anchors.top: parent.top;
                height: innerCol.height;
                width: innerCol.width;

                Timer {
                  id: hideTimer;
                  interval: 1000;

                  onTriggered: {
                    inner.visible = false;
                  }
                }

                function retain() {
                  hideTimer.running = false;
                }

                function hide() {
                  hideTimer.restart();
                }

                color: "#ee181A1F"
                border.color: "#333842"

                radius: 4;

                Column {
                  id: innerCol;

                  Repeater {
                    model: modelData.items;

                    Item {
                      id: innerItem;
                      property string color: innerMA.containsMouse ? "#fff" : "#9DA5B4";
                      width: Math.max(innerLabel.width + 50, innerCol.width);
                      height: innerLabel.height + 10;

                      Lib.Label {
                        id: innerLabel;

                        text: model.label;
                        color: innerItem.color;
                        font.pointSize: 14;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.left: parent.left;
                        anchors.leftMargin: 8;
                      }

                      Rectangle {
                        anchors.left: parent.left;
                        anchors.right: parent.right;
                        anchors.bottom: parent.bottom;
                        height: 1;
                        color: "#333842";
                        visible: model.separator;
                      }

                      MouseArea {
                        id: innerMA;
                        anchors.fill: parent;
                        hoverEnabled: true;

                        onClicked: {
                          item.focus = false;
                          App.menu.select(modelData);
                        }

                        onExited: {
                          inner.hide();
                        }

                        onEntered: {
                          inner.retain();
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
