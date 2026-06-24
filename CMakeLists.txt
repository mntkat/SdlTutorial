cmake_minimum_required(VERSION 3.20)
project(SdlTutorial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
add_subdirectory(SDL3 EXCLUDE_FROM_ALL)

if ( APPLE )
    add_executable(SdlTutorial MACOSX_BUNDLE src/main.cpp src/App.cpp)

    set_target_properties(SdlTutorial PROPERTIES
            BUNDLE True
            MACOSX_BUNDLE_GUI_IDENTIFIER com.mintkat.${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/SdlTutorial.plist.in
    )
else ()
    add_executable(SdlTutorial src/main.cpp src/App.cpp)
endif ()

target_link_libraries(SdlTutorial PRIVATE SDL3::SDL3)

configure_file(${CMAKE_SOURCE_DIR}/Untitled.bmp ${CMAKE_BINARY_DIR}/Untitled.bmp COPYONLY)