cmake_minimum_required(VERSION 3.10)


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


set(target courtdemo)
add_executable(${target} 
    main.cpp
    util.cpp
    objid.cpp
    scene.cpp
    camera.cpp
    shader.cpp
    introscene.cpp
    inputmanager.cpp
    openglwindow.cpp
    shadersource.cpp
    texturemanager.cpp
    meshes/geometry.cpp
    )
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR})

if (APPLE)
    message(STATUS "Yes, Apple")
    target_link_libraries(${target} PRIVATE
        Qt5::Core
        Qt5::Gui
        "-framework DiskArbitration"
        "-framework IOKit" 
        "-framework OpenGL" 
        "-framework AGL"
        )
else()
    target_link_libraries(${target} PRIVATE
        Qt5::Core
        Qt5::Gui
    )
endif()
find_package(Qt5 COMPONENTS Core Quick REQUIRED)
target_compile_definitions(${target} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)



































