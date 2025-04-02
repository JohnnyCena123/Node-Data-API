#include <Geode/Geode.hpp>

#include "../include/functions.hpp"

using namespace geode::prelude;

CCNode* NodeDataAPI::utils::getDesByUniqueID(std::string ID, CCNode* node) {
    auto uniqueStringID = static_cast<CCString*>(node->getUserObject("unique-string-id"_spr));
    if (uniqueStringID) {
        if (uniqueStringID->getCString() == ID) return node;
        else for (auto child : CCArrayExt<CCNode*>(node->getChildren())) {
            auto des = getDesByUniqueID(ID, child);
            if (des) return des;
        }
    } else {
        for (auto child : CCArrayExt<CCNode*>(node->getChildren())) {
            auto des = getDesByUniqueID(ID, child);
            if (des) return des;
        }
    }
    
    return nullptr;
}


CCNode* NodeDataAPI::utils::createNodeUniqueExt(NodeDataAPI::UniqueNodeData<CCNode*>* data) {
    switch (data->nodeType()) {
        case NodeType::CCSprite: return NodeDataAPI::createNodeWithUniqueData<CCSprite*>(static_cast<NodeDataAPI::UniqueNodeData<CCSprite*>*>(data));
        case NodeType::CCMenuItemSpriteExtra: return NodeDataAPI::createNodeWithUniqueData<CCMenuItemSpriteExtra*>(static_cast<NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*>*>(data));
        case NodeType::CCNode: return NodeDataAPI::createNodeWithUniqueData<CCNode*>(static_cast<NodeDataAPI::UniqueNodeData<CCSprite*>*>(data));
        default: return nullptr; 
    }
}

CCNode* NodeDataAPI::utils::createNodeExt(NodeDataAPI::NodeData<CCNode*>* data, bool considerChildren) {
    switch (data->m_uniqueData->nodeType()) {
        case NodeType::CCSprite: return NodeDataAPI::createNodeWithData<CCSprite*>(static_cast<NodeDataAPI::NodeData<CCSprite*>*>(data), considerChildren);
        case NodeType::CCMenuItemSpriteExtra: return NodeDataAPI::createNodeWithData<CCMenuItemSpriteExtra*>(static_cast<NodeDataAPI::NodeData<CCMenuItemSpriteExtra*>*>(data), considerChildren);
        case NodeType::CCNode: return NodeDataAPI::createNodeWithData<CCNode*>(data, considerChildren);
        default: return nullptr; 
    }
}


NodeDataAPI::UniqueNodeData<CCNode*>* NodeDataAPI::utils::getUniqueDataExt(CCNode* node) {
    if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
        return NodeDataAPI::getUniqueNodeData<CCSprite*>(sprite);
    } else if (auto menuItemSpriteExtra = typeinfo_cast<CCMenuItemSpriteExtra*>(node)) {
        return NodeDataAPI::getUniqueNodeData<CCMenuItemSpriteExtra*>(menuItemSpriteExtra);
    } else return NodeDataAPI::getUniqueNodeData<CCNode*>(node);
}

NodeDataAPI::NodeData<CCNode*>* NodeDataAPI::utils::getDataExt(CCNode* node, bool considerChildren) {
    if (auto sprite = typeinfo_cast<CCSprite*>(node)) {
        return NodeDataAPI::getNodeData<CCSprite*>(sprite, considerChildren);
    } else if (auto menuItemSpriteExtra = typeinfo_cast<CCMenuItemSpriteExtra*>(node)) {
        return NodeDataAPI::getNodeData<CCMenuItemSpriteExtra*>(menuItemSpriteExtra, considerChildren);
    } else return NodeDataAPI::getNodeData<CCNode*>(node, considerChildren);
}



