#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <iostream>
#include <string>

#include <QMap>
#include <QDir>
#include <QImage>
#include <QVector>
#include <QOpenGLShaderProgram>


class TextureData {


protected:
    void configureTextures();
    QMap<unsigned int, QImage> tbo_image_map{}; 

public:

    TextureData() = delete;
    TextureData(const QImage& rimage);
    TextureData(QVector<QImage> rimages);

    

};
class TextureManager {


public:
    static const std::string solvePath(const char* ppath){
        return std::string(RESOURCES_DIR) + ppath; 
    }

};

class TextureManagerQT : public TextureManager {

public:
    static QImage initializeTexture(const std::string filename_texture);

}; 

class TextureAtlas {

    std::map<std::string, QRect> m_atlas{};
    QImage m_image; 
public:
    QImage getTexture(const std::string& atlasEntryName);
    TextureAtlas(const std::string filename_texture, const std::string filename_atlas); 


};


#endif

