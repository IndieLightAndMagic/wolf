#include "fasttexturedata.h"
#include <cassert>

HDC::FastTextureData::FastTextureData(int w, int h)
{
    assert(HDC::TextureManager::tunits>0);

    m_w = w;
    m_h = h;
    m_sz = w*h;
    assert(m_w > 0 && m_h > 0);

    unsigned int gltxture{0};
    glGenTextures(1, &gltxture);
    assert(gltxture > 0);

    auto _tunits = ~HDC::TextureManager::tunits;
    unsigned int tmask = 0;
    while(  (1 << tmask ) & _tunits  ) tmask++;
    assert(tmask < 32);

    gl.slot = tmask;
    gl.txture = gltxture;
    HDC::TextureManager::tunits &= ~(1 << tmask);

}


void HDC::FastTextureData::bind() const {

    glActiveTexture(GL_TEXTURE0 + gl.slot);
    glBindTexture(GL_TEXTURE_2D, gl.txture);

}

void HDC::FastTextureData::unbind() const {

    glActiveTexture(GL_TEXTURE0 + gl.slot);
    glBindTexture(GL_TEXTURE_2D, 0);

}
