#include "texturemanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QImage>
#include <QFile>

#include <deque>
#include <tuple>
#include <cassert>
#include <utility>

QString getAbsolutePath(std::string filename){

    auto path = QDir(QString(filename.c_str()));
    auto absoluteTestPath = path.cleanPath(path.absoluteFilePath(filename.c_str()));
    return absoluteTestPath;

}
void printTextureInformation(const QImage& crqimage){

    auto colorformat = crqimage.pixelFormat().typeInterpretation();
    if (colorformat  == QPixelFormat::UnsignedInteger ) std::cout << "Color is QPixelFormat::UnsignedInteger " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedShort ) std::cout << "Color is QPixelFormat::UnsignedShort " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedByte ) std::cout << "Color is QPixelFormat::UnsignedByte " << std::endl;     
    if (colorformat  == QPixelFormat::FloatingPoint ) std::cout << "Color is QPixelFormat::FloatingPoint " << std::endl;     

    auto colormodel = crqimage.pixelFormat().colorModel();
    if (colormodel == QPixelFormat::RGB) std::cout << "Color model is QPixelFormat::RGB" << std::endl;   ;//0   The color model is RGB.
    if (colormodel == QPixelFormat::BGR) std::cout << "Color model is QPixelFormat::BGR" << std::endl;   ;//1   This is logically the opposite endian version of RGB. However, for ease of use it has its own model.
    if (colormodel == QPixelFormat::Indexed) std::cout << "Color model is QPixelFormat::Indexed" << std::endl;   ;//2   The color model uses a color palette.
    if (colormodel == QPixelFormat::Grayscale) std::cout << "Color model is QPixelFormat::Grayscale" << std::endl; ;//3   The color model is Grayscale.
    if (colormodel == QPixelFormat::CMYK) std::cout << "Color model is QPixelFormat::CMYK" << std::endl;  ;//4   The color model is CMYK.
    if (colormodel == QPixelFormat::HSL) std::cout << "Color model is QPixelFormat::HSL" << std::endl;   ;//5   The color model is HSL.
    if (colormodel == QPixelFormat::HSV) std::cout << "Color model is QPixelFormat::HSV" << std::endl;   ;//6   The color model is HSV.
    if (colormodel == QPixelFormat::YUV) std::cout << "Color model is QPixelFormat::YUV" << std::endl;   ;//7   The color model is YUV.
    if (colormodel == QPixelFormat::Alpha) std::cout << "Color model is QPixelFormat::Alpha" << std::endl; ;//8   There is no color model, only alpha is used.

}
std::map<std::string, unsigned int> HDC::TextureManager::filename_index_map{};
std::map<std::string, unsigned int> HDC::TextureManager::filename_gltxture_map{};
std::map<unsigned int, unsigned int> HDC::TextureManager::gltxture_txtureslot_map{};
std::map<unsigned int, void*> HDC::TextureManager::gltxture_imageptr_map{};

std::map<unsigned int, void*> HDC::TextureManager::index_ptrimage_map{}; 

std::deque<unsigned int> HDC::TextureManager::emptytextureslots {
    GL_TEXTURE0,
    GL_TEXTURE1,
    GL_TEXTURE2,
    GL_TEXTURE3,
    GL_TEXTURE4,
    GL_TEXTURE5,
    GL_TEXTURE6,
    GL_TEXTURE7,
    GL_TEXTURE8,
    GL_TEXTURE9,
    GL_TEXTURE10,
    GL_TEXTURE11,
    GL_TEXTURE12,
    GL_TEXTURE13,
    GL_TEXTURE14,
    GL_TEXTURE15,
    GL_TEXTURE16,
    GL_TEXTURE17,
    GL_TEXTURE18,
    GL_TEXTURE19,
    GL_TEXTURE20,
    GL_TEXTURE21,
    GL_TEXTURE22,
    GL_TEXTURE23,
    GL_TEXTURE24,
    GL_TEXTURE25,
    GL_TEXTURE26,
    GL_TEXTURE27,
    GL_TEXTURE28,
    GL_TEXTURE29,
    GL_TEXTURE30,
    GL_TEXTURE31,
  
};        
void HDC::TextureManager::stageTextures(std::vector<unsigned int> textureids){

    std::vector<unsigned int> textures_enumeration{
        GL_TEXTURE0,
        GL_TEXTURE1,
        GL_TEXTURE2,
        GL_TEXTURE3,
        GL_TEXTURE4,
        GL_TEXTURE5,
        GL_TEXTURE6,
        GL_TEXTURE7,
        GL_TEXTURE8,
        GL_TEXTURE9,
        GL_TEXTURE10,
        GL_TEXTURE11,
        GL_TEXTURE12,
        GL_TEXTURE13,
        GL_TEXTURE14,
        GL_TEXTURE15,
        GL_TEXTURE16,
        GL_TEXTURE17,
        GL_TEXTURE18,
        GL_TEXTURE19,
        GL_TEXTURE20,
        GL_TEXTURE21,
        GL_TEXTURE22,
        GL_TEXTURE23,
        GL_TEXTURE24,
        GL_TEXTURE25,
        GL_TEXTURE26,
        GL_TEXTURE27,
        GL_TEXTURE28,
        GL_TEXTURE29,
        GL_TEXTURE30,
        GL_TEXTURE31,
    };
    auto size = textureids.size();
    assert(size>0);
    for (auto index = 0; index < size; ++index){
        glActiveTexture(textures_enumeration[index]);
        glBindTexture(GL_TEXTURE_2D, textureids[index]);
    }
}
void HDC::TextureManager::unstageTextures(){
    std::vector<unsigned int> textures_enumeration{
        GL_TEXTURE0, 
        GL_TEXTURE1, 
        GL_TEXTURE2, 
        GL_TEXTURE3, 
        GL_TEXTURE4, 
        GL_TEXTURE5, 
        GL_TEXTURE6, 
        GL_TEXTURE7, 
        GL_TEXTURE8, 
        GL_TEXTURE9, 
        GL_TEXTURE10,
        GL_TEXTURE11,
        GL_TEXTURE12,
        GL_TEXTURE13,
        GL_TEXTURE14,
        GL_TEXTURE15,
        GL_TEXTURE16,
        GL_TEXTURE17,
        GL_TEXTURE18,
        GL_TEXTURE19,
        GL_TEXTURE20,
        GL_TEXTURE21,
        GL_TEXTURE22,
        GL_TEXTURE23,
        GL_TEXTURE24,
        GL_TEXTURE25,
        GL_TEXTURE26,
        GL_TEXTURE27,
        GL_TEXTURE28,
        GL_TEXTURE29,
        GL_TEXTURE30,
        GL_TEXTURE31,
    };
    for(auto texture_enumeration : textures_enumeration){
        glActiveTexture(texture_enumeration);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
unsigned int HDC::TextureManager::registerImage(std::string ppath){

    auto path = solvePath(ppath);
    //check the texture filename and texture target are not created/used yet.

    assert(filename_index_map.find(path) == filename_index_map.end());
    unsigned int tbo{0};
    glGenTextures(1, &tbo);
    assert(index_ptrimage_map.find(tbo) == index_ptrimage_map.end());
    //assert(glIsTexture(tbo));

    //Create image and check it is good.
    auto pqimage = new QImage(initializeTexture(path));
    assert(pqimage->isNull() == false);
    
    filename_index_map[path] = tbo;
    index_ptrimage_map[tbo] = pqimage;
    assert(configureTexture(tbo));
    return tbo;

}

bool HDC::TextureManager::registerimg(std::string imgpath){
    
    assert(HDC::TextureManager::filename_gltxture_map.find(imgpath) == HDC::TextureManager::filename_gltxture_map.end());

    unsigned int gltxture{0};
    glGenTextures(1, &gltxture);
    assert(HDC::TextureManager::gltxture_txtureslot_map.find(gltxture) == HDC::TextureManager::gltxture_txtureslot_map.end());

    auto pqimage = new QImage(initializeTexture(imgpath));
    assert(pqimage->isNull() == false);
    
    filename_gltxture_map[imgpath] = gltxture;
    gltxture_imageptr_map[gltxture] = pqimage;

    return configureTexture(gltxture);

}

bool HDC::TextureManager::registerimg(std::vector<std::string> imgpaths){
    for (auto& imgpath : imgpaths) assert(registerimg(imgpath));
    return true;
}

bool HDC::TextureManager::configureTexture(unsigned int gltxture){

    auto found = gltxture_imageptr_map.find(gltxture) != gltxture_imageptr_map.end();
    assert(found);
    auto pqimage = static_cast<QImage*>(gltxture_imageptr_map[gltxture]);
    auto& qimage = pqimage[0];
    glBindTexture(GL_TEXTURE_2D, gltxture); 
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto [qimagewidth, qimageheight] = std::make_tuple(qimage.width(), qimage.height());
    auto imagedata = qimage.bits();
    assert(qimagewidth>0);
    assert(qimageheight>0);
    assert(imagedata!=nullptr);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, qimagewidth, qimageheight, 0, GL_BGRA, GL_UNSIGNED_BYTE, imagedata);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return true;

}
unsigned int HDC::TextureManager::getgltxture(std::string imgpath){
    auto found = filename_gltxture_map.find(imgpath) != filename_gltxture_map.end();
    assert(found);
    return filename_gltxture_map[imgpath];
}
std::tuple<unsigned int, bool> HDC::TextureManager::getslot(unsigned int gltxture){
    //Check if already
    if (gltxture_txtureslot_map.find(gltxture) != gltxture_txtureslot_map.end())
        return std::make_pair(gltxture_txtureslot_map[gltxture], true);
    
    //Grab slot
    assert(!emptytextureslots.empty());
    auto glslot = emptytextureslots.front();
    emptytextureslots.pop_front();
    
    //Update dict
    gltxture_txtureslot_map[gltxture] = glslot;
    return std::make_pair(glslot, true);

}
std::tuple<unsigned int, bool> HDC::TextureManager::getslot(std::string imgpath){
    return getslot(getgltxture(imgpath));
}
bool HDC::TextureManager::unstage(unsigned int gltxture){
    
    assert(gltxture_txtureslot_map.find(gltxture) != gltxture_txtureslot_map.end());
    auto glslot = gltxture_txtureslot_map[gltxture];
    gltxture_txtureslot_map.erase(gltxture);
    emptytextureslots.push_front(glslot);
    return true;

}

QImage HDC::TextureManager::initializeTexture(const std::string filename_texture){

    auto qimage = QImage(getAbsolutePath(filename_texture)).mirrored(false, true);
    auto [qimagewidth, qimageheight, qbpp] = std::make_tuple(qimage.width(), qimage.height(), qimage.pixelFormat().bitsPerPixel());
    std::cout << "Width :" << qimagewidth << std::endl << "Height: " << qimageheight << std::endl  << "Bitsperpixel: " << (unsigned long)qbpp << std::endl;
    return qimage;

}

