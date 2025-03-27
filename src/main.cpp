#include <Geode/Geode.hpp>

#include "../include/functions.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        auto spr = NodeDataAPI::utils::cloneNode(static_cast<CCSprite*>(this->getChildByID("main-title")));
	this->addChild(spr);
	spr->runAction(CCMoveBy::create(1.f, {0, -50}));

        auto menu = this->getChildByID("bottom-menu");
        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_gpgBtn_001.png");
        auto button = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyMenuLayer::onTestException));
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

     void onTestException(CCObject* sender) {
         auto test = NodeDataAPI::getUniqueNodeData<CCMenuItemSpriteExtra*>(static_cast<CCMenuItemSpriteExtra*>(sender));
     }
};
