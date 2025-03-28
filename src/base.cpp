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

CCNode* NodeDataAPI::utils::createNodeExt(NodeData<CCNode*> data, bool considerChildren = true) {
    if (auto spriteData = typeinfo_cast<NodeData<CCSprite*>*>(&data)) {
        return createNodeWithData<CCSprite*>(*spriteData, considerChildren);
    } else if (auto menuItemSpriteExtraData = typeinfo_cast<NodeData<CCMenuItemSpriteExtra*>*>(&data)) {
        return createNodeWithData<CCMenuItemSpriteExtra*>(*menuItemSpriteExtraData, considerChildren);
    } else return createNodeWithData<NodeData<CCNode*>>(data, considerChildren);
}

NodeData<CCNode*> NodeDataAPI::utils::getDataExt(CCNode* node, bool considerChildren = true) {
    if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
        return getNodeData<CCSprite*>(sprite, considerChildren);
    } else if (auto MISE = typeinfo_cast<CCMenuItemSpriteExtra*>(node)) {
        return getNodeData<CCMenuItemSpriteExtra*>(MISE, considerChildren);
    } else return getNodeData<CCNode*>(node, considerChildren);
}

inline CCNode* NodeDataAPI::utils::cloneNodeExt(CCNode* node, bool considerChildren = true) {
    return createNodeExt(getDataExt(node, considerChildren), considerChildren);
}
