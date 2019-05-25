QT += core
QT += gui
QT += quick

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CFLAGS_RELEASE    = -O2 -MT
QMAKE_CXXFLAGS_GNUCXX11 -= -std=gnu++11
QMAKE_CXXFLAGS_CXX11 -= -std=c++11

message("Heathmap Data Court. A Genius Sports Tech Demo")
include(openglwindow.pri)
SOURCES += \
	src/util.cpp \
	src/objid.cpp \
	src/scene/scene.cpp \
	src/shader/shader.cpp \
	src/camera/camera.cpp \
	src/meshes/geometry120.cpp \
	src/opengl/openglwindow.cpp \
	src/shader/shadersource.cpp \
	src/texture/texturemanager.cpp \
	src/texture/fasttexturedata.cpp \
	src/texture/fastqtexturedata.cpp \
	src/inputmanager/inputmanager.cpp \
	src/texture/fastclampedtexturedata.cpp \
	samples/heathmap/hdata.cpp \
	samples/heathmap/heatmap.cpp \
	samples/heathmap/heatmapplayer.cpp \
	samples/heathmap/heatmapscene.cpp \
	samples/heathmap/json.cpp \
	samples/heathmap/main.cpp \
	samples/heathmap/timedcounter.cpp \
	samples/heathmap/trackletplayer.cpp \
	samples/heathmap/threadrenderer.cpp
GIT_COMMIT_NUMBER=$$system(git rev-parse --short=7 HEAD) 
message(At the moment of qmake execution git number is $$GIT_COMMIT_NUMBER)

RESOURCES_SYSTEM_PATH=$$absolute_path(".")/resources
message(Resources system path is: $$RESOURCES_SYSTEM_PATH)
DEFINES += RESOURCES_DIR='"\\\"$$RESOURCES_SYSTEM_PATH\\\""' 

target.path = $$[QT_INSTALL_EXAMPLES]/gui/openglwindow
INSTALLS += target




