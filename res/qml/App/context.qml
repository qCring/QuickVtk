import QtQuick 2.6
import Lib 1.0 as Lib

Item  {

  property alias utilsView: utilsView;
  property var file: Controllers.document.file;

  FocusScope {
    id: header;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;
    height: row.height;

    Row {
      id: row;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;

      Lib.Button {
        icon: icons.fa_list;
        use_toggle: true;
        toggle_on_click: false;
        toggle: focus;
        focus: true;

        onClicked: {
          this.forceActiveFocus();
          utilsView.visible = true;
          codeView.visible = false;
          errorsView.visible = false;
        }
      }

      Lib.Button {
        icon: icons.fa_file;
        use_toggle: true;
        toggle_on_click: false;
        toggle: focus;

        onClicked: {
          this.forceActiveFocus();
          utilsView.visible = false;
          codeView.visible = true;
          errorsView.visible = false;
        }
      }

      Lib.Button {
        icon: icons.fa_exclamation_triangle;
        use_toggle: true;
        toggle_on_click: false;
        toggle: focus;
        label.color: (file != undefined) && (file.errors.length) > 0 ? "#ff0000" : "#aaa";

        onClicked: {
          this.forceActiveFocus();
          utilsView.visible = false;
          codeView.visible = false;
          errorsView.visible = true;
        }
      }
    }
  }

  Item {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: header.bottom;
    anchors.bottom: parent.bottom;

    Item {
      id: utilsView;

      anchors.fill: parent;
    }

    CodeView {
      id: codeView;

      visible: false;
      anchors.fill: parent;
    }

    Errors {
      id: errorsView;

      visible: false;
      anchors.fill: parent;
    }
  }
}
