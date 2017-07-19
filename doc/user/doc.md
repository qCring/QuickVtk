QuickVtk
===
User Documentation
----

Just some helpful notes until I have time to provide more detailed tutorials / guides:

- **Check out the examples folder**   
	There are a bunch of *.qml* files located at **res/examples/qml** to showcase and test functionality of some [**VTK**](http://www.vtk.org) classes. You can load a file, edit stuff in the editor and recompile your changes to get a feeling for how things work.
	
- **Editor Shortcuts**    
	The code editor is (attempt 1: <del>garbage</del>, attempt 2: <del>very alpha</del>, attempt 3: <del>does an okay job for basic text editing</del>) does not support syntax formatting but at least basic syntax highlighting. The editor supports some helpful shortcuts:
	- `cmd/ctrl` + `N`: New File
	- `cmd/ctrl` + `O`: Open File
	- `cmd/ctrl` + `S`: Save File
	- <del>`cmd/ctrl` + `I`: Format File</del>
	- `cmd/ctrl` + `R`: Compile & Run
	- `cmd/ctrl` + `F`: Find & Replace
	- `cmd/ctrl` + `1`: Toggle Editor View

	**Note:** Implementing proper code formatting in [**QML**](http://doc.qt.io/qt-5/qtqml-index.html) turns out to be *real* tough... So you're best off using an external editor for writing code and reloading modified files manually.
	
- **Use the type browser**   
	The search bar in the application's upper-right corner allows you to search for types available in QuickVtk. You can quickly get an overview of all properties, methods and some other useful meta information of any type this way.

- **Knowing VTK is helpful**    
	There are some concepts in [**VTK**](http://www.vtk.org) that take some getting used to. You can familiarize by either looking at the examples located at **res/examples/qml** or examples and documentation on the [**VTK**](http://www.vtk.org) website.