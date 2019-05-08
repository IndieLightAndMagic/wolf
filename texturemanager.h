#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <iostream>
#include <string>

#include <QDir>
#include <QImage>

#include <map>
#include <deque>
#include <tuple>
#include <vector>
#include <utility>
#include <QOpenGLShaderProgram>

namespace HDC {
    class TextureManager {

        static QImage initializeTexture(const std::string filename_texture);

        static std::map<std::string, unsigned int> filename_gltxture_map;
        static std::map<unsigned int, unsigned int> gltxture_txtureslot_map;
        static std::map<unsigned int, void*> gltxture_imageptr_map;

        static std::map<std::string, unsigned int> filename_index_map;
        static std::map<unsigned int, void*> index_ptrimage_map; 

        static bool configureTexture(unsigned int);
        static std::vector<unsigned int> stagedtextures;
        static std::deque<unsigned int> emptytextureslots;
    
    public:
        static bool registerimg(std::vector<std::string>);
        static bool registerimg(std::string);
        static unsigned int getgltxture(std::string);
        static std::tuple<unsigned int, bool> getslot(std::string);
        static std::tuple<unsigned int, bool> getslot(unsigned int);
        static bool unstage(std::string);
        static bool unstage(unsigned int);
        static bool unstagebyslot(unsigned int);
        
        static const std::string solvePath(std::string ppath){
            return std::string(RESOURCES_DIR) + ppath; 
        }
        /**
         * @brief      Register an image as texture. Supports the following:
         * 
         * BMP  Windows Bitmap  Read/write
         * GIF  Graphic Interchange Format (optional)   Read
         * JPG  Joint Photographic Experts Group    Read/write
         * JPEG Joint Photographic Experts Group    Read/write
         * PNG  Portable Network Graphics   Read/write
         * PBM  Portable Bitma  Read
         * PGM  Portable Graymap    Read
         * PPM  Portable Pixmap  Read/write
         * XBM  X11 Bitmap  Read/write
         * XPM  X11 Pixmap  Read/write
         *
         * @param[in]  ppath An STL std::string containing the path for the texture file.
         *
         * @return     An unsigned int with the opengl texture target. 
         */
        static unsigned int registerImage(std::string ppath);
        /**
         * @brief      Register a set of textures. @sa TextureManager::registerImage to check what type of images are supported. 
         *
         * @param[in]  ppaths A vector of std::string with the path of the textures to register. 
         *
         * @return     A vector of unsigned int, returning the opengl target texture of each texture path and in the same order thna ppaths. 
         */
        static std::vector<unsigned int> registerImages(std::vector<std::string> ppaths);
        /**
         * @brief      Stages the textures that are ready to be used. 
         *
         * @param[in]  textureids  A vector of unsigned int with the opengl target texture of the textures to stage.
         */
        static void stageTextures(std::vector<unsigned int> textureids);
        /**
         * @brief      Unstage all the current staged targets.
         */
        static void unstageTextures();

    };




}


#endif

