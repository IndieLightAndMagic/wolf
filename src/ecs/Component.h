//
// Created by Guarin on 2019-08-10.
//

#ifndef WOLF_COMPONENT_H
#define WOLF_COMPONENT_H

namespace ECS_SYSTEM {
    class Component;
    using PComponent = std::weak_ptr<ECS_SYSTEM::Component>;
    class Component {
    public:

    };

    class InformationComponent : public Component {

    };

    class ShaderComponent : public Component {

    };

    class VAOComponent : public Component {

    };

    class TextureComponent : public Component {

    };


}


#endif //WOLF_COMPONENT_H
