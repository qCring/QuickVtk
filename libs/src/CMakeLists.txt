# project dependencies setup
# ******************************************************************************
cmake_minimum_required(VERSION 3.0)

include (ExternalProject)

set(PROJECT_NAME "QuickVtkLibs")

project(${PROJECT_NAME})

set(VTK_GIT_TAG "42ce603" CACHE STRING "VTK git tag")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/VTK/install)

ExternalProject_Add(
    VTK
    GIT_REPOSITORY      https://github.com/Kitware/VTK.git
    PREFIX              VTK
    GIT_TAG             ${VTK_GIT_TAG}
    BINARY_DIR          VTK/bin
    TMP_DIR             VTK/tmp
    SOURCE_DIR          VTK/src
    DOWNLOAD_DIR        VTK/download
    STAMP_DIR           VTK/stamp
    UPDATE_DISCONNECTED 1
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    CMAKE_CACHE_ARGS    -DVTK_RENDERING_BACKEND:STRING=OpenGL2 -DModule_vtkRenderingExternal:BOOL=ON -DBUILD_TESTING:BOOL=OFF
)
