#include "objid.h"

unsigned int HDC::ObjId::__id__ = 0;
HDC::ObjId::ObjId(std::function<void(bool)> invalid_handler):
invalid_object_handle(invalid_handler), 
m_value(++ObjId::__id__) 
{

}

unsigned int HDC::ObjId::GetId() const{
	return m_value * static_cast<unsigned int>(m_valid == true);
}

bool HDC::ObjId::IsValid() const{
	return m_valid;
}
void HDC::ObjId::Validate() {
    m_valid = true;
}
void HDC::ObjId::Invalidate() {
	m_valid = false;
    invalid_object_handle(m_valid);
    IsValid();
}


void HDC::ObjId::set_invalid_object_handle(std::function<void(bool)> ioh){
	invalid_object_handle = ioh;
}
