#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace NodeDataAPI { namespace callbacks {

    class CallbackObject : public CCObject {
    public:
        CallbackData m_data;
    }

    class CallbackHandler : public CCObject {
        static CallbackHandler* create() {
            CallbackHandler* ret = new CallbackHandler();
            ret->autorelease();
            return ret;
        }

    public:
        static constexpr callbackHandler = CallbackHandler::create();

        void onCallback(CCObject* sender) {
            auto node = static_cast<CCMenuItemSpriteExtra*>(sender);
            node->getNormalImage()->runAction(CCEaseInOut::create(
                CCScaleBy::create(
                    node->getUserObject("callback-data-time"_spr),
                    node->getUserObject("callback-data-scale-by"_spr)
                ), 
                node->getUserObject("callback-data-easing-rate"_spr)
            ))
        }
    };

}}

$execute {
    NodeDataAPI::callbacks::CallbackHandler::callbackHandler->retain();
}