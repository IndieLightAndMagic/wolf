#include "fasttexturedata.h"
#include <cassert>

QQE::FastTextureData::FastTextureData(int w, int h)
{
    assert(QQE::TextureManager::tunits>0);

    m_w = w;
    m_h = h;
    m_sz = w*h;
    assert(m_w > 0 && m_h > 0);

    unsigned int gltxture{0};
    glGenTextures(1, &gltxture);
    assert(gltxture > 0);

    auto _tunits = ~QQE::TextureManager::tunits;
    unsigned int tmask = 0;
    while(  (1 << tmask ) & _tunits  ) tmask++;
    assert(tmask < 32);

    gl.slot = tmask;
    gl.txture = gltxture;
    QQE::TextureManager::tunits &= ~(1 << tmask);

}


void QQE::FastTextureData::bind() const {

    glActiveTexture(GL_TEXTURE0 + gl.slot);
    glBindTexture(GL_TEXTURE_2D, gl.txture);

}

void QQE::FastTextureData::unbind() const {

    glActiveTexture(GL_TEXTURE0 + gl.slot);
    glBindTexture(GL_TEXTURE_2D, 0);

}
