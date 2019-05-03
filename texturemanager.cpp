#include "texturemanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QImage>
#include <QFile>

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
std::map<unsigned int, void*> HDC::TextureManager::index_ptrimage_map{}; 
        
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

std::vector<unsigned int> HDC::TextureManager::registerImages(std::vector<std::string> ppaths){

    std::vector<unsigned int> textureTargets{};
    for (const auto ppath : ppaths) textureTargets.push_back(HDC::TextureManager::registerImage(ppath));
    return textureTargets;

}

bool HDC::TextureManager::configureTexture(unsigned int textureIndex){

    auto found = index_ptrimage_map.find(textureIndex) != index_ptrimage_map.end();
    assert(found);
    auto pqimage = static_cast<QImage*>(index_ptrimage_map[textureIndex]);
    auto& qimage = pqimage[0];
    glBindTexture(GL_TEXTURE_2D, textureIndex); 
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

QImage HDC::TextureManager::initializeTexture(const std::string filename_texture){

    auto qimage = QImage(getAbsolutePath(filename_texture)).mirrored(false, true);
    auto [qimagewidth, qimageheight, qbpp] = std::make_tuple(qimage.width(), qimage.height(), qimage.pixelFormat().bitsPerPixel());
    std::cout << "Width :" << qimagewidth << std::endl << "Height: " << qimageheight << std::endl  << "Bitsperpixel: " << (unsigned long)qbpp << std::endl;
    return qimage;

}

HDC::TextureAtlas::TextureAtlas(const std::string filename_texture, const std::string filename_atlas){

    QFile loadFile(getAbsolutePath(filename_atlas));
    loadFile.open(QIODevice::ReadOnly);

    QJsonDocument jsonDocument(QJsonDocument::fromJson(loadFile.readAll()));

    auto jsonObj = jsonDocument.object();
    auto jsonObjKeys = jsonObj.keys();

    for (auto jsonObjKey : jsonObjKeys){
        if (jsonObjKey != QString("data")) continue;
        std::cout << jsonObjKey.toStdString() << std::endl;
        auto dataList = jsonObj[jsonObjKey].toArray();
        auto dataListSize = dataList.count();
        for (auto index = 0; index < dataListSize; ++index){
            auto rectanglesDictionary = dataList[index].toObject();
            for (auto key : rectanglesDictionary.keys()){
                auto rectangleDictionary = rectanglesDictionary[key].toObject();
                auto offsetList = rectangleDictionary["offset"].toArray();
                auto sizeList = rectangleDictionary["size"].toArray();
                QRect r{
                    offsetList[0].toInt(),  offsetList[1].toInt(),
                    sizeList[0].toInt(),    sizeList[1].toInt()
                };
                m_atlas[key.toStdString()] = r;
            }
        }

    }

    m_image = QImage(getAbsolutePath(filename_texture));
    std::cout << "Texture Atlas Created with " << m_atlas.size() << " textures." << std::endl;

}

QImage HDC::TextureAtlas::getTexture(const std::string& atlasEntryName){

    return m_atlas.find(atlasEntryName) == m_atlas.end() ?
                QImage() :
                m_image.copy(m_atlas[atlasEntryName]);

}
