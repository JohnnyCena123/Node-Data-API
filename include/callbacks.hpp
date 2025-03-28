#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace NodeDataAPI::callbacks {

    class CallbackObject : public CCObject {
    public:
        CallbackData m_data;
        static CallbackObject* create(CallbackData data);

        virtual ~CallbackObject() {log::debug()}
    }

    class CallbackHandler : public CCObject {
        static CallbackHandler* create();
    public:
        static constexpr callbackHandler = CallbackHandler::create();
        void onCallback(CCObject* sender);
    };

}

$execute {
    NodeDataAPI::callbacks::CallbackHandler::callbackHandler->retain();
}