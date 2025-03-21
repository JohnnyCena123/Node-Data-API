#include <Geode/Geode.hpp>

#include "../include/NodeDataAPI.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer>
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        this->addChild(NodeDataAPI::cloneNode<CCSprite*>(this->getChildByID("main-title")));
        return true;
    }
};
