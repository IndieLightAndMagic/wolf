#ifndef __OBJID_H__
#define __OBJID_H__

#include <functional>
#include <iostream>

namespace HDC {

    class ObjId {

        std::function<void(bool)> invalid_object_handle {
            [&](bool isValid){ 
                if (!isValid){
                    std::cout << "Warning this object 0x" << std::hex << (unsigned long)(this) << std::dec << " is invalid!!!" << std::endl;    
                } 
            }
        };

    public:
        ObjId(std::function<void(bool)> invalid_handler) : invalid_object_handle (invalid_handler) {}
        bool m_valid{false};
        unsigned int m_value{0};
        unsigned int GetId() const{
            return m_value * static_cast<unsigned int>(m_valid == true);
        }
        bool IsValid() const{

            invalid_object_handle(m_valid);
            return m_valid;
        }
        void Invalidate() {
            m_valid = false;
            invalid_object_handle(m_valid);
            IsValid();
        }
        void set_invalid_object_handle(std::function<void(bool)> ioh){
            invalid_object_handle = ioh;
        }

    };

}

#endif //__OBJID_H__