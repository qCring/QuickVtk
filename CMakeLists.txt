# project setup
# ******************************************************************************
cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;")
include(Functions)

set(PROJECT_NAME "QuickVtk")
set(TARGET_APPLICATION "QuickVtk")
set(TARGET_CORE "QuickVtk-Core")
set(TARGET_DOCS "QuickVtk-Docs")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_DEBUG_POSTFIX "d")

# c++14 for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
set(QUICKVTK_ORG_DOMAIN quickvtk.io)
set(QUICKVTK_ORG_NAME quickvtk)

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
set(QUICKVTK_QT_VERSION "5.12.0" CACHE STRING "Qt Version")
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
AddApplicationSources("${SOURCE_DIR}/${TARGET_APPLICATION}/App" "App" list_app_src)
AddApplicationSources("${SOURCE_DIR}/${TARGET_APPLICATION}/Console" "Console" list_app_src)
AddApplicationSources("${SOURCE_DIR}/${TARGET_APPLICATION}/Document" "Document" list_app_src)
AddApplicationSources("${SOURCE_DIR}/${TARGET_APPLICATION}/Menu" "Menu" list_app_src)

AddCoreSources("${SOURCE_DIR}/${TARGET_CORE}/Math" "Math" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/${TARGET_CORE}/SampleData" "SampleData" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/${TARGET_CORE}/TypeInfo" "TypeInfo" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/${TARGET_CORE}/Utils" "Utils" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/${TARGET_CORE}/Vtk" "Vtk" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/${TARGET_CORE}/Vtk/Internal" "Vtk\\Internal" list_core_src list_core_hdr)
AddCoreSources("${SOURCE_DIR}/${TARGET_CORE}/Vtk/Wrapper" "Vtk\\Wrapper" list_core_src list_core_hdr)

#configure directories
set (LIBRARY_MODULE_PATH "${PROJECT_SOURCE_DIR}/${TARGET_CORE}")

#setup library
# ******************************************************************************
add_library (${TARGET_CORE} SHARED ${list_core_src} ${list_core_hdr})
set_target_properties(${TARGET_CORE} PROPERTIES PUBLIC_HEADER "${list_core_hdr}")

set(LINK_LIBRARIES PUBLIC ${VTK_LIBRARIES} PUBLIC Qt5::Core PUBLIC Qt5::Widgets PUBLIC Qt5::Gui PUBLIC Qt5::Quick PUBLIC Qt5::Qml PUBLIC Qt5::Concurrent)
if(UNIX AND NOT APPLE)
    set(LINK_LIBRARIES ${LINK_LIBRARIES} PUBLIC Qt5::X11Extras)
endif()

# link
target_link_libraries(${TARGET_CORE} ${LINK_LIBRARIES})


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
add_executable(${TARGET_DOCS}
  "${SOURCE_DIR}/${TARGET_DOCS}/main.cpp"
  "${SOURCE_DIR}/${TARGET_DOCS}/APIGenerator.hpp"
  "${SOURCE_DIR}/${TARGET_DOCS}/APIGenerator.cpp"
)

target_link_libraries(${TARGET_DOCS} ${LINK_LIBRARIES} ${TARGET_CORE})
target_include_directories(${TARGET_DOCS} PRIVATE ${list_core_hdr})
target_include_directories(${TARGET_DOCS} PUBLIC ${BINARY_DIR})

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

target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES} ${TARGET_CORE})
target_include_directories(${PROJECT_NAME} PRIVATE ${list_core_hdr})

if(NOT APPLE)
  install(
    TARGETS ${TARGET_CORE}
    EXPORT ${TARGET_CORE}-targets
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    PUBLIC_HEADER DESTINATION "include"
    FRAMEWORK DESTINATION Library/Frameworks
    COMPONENT libraries
  )

  install(
    EXPORT ${TARGET_CORE}-targets
    DESTINATION lib/cmake/${TARGET_CORE}
    FILE ${TARGET_CORE}-config.cmake
    COMPONENT headers
  )

  install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION "bin/"
    FRAMEWORK DESTINATION Library/Frameworks
    COMPONENT libraries
  )

endif()
