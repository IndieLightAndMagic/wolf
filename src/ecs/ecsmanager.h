//
// Created by Guarin on 2019-08-05.
//

#ifndef WOLF_ECSMANAGER_H
#define WOLF_ECSMANAGER_H


#include <string>
#include <tuple>
namespace ECS_SYSTEM {

    class ECSManager {
        static unsigned long suiid;
    public:
        static const unsigned long generateId();


        using id_string = std::tuple<unsigned int, std::string>;
        using v_id_string = std::vector<id_string>;
        using v_id = std::vector<unsigned int>;
        /*!
         * @brief This is very slow. Must be used only when loading a scene.... This function creates the memory layout archetype for a particular component type.
         * For example let's say your scene has 10 equilateral triangles.\n
         * These triangles use the same archetype datablock (a block with three 3D points).\n
         * This implies that a data block might be used by several instances of an entity. \n
         * In general this function is used by ECS Systems.
         *

         * @param ptrComponent A raw pointer to component's data. All the data is going to be copied. So the user is responsible for deallocating data pointed by ptrComponent (if such data is on the freestore/heap, when applies).
         * @param byteSize Size in Bytes of the memory region pointed by ptrComponent.
         * @param componentDataBlockName The name of the component, ECSManager might be queried later using that name. It is optional to use. So leave it empty if you don't want to use this feature.\n
         * But if you want to use the feature you must use an unused name.
         *
         * @return On Success the Component's Data Block a tuple  xx , name will be returned, where xx is the number of the id of the data block and name is the name of the datablock.\n
         * If the componentName was empty, an empty name is returned. If the name already existed, an error occurs and an assertion fails.
         *
         */

        static id_string createComponentDataBlock(void *ptrComponent, unsigned int byteSize,
                                                  const std::string &componentDataBlockName = std::string{});
        /*!
         * @brief get a shared ptr to a component Data Block using it's Id. This function is used by ECS Systems.
         * @param componentDataBlockId, the data block id (returned by createComponentDataBlock).
         * @return if component id is available, a shared ptr with the block data will be returned. Otherwise nullptr is returned.
         */
        static std::shared_ptr<void> getComponentDataBlock(unsigned int componentDataBlockId);
        /*!
         * @brief get a shared ptr to a component Data Block using it's name. This function is used by ECS Systems.
         * @param componentDataBlockName, the data block name (returned by createComponentDataBlock).
         * @return if component id is available, a shared ptr with the block data will be returned. Otherwise nullptr is returned.
         */
        static std::shared_ptr<void> getComponentDataBlock(std::string componentDataBlockName);

        /*!
         * @brief get a vector listing id, name pairs of datablocks. A data block at least will have an id number and an optional name.
         * @return a vector of tuples <id, names>. When an object doesn't have a name the name is an empty string.
         */
        static v_id_string getComponentDataBlockKeys();


        /****** COMPONENT *****************************/

        /*!
         * @brief create a component using a data block id. Any time you invoke this function a component will be created so be careful when calling this function!.
         * @param entityId, the entity of the id where the component is going to live at.
         * @param dataBlockId, the id of the data block to use.
         * @param deepcopy, when true the datablock pointed through datablockid will be copied, and registered as new datablock, this new datablock will be used by the component on creation. Usually this is not the case you want to share datablocks among components.
         * @return On error 0 will be returned. The id of the datablock added within the entity will be returned on success.
         */
        static unsigned int createComponentWithDataBlockId(unsigned int entityId, unsigned int dataBlockId, bool deepcopy = false);
        /*!
         * @brief Check createComponentWithDataBlockId, but instead of dataBlockId which is an integer, the parameter will be a string: datablockName
         * @param entityId
         * @param dataBlockName
         * @param deepcopy
         * @return
         */
        static unsigned int createComponentWithDataBlockName(unsigned int entityId, const std::string& dataBlockName, bool deepcopy = false);

        /******* ENTITY *******************************/
        /*!
         * @brief create an entity.
         * @param entityName
         * @return an entity id on success, with it's name. If no entity name used, then the name will be returned empty.
         *
         */
        static id_string createEntity(std::string entityName = std::string{});

        /*!
         * @brief create an entity as a copy of another entity.
         * @param entityId, the to-be-copied entity.
         * If the original entity has it's own name, then the new entity will be named "originalEntityName.nnnn" where nnnn is a hex number representing the number of already made copies of the object.
         * @return on success the id of the new entity, along with it's new name.
         */
        static id_string copyEntity(unsigned int entityId);

        /*!
         * @brief rename a specific entity.
         * @param entityId The id of the entity to rename
         * @param newName The new name to use.
         * @return True when the rename operation went ok, and false when the rename operation couldn't be performed because, the name existed for another entity for example. .
         */

        static bool renameEntity(unsigned int entityId, std::string newName);
        /*!
         * @brief Get Component Id vector.
         * @param entityId, the Id of the entity to get the vector of components from.
         * @return a vector of component ids of components belonging to the entity.
         */
        static v_id getComponentVector(unsigned int entityId);

        /*!
         * @brief Add a component to the entity, using the componentId.
         *
         * @return On success true, on error false.
         *
         */
        static bool addComponentUsingId(unsigned int entityId, unsigned int componentId);

        /*!
         * @brief Add a component using the component name (if the component has it),
         * @param entityId
         * @param componentName
         * @return
         */
        static bool addComponentUsingName(unsigned int entityId, std::string componentName);

        static bool addComponentUsingDataBlockId(unsigned int entityId, unsigned int componentDataBlockId);

        static bool addComponentUsingDataBlockName(unsigned int entityId, std::string componentDataBlockName);


    };
}


#endif //WOLF_ECSMANAGER_H
