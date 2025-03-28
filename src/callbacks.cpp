#include <Geode/Geode.hpp>

#include "../include/callbacks.hpp"

using namespace geode::prelude;

NodeDataAPI::callbacks::CallbackObject* NodeDataAPI::callbacks::CallbackObject::create(CallbackData data) {
    auto ret = new NodeDataAPI::callbacks::CallbackObject();
    ret->m_data = data;
    ret->autorelease(); 
    return ret;
}

NodeDataAPI::callbacks::CallbackObject* NodeDataAPI::callbacks::CallbackHandler::create() {
    auto ret = new NodeDataAPI::callbacks::CallbackHandler();
    ret->autorelease(); 
    return ret;
}

void NodeDataAPI::callbacks::CallbackHandler::onCallback(CCObject* sender) {
    auto node = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto callback = static_cast<CallbackObject*>(node->getUserObject("callback-data"_spr));
    node->getNormalImage()->runAction(
        CCEaseInOut::create(
            CCSkewTo::create(
                callback->m_data.m_time,
                callback->m_data.m_skewTo
            ), 
            callback->m_data.m_easingRate
        )
    );
}