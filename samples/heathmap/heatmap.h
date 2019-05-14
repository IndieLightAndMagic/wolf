#ifndef __HEATMAP_H__
#define __HEATMAP_H__
#include <vector>
#include "fastclampedtexturedata.h"

namespace HDC{
    struct HeatMap : public HDC::FastClampedTextureData{

		float m_steps;
		int m_sz;
		HeatMap(int w, int h, float mapresolution = 0.1f);

		void initheatmap(float sh);
        void inc(int x, int y);
        void dec(int x, int y);
        void reset();
        const float& getmax() const;

    private:
    	void updatemax();
        void rectify();
        float m_max_value{0.0f};

    };
}

#endif
