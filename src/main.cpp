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

    struct Fields {
        static int n = 1;
    };

    bool init() {
        if (!MenuLayer::init()) return false;

        CCScheduler::get()->scheduleSelector(schedule_selector(MyMenuLayer::cloneTitle), this, .025f, 200, .5f, false);
            

        auto menu = this->getChildByID("bottom-menu");
        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_gpgBtn_001.png");
        auto button = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyMenuLayer::onTestException));
        menu->addChild(button);



        NodeDataAPI::NodeData<CCSprite*> child1;
        NodeDataAPI::NodeData<CCSprite*> child2;

        auto child1UniqueData = new NodeDataAPI::UniqueNodeData<cocos2d::CCSprite*>();
        auto child2UniqueData = new NodeDataAPI::UniqueNodeData<cocos2d::CCSprite*>();

        child1UniqueData->m_spriteName = "GJ_starBtnMod_001.png";
        child2UniqueData->m_spriteName = "accountBtn_blocked_001.png";

        child1UniqueData->m_isSpritesheet = true;
        child2UniqueData->m_isSpritesheet = true;

        child1UniqueData->m_color = ccc3(
            -11*m_fields->n % 256 + rand() % 29, 
            -13*m_fields->n % 256 + rand() % 29, 
            -15*m_fields->n % 256 + rand() % 29
        );

        child2UniqueData->m_color = ccc3(
            -15*m_fields->n % 256 + rand() % 43, 
            -13*m_fields->n % 256 + rand() % 43, 
            -11*m_fields->n % 256 + rand() % 43
        );


        auto child1LayoutOptions = new NodeDataAPI::AnchorLayoutOptionsData();
        auto child2LayoutOptions = new NodeDataAPI::AnchorLayoutOptionsData();

        child1LayoutOptions->m_anchor = Anchor::Center;
        child2LayoutOptions->m_anchor = Anchor::Center;

        child1LayoutOptions->m_offset = {5.f, 5.f};
        child2LayoutOptions->m_offset = {-5.f, -5.f};


        child1UniqueData->m_flipY = true;
        child2UniqueData->m_flipY = true;

        child1UniqueData->m_opacity = -16*Fields::n % 256;
        child2UniqueData->m_opacity = -12*Fields::n % 256;

        child1.m_skew = {6.f, -9.f};
        child2.m_rotation = {-9.f, 6.f};      

        child1.m_scale = {.15f, .15f};
        child2.m_scale = {.15f, .15f};


        NodeDataAPI::NodeData<CCSprite*> sprData;
        
        sprData.m_children.push_back(child1);
        sprData.m_children.push_back(child2);


        sprData.m_layout = new NodeDataAPI::AnchorLayoutData();

        auto sprUniqueData = new NodeDataAPI::UniqueNodeData<cocos2d::CCSprite*>();
        sprUniqueData->m_spriteName = "GJ_chatBtn_001.png";
        sprUniqueData->m_isSpritesheet = true;
        sprUniqueData->m_color = ccc3(
            -21*Fields::n % 256 + rand() % 29, 
            -4*Fields::n % 256 + rand() % 29, 
            -17*Fields::n % 256 + rand() % 29
        );
        sprUniqueData->m_opacity = -19*Fields::n % 256;
        sprData.m_uniqueData = sprUniqueData;

        NodeDataAPI::NodeData<CCMenuItemSpriteExtra*> data;

        data.m_sprite = &sprData;
        
        data.m_callback = {3.f, {-4.f, 13.f}, 4.5f};

        menu->updateLayout();

        m_fields->n += 4;

        return true;
    }

    void onTestException(CCObject* sender) {
        auto test = NodeDataAPI::getUniqueNodeData<CCTextInputNode*>(CCTextInputNode::create(69.f, 420.f, "skibidi", "gjFont24.fnt"));
    }

    void onCloneButton(CCObject* sender) {
        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        auto menu = this->getChildByID("bottom-menu");
        menu->addChild(NodeDataAPI::cloneNode<CCMenuItemSpriteExtra*>(button));
        menu->updateLayout();
    }

    void cloneTitle(float param) {
        auto spr = NodeDataAPI::cloneNode<CCSprite*>(static_cast<CCSprite*>(this->getChildByID("main-title")), true);
        this->addChild(spr);
        spr->runAction(CCEaseBounceOut::create(CCMoveBy::create(5.f, ccp(0, -150))));
        spr->runAction(CCMoveBy::create(5.f, ccp(-300, 0)));

        spr->runAction(
            CCSequence::createWithTwoActions(
                CCEaseExponentialIn::create(CCFadeOut::create(5.f)),
                CCRemoveSelf::create(true)
            )
        );
    }
};
