import QtQuick 2.5

import "Icons.js" as Icons

Text
{
    property var types: Icons.Types;
    property string type: "-"

    textFormat: Text.PlainText;
    style: Text.Normal;
    color: "#fff"
    font.family: "FontAwesome";
    verticalAlignment: Text.AlignVCenter;
    text: type;
}
