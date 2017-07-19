QuickVtk
===
Developer Documentation
----

### General
This section will be updated as soon as I've got some time to add more content. Until then, here are some hopefully useful notes:

1. **Rebuilding VTK**   
From time to time I'll advance the VTK version just to make sure that QuickVtk remains compatible. The idea is to isolate dependencies from the project by providing a separate *CMakeLists* file in the **libs/src** folder. The downside of this separation is that the project's main *CMakeLists* has no knowledge or control about the VTK version. This means that if you want to keep up with newer versions of VTK, you have to do this manually.

	Check out the [**Build instructions**](./../build.md) for more information on how to build VTK.
	
	
2. **Changing resources**   
	This is an issue exclusive to Visual Studio (or non-XCode IDEs probably). When changing content located in the **res** directory, those changes won't be copied to the build directory **unless** Visual Studio compiles something. So in case you're editing *qml* files and don't see anything, the problem is that the post-build step configured via CMake will not be performed if no changes appear in the project source. Visual Studio argues, that running an unmodified project is no actual build (which technically is correct...)
	
	**Note:** As a workaround, you can build the **CopyResources** target. This target is provided on all non-Mac platforms and will invoke copying files to **build/Resources**, where the application expects resources to be.
	
3. **Deleting QuickVtk/bin/ can help sometimes**    
	The **bin** directory is where all the generated moc files, some other stuff and project files are stored. If there are weird things going on with QuickVtk, try deleting the **bin/** directory and generate a fresh and clean project via CMake.
