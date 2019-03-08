#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <iostream>
#include <QDir>
#include <QImage>
#include <QtGui/QOpenGLShaderProgram>

class TextureManager {


public:
	static const std::string solvePath(const char* ppath){
		return std::string(RESOURCES_DIR) + ppath; 
	}

};

class TextureManagerQT : public TextureManager {

public:
	static QImage initializeTexture(GLuint* ptbo, const std::string filename_texture);

};



#endif

