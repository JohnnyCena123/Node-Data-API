#pragma once
#include <Geode/Geode.hpp>

#include "structs.hpp"

using namespace geode::prelude;

namespace NodeDataAPI::callbacks {

    class CallbackObject : public CCObject {
    public:
        CallbackData m_data;
        static CallbackObject* create(CallbackData data);

        virtual ~CallbackObject() override {logDtor("CallbackObject");}
    };

    class CallbackHandler : public CCObject {
        static CallbackHandler* create();
    public:
        static constexpr CallbackHandler* callbackHandler = CallbackHandler::create();
        void onCallback(CCObject* sender);

        virtual ~CallbackHandler() override {logDtor("CallbackHandler");}
    };

}

$execute {
    NodeDataAPI::callbacks::CallbackHandler::callbackHandler->retain();
}