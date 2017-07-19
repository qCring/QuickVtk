import QtQuick 2.6

import Lib 1.0 as Lib

ListView {
    visible: Controllers.typeList.visible;
    clip: true;
    width: 420;

    boundsBehavior: Flickable.StopAtBounds;

    model: Controllers.typeList;
    delegate: Symbol {
        symbol: model.symbol;
    }
}
