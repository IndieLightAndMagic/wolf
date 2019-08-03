#ifndef __FAST_CLAMPED_TEXTURED_DATA_
#define __FAST_CLAMPED_TEXTURED_DATA_
#include "fasttexturedata.h"
#include <vector>
namespace QQE{

    struct FastClampedTextureData : public QQE::FastTextureData {

        FastClampedTextureData(int, int);
        float *data{nullptr};
        void updateTexture();
        void resetTexture();
    };

}


#endif 