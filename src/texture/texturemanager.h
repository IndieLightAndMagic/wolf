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
    struct FastTextureData {
        
        static unsigned int                                 tunits;
        static std::map<unsigned int, QImage::Format>       ui_format_map; 
        static std::map<QImage::Format, std::string>        format_map;


        FastTextureData(unsigned int, void*);
        
        int                 width, height;
        unsigned char*      data;
        
        struct {
            unsigned int    slot;
            unsigned int    txture;
        } gl;
        
        void                bind() const;
        void                unbind() const;
        void                printtextureinformation();

        unsigned int        format_info_vendor;
        void*               image_data_vendor;
        
        void                updateTexture();

    };
	class TextureManager {

        static std::map<std::string, unsigned int>          filename_gltxture_map;
        static std::map<unsigned int, HDC::FastTextureData*> gltxture_fastdata_map;

    public:
        

        static HDC::FastTextureData*    registerimg(std::string);
        static HDC::FastTextureData*    registerimg(std::string, unsigned int, unsigned int, unsigned int);
    
    private:

        static QImage           initializeTexture(const std::string filename_texture);
        static void             configureTexture(unsigned int);
        static void             imgisnotregistered(std::string);
        static QImage*          createimg(std::string);
        static QImage*          createimg(unsigned int, unsigned int, unsigned int);
        static void             generateandregistertxture(std::string, QImage*);

        
    };




}


#endif

