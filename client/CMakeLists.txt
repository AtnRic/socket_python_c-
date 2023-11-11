cmake_minimum_required(VERSION 3.2)
project(main)

set (CMAKE_CXX_STANDARD 17)

set(SRC_FILES main.cpp)
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SRC_FILES})


if(MSVC)
    set(wxWidgets_ROOT_DIR  "C:/tools/wxWidgets")
    set(CMAKE_PREFIX_PATH  C:/tools/wxWidgets)
    set(wxWidgets_DIR  "C:/tools/wxWidgets/lib/cmake/wxWidgets")
    set(wxWidgets_LIB_DIR "C:/tools/wxWidgets/lib/vc_x64_lib")

    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    #set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)

   
    set(Boost_DIR "C:/tools/Boost/lib/cmake/Boost-1.80.0") 
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_RELEASE_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME ON)

    find_package(Boost 1.80.0 COMPONENTS json serialization REQUIRED)
    else(MSVC)
    set(wxWidgets_ROOT_DIR /usr/local/include/wx-3.2)

    find_package(wxWidgets COMPONENTS net core base REQUIRED)

    include(${wxWidgets_USE_FILE})


    set(Boost_DIR /usr/local/lib/cmake/Boost-1.80.0)
    find_package(Boost 1.80.0 COMPONENTS json serialization REQUIRED)
endif(MSVC)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            RESOURCE "../../src/osx/carbon/wxmac.icns"
            MACOSX_BUNDLE_ICON_FILE wxmac.icns
            MACOSX_BUNDLE_COPYRIGHT "Copyright wxWidgets"
            MACOSX_BUNDLE_GUI_IDENTIFIER "org.wxwidgets.minimal"
            )
endif()





target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)

