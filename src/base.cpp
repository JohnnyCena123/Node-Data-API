#include <Geode/Geode.hpp>

#include "../include/functions.hpp"

using namespace geode::prelude;


CCNode* NodeDataAPI::utils::getDesByUniqueID(std::string ID, CCNode* node) {
    auto uniqueStringID = static_cast<CCString*>(node->getUserObject("unique-string-id"_spr));
    if (uniqueStringID) if (uniqueStringID->getCString() == ID) return node;
    else {
        for (auto child : CCArrayExt<CCNode*>(node->getChildren())) {
            auto des = getDesByUniqueID(ID, child);
            if (des) return des;
        }
    }
    return nullptr;
}

CCNode* NodeDataAPI::utils::getNodeByUniqueID(std::string ID) {
    return getDesByUniqueID(ID, CCScene::get());
}
