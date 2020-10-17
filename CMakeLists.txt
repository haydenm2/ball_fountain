cmake_minimum_required(VERSION 3.4)
project(PhysicsFountain)

find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText)
find_package(GTest REQUIRED)
find_package(Eigen3 3.3 REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories( ${OPENSCENEGRAPH_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(PHYSICS_NAME BallPhysics)
set(TEST_NAME ${PHYSICS_NAME}_UnitTest)

add_library(${PHYSICS_NAME} STATIC
        BallPhysics.hpp
        BallPhysics.cpp
        Ball.hpp
        Ball.cpp
        )

add_executable(${TEST_NAME}
    UnitTest.cpp
    )

set(GUI_SOURCE
    Main.cpp
    MainWindow.cpp
    MainWindow.hpp
    MainWindowForm.ui
    OSGWidget.hpp
    OSGWidget.cpp
    SphereUpdateCallback.cpp
    SphereUpdateCallback.hpp
    )

add_executable(${PROJECT_NAME}
    ${GUI_SOURCE}
    )

target_link_libraries(${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    ${PHYSICS_NAME}
    Eigen3::Eigen
    )

target_link_libraries(${TEST_NAME}
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    ${PHYSICS_NAME}
    Eigen3::Eigen
    )

