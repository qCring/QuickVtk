---
layout: page
nav: guide
title: The VTK visualization pipeline in QuickVtk
topics:
  - How the VTK visualization pipeline is applied in QuickVtk
  - Visualizing procedural geometry in a simple pipeline
---

![image]({{ site.baseurl }}/assets/guide/03/img-01.png)

For a comprehensive documentation on the visualization pipeline see the official [VTK documentation website](https://vtk.org/documentation/) from where you also have access to the free PDF versions of

- The VTK User's Guide
- The Visualization Toolkit

# 1. A practical approach
Let's start with a simple QML file instead of diving right into the many different concepts used in the [VTK](https://vtk.org/) framework. To access types from [VTK](https://vtk.org/), we first have to `import` the `Vtk` namespace. The following code snippet shows how a [vtkCylinderSource](https://vtk.org/doc/nightly/html/classvtkCylinderSource.html) is created in QuickVtk

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

import Vtk 1.0 as Vtk

Item {
    anchors.fill: parent

    Vtk.CylinderSource {
    }
}
{% endhighlight %}

The code is valid but we will not be able to see anything yet. To make sure that the cylinder actually exists, we need some proof. One option is to simply print the object to the console

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

import Vtk 1.0 as Vtk

Item {
    anchors.fill: parent

    Vtk.CylinderSource {
        Component.onCompleted: console.log(this)
    }
}
{% endhighlight %}

We can switch to the **Log** panel and see that `this` is resolved to `quick::Vtk::CylinderSource(0x...)` which indicates that the object was in fact constructed and has a valid memory address. This is admittedly pretty boring but demonstrates that all available types from [VTK](https://vtk.org/) are fully integrated just as built-in QML types.

We can go one step further and convert the object to the JavaScript object notation (JSON)

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

import Vtk 1.0 as Vtk

Item {
    anchors.fill: parent

    Vtk.CylinderSource {
        Component.onCompleted: console.log(JSON.stringify(this))
    }
}
{% endhighlight %}

Again, this might not seem very useful. But to point out the seamless integration of [VTK](https://vtk.org/) in the QML context this is a good example.

Another advantage of the JSON representation is simpler debugging. You will get a snapshot of the object with all related properties in a structured and readable notation

{% highlight json %}
{
	"objectName": "",
	"input": {},
	"center": {
		"objectName": "",
		"x": 0,
		"y": 0,
		"z": 0
	},
	"height": 1,
	"radius": 0.5,
	"resolution": 6,
	"capping": true
}
{% endhighlight %}

# 2. The VTK visualization pipeline
While visual QML elements are rendered directly by the QML engine, objects from [VTK](https://vtk.org/) must be assigned to a `Vtk.Viewer` instance in order to appear on screen

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

import Vtk 1.0 as Vtk

Item {
    anchors.fill: parent

    Vtk.CylinderSource {
        id: sphereSource
    }

    Vtk.Viewer {
        anchors.fill: parent
        input: sphereSource
    }
}
{% endhighlight %}

We still can't see anything since our cylinder is not an actual geometric shape as you might expect. Instead, the object only provides the **data** necessary to represent a cylinder. Now let's talk about the visualization pipeline in [VTK](https://vtk.org/).

The first step in the visualization process is to provide some kind of data. Every data has an origin or source. As the name suggests this is exactly what `CylinderSource` does. Based on different parameters (which we saw in the JSON earlier) data is generated procedurally. There are of course other ways to bring data into the pipeline like loading 3D models or images from the file system which we will discuss later.

We connected the first and the last step of the visualization pipeline by assigning a data source to the `input` of the viewer using the `id` property. In order to display something on the screen there are two more steps necessary. First, we have to specify **how** the data provided by `CylinderSource` should be interpreted. Do we want to visualize the cylinder as a volumetric object or polygonal geometry? This processing step is done by converting or **mapping** the underlying dataset accordingly. While volumes consist of many voxels, polygons are built from vertices, lines, and faces. We will use a `PolyDataMapper` to construct a polygon from the connected `CylinderSource` and connect the resulting output to the viewer by assigning the mapper to the viewer's `input` property

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

import Vtk 1.0 as Vtk

Item {
    anchors.fill: parent

    Vtk.CylinderSource {
        id: sphereSource
    }

    Vtk.PolyDataMapper {
        id: sphereMapper
        input: sphereSource
    }

    Vtk.Viewer {
        anchors.fill: parent
        input: sphereMapper
    }
}
{% endhighlight %}

The `PolyDataMapper` simply provides the **mesh** for our cylinder. We still need to specify how we want to render it. Do we want to visualize a wireframe or shaded solid geometry? Also, we probably want to position the cylinder somewhere in the scene and apply basic transformations like rotation and scale. It wouldn't really make sense for the mapper to be responsible for this functionality. Instead, [VTK](https://vtk.org/) introduces **actors** to represent rendered 3D geometry in a more generic and abstract way. We will add an actor and change the connections in order to configure a working visualization pipeline. To enable basic camera controls using the mouse, we will also set the viewer's `mouseEnabled` property to `true`

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

import Vtk 1.0 as Vtk

Item {
    anchors.fill: parent

    Vtk.CylinderSource {
        id: sphereSource
    }

    Vtk.PolyDataMapper {
        id: sphereMapper
        input: sphereSource
    }

    Vtk.Actor {
        id: sphereActor
        mapper: sphereMapper
    }

    Vtk.Viewer {
        anchors.fill: parent
        mouseEnabled: true
        input: sphereActor
    }
}
{% endhighlight %}

The visualization pipeline can be described as a sequence of different processing steps. We always need to provide some **data** which is the first step in the sequential workflow. A **mapper** will consume data which might be processed by some **filters** first (we will discuss filters in the next article). Finally, an **actor** has access to the render primitives generated from the connected mapper (voxels or meshes constructed from the incoming dataset) and is responsible for managing the object in the scene. Finally, the **viewer** performs the actual rendering

![image]({{ site.baseurl }}/assets/guide/03/img-02.svg){: .noshadow }

It makes sense to separate visualization from rendering. The core visualization layer is designed to be independent from the rendering system in order to offer a consistent pipeline infrastructure. While QuickVtk relies on OpenGL, there are other implementations available which supporting WebGL, VR or alternative rendering techniques like raytracing for example.

# 3. The visualization pipeline in QuickVtk
If you are familiar with [VTK](https://vtk.org/) you'll notice that the same building blocks are used in QuickVtk. Pipelines written in C++, TCL, Python, etc. should be conceptually compatible and easy to implement in QuickVtk. Besides the fact that there are many types still missing in QuickVtk the most noticeable difference is the use of **properties** instead of get and set methods. For example, the [vtkCylinderSource](https://vtk.org/doc/nightly/html/classvtkCylinderSource.html) class provides the method pair `SetResolution` and `GetResolution` while QuickVtk uses an equivalent `resolution` property. We will discuss properties in the context of [VTK](https://vtk.org/) in a later article.

With the declarative nature of QML you can design the visualization pipeline using the object hierarchy. The following code demonstrates the different notation and also the access to the `resolution` property to generate a smoother cylinder shape

{% highlight qml %}
import QtQuick {{ site.snippets.qtquick_version }}

import Vtk 1.0 as Vtk

Item {
    anchors.fill: parent

    Vtk.Viewer {
        anchors.fill: parent

        mouseEnabled: true

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.CylinderSource {
                    resolution: 32
                }
            }
        }
    }
}
{% endhighlight %}

Instead of connecting inputs and outputs for each element individually, a pipeline can be created by nesting objects in the hierarchy. Since the QML engine creates C++ instances based on the processed QML code, the performance should be comparable to the native implementation in C++. We will analyze the performance of [VTK](https://vtk.org/) operations in QuickVtk in a future article.

In the next article we are going to discuss **properties** in the context of **filters** and the basics of reactive programming enabled by QML property bindings.
