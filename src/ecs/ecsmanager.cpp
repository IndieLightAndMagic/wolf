//
// Created by Guarin on 2019-08-05.
//

#include <iostream>
#include "ecs/ecsmanager.h"

#include <map>
#include <QtGlobal>
#include <vector>


#include "ecs/Entity.h"

class MemoryBlock {
    std::shared_ptr<unsigned char> blockPtr;
    unsigned int blockSize;
public:

    explicit MemoryBlock(unsigned int blockSize):

            blockPtr(std::shared_ptr<unsigned char>(new unsigned char[blockSize], std::default_delete<unsigned char[]>())),
            blockSize(blockSize){

    }

    ~MemoryBlock(){
        std::cout << "Killing BlockSize: " << blockSize << std::endl;
        blockPtr.reset();
    }

    std::shared_ptr<void> get() const{
        std::weak_ptr<unsigned char> wp = blockPtr;
        return wp.lock();
    }
    void reset() {
        blockPtr.reset();
        blockSize = 0;
    }

    unsigned int size() const{
        return blockSize;
    }

    MemoryBlock() = delete;
    MemoryBlock(const MemoryBlock& rOther) = delete;
    MemoryBlock& operator=(const MemoryBlock& rOther){

        auto blockSize = rOther.size();
        blockPtr = std::shared_ptr<unsigned char>(new unsigned char[blockSize], std::default_delete<unsigned char>());

        if(blockPtr) {

            auto rPtDst = blockPtr.get();
            auto rPtSrc = rOther.get().get();
            memcpy(rPtDst, rPtSrc, blockSize);
            return *this;

        } else {
            blockSize = 0;
            blockPtr.reset();
        }
        return *this;

    }
};

using PMemoryBlock = std::weak_ptr<MemoryBlock>;
using m_string_uid = std::map<std::string, unsigned int>;
using m_uid_pmb = std::map<unsigned int, PMemoryBlock>;

m_string_uid m_name_id;
m_uid_pmb m_id_pmemblock;

ECS_SYSTEM::ECSManager::id_string ECS_SYSTEM::ECSManager::createComponentDataBlock(void *ptrComponent,
                                                                                   unsigned int byteSize,
                                                                                   const std::string& componentDataBlockName){

    static unsigned int idgen {0x0001};
    auto nameForDataBlockUsed = !componentDataBlockName.empty();
    if (nameForDataBlockUsed) Q_ASSERT(m_name_id.count(componentDataBlockName) == 0);

    auto pmb = std::shared_ptr<MemoryBlock>(new MemoryBlock(byteSize));
    Q_ASSERT(pmb->size() == byteSize);

    auto id = idgen++;
    if (nameForDataBlockUsed) m_name_id[componentDataBlockName] = id;
    m_id_pmemblock[id] = pmb;

    auto pmbRaw = pmb->get().get();
    std::memcpy(pmbRaw, ptrComponent, byteSize);

    auto id_string_tuple = std::make_tuple(id, componentDataBlockName);
    return id_string_tuple;

}

std::shared_ptr<void> ECS_SYSTEM::ECSManager::getComponentDataBlock(std::string componentDataBlockName) {

    Q_ASSERT(m_name_id.count(componentDataBlockName));
    return m_id_pmemblock[m_name_id[componentDataBlockName]].lock();

}

std::shared_ptr<void> ECS_SYSTEM::ECSManager::getComponentDataBlock(unsigned int componentDataBlockId) {

    Q_ASSERT(m_id_pmemblock.count(componentDataBlockId));
    return m_id_pmemblock[componentDataBlockId].lock();

}

ECS_SYSTEM::ECSManager::v_id_string ECS_SYSTEM::ECSManager::getComponentDataBlockKeys() {

    auto v = v_id_string{};
    for (auto name_id : m_name_id){

        v.push_back(std::make_pair(name_id.second, name_id.first));

    }
    return v;
}

unsigned int ECS_SYSTEM::ECSManager::createComponentWithDataBlockId(unsigned int entityId, unsigned int dataBlockId,
                                                                    bool deepcopy) {




}



