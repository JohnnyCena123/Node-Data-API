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
        static int n;
    };

    bool init() {
        if (!MenuLayer::init()) return false;

        // CCScheduler::get()->scheduleSelector(schedule_selector(MyMenuLayer::cloneTitle), this, .1f, 100, .5f, false);


        auto menu = this->getChildByID("bottom-menu");
        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_gpgBtn_001.png");
        auto button = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyMenuLayer::onTestException));
        menu->addChild(button);



        auto data = new NodeDataAPI::NodeData<CCMenuItemSpriteExtra*>();
        auto uniqueData = new NodeDataAPI::UniqueNodeData<CCMenuItemSpriteExtra*>;
        data->m_uniqueData = uniqueData;
        uniqueData->m_callback = {3.f, {-4.f, 13.f}, 4.5f};

        auto sprData = new NodeDataAPI::NodeData<CCSprite*>();
        uniqueData->m_sprite = sprData;

        auto sprUniqueData = new NodeDataAPI::UniqueNodeData<cocos2d::CCSprite*>();
        sprData->m_uniqueData = sprUniqueData;

        sprUniqueData->m_spriteName = "GJ_chatBtn_001.png";
        sprUniqueData->m_isSpritesheet = true;
        sprUniqueData->m_color = ccc3(50, 200, 250);
        sprUniqueData->m_opacity = /*(-19*Fields::n % 256) % 256*/255;

        // sprData->m_layout = new NodeDataAPI::AnchorLayoutData();

        sprData->m_scale = {1.25f, 1.f};


        auto child1 = new NodeDataAPI::NodeData<CCSprite*>();
        auto child2 = new NodeDataAPI::NodeData<CCSprite*>();

        auto child1UniqueData = new NodeDataAPI::UniqueNodeData<cocos2d::CCSprite*>();
        auto child2UniqueData = new NodeDataAPI::UniqueNodeData<cocos2d::CCSprite*>();
        child1->m_uniqueData = child1UniqueData;
        child2->m_uniqueData = child2UniqueData;

        child1UniqueData->m_spriteName = "GJ_starBtnMod_001.png";
        child2UniqueData->m_spriteName = "accountBtn_blocked_001.png";

        child1UniqueData->m_isSpritesheet = true;
        child2UniqueData->m_isSpritesheet = true;

        child1UniqueData->m_color = ccc3(200, 100, 250);

        child2UniqueData->m_color = ccc3(169, 254, 80);


        auto child1LayoutOptions = new NodeDataAPI::AnchorLayoutOptionsData();
        auto child2LayoutOptions = new NodeDataAPI::AnchorLayoutOptionsData();
        child1->m_layoutOptions = child1LayoutOptions;
        child2->m_layoutOptions = child2LayoutOptions;

        child1LayoutOptions->m_anchor = Anchor::Center;
        child2LayoutOptions->m_anchor = Anchor::Center;

        child1LayoutOptions->m_offset = {5.f, 5.f};
        child2LayoutOptions->m_offset = {-5.f, -5.f};


        child1UniqueData->m_flipY = true;
        child2UniqueData->m_flipY = true;

        child1UniqueData->m_opacity = -16*Fields::n % 256;
        child2UniqueData->m_opacity = -12*Fields::n % 256;

        child1->m_skew = {6.f, -9.f};
        child2->m_rotation = {-9.f, 6.f};      

        child1->m_scale = {.25f, .25f};
        child2->m_scale = {.25f, .25f};

        
        sprData->m_children.push_back(child1);
        sprData->m_children.push_back(child2);



        menu->addChild(NodeDataAPI::createNodeWithData(data));

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
        auto spr = NodeDataAPI::utils::cloneNodeExt(this->getChildByID("main-title"), true);
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

int MyMenuLayer::Fields::n = 1;
