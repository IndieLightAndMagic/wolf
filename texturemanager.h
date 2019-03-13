#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <iostream>
#include <string>
#include <map>

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
	static QImage initializeTexture(GLuint* ptbo, const QImage& atlas, QRect targetRect);

}; 

class TextureAtlas {

	std::map<std::string, QRect> m_atlas{};
	QImage m_image;	
public:
	//const QImage& getAtlas(const std::string& atlasName);
	TextureAtlas(const std::string filename_texture, const std::string filename_atlas); 


};


#endif

