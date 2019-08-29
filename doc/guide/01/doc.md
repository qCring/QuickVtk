QuickVtk
===

#### User Guide
## 01 - Getting started with QuickVtk

This article covers how to set up an external text editor for proper code formatting and how to compile and run QML code using QuickVtk

#### 1. Using an external editor
The built-in code editor still needs a lot of work and is currently deactivated. It is recommended to use external software like [**Atom**](https://atom.io/) or any other editor you feel comfortable working with. Most editors should provide a way to enable QML syntax highlighting. In case you're using [**Atom**](https://atom.io/), install the `language-qml` package

Create a new file in the editor of your choice, paste the following Hello, World snippet and save the file as `.qml` on your system

```
import QtQuick 2.3

Text {
    anchors.centerIn: parent

    font.bold: true
    font.pointSize: 40
    
    text: "Hello, QuickVtk"
    color: "#fff"
}

```

#### 2. Compile and run QML code in QuickVtk
Open QuickVtk and load the newly created file via **File &rarr; Load...** from the menu. Internally, the selected file will be observed. Any time a modification is registered (by saving the file externally), QuickVtk will be notified. An indicator on the lower-left of the application window informs about the state of the currently observed file. With `autorun` enabled, QuickVtk will automatically compile and run the code from the opened file. The generated output will be embedded in the 'preview' area on the right.

In this screenshot, [**Atom**](https://atom.io/) and QuickVtk are opened side by side and both applications are operating on the same file. Saving the file in [**Atom**](https://atom.io/) will trigger QuickVtk to reload, compile and run the code immediately since `autorun` is enabled

<center>
	<image src="screen-01.png">
</center>

#### 3. Loading examples
There are also some examples available to demonstrate how to access different types from the [**VTK**](https://vtk.org/) framework. You can load example `.qml` files from the menu via **Help &rarr; Examples**