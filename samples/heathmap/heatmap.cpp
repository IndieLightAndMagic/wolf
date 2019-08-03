#include <math.h>
#include "heatmap.h"



QQE::HeatMap::HeatMap(int w, int h, float mapresolution):FastClampedTextureData(w,h) {
    m_sz = w*h;
    m_steps = mapresolution;
    m_max_value = 0.0f;
}
const float& QQE::HeatMap::getmax() const{
    return m_max_value;
}
void QQE::HeatMap::reset(){

    FastClampedTextureData::resetTexture();
    m_max_value = 0.0f;

}
void QQE::HeatMap::rectify() {
    auto rectify = false;
    for (auto index = 0; index < m_sz and m_max_value > 1.0f; ++index){
        if(!index) rectify = true;
        data[index] /= m_max_value;
    }
    if (rectify) m_max_value = 1.0f;
}
void QQE::HeatMap::updatemax() {

    m_max_value = 0.0f;
    for (auto index = 0; index < m_sz; ++index){
        if(data[index] > m_max_value){
            m_max_value = data[index];
        }
    }
    rectify();
}

void QQE::HeatMap::inc(int x, int y){
	
	auto index = x + y * m_w;
	data[index] += m_steps;
	if (data[index] > m_max_value){
	    m_max_value = data[index];
	}
	rectify();

} 
void QQE::HeatMap::dec(int x, int y){
	
	auto index = x + y * m_w;
	data[index] -= m_steps;
	updatemax();
}
