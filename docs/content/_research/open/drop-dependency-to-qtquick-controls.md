---
layout: subpage
nav: research
title: Drop Dependency to QtQuick.Controls
category: open
---

## Drop Dependency to QtQuick.Controls in QML
The most critical problem with [QtQuick.Controls](https://doc.qt.io/qt-5/qtquickcontrols-index.html) is [this reported issue](https://github.com/qCring/QuickVtk/issues/44). It seems that the use of the [Menu type](https://doc.qt.io/qt-5/qml-qtquick-controls2-menu.html) causes the application to become unresponsive after resizing the window.

This might not be a general issue but an edge-case in the context of QuickVtk (caused by the whole OpenGL context sharing between QML and VTK maybe). A working solution is to switch the application's root element from [ApplicationWindow](https://doc.qt.io/qt-5/qml-qtquick-controls2-applicationwindow.html) back to [Window](https://doc.qt.io/qt-5/qml-qtquick-window-window.html). But this means loosing the ability to use [Menu](https://doc.qt.io/qt-5/qml-qtquick-controls2-menu.html) elements.

Dropping [QtQuick.Controls](https://doc.qt.io/qt-5/qtquickcontrols-index.html) means implementing basic control elements from scratch which might take a while. But there's an advantage. QuickVtk would have a consistent look-and-feel across different platforms.
