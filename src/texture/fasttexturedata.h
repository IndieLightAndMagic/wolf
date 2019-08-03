#ifndef __FAST_TEXTURE_DATA__
#define __FAST_TEXTURE_DATA__
#include "texturemanager.h"
namespace QQE {
    struct FastTextureData {


        FastTextureData(int,int);
        int                 m_sz;
        int                 m_w, m_h;
        struct {
            unsigned int    slot;
            unsigned int    txture;
        }gl;

        void                bind() const;
        void                unbind() const;
        void                updateTexture();

    };

}

#endif