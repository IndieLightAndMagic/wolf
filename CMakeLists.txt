cmake_minimum_required(VERSION 3.10)

function(checkqtversion)
    
    find_package(Qt5 COMPONENTS 
        Core
        Gui
    REQUIRED)
    message(STATUS "Qt5 cmake files path: ${Qt5_DIR}")
    set(Qt5_DIR ${Qt5_DIR} PARENT_SCOPE)
    
    message(STATUS "Qt5 path: $ENV{Qt5_PATH}")
    
    message(STATUS "Qt5 Core include directories path: ${Qt5Core_INCLUDE_DIRS}")
    message(STATUS "Qt5 Gui include directories path: ${Qt5Gui_INCLUDE_DIRS}")
    
    set(Qt5Core_INCLUDE_DIRS ${Qt5Core_INCLUDE_DIRS} PARENT_SCOPE)
    set(Qt5Gui_INCLUDE_DIRS ${Qt5Gui_INCLUDE_DIRS} PARENT_SCOPE)
    set(Qt5Dummy_MOC_FILE $ENV{Qt5_PATH}/clang_64/mkspecs/features/data/dummy.cpp PARENT_SCOPE) 
    set(CMAKE_AUTOMOC ON)

endfunction()

set(CMAKE_CXX_STANDARD 17)



function(generatecustommacros)
    add_compile_definitions(RESOURCES_DIR="${CMAKE_SOURCE_DIR}/resources")
    if (APPLE)
        add_compile_definitions(GL_SILENCE_DEPRECATION)
    endif()
endfunction()

checkqtversion()
generatecustommacros()



set(target wolf)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
add_executable(${target} 
    main.cpp
    util.cpp
    scene.cpp
    camera.cpp
    shader.cpp
    introscene.cpp
    inputmanager.cpp
    texturemanager.cpp
    )

target_include_directories(${target} PUBLIC
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
)

target_link_libraries(${target}
    Qt5::Core
    Qt5::Gui
)

if (APPLE)
    message(STATUS "Yes, Apple")
    target_link_libraries(${target} 
        "-framework DiskArbitration"
        "-framework IOKit" 
        "-framework OpenGL" 
        "-framework AGL"
        )
else()
endif()


































