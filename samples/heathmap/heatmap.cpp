#include <math.h>
#include "heatmap.h"



HDC::HeatMap::HeatMap() {}
const float& HDC::HeatMap::getmax() const{
    return m_max_value;
}
void HDC::HeatMap::reset(){
	m_max_value = 0.0f;
}
void HDC::HeatMap::updatemax() {
    m_max_value = 0.0f;
    auto sz = m_map.size();
    bool dirty = false;

    for ( auto index = 0; index < sz; ++index){
        if (m_map_[index] > m_max_value){
            dirty = true;
            m_max_value = m_map_[index];
        }
    }
    if (dirty){
        for (auto index = 0; index < sz; ++index){

            float fred = m_map_[index] / m_max_value;
            fred *= 255.9f;
            m_map_txture[index*4 + 2] = static_cast<unsigned char>(floorf(fred));

        }
    }

}
void HDC::HeatMap::initheatmap(const QSize& sz, int sh){

	m_size_w = sz.width();
	m_size_h = sz.height();
	
	assert(sh>0);
	assert(!sz.isEmpty());

	m_step = sh;
	m_step = 1/m_step;
	if (m_map.size()) m_map.clear();
	auto vector_size = m_size_w * m_size_h;
	while(vector_size--) m_map.push_back(0.0f);
	m_map_ = m_map.data();

}

void HDC::HeatMap::inc(int x, int y){
	
	auto data = m_map.data();
	auto index = x + y * m_size_w;
	data[index] += m_step;
	m_map_txture[index*4 + 2] = 255;
	/*if (data[index] > m_max_value){
	    m_max_value = data[index];
        auto sz = m_map.size();
        for (auto index = 0; index < sz; ++index){

            float fred = m_map_[index] / m_max_value;
            fred *= 255.9f;
            auto ucfred = static_cast<unsigned char>(floorf(fred));
            m_map_txture[index*4 + 2] = ucfred;

        }
	}*/

} 
void HDC::HeatMap::dec(int x, int y){
	
	auto data = m_map.data();
	auto index = x + y * m_size_w;
	data[index] -= m_step;
	updatemax();
}
void HDC::HeatMap::settexturedata(unsigned char * pmaptxture) {
    m_map_txture = pmaptxture;
}