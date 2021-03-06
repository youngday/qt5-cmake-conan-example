cmake_minimum_required(VERSION 3.14)
project(qt5_conan LANGUAGES CXX)

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

find_package(QT NAMES Qt6 Qt5  )
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Multimedia Concurrent Gui Widgets 3DCore 3DExtras 3DQuickExtras  3DRender 3DInput REQUIRED)
find_package(xtensor-blas REQUIRED)
# QT3D新增 .pro
#QT += 3dcore 3drender 3dinput 3dquick 3dlogic qml quick 3dquickextras 3dextras
# for qt quick controls ----------------

# file(GLOB_RECURSE source_files "${CMAKE_CURRENT_LIST_DIR}/src/*")
# add_library(logger_lib STATIC ${source_files})
# target_include_directories(logger_lib PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include/")

add_executable(${PROJECT_NAME}
  main.cpp
  test.cpp
  InterfaceWithOpenCV.cpp
  tcp_client_timeout.cpp
  tcp_client_coro.cpp
  Logger.cpp
  qml.qrc
  ${TaoQuickRes}
)
     # test_concurent.cpp
target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Multimedia
   Qt${QT_VERSION_MAJOR}::Concurrent  Qt${QT_VERSION_MAJOR}::3DExtras  Qt${QT_VERSION_MAJOR}::3DCore
   Qt${QT_VERSION_MAJOR}::3DRender Qt${QT_VERSION_MAJOR}::3DInput Qt${QT_VERSION_MAJOR}::Gui 
   Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::3DQuickExtras
    ${CONAN_LIBS} ${OpenCV_LIBS} xtensor-blas )


  # $ mkdir build; cd build
  # $ cmake .. -G "<cmake_generator>" "-DCMAKE_PREFIX_PATH=<path_to_your_qt_sources>"
  # $ cmake --build . --config "Debug"
  # mkdir build; cd build
  # conan install .. --build=missing
  # conan build ..