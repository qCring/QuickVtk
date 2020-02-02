import QtQuick 2.12

import UI 1.0 as UI

Item {
  anchors.fill: parent;

  OverView {
    onSelectSymbol: detailView.symbol = symbol;

    visible: !detailView.symbol;
  }

  DetailView {
    id: detailView;

    visible: symbol;
  }
}
