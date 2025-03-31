#pragma once
#include <Geode/Geode.hpp>

#include "structs.hpp"

using namespace geode::prelude;


#define DTOR_CLASS(className) class className {\
    virtual ~className() {\
        if (Mod::get()->getSettingValue<bool>("logging-destructions-enabled")) log::debug("destructed {}!", #className);\
    }

#define DTOR_CLASS_DERIVE(className) class className {\
    virtual ~className() {\
        if (Mod::get()->getSettingValue<bool>("logging-destructions-enabled")) log::debug("destructed {}!", #className);\
    }
#define CLASS_END };

namespace NodeDataAPI::callbacks {

    DTOR_CLASS_DERIVE(CallbackObject, public CCObject)
    public:
        CallbackData m_data;
        static CallbackObject* create(CallbackData data);
    CLASS_END

    DTOR_CLASS_DERIVE(CallbackHandler, public CCObject)
    public:
        static CallbackHandler* create();
        static CallbackHandler* s_callbackHandler;
        void onCallback(CCObject* sender);
    CLASS_END

}