#include "fastclampedtexturedata.h"

QQE::FastClampedTextureData::FastClampedTextureData(int w, int h):QQE::FastTextureData(w,h){

    resetTexture();
    updateTexture();

}
void QQE::FastClampedTextureData::resetTexture() {
    data = new float[m_sz]();
    for (auto index = 0; index < m_sz; ++index){
        data[index] = 0.0f;
    }

}
void QQE::FastClampedTextureData::updateTexture(){

    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 0x1903, m_w, m_h, 0, 0x1903, GL_FLOAT, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();

}

