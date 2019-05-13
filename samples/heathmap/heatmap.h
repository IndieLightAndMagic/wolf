#ifndef __HEATMAP_H__
#define __HEATMAP_H__
#include <QSize>
#include <vector>
namespace HDC{
	struct HeatMap {
		
		int m_size_w;
		int m_size_h;
		float m_step;
        HeatMap();
        void initheatmap(const QSize& sz, int sh);
        void inc(int x, int y);
        void dec(int x, int y);
        const float& getmax() const;
        float* data();
    private:
    	void updatemax();

    	std::vector<float>m_map;
    	float* m_map_;
    	float m_max_value{0};
    };
}

#endif
