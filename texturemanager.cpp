#include "texturemanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>

QString getAbsolutePath(std::string filename){

    auto path = QDir(QString(filename.c_str()));
    auto absoluteTestPath = path.cleanPath(path.absoluteFilePath(filename.c_str()));
    return absoluteTestPath;
}

QImage TextureManagerQT::initializeTexture(GLuint* ptbo, const std::string filename_texture){

    auto absoluteTestPath = getAbsolutePath(filename_texture);
    std::cout << "\n\tPath Test : " << absoluteTestPath.toStdString() << std::endl;
    auto qimage = QImage(absoluteTestPath).mirrored(false, true);
    auto [qimagewidth, qimageheight, qbpp] = std::make_tuple(qimage.width(), qimage.height(), qimage.pixelFormat().bitsPerPixel());
    std::cout << "Width :" << qimagewidth << std::endl << "Height: " << qimageheight << std::endl  << "Bitsperpixel: " << (unsigned long)qbpp << std::endl;
    auto colorformat = qimage.pixelFormat().typeInterpretation();
    if (colorformat  == QPixelFormat::UnsignedInteger ) std::cout << "Color is QPixelFormat::UnsignedInteger " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedShort ) std::cout << "Color is QPixelFormat::UnsignedShort " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedByte ) std::cout << "Color is QPixelFormat::UnsignedByte " << std::endl;     
    if (colorformat  == QPixelFormat::FloatingPoint ) std::cout << "Color is QPixelFormat::FloatingPoint " << std::endl;     

    auto colormodel = qimage.pixelFormat().colorModel();
    if (colormodel == QPixelFormat::RGB) std::cout << "Color model is QPixelFormat::RGB" << std::endl;   ;//0   The color model is RGB.
    if (colormodel == QPixelFormat::BGR) std::cout << "Color model is QPixelFormat::BGR" << std::endl;   ;//1   This is logically the opposite endian version of RGB. However, for ease of use it has its own model.
    if (colormodel == QPixelFormat::Indexed) std::cout << "Color model is QPixelFormat::Indexed" << std::endl;   ;//2   The color model uses a color palette.
    if (colormodel == QPixelFormat::Grayscale) std::cout << "Color model is QPixelFormat::Grayscale" << std::endl; ;//3   The color model is Grayscale.
    if (colormodel == QPixelFormat::CMYK) std::cout << "Color model is QPixelFormat::CMYK" << std::endl;  ;//4   The color model is CMYK.
    if (colormodel == QPixelFormat::HSL) std::cout << "Color model is QPixelFormat::HSL" << std::endl;   ;//5   The color model is HSL.
    if (colormodel == QPixelFormat::HSV) std::cout << "Color model is QPixelFormat::HSV" << std::endl;   ;//6   The color model is HSV.
    if (colormodel == QPixelFormat::YUV) std::cout << "Color model is QPixelFormat::YUV" << std::endl;   ;//7   The color model is YUV.
    if (colormodel == QPixelFormat::Alpha) std::cout << "Color model is QPixelFormat::Alpha" << std::endl; ;//8   There is no color model, only alpha is used.

    //Bind textures into opnegl.
    glGenTextures(1, ptbo);
    glBindTexture(GL_TEXTURE_2D, *ptbo); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, qimagewidth, qimageheight, 0, GL_BGRA, GL_UNSIGNED_BYTE, qimage.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    return qimage;

}

TextureAtlas::TextureAtlas(const std::string filename_texture, const std::string filename_atlas){

    QFile loadFile(QString::fromStdString(filename_atlas));
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
            }
        }

    }

    m_image = QImage(getAbsolutePath(filename_texture));


}
