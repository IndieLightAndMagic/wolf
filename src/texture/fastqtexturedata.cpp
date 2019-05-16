#include "fastqtexturedata.h"


static std::map<QImage::Format, std::string> format_map{

    std::make_pair(QImage::Format_Invalid,  "QImage::Format_Invalid:\tThe image is invalid."),
    std::make_pair(QImage::Format_Mono, "QImage::Format_Mono:\tThe image is stored using 1-bit per pixel. Bytes are packed with the most significant bit (MSB) first."),
    std::make_pair(QImage::Format_MonoLSB,  "QImage::Format_MonoLSB:\tThe image is stored using 1-bit per pixel. Bytes are packed with the less significant bit (LSB) first."),
    std::make_pair(QImage::Format_Indexed8, "QImage::Format_Indexed8:\tThe image is stored using 8-bit indexes into a colormap."),
    std::make_pair(QImage::Format_RGB32,    "QImage::Format_RGB32:\tThe image is stored using a 32-bit RGB format (0xffRRGGBB)."),
    std::make_pair(QImage::Format_ARGB32,   "QImage::Format_ARGB32:\tThe image is stored using a 32-bit ARGB format (0xAARRGGBB)."),
    std::make_pair(QImage::Format_ARGB32_Premultiplied, "QImage::Format_ARGB32_Premultiplied:\tThe image is stored using a premultiplied 32-bit ARGB format (0xAARRGGBB), i.e. the red, green, and blue channels are multiplied by the alpha component divided by 255. (If RR, GG, or BB has a higher value than the alpha channel, the results are undefined.) Certain operations (such as image composition using alpha blending) are faster using premultiplied ARGB32 than with plain ARGB32."),
    std::make_pair(QImage::Format_RGB16,    "QImage::Format_RGB16:\tThe image is stored using a 16-bit RGB format (5-6-5)."),
    std::make_pair(QImage::Format_ARGB8565_Premultiplied,   "QImage::Format_ARGB8565_Premultiplied:\tThe image is stored using a premultiplied 24-bit ARGB format (8-5-6-5)."),
    std::make_pair(QImage::Format_RGB666,   "QImage::Format_RGB666:\tThe image is stored using a 24-bit RGB format (6-6-6). The unused most significant bits is always zero."),
    std::make_pair(QImage::Format_ARGB6666_Premultiplied,   "QImage::Format_ARGB6666_Premultiplied:\tThe image is stored using a premultiplied 24-bit ARGB format (6-6-6-6)."),
    std::make_pair(QImage::Format_RGB555,   "QImage::Format_RGB555:\tThe image is stored using a 16-bit RGB format (5-5-5). The unused most significant bit is always zero."),
    std::make_pair(QImage::Format_ARGB8555_Premultiplied,   "QImage::Format_ARGB8555_Premultiplied:\tThe image is stored using a premultiplied 24-bit ARGB format (8-5-5-5)."),
    std::make_pair(QImage::Format_RGB888,   "QImage::Format_RGB888:\tThe image is stored using a 24-bit RGB format (8-8-8)."),
    std::make_pair(QImage::Format_RGB444,   "QImage::Format_RGB444:\tThe image is stored using a 16-bit RGB format (4-4-4). The unused bits are always zero."),
    std::make_pair(QImage::Format_ARGB4444_Premultiplied,   "QImage::Format_ARGB4444_Premultiplied:\tThe image is stored using a premultiplied 16-bit ARGB format (4-4-4-4)."),
    std::make_pair(QImage::Format_RGBX8888, "QImage::Format_RGBX8888:\tThe image is stored using a 32-bit byte-ordered RGB(x) format (8-8-8-8). This is the same as the Format_RGBA8888 except alpha must always be 255. (added in Qt 5.2)"),
    std::make_pair(QImage::Format_RGBA8888, "QImage::Format_RGBA8888:\tThe image is stored using a 32-bit byte-ordered RGBA format (8-8-8-8). Unlike ARGB32 this is a byte-ordered format, which means the 32bit encoding differs between big endian and little endian architectures, being respectively (0xRRGGBBAA) and (0xAABBGGRR). The order of the colors is the same on any architecture if read as bytes 0xRR,0xGG,0xBB,0xAA. (added in Qt 5.2)"),
    std::make_pair(QImage::Format_RGBA8888_Premultiplied,   "QImage::Format_RGBA8888_Premultiplied:\tThe image is stored using a premultiplied 32-bit byte-ordered RGBA format (8-8-8-8). (added in Qt 5.2)"),
    std::make_pair(QImage::Format_BGR30,    "QImage::Format_BGR30:\tThe image is stored using a 32-bit BGR format (x-10-10-10). (added in Qt 5.4)"),
    std::make_pair(QImage::Format_A2BGR30_Premultiplied,    "QImage::Format_A2BGR30_Premultiplied:\tThe image is stored using a 32-bit premultiplied ABGR format (2-10-10-10). (added in Qt 5.4)"),
    std::make_pair(QImage::Format_RGB30,    "QImage::Format_RGB30:\tThe image is stored using a 32-bit RGB format (x-10-10-10). (added in Qt 5.4)"),
    std::make_pair(QImage::Format_A2RGB30_Premultiplied,    "QImage::Format_A2RGB30_Premultiplied:\tThe image is stored using a 32-bit premultiplied ARGB format (2-10-10-10). (added in Qt 5.4)"),
    std::make_pair(QImage::Format_Alpha8,   "QImage::Format_Alpha8:\tThe image is stored using an 8-bit alpha only format. (added in Qt 5.5)"),
    std::make_pair(QImage::Format_Grayscale8,   "QImage::Format_Grayscale8:\tThe image is stored using an 8-bit grayscale format. (added in Qt 5.5)"),
    std::make_pair(QImage::Format_RGBX64,   "QImage::Format_RGBX64:\tThe image is stored using a 64-bit halfword-ordered RGB(x) format (16-16-16-16). This is the same as the Format_RGBX64 except alpha must always be 65535. (added in Qt 5.12)"),
    std::make_pair(QImage::Format_RGBA64,   "QImage::Format_RGBA64:\tThe image is stored using a 64-bit halfword-ordered RGBA format (16-16-16-16). (added in Qt 5.12)"),
    std::make_pair(QImage::Format_RGBA64_Premultiplied, "QImage::Format_RGBA64_Premultiplied:\tThe image is stored using a premultiplied 64-bit halfword-ordered RGBA format (16-16-16-16). (added in Qt 5.12)"),

    };

HDC::FastQTextureData::FastQTextureData(QImage* qimg): FastTextureData(qimg->width(), qimg->height()){

    qimage = qimg;
    data = qimg->bits();
    updateTexture();

}

HDC::FastQTextureData::FastQTextureData(int w, int h, unsigned int format): FastTextureData(w,h){
    
    qimage = new QImage(static_cast<int>(m_w), static_cast<int>(m_h), static_cast<QImage::Format>(format));
    data = qimage->bits();

}

void HDC::FastQTextureData::updateTexture(){

    bind();
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    unbind();

}

void HDC::FastQTextureData::printtextureinformation(){
    auto& gltxture = gl.txture; 

    QImage& rqimage = *(qimage);
    
    std::cout << "Image Format is: " << format_map[rqimage.format()] << std::endl;

    auto colorformat = rqimage.pixelFormat().typeInterpretation();

    if (colorformat  == QPixelFormat::UnsignedInteger ) std::cout << "Color is QPixelFormat::UnsignedInteger " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedShort ) std::cout << "Color is QPixelFormat::UnsignedShort " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedByte ) std::cout << "Color is QPixelFormat::UnsignedByte " << std::endl;     
    if (colorformat  == QPixelFormat::FloatingPoint ) std::cout << "Color is QPixelFormat::FloatingPoint " << std::endl;     

    auto colormodel = rqimage.pixelFormat().colorModel();
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

