QuickVtk
===
Developer Documentation
----

###General
This section will be updated as soon as I've got some time to add more content. Until then, here are some hopefully useful notes:

1. **Notes on building after pulling from git**   
	For Mac OS X. Make sure to re-configure and generate the project via CMake before building QuickVtk from a new commit. This is neccessary to trigger Qt's meta object compiler to re-generate moc files. Chances are, that some new Q_OBJECT derived classes will be part of a pull which will cause linker errors when moc is not triggered.
	
2. **Changing resources**   
	This is an issue exclusive to Visual Studio (or non-XCode IDEs probably). When changing content located in the **res** directory, those changes won't be copied to the build directory **unless** visual studio compiles something. So in case you're editing *qml* files and don't see anything, the problem is that the post-build step configured via CMake will not be performed by Visual Studio if no changes appear in the project source. Visual Studio argues, that running an unmodified project is no actual build (which technically is correct...)
	
	**Note:** As a workaround, you can build the **CopyResources** target. This target is provided on all non-Mac platforms and will invoke copying files to **build/Resources**, where the application expects resources to be.
	
3. **Deleting QuickVtk/bin/ can help sometimes**    
	The **bin** directory is where all generated moc files, some other stuff and the project file are stored. If there are weird things going on with QuickVtk, try deleting the **bin/** directory and generate a fresh and clean one via CMake.
