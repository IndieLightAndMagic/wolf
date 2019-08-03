#ifndef __FAST_Q_TEXTURE_DATA__
#define __FAST_Q_TEXTURE_DATA__
#include "fasttexturedata.h"
#include <QImage>
namespace QQE {
    struct FastQTextureData : public FastTextureData {

    	FastQTextureData(QImage*);
    	FastQTextureData(int,int,unsigned int);
    	QImage*             qimage;
    	unsigned char*		data;
    	void                printtextureinformation();
    	void 				updateTexture();

    };
}

#endif
