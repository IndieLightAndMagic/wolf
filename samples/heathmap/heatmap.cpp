#include "heatmap.h"



HDC::HeatMap::HeatMap() {}
const float& HDC::HeatMap::getmax() const{
    return m_max_value;
}
void HDC::HeatMap::updatemax() {
    m_max_value = 0.0f;
    auto aux = m_map_;
    auto end = &(m_map_ [m_map.size()]);
    while (aux < end) {
        if (*aux > m_max_value) m_max_value = *aux;
        ++aux;
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
	if (data[index] > m_max_value) m_max_value = data[index];
} 
void HDC::HeatMap::dec(int x, int y){
	
	auto data = m_map.data();
	auto index = x + y * m_size_w;
	data[index] -= m_step;
	updatemax();
}