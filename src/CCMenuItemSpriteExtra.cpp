#include <Geode/Geode.hpp>

#include "../include/functions.hpp"
#include "../include/callbacks.hpp"

using namespace geode::prelude;

template <>
CCMenuItemSpriteExtra* NodeDataAPI::createNodeWithUniqueData<CCMenuItemSpriteExtra*>(NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*>* data) {
    auto spr = NodeDataAPI::utils::createNodeExt(data->m_sprite, true);
    auto ret = CCMenuItemSpriteExtra::create(
        spr, NodeDataAPI::callbacks::CallbackHandler::s_callbackHandler, 
        menu_selector(NodeDataAPI::callbacks::CallbackHandler::onCallback)
    );

    ret->setColor(data->m_color);
    ret->setOpacity(data->m_opacity);

    auto callback = NodeDataAPI::callbacks::CallbackObject::create(data->m_callback);
    ret->setUserObject("callback-data"_spr, callback);

    return ret; 
}

template <>
NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*>* NodeDataAPI::getUniqueNodeData<CCMenuItemSpriteExtra*>(CCMenuItemSpriteExtra* node) {
    auto ret = new NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*>();

    ret->m_sprite = NodeDataAPI::utils::getDataExt(node->getNormalImage(), true);

    ret->m_color = node->getColor();
    ret->m_opacity = node->getOpacity();

    auto callbackObject = static_cast<NodeDataAPI::callbacks::CallbackObject*>(node->getUserObject("callback-data"_spr));
    if (callbackObject) ret->m_callback = callbackObject->m_data;

    return ret;
}
