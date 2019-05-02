#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <iostream>
#include <string>

#include <map>
#include <QDir>
#include <QImage>
#include <vector>
#include <utility>
#include <QOpenGLShaderProgram>

namespace HDC {
    class TextureManager {

        static QImage initializeTexture(const std::string filename_texture);
        static std::map<std::string, unsigned int> filename_index_map;
        static std::map<unsigned int, void*> index_ptrimage_map; 
        static bool configureTexture(unsigned int);
    public:
        static const std::string solvePath(std::string ppath){
            return std::string(RESOURCES_DIR) + ppath; 
        }
        static unsigned int registerImage(std::string ppath);
        static std::vector<unsigned int> registerImages(std::vector<std::string> ppaths);
        static void stageTextures(std::vector<unsigned int> textureids);
        static void unstageTextures();

    };


    class TextureAtlas {

        std::map<std::string, QRect> m_atlas{};
        QImage m_image; 
    public:
        QImage getTexture(const std::string& atlasEntryName);
        TextureAtlas(const std::string filename_texture, const std::string filename_atlas); 


    };

}


#endif

