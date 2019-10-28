---
layout: page
nav: guide
title: Getting started with QuickVtk
topics:
  - Setting up an external text editor
  - Compiling QML code
  - Loading examples
---

## Using an external editor
The built-in code editor still needs a lot of work and is currently deactivated. It is recommended to use external software like [Atom](https://atom.io/) or any other editor you feel comfortable working with. Most editors should provide a way to enable QML syntax highlighting. In case you're using [Atom](https://atom.io/), install the `language-qml` package

Create a new file in the editor of your choice, paste the following Hello, World snippet and save the file as *.qml* on your system

>"Hello, World" QML
{: .hl-caption}

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Text {
    anchors.centerIn: parent

    font.bold: true
    font.pointSize: 40

    text: "Hello, QuickVtk"
    color: "#fff"
}
{% endhighlight %}

## Compile and run QML code in QuickVtk
Open QuickVtk and load the newly created file via **File &rarr; Load...** from the menu. Internally, the selected file will be observed. Any time a modification is registered (by saving the file externally), QuickVtk will be notified. An indicator on the lower-left of the application window informs about the state of the currently observed file. With `autorun` enabled, QuickVtk will automatically compile and run the code from the opened file. The generated output will be embedded in the 'preview' area on the right.

In this screenshot, [Atom](https://atom.io/) and QuickVtk are opened side by side and both applications are operating on the same file. Saving the file in [Atom](https://atom.io/) will trigger QuickVtk to reload, compile and run the code immediately since `autorun` is enabled

![image]({{ site.baseurl }}/assets/guide/01/img-01.png)

## Loading examples
There are also some examples available to demonstrate how to access different types from the [VTK](https://vtk.org/) framework. You can load example *.qml* files from the menu via **Help &rarr; Examples**
