# project setup
# ******************************************************************************
cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;")
include(Functions)

set(PROJECT_NAME "QuickVtk")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_DEBUG_POSTFIX "d")

# c++14 for all targets
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(${PROJECT_NAME})

# project directories
# ******************************************************************************
#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(PROJECT_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)

message(STATUS "  Project directories:")
message(STATUS "   - project source dir: " ${SOURCE_DIR})
message(STATUS "   - project binary dir: " ${BINARY_DIR})
message(STATUS "   - project build dir: " ${BUILD_DIR})
message(STATUS "   - project install dir: " ${PROJECT_INSTALL_DIR})

# output directories
# ******************************************************************************
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR})

# moc
# ******************************************************************************
set(CMAKE_AUTOMOC true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# project meta information
# ******************************************************************************
set(QUICKVTK_VERSION_MAJOR 0)
set(QUICKVTK_VERSION_MINOR 5)
set(QUICKVTK_VERSION_PATCH 6)
set(QUICKVTK_ORG_NAME quickvtk)
set(QUICKVTK_ORG_DOMAIN org)

message(STATUS "> Configure project: ${PROJECT_NAME} (v${QUICKVTK_VERSION_MAJOR}.${QUICKVTK_VERSION_MINOR}.${QUICKVTK_VERSION_PATCH})")

# apple rpath
# ******************************************************************************
if(APPLE)
    set(CMAKE_SKIP_BUILD_RPATH false)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH false)
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

    message(STATUS "  rpath: " ${CMAKE_INSTALL_RPATH})
endif()

# libraries
# ******************************************************************************
set(QUICKVTK_QT_VERSION "5.13.0" CACHE STRING "Qt Version")
set(QUICKVTK_QT_MODULES Core Gui Widgets Quick Qml Concurrent Network DBus PrintSupport)

if(UNIX AND NOT APPLE)
    set(QUICKVTK_QT_MODULES ${QUICKVTK_QT_MODULES} X11Extras)
endif()

set(QUICKVTK_INTERNAL_LIBRARY_TARGETS)

find_package(Qt5 ${QUICKVTK_QT_VERSION} EXACT CONFIG REQUIRED ${QUICKVTK_QT_MODULES})

# definitions
# ******************************************************************************
add_definitions(${QT_DEFINITIONS})
add_definitions(-DUSE_INSTALL_TARGET)

# Vtk
# ******************************************************************************
find_package(VTK CONFIG REQUIRED)
include(${VTK_USE_FILE})

# sources
# ******************************************************************************
AddApplicationSources("${SOURCE_DIR}/App" "App" list_app_src)
AddApplicationSources("${SOURCE_DIR}/Editor" "Editor" list_app_src)

AddCoreSources("${SOURCE_DIR}/Core/Math" "Math" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/Core/SampleData" "SampleData" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/Core/TypeInfo" "TypeInfo" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/Core/Utils" "Utils" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/Core/Vtk" "Vtk" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/Core/Vtk/Internal" "Vtk\\Internal" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/Core/Vtk/Wrapper" "Vtk\\Wrapper" list_core_src list_core_hdr)

#configure directories
set (LIBRARY_MODULE_PATH "${PROJECT_SOURCE_DIR}/Core")

#setup library
# ******************************************************************************
set (QUICKVTK_CORE_NAME "${PROJECT_NAME}Core")
add_library (${QUICKVTK_CORE_NAME} SHARED ${list_core_src} ${list_core_hdr})
set_target_properties(${QUICKVTK_CORE_NAME} PROPERTIES PUBLIC_HEADER "${list_core_hdr}")

set(LINK_LIBRARIES PUBLIC ${VTK_LIBRARIES} PUBLIC Qt5::Core PUBLIC Qt5::Widgets PUBLIC Qt5::Gui PUBLIC Qt5::Quick PUBLIC Qt5::Qml PUBLIC Qt5::Concurrent)
if(UNIX AND NOT APPLE)
    set(LINK_LIBRARIES ${LINK_LIBRARIES} PUBLIC Qt5::X11Extras)
endif()

# link
target_link_libraries(${QUICKVTK_CORE_NAME} ${LINK_LIBRARIES})


# setup target
# ******************************************************************************
if(APPLE)
    set(MACOSX_BUNDLE_BUNDLE_VERSION 1)
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${QUICKVTK_VERSION_MAJOR}.${QUICKVTK_VERSION_MINOR}.${QUICKVTK_VERSION_PATCH})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${QUICKVTK_VERSION_MAJOR}.${QUICKVTK_VERSION_MINOR}.${QUICKVTK_VERSION_PATCH})
    set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_RESOURCES ${BUILD_DIR}/${PROJECT_NAME}.app/Contents/Resources)
    set(MACOSX_BUNDLE_ICON ${ROOT_DIR}/res/icons/develop/${MACOSX_BUNDLE_ICON_FILE})

    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${list_app_src} ${MACOSX_BUNDLE_ICON})
else()
    add_executable(${PROJECT_NAME} ${list_app_src})
endif()

# configure files
# ******************************************************************************
configure_file(${ROOT_DIR}/cmake/meta_quickvtk.hpp.in ${BINARY_DIR}/meta_quickvtk.hpp)

if(APPLE)
    configure_file(${ROOT_DIR}/cmake/info.plist.in ${BINARY_DIR}/info.plist)
endif()

# target properties
# ******************************************************************************
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${BINARY_DIR}/info.plist)
endif()

# setup api-docs generator target
# ******************************************************************************
set(API_DOCS_TARGET "API-Docs")
add_executable(${API_DOCS_TARGET}
  "${SOURCE_DIR}/API-Docs/main.cpp"
  "${SOURCE_DIR}/API-Docs/APIGenerator.hpp"
  "${SOURCE_DIR}/API-Docs/APIGenerator.cpp"
)

target_link_libraries(${API_DOCS_TARGET} ${LINK_LIBRARIES} ${QUICKVTK_CORE_NAME})
target_include_directories(${API_DOCS_TARGET} PRIVATE ${list_core_hdr})
target_include_directories(${API_DOCS_TARGET} PUBLIC ${BINARY_DIR})

# includes
# ******************************************************************************
target_include_directories(${PROJECT_NAME} PUBLIC ${BINARY_DIR})

# copy resources
# ******************************************************************************
if(APPLE)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MACOSX_BUNDLE_RESOURCES})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MACOSX_BUNDLE_ICON} ${MACOSX_BUNDLE_RESOURCES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${ROOT_DIR}/res" ${BUILD_DIR}/${PROJECT_NAME}.app/Contents/Resources)
else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${ROOT_DIR}/res" ${BUILD_DIR}/Resources)
    add_custom_target(CopyResources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${ROOT_DIR}/res" ${BUILD_DIR}/Resources)
endif()

# link
# ******************************************************************************
#set(LINK_LIBRARIES PUBLIC ${VTK_LIBRARIES} PUBLIC Qt5::Core PUBLIC Qt5::Widgets PUBLIC Qt5::Gui PUBLIC Qt5::Quick PUBLIC Qt5::Qml PUBLIC Qt5::Concurrent)
#if(UNIX AND NOT APPLE)
#    set(LINK_LIBRARIES ${LINK_LIBRARIES} PUBLIC Qt5::X11Extras)
#endif()

target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES} ${QUICKVTK_CORE_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${list_core_hdr})

if(NOT APPLE)
  install(
      TARGETS QuickVtkCore
        EXPORT QuickVtkCore-targets
        ARCHIVE DESTINATION "lib"
        RUNTIME DESTINATION "bin"
        PUBLIC_HEADER DESTINATION "include"
        FRAMEWORK DESTINATION Library/Frameworks
        COMPONENT libraries)

  install(
   EXPORT QuickVtkCore-targets
    DESTINATION lib/cmake/QuickVtkCore
    FILE QuickVtkCore-config.cmake
    COMPONENT headers)

  install(
    TARGETS QuickVtk
      EXPORT QuickVtk-targets
      RUNTIME DESTINATION "bin/"
      FRAMEWORK DESTINATION Library/Frameworks
      COMPONENT libraries)
endif()
