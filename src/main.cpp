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
        geodeLoader->getSettingValue<std::string>("console-logging-level") == "debug" 
        || geodeLoader->getSettingValue<std::string>("file-logging-level") == "debug"
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
int $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        CCScheduler::get()->scheduleSelector(schedule_selector(MyMenuLayer::cloneTitle), this, .1f, 100, 0.f, false);
            

        auto menu = this->getChildByID("bottom-menu");
        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_gpgBtn_001.png");
        auto button = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyMenuLayer::onTestException));
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void cloneTitle(float param) {
        auto spr = NodeDataAPI::cloneNode<CCSprite*>(static_cast<CCSprite*>(this->getChildByID("main-title")), true);
        this->addChild(spr);
        spr->runAction(CCEaseBounceOut::create(CCMoveBy::create(10.f, ccp(0, -250))));
        spr->runAction(CCMoveBy::create(10.f, ccp(-500, 0)));

        spr->runAction(
            CCSequence::createWithTwoActions(
                CCEaseExponentialOut::create(CCFadeOut::create(10.f)),
                CCRemoveSelf::create(true)
            )
        );
    }

    void onTestException(CCObject* sender) {
        auto test = NodeDataAPI::getUniqueNodeData<CCTextInputNode*>(CCTextInputNode::create(69.f, 420.f, "skibidi", "gjFont24.fnt"));
    }

    void onPlay(CCObject* sender) {
        MenuLayer::onPlay(sender);
        CCScheduler::get()->unscheduleSelector(schedule_selector(MyMenuLayer::cloneTitle), this);
    }

    void onCreator(CCObject* sender) {
        MenuLayer::onCreator(sender);
        CCScheduler::get()->unscheduleSelector(schedule_selector(MyMenuLayer::cloneTitle), this);
    }

    void onGarage(CCObject* sender) {
        MenuLayer::onGarage(sender);
        CCScheduler::get()->unscheduleSelector(schedule_selector(MyMenuLayer::cloneTitle), this);
    }
};
