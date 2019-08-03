#include "objid.h"

unsigned int QQE::ObjId::__id__ = 0;
QQE::ObjId::ObjId(std::function<void(bool)> invalid_handler):
invalid_object_handle(invalid_handler), 
m_value(++ObjId::__id__) 
{

}

unsigned int QQE::ObjId::GetId() const{
	return m_value * static_cast<unsigned int>(m_valid == true);
}

bool QQE::ObjId::IsValid() const{
	return m_valid;
}
void QQE::ObjId::Validate() {
    m_valid = true;
}
void QQE::ObjId::Invalidate() {
	m_valid = false;
    invalid_object_handle(m_valid);
    IsValid();
}


void QQE::ObjId::set_invalid_object_handle(std::function<void(bool)> ioh){
	invalid_object_handle = ioh;
}
