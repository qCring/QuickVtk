---
layout: page
nav: guide
title: An introduction to QML
topics:
  - Optional but recommended for QML newcomers
  - Learn about basic language features and concepts by implementing a simple stop watch in QML
---

![image]({{ site.baseurl }}/assets/guide/02/img-01.png)

For a more comprehensive introduction check out the official [documentation](https://doc.qt.io/qt-5/qmlfirststeps.html#) or take a look at the [open qmlbook](https://qmlbook.github.io/)

## Using an external editor
As mentioned in article [01 - Getting Started]({{ site.baseurl }}/docs/01.html), it is recommended to use an external editor like [Atom](https://atom.io/) or any other editor you feel comfortable working with. Make sure to use a proper QML syntax highlighter which should be available for pretty much any editor

Let's start off by creating a new file in the editor of your choice and paste the following snippet which creates a rectangle element, the starting point of our stop watch implementation

>Step 1
{: .hl-caption }

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Rectangle {
    id: clock

    anchors.centerIn: parent

    width: parent.width / 2
    height: width
    radius: width / 2

    border.color: "#48f"
    border.width: 4
}
{% endhighlight %}

## Compile and run QML code in QuickVtk
Save the file as `01-basics.qml`. Open QuickVtk and load the newly created file via **File &rarr; Load...** from the menu and execute the code by pressing the **Run** button or **Code &rarr; Run** from the menu. Check `autorun` to automatically compile and run after changes are made to the file by your external editor.

In the following screenshot, [Atom](https://atom.io/) and QuickVtk are opened side by side. This workflow allows you to work on QML in any external text editor and preview the compiled output in QuickVtk everytime you save the file

![image]({{ site.baseurl }}/assets/guide/02/img-02.png)

## Property Bindings
One of QML's major features are [Property Bindings](https://doc.qt.io/qt-5/qtqml-syntax-propertybinding.html). They allow you to define expressions as bindings instead of simple assignments. Every time a property changes, the corresponding values are updated. This is a key concept in QML and enables reactive programming which has many advantages.

Instead of using constant values for the Rectangle's `width`, `height` and `radius` properties, we simply define them relative to the parent object in a declarative fashion. The root object's parent is always the viewport of the preview area on the right side. You can drag the separator between the preview and the built-in editor or resize the application window to see how changing the size affects the `Rectangle` element

## Object hierarchy
Next, we will add a child to the `Rectangle` to display the second hand of our stop watch. The `anchors` property is used for [item positioning](https://doc.qt.io/qt-5/qtquick-positioning-topic.html). The `width` property of the inner `Rectangle` scales with the `parent` object which in this case points to the outer `Rectangle`. As you can see, the `parent` is always relative to the current object scope

>Step 2
{: .hl-caption }

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Rectangle {
    id: clock

    anchors.centerIn: parent

    width: parent.width / 2
    height: width
    radius: width / 2

    border.color: "#48f"
    border.width: 4

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.horizontalCenter

        width: parent.width / 2 - 12
        height: 10
        radius: height / 2
        color: "#943"
    }
}
{% endhighlight %}

## Adding a Timer
In order to rotate the inner `Rectangle` each time a second passes, we need to add a [Timer](https://doc.qt.io/qt-5/qml-qtqml-timer.html) object. Not every type in the hierarchy is necessarily visible. This is also the case for [Timer](https://doc.qt.io/qt-5/qml-qtqml-timer.html) instances. We will use this object only to invoke a [Handler](https://doc.qt.io/qt-5/qtqml-syntax-signals.html) which basically is a JavaScript function. The underlying QML engine provides a built-in [JavaScript runtime](https://doc.qt.io/qt-5/qtqml-javascript-expressions.html) in order to enable imperative programming

The [Timer](https://doc.qt.io/qt-5/qml-qtqml-timer.html) is initialized with the properties `running` and `repeat` set to `true` and an `interval` of `1000`. In this case, the expression assigned to `onTriggered` will be invoked every second

>Step 3
{: .hl-caption }

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Rectangle {
    id: clock

    anchors.centerIn: parent

    width: parent.width / 2
    height: width
    radius: width / 2

    border.color: "#48f"
    border.width: 4

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.horizontalCenter

        width: parent.width / 2 - 12
        height: 10
        radius: height / 2
        color: "#943"
    }

    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: console.log("one second")
    }
}
{% endhighlight %}

You can inspect output from `console.log` by switching to the **Log** tab on the bottom of the preview area

## Adding Custom Properties and Functions
To keep track of how many seconds passed, we define a custom [Object Attribute](https://doc.qt.io/qt-5/qtqml-syntax-objectattributes.html). In this case a simple `int` property. Instead of just printing constant text to the console, the new `second` property should be incremented and capped at `60` every time the timer is triggered. The following snippet shows how the `second` property and a function named `timeChanged` are defined in the outer object scope. Note that the timer's `onTriggered` property now calls the function instead of executing inline JavaScript code

>Step 4
{: .hl-caption }

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Rectangle {
    id: clock

    anchors.centerIn: parent

    width: parent.width / 2
    height: width
    radius: width / 2

    border.color: "#48f"
    border.width: 4

    property int second: 0

    function timeChanged () {
        clock.second = ++clock.second % 60;
        console.log(clock.second)
    }

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.horizontalCenter

        width: parent.width / 2 - 12
        height: 10
        radius: height / 2
        color: "#943"
    }

    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: timeChanged()
    }
}
{% endhighlight %}

## Animation
A classic approach to animate the second hand would be to rotate the `Rectangle` from within the previously added function. There is nothing wrong about that but to demonstrate the advantages of declarative programming, we will do this differently. First, we assign a `Rotation` component to the inner object's `transform` and set the `origin` to the relative position `(5, 5)`. This is purely cosmetic and simply moves the rotation axis from the rectangle's top-left corner to the center, taking the rectangle's constant height of `10` into account. The actual rotation is performed by assigning the expression `clock.second * 6 - 90` to the `angle` property

We can rely on [Property Bindings](https://doc.qt.io/qt-5/qtqml-syntax-propertybinding.html) to calculate the correct angle. Every time the `second` property is changed in the `timeChanged` function, the `angle` property will be re-evaluated. The calculation is simple: A full rotation equals 360° and there are 60 seconds. So each second we want to apply a rotation of `n` times 360°/60, where `n` equals the current second. For any value of `clock.second` the expression `clock.second * 6` returns the correct angle. Since the hand is pointing up, we also have to subtract a constant 90°

>Step 5
{: .hl-caption }

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Rectangle {
    id: clock

    anchors.centerIn: parent

    width: parent.width / 2
    height: width
    radius: width / 2

    border.color: "#48f"
    border.width: 4

    property int second: 0

    function timeChanged () {
        clock.second = ++clock.second % 60;
        console.log(clock.second)
    }

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.horizontalCenter

        width: parent.width / 2 - 12
        height: 10
        radius: height / 2
        color: "#943"

        transform: Rotation {
            origin.x: 5
            origin.y: 5

            angle: clock.second * 6 - 90
        }
    }

    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: timeChanged()
    }
}
{% endhighlight %}

## Property Behaviours
To further improve the visual quality of our second hand animation, we are going to add a [Behavior](https://doc.qt.io/qt-5/qml-qtquick-behavior.html) to the `angle` property. Let's recap. The effective value of the `angle` property changes every 1000 milliseconds, starting at 0 and increasing by 6 each time a second passes. By adding a [Behavior](https://doc.qt.io/qt-5/qml-qtquick-behavior.html) to this property, we can specify a transition that should be applied when the raw property data changes. Since  `angle` is a `float` property, we can interpolate between two values. For demonstration purposes we use a [SpringAnimation](https://doc.qt.io/qt-5/qml-qtquick-springanimation.html) to achieve a more realistic animation

>Step 6
{: .hl-caption }

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Rectangle {
    id: clock

    anchors.centerIn: parent

    width: parent.width / 2
    height: width
    radius: width / 2

    border.color: "#48f"
    border.width: 4

    property int second: 0

    function timeChanged () {
        clock.second = ++clock.second % 60;
        console.log(clock.second)
    }

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.horizontalCenter

        width: parent.width / 2 - 12
        height: 10
        radius: height / 2
        color: "#943"

        transform: Rotation {
            origin.x: 5
            origin.y: 5

            angle: clock.second * 6 - 90

            Behavior on angle {
                SpringAnimation {
                    spring: 10
                    damping: 0.3
                    modulus: 360
                }
            }
        }
    }

    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: timeChanged()
    }
}
{% endhighlight %}

While this appears to be mostly UI polishing it is still interesting to see how easy it is to achieve smooth animations and transitions in the context of data visualization. Since QuickVtk integrates [VTK](https://vtk.org/) in QML, all of the above concepts can be applied to filters and actors in the same fashion

## Interaction
To discuss user interaction on a basic level, we will add two buttons to manually start/stop and reset our stop watch. To keep this example simple, this will be the last change we make. There are many UI specific details and also some new elements in the final version of the code. The [Text](https://doc.qt.io/qt-5/qml-qtquick-text.html) elements display text on the screen, the [Row](https://doc.qt.io/qt-5/qml-qtquick-row.html) element  helps nesting objects instead of manually position each object individually, and finally two [MouseArea](https://doc.qt.io/qt-5/qml-qtquick-mousearea.html) elements can be found which are needed in order to detect mouse events

![image]({{ site.baseurl }}/assets/guide/02/img-03.png)

There are some things worth mentioning. First, the timer now has an `id` which is necessary to access the `running` property and invoke the built-in `restart` method from outside the timer's scope. The label on the left changes its text depending on whether the timer is currently running or not. For this, the ternary `? :` operator is used.

The line `text: timer.running? "Stop" : "Start"` demonstrates a common way to perform state-dependent assignments in a declarative way. The same goes for the `color` property. We assign a specific color depending on the timer's `running` flag by writing `color: timer.running ? "#f84" : "#48f"`

Each [Text](https://doc.qt.io/qt-5/qml-qtquick-text.html) element contains a [MouseArea](https://doc.qt.io/qt-5/qml-qtquick-mousearea.html) child in order to respond to click events using the `onClicked` handler. The start/stop label simply inverts the `boolean` value by executing the line `timer.running = !timer.running;` while the mouse area inside the `Reset` label calls `timer.restart()` and sets the `second` and `minute` properties to `0`.

A new `minute` property stores the value for elapsed minutes simply to make the stop watch a bit more useful. The `timeChanged` function of course has to be extended to track the current minute

>Step 7
{: .hl-caption }

{% highlight qml %}
function timeChanged () {
    ++clock.second;

    if (clock.second == 60) {
        clock.second = 0;
        ++clock.minute;

        if (clock.minute == 60) {
            clock.minute = 0;
        }
    }

    console.log(clock.minute + "m " + clock.second + "s");
}
{% endhighlight %}

## Final version of the QML code
With these last additions we have a basic working stop watch implementation. We covered some of QML's major features but of course there's much more. For a basic understanding, however, it should be enough

>Final Version
{: .hl-caption }

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

Rectangle {
    id: clock

    anchors.centerIn: parent

    width: parent.width / 2
    height: width
    radius: width / 2

    border.color: "#48f"
    border.width: 4

    property int second: 0
    property int minute: 0

    function timeChanged () {
        ++clock.second;

        if (clock.second == 60) {
            clock.second = 0;
            ++clock.minute;

            if (clock.minute == 60) {
                clock.minute = 0;
            }
        }

        console.log(clock.second)
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        font.bold: true

        text: clock.minute + "m " + clock.second + "s"
        color: "#48f"
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60

        spacing: 40

        Text {
            text: timer.running ? "Stop" : "Start"

            font.bold: true
            color: timer.running ? "#f84" : "#48f"

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    timer.running = !timer.running;
                }
            }
        }

        Text {
            text: "Reset"

            font.bold: true
            color: "#666"

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    clock.minute = 0;
                    clock.second = 0;
                    timer.restart();
                }
            }
        }
    }

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.horizontalCenter

        width: parent.width / 2 - 12
        height: 10
        radius: height / 2
        color: "#943"

        transform: Rotation {
            origin.x: 5
            origin.y: 5

            angle: clock.second * 6 - 90

            Behavior on angle {
                SpringAnimation {
                    spring: 10
                    damping: 0.3
                    modulus: 360
                }
            }
        }
    }

    Timer {
        id: timer

        repeat: true
        interval: 1000
        onTriggered: timeChanged()
    }
}
{% endhighlight %}
