import QtQuick 2.12

import Lib 1.0 as Lib

Lib.List {
    clip: true;

    model: App.typeList;

    delegate: Symbol {
        symbol: model.symbol;
    }
}
