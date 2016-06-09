import QtQuick 2.6

import "Icons.js" as Icons

Text
{
    property var types: Icons.Types;
    property string type;

    font.family: "FontAwesome";
    font.pointSize: 13;
    style: Text.Normal;
    color: enabled ? "#9DA5B4" : "#6E7582"
    textFormat: Text.PlainText;
    verticalAlignment: Text.AlignVCenter;
    text: type;
}
