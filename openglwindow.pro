QMAKE_CXXFLAGS += -std=c++17
QMAKE_CFLAGS_RELEASE    = -O2 -MT
QMAKE_CFLAGS_DEBUG -= -std=gnu++11


message("Wolfenstein 3D clone. 100 Days of Code by JG")
include(openglwindow.pri)
SOURCES += \
    main.cpp \
    scene.cpp \
    camera.cpp \
    gamescene.cpp \
    introscene.cpp \
    inputmanager.cpp \
    texturemanager.cpp \
    
GIT_COMMIT_NUMBER=$$system(git rev-parse --short=7 HEAD) 
message(At the moment of qmake execution git number is $$GIT_COMMIT_NUMBER)

RESOURCES_SYSTEM_PATH=$$absolute_path(".")/resources
message(Resources system path is: $$RESOURCES_SYSTEM_PATH)
DEFINES += RESOURCES_DIR='"\\\"$$RESOURCES_SYSTEM_PATH\\\""' 

target.path = $$[QT_INSTALL_EXAMPLES]/gui/openglwindow
INSTALLS += target




