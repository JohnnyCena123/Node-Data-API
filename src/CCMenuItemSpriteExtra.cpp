#include <Geode/Geode.hpp>

#include "../include/functions.hpp"
#include "../include/callbacks.hpp"

using namespace geode::prelude;

template <>
CCMenuItemSpriteExtra* NodeDataAPI::createNodeWithUniqueData<CCMenuItemSpriteExtra*>(NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*> data) {
    auto spr = NodeDataAPI::utils::createNodeExt(data.m_sprite);
    auto ret = CCMenuItemSpriteExtra::create(spr, NodeDataAPI::callbacks::CallbackHandler::callbackHandler, menu_selector(NodeDataAPI::callbacks::CallbackHandler::onCallback));

    ret->setColor(data.m_color);
    ret->setOpacity(data.m_opacity);

    auto callback = CallbackObject::create(data.m_callback);
    ret->setUserObject("callback-data"_spr, callback);

    return ret; 
}

template <>
NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*> NodeDataAPI::getUniqueNodeData<CCMenuItemSpriteExtra*>(CCMenuItemSpriteExtra* node) {
    NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*> ret;

    ret.m_sprite = getDataExt(node->getNormalImage());

    ret.m_color = node->getColor();
    ret.m_opacity = node->getOpacity();

    ret.m_callback = static_cast<CallbackObject*>(node->getUserObject("callback-data"_spr))->m_data;

    return ret;
}
