#include <Geode/Geode.hpp>

#include "../include/callbacks.hpp"

using namespace geode::prelude;

NodeDataAPI::callbacks::CallbackObject* NodeDataAPI::callbacks::CallbackObject::create(CallbackData data) {
    auto ret = new NodeDataAPI::callbacks::CallbackObject();
    ret->m_data = data;
    ret->autorelease(); 
    return ret;
}

NodeDataAPI::callbacks::CallbackHandler* NodeDataAPI::callbacks::CallbackHandler::create() {
    auto ret = new NodeDataAPI::callbacks::CallbackHandler();
    ret->autorelease(); 
    return ret;
}

NodeDataAPI::callbacks::CallbackHandler* NodeDataAPI::callbacks::CallbackHandler::s_callbackHandler = nullptr;

void NodeDataAPI::callbacks::CallbackHandler::onCallback(CCObject* sender) {
    auto node = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto callback = static_cast<CallbackObject*>(node->getUserObject("callback-data"_spr));
    node->getNormalImage()->runAction(
        CCEaseInOut::create(
            CCSkewTo::create(
                callback->m_data.m_time,
                callback->m_data.m_skewTo.x, callback->m_data.m_skewTo.y
            ), 
            callback->m_data.m_easingRate
        )
    );
}

$execute {
    NodeDataAPI::callbacks::CallbackHandler::s_callbackHandler = NodeDataAPI::callbacks::CallbackHandler::create();
    NodeDataAPI::callbacks::CallbackHandler::s_callbackHandler->retain();
}