import QtQuick 2.6
import QtQuick.Controls 1.4

TextEdit {
    font.family: "Bitstream Vera Sans Mono";
    font.pointSize: 13;

    selectByMouse: true
    mouseSelectionMode: TextEdit.SelectCharacters
    selectionColor: "#3d4856"
    color: "#fff"

    textFormat: TextEdit.PlainText
    wrapMode: TextEdit.NoWrap
}
