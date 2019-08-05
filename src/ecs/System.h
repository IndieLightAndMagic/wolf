//
// Created by Guarin on 2019-08-04.
//

#ifndef WOLF_SYSTEM_H
#define WOLF_SYSTEM_H

namespace ECS_SYSTEM{
    class System {
    public:
        virtual void AddComponent(int componentId) = 0;
    };    
}


#endif //WOLF_SYSTEM_H
