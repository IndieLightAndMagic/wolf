#ifndef __FAST_CLAMPED_TEXTURED_DATA_
#define __FAST_CLAMPED_TEXTURED_DATA_
#include "fasttexturedata.h"
#include <vector>
namespace HDC{

    struct FastClampedTextureData : public HDC::FastTextureData {

        FastClampedTextureData(int, int);
        float *data{nullptr};
        void updateTexture();
        void resetTexture();
    };

}


#endif 