#include <Geode/Geode.hpp>

#include "../include/functions.hpp"

using namespace geode::prelude;

void updateSavedLogLevels() {
    auto geodeLoader = Loader::get()->getLoadedMod("geode.loader");

    if (!geodeLoader) {
        log::error("couldnt get the geode loader. something has gone TERRIBLY wrong.");
        return;
    }

    (void)Mod::get()->setSavedValue<bool>(
        "is-logging-level-debug", 
        geodeLoader->getSettingValue<std::string>("console-logging-level") == "debug" || geodeLoader->getSettingValue<std::string>("file-logging-level") == "debug"
    );
}

$execute {
    updateSavedLogLevels();
    listenForAllSettingChangesV3(
        [](std::shared_ptr<SettingV3> setting) {updateSavedLogLevels();}, 
        Loader::get()->getLoadedMod("geode.loader")
    );
}


#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {

    struct Fields {
        SEL_SCHEDULE m_cloneTitleSelector;
    };
    bool init() {
        if (!MenuLayer::init()) return false;

        m_fields->m_cloneTitleSelector = schedule_selector(MyMenuLayer::cloneTitle);
        CCScheduler::get()->scheduleSelector(m_fields->m_cloneTitleSelector, this, .1f, 100, 0.f, false);
            

        auto menu = this->getChildByID("bottom-menu");
        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_gpgBtn_001.png");
        auto button = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyMenuLayer::onTestException));
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void cloneTitle(float param) {
        auto spr = NodeDataAPI::utils::cloneNodeExt(static_cast<CCSprite*>(this->getChildByID("main-title")));
        this->addChild(spr);
        spr->runAction(CCEaseBounceOut::create(CCMoveBy::create(10.f, ccp(0, -150))));
        spr->runAction(CCMoveBy::create(10.f, ccp(-500, 0)));

        auto actions = CCArray::create();
        actions->addObject(CCEaseExponentialOut::create(CCFadeOut::create(10.f)));
        actions->addObject(CCRemoveSelf::create(true));
        spr->runAction(CCSequence::create(actions));
    }

    void onTestException(CCObject* sender) {
        auto test = NodeDataAPI::getUniqueNodeData<CCTextInputNode*>(CCTextInputNode::create(69.f, 420.f, "skibid", "gjFont24.fnt"));
    }

    void onPlay(CCObject* sender) {
        MenuLayer::onPlay(sender);
        CCScheduler::get()->unscheduleSelector(m_fields->m_cloneTitleSelector, this);
    }

    void onCreator(CCObject* sender) {
        MenuLayer::onCreator(sender);
        CCScheduler::get()->unscheduleSelector(m_fields->m_cloneTitleSelector, this);
    }

    void onGarage(CCObject* sender) {
        MenuLayer::onGarage(sender);
        CCScheduler::get()->unscheduleSelector(m_fields->m_cloneTitleSelector, this);
    }
};
