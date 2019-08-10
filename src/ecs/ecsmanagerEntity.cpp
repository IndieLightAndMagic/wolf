//
// Created by Guarin on 2019-08-10.
//
#include "ecs/ecsmanager.h"
#include "Entity.h"
#include <map>
#include <QtGlobal>
#include <mutex>
#include <sstream>

using m_uid_pcomp = std::map<unsigned int, ECS_SYSTEM::PComponent>;
using m_uid_pentt = std::map<unsigned int, ECS_SYSTEM::PEntity>;
using m_string_uid = std::map<std::string, unsigned int>;
using m_uid_uid = std::map<unsigned int, unsigned int>;

m_uid_pcomp m_id_pcomponent;
m_uid_pentt m_id_pntt;
m_string_uid m_name_id;

ECS_SYSTEM::ECSManager::id_string ECS_SYSTEM::ECSManager::createEntity(std::string entityName){

    std::mutex suiidmtx;
    static unsigned long suiid {0x0000000000000000};
    unsigned long theId;
    {
        /* Scoped protection for id */
        std::lock_guard<std::mutex> lock(suiidmtx);
        theId = ++suiid;

        if (!entityName.empty()){
            Q_ASSERT(m_name_id.count(entityName) == 0);
            m_name_id[entityName] = theId;
        }

    }
    m_id_pntt[theId] = std::make_shared<ECS_SYSTEM::Entity>(new ECS_SYSTEM::Entity);
    return std::make_pair(theId, entityName);

}
bool ECS_SYSTEM::ECSManager::renameEntity(unsigned int entityId, std::string newName) {

    Q_ASSERT(m_name_id.count(newName) == 0);
    Q_ASSERT(m_id_pntt.count(entityId) == 1);
    auto stringtofoq = std::string{};
    for(auto&kv:m_name_id) if (kv.second == entityId) stringtofoq = kv.first;
    if (!stringtofoq.empty()) m_name_id.erase(stringtofoq);
    m_name_id[newName] = entityId;
    return true;

}

ECS_SYSTEM::ECSManager::id_string ECS_SYSTEM::ECSManager::copyEntity(unsigned int entityId) {

    auto [newEntityId, newEntityName] = createEntity();

    for(auto&kv:m_name_id){

        if(kv.second == entityId){

            auto pntt = m_id_pntt[entityId].lock();
            if (!pntt) Q_ASSERT(false);

            std::stringstream ss;
            ss << kv.first << "_0x" << std::hex << (unsigned long)(pntt.get());
            newEntityName = ss.str();
            break;
        }

    }

    if (!newEntityName.empty()) renameEntity(newEntityId, newEntityName);

    return std::make_pair(newEntityId, newEntityName);

}

