cmake_minimum_required(VERSION 3.5)

project(excle_test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)
find_package(Qt6 COMPONENTS MultimediaWidgets REQUIRED)

file(GLOB QXLSX_CPP "source/*.cpp")
file(GLOB QXLSX_H "header/*.h")
file(GLOB CPP_FILE "*.cpp")
file(GLOB HEAD_FILE "*.h")
file(GLOB UI_FILE "*.ui")
set(QXLSX_HEADERPATH ${CMAKE_CURRENT_SOURCE_DIR}/header/)
include_directories(${QXLSX_HEADERPATH})
qt_add_big_resources(SOURCES resource.qrc)
set(PROJECT_SOURCES
        ${CPP_FILE}
        ${HEAD_FILE}
        ${QXLSX_CPP}
        ${QXLSX_H}
        ${UI_FILE}
        resource.qrc
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(excle_test
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET excle_test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(excle_test SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(excle_test
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()
target_sources(excle_test PRIVATE ${SOURCES})
target_link_libraries(excle_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt6::Sql PRIVATE Qt6::Multimedia PRIVATE Qt6::MultimediaWidgets)

set_target_properties(excle_test PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(excle_test)
endif ()
