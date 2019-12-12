import QtQuick 2.12

import "fontawesome.js" as FA

Text {
    id: root;

    property var icons: FA.Icons;
    property alias icon: root.text;
    property alias pointSize: root.font.pointSize;

    font.family: "FontAwesome";
    font.pointSize: 13;
    style: Text.Normal;
    color: enabled ? "#9DA5B4" : "#6E7582"
    textFormat: Text.PlainText;
    verticalAlignment: Text.AlignVCenter;
}
