import QtQuick 2.5

import "./lib" as Lib

Rectangle {

    visible: App.symbols.visible;

    clip: true;
    color: "#21252B"

    ListView {
        anchors.fill: parent;

        model: App.symbols;
        delegate: SymbolView {
            symbol: model.symbol;
        }
    }

    Rectangle {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        width: 1;

        color: "#181A1F"
    }
}
