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

        static std::map<QImage::Format, std::string>    format_map;
        static std::map<std::string, unsigned int>      filename_gltxture_map;
        static std::map<unsigned int, unsigned int>     gltxture_txtureslot_map;
        static std::map<unsigned int, void*>            gltxture_imageptr_map;

        static std::map<std::string, unsigned int>      filename_index_map;
        static std::map<unsigned int, void*>            index_ptrimage_map; 

        static std::vector<unsigned int>                stagedtextures;
        static std::deque<unsigned int>                 emptytextureslots;

    public:
        static std::pair<std::vector<unsigned int>, bool>   registerimg(std::vector<std::string>);
        static std::pair<unsigned int, bool>                registerimg(std::string);
        static std::pair<unsigned int, bool> 				registerimg(std::string, unsigned int, unsigned int, QImage::Format);
        static std::tuple<unsigned int, bool>               getslot(std::string);
        static std::tuple<unsigned int, bool>               getslot(unsigned int);
        static bool                                         unstage(std::string);
        static bool                                         unstage(unsigned int);
        static void*                                        getimageptr(unsigned int);
        static void                                         printtextureinformation(unsigned int); 
    private:

        static constexpr unsigned int                       slot(unsigned int uislot);        
        static QImage                                       initializeTexture(const std::string filename_texture);
        static bool                                         configureTexture(unsigned int);

        static void                               imgisnotregistered(std::string);
        static QImage*                            createimg(std::string);
        static QImage*                            createimg(unsigned int, unsigned int, QImage::Format);
        static void                               generateandregistertxture(std::string, QImage*);

        
    };




}


#endif

