cmake_minimum_required(VERSION 3.14)

project(qt5_conan LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
message(STATUS "Compiling with C++ standard: ${CMAKE_CXX_STANDARD}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# for conan lib 
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# for local lib of quick 
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(taoQuick.cmake)


# for qt quick controls ++++++++:
# Find dependencies.# path of qt installed
set(QT_DIR ~/Qt5.12.12/5.12.12/gcc_64)

# Prepare project for Qt. 
#set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_PREFIX_PATH ${QT_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories.
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Multimedia Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Multimedia Concurrent REQUIRED)

# for qt quick controls ----------------

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(${PROJECT_NAME}
      main.cpp
      test.cpp
      InterfaceWithOpenCV.cpp
      qml.qrc
      ${TaoQuickRes}
    )
endif()
     # test_concurent.cpp
target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Concurrent ${CONAN_LIBS} ${OpenCV_LIBS} )


  # $ mkdir build; cd build
  # $ cmake .. -G "<cmake_generator>" "-DCMAKE_PREFIX_PATH=<path_to_your_qt_sources>"
  # $ cmake --build . --config "Debug"
  # mkdir build; cd build
  # conan install .. --build=missing
  # conan build ..