cmake_minimum_required(VERSION 3.10)
message(STATUS "-- Trying to build $ENV{SAMPLE_TO_BUILD}")
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



function(generatecustommacros)
    add_compile_definitions(RESOURCES_DIR="${CMAKE_SOURCE_DIR}/resources")
    if (APPLE)
        add_compile_definitions(GL_SILENCE_DEPRECATION)
    endif()
endfunction()
generatecustommacros()

set(target $ENV{SAMPLE_TO_BUILD})
function(get_target_sources)
    file(GLOB_RECURSE target_srcs RELATIVE ${CMAKE_SOURCE_DIR} samples/${target}/*.cpp)
    set(target_srcs ${target_srcs} PARENT_SCOPE)
    foreach(target_src ${target_srcs})
        message(STATUS ${target_src})
    endforeach()
endfunction()

get_target_sources()
add_executable(${target} 
    ${target_srcs}
    src/util.cpp
    src/objid.cpp
    src/scene/scene.cpp
    src/camera/camera.cpp
    src/shader/shader.cpp
    src/meshes/geometry.cpp
    src/opengl/openglwindow.cpp
    src/shader/shadersource.cpp
    src/texture/texturemanager.cpp
    src/texture/fasttexturedata.cpp
    src/texture/fastqtexturedata.cpp
    src/texture/fastclampedtexturedata.cpp
    src/inputmanager/inputmanager.cpp
    )
target_include_directories(${target} PUBLIC
    samples/${target}
    ${CMAKE_SOURCE_DIR}/src/ 
    ${CMAKE_SOURCE_DIR}/src/camera
    ${CMAKE_SOURCE_DIR}/src/meshes
    ${CMAKE_SOURCE_DIR}/src/shader
    ${CMAKE_SOURCE_DIR}/src/opengl
    ${CMAKE_SOURCE_DIR}/src/texture
    ${CMAKE_SOURCE_DIR}/src/scene
    ${CMAKE_SOURCE_DIR}/src/inputmanager
    /usr/local/include
    ) 

if (APPLE)
    message(STATUS "Yes, Apple")
    target_link_libraries(${target} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Quick
        "-framework DiskArbitration"
        "-framework IOKit" 
        "-framework OpenGL" 
        "-framework AGL"
        )
else()
    target_link_libraries(${target} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Quick

    )
endif()
find_package(Qt5 COMPONENTS Core Quick REQUIRED)
target_compile_definitions(${target} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
qt5_add_resources(QT_RESOURCES samples/${target}/qml/heatmap.qrc)


































