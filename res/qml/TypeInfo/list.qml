import QtQuick 2.12

import Lib 1.0 as Lib

ListView {
    visible: context.typeList.visible;
    clip: true;
    width: 420;

    boundsBehavior: Flickable.StopAtBounds;

    model: context.typeList;
    delegate: Symbol {
        symbol: model.symbol;
    }
}
