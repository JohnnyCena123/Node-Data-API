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


CCNode* NodeDataAPI::utils::createNodeUniqueExt(NodeDataAPI::UniqueNodeData<CCNode*> data, bool considerChildren = true) {
    if (auto spriteData = typeinfo_cast<NodeDataAPI::UniqueNodeData<CCSprite*>*>(&data)) {
        return NodeDataAPI::createNodeWithUniqueData<CCSprite*>(*spriteData, considerChildren);
    } else if (auto menuItemSpriteExtraData = typeinfo_cast<NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*>*>(&data)) {
        return NodeDataAPI::createNodeWithUniqueData<CCMenuItemSpriteExtra*>(*menuItemSpriteExtraData, considerChildren);
    } else return createNodeWithUniqueData<NodeDataAPI::NodeData<CCNode*>>(data, considerChildren);
}

CCNode* NodeDataAPI::utils::createNodeExt(NodeDataAPI::NodeData<CCNode*> data, bool considerChildren = true) {
    if (auto spriteData = typeinfo_cast<NodeDataAPI::NodeData<CCSprite*>*>(&data)) {
        return NodeDataAPI::createNodeWithData<CCSprite*>(*spriteData, considerChildren);
    } else if (auto menuItemSpriteExtraData = typeinfo_cast<NodeDataAPI::NodeData<CCMenuItemSpriteExtra*>*>(&data)) {
        return NodeDataAPI::createNodeWithData<CCMenuItemSpriteExtra*>(*menuItemSpriteExtraData, considerChildren);
    } else return NodeDataAPI::createNodeWithData<CCNode*>(data, considerChildren);
}


NodeDataAPI::UniqueNodeData<CCNode*> NodeDataAPI::utils::getUniqueDataExt(CCNode* node, bool considerChildren = true) {
    if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
        return NodeDataAPI::getUniqueNodeData<CCSprite*>(sprite, considerChildren);
    } else if (auto menuItemSpriteExtra = typeinfo_cast<CCMenuItemSpriteExtra*>(node)) {
        return NodeDataAPI::getUniqueNodeData<CCMenuItemSpriteExtra*>(menuItemSpriteExtra, considerChildren);
    } else return NodeDataAPI::getUniqueNodeData<CCNode*>(node, considerChildren);
}

NodeDataAPI::NodeData<CCNode*> NodeDataAPI::utils::getDataExt(CCNode* node, bool considerChildren = true) {
    if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
        return NodeDataAPI::getNodeData<CCSprite*>(sprite, considerChildren);
    } else if (auto MISE = typeinfo_cast<CCMenuItemSpriteExtra*>(node)) {
        return NodeDataAPI::getNodeData<CCMenuItemSpriteExtra*>(MISE, considerChildren);
    } else return NodeDataAPI::getNodeData<CCNode*>(node, considerChildren);
}


CCNode* NodeDataAPI::utils::cloneNodeExt(CCNode* node, bool considerChildren = true) {
    return NodeDataAPI::utils::createNodeExt(NodeDataAPI::utils::getDataExt(node, considerChildren), considerChildren);
}
