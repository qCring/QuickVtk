import QtQuick 2.6

import Lib 1.0 as Lib

ListView {
    visible: App.typeList.visible;
    clip: true;
    width: 420;

    boundsBehavior: Flickable.StopAtBounds;

    model: App.typeList;
    delegate: Symbol {
        symbol: model.symbol;
    }
}
