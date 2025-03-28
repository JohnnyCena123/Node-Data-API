#include <Geode/Geode.hpp>

#include "../include/functions.hpp"
#include "../include/callbacks.hpp"

using namespace geode::prelude;

template <>
CCMenuItemSpriteExtra* NodeDataAPI::createNodeWithUniqueData<CCMenuItemSpriteExtra*>(NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*> data) {
    auto spr = NodeDataAPI::utils::createNodeExt(data.m_sprite);
    auto ret = CCMenuItemSpriteExtra::create(spr, NodeDataAPI::callbacks::CallbackHandler::callbackHandler, menu_selector(NodeDataAPI::callbacks::CallbackHandler::onCallback));

    return ret; 
}

template <>
NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*> NodeDataAPI::getUniqueNodeData<CCMenuItemSpriteExtra*>(CCMenuItemSpriteExtra* node) {
    NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*> ret;

    
    
    
    return ret;
}
