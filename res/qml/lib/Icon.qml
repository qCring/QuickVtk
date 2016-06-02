import QtQuick 2.6

import "Icons.js" as Icons

Text
{
    property var types: Icons.Types;
    property string type;

    textFormat: Text.PlainText;
    style: Text.Normal;
    color: enabled ? "#9DA5B4" : "#6E7582"
    font.family: "FontAwesome";
    verticalAlignment: Text.AlignVCenter;
    text: type;
}
