#ifndef __OBJID_H__
#define __OBJID_H__

#include <functional>
#include <iostream>

namespace QQE {

    class ObjId {
    private:

        //+
        static unsigned int __id__;
        //


        bool m_valid{false};
        std::function<void(bool)> invalid_object_handle {
            [&](bool isValid){ 
                if (!isValid){
                    std::cout << "Warning this object 0x" << std::hex << (unsigned long)(this) << std::dec << " is invalid!!!" << std::endl;    
                } 
            }
        };

    protected:

        unsigned int m_value{0};

    public:

        ObjId(std::function<void(bool)> invalid_handler = (std::function<void(bool)>)[](bool){});
        unsigned int GetId() const;

        bool IsValid() const;
        void Validate();
        void Invalidate();
        void set_invalid_object_handle(std::function<void(bool)> ioh);

    };

}

#endif //__OBJID_H__