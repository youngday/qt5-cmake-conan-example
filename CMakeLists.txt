cmake_minimum_required(VERSION 3.14)

project(qt5_conan LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# for conan lib 
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#find_package(spdlog 1.10.0 REQUIRED)

# for local lib of quick 
#SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(taoQuick.cmake)


# for qt quick controls ++++++++:
# Find dependencies.# path of qt installed
#set(QT_DIR ~/Qt5.12.12/5.12.12/gcc_64)

# Prepare project for Qt. 
#set(CMAKE_PREFIX_PATH ${QT_DIR})
#set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories.
#set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

# for qt quick controls ----------------

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(${PROJECT_NAME}
      main.cpp
      qml.qrc
      ${TaoQuickRes}
    )
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${CONAN_LIBS})
