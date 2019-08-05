//
// Created by Guarin on 2019-08-04.
//

#ifndef WOLF_ENTITY_H
#define WOLF_ENTITY_H
#include <vector>
namespace ECS {

    class Component;
    using WpComponent  = std::weak_ptr<Component>;
    using WpComponents = std::vector<WpComponent>;
    
    using UpComponent = std::unique_ptr<Component>;
    using SpComponent = std::shared_ptr<Component>;

    class Component {

    };

    class InformationComponent : public Component {

    };

    class ShaderComponent : public Component {

    };

    class VAOComponent : public Component {
        
    };

    class TextureComponent : public Component {

    };

    class Entity {

    public:
        InformationComponent info;
        std::vector<Component*>

    };
}
#endif //WOLF_ENTITY_H
