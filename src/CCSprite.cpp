#include <Geode/Geode.hpp>

#include "../include/functions.hpp"

using namespace geode::prelude;

template <>
CCSprite* NodeDataAPI::createNodeWithUniqueData<CCSprite*>(NodeDataAPI::UniqueNodeData<CCSprite*> data) {
    CCSprite* ret;
    if (data.m_isSpritesheet) {
        ret = CCSprite::createWithSpriteFrameName(data.m_spriteName.c_str());
    } else {
        ret = CCSprite::create(data.m_spriteName.c_str());
    }

    ret->setColor(data.m_color);
    ret->setOpacity(data.m_opacity);

    ret->setFlipX(data.m_flipX);
    ret->setFlipY(data.m_flipY);
    return ret; 
}

template <>
NodeDataAPI::UniqueNodeData<CCSprite*> NodeDataAPI::getUniqueNodeData<CCSprite*>(CCSprite* node) {
    NodeDataAPI::UniqueNodeData<CCSprite*> ret;

    // everything from here

    if (auto textureProtocol = typeinfo_cast<CCTextureProtocol*>(node)) {
        if (auto texture = textureProtocol->getTexture()) {
            auto* cachedTextures = CCTextureCache::sharedTextureCache()->m_pTextures;
            for (auto [key, obj] : CCDictionaryExt<std::string, CCTexture2D*>(cachedTextures)) {
                if (obj == texture) {
                    ret.m_isSpritesheet = false;
                    ret.m_spriteName = key;
                    break;
                }
            }
    
            if (auto spriteNode = typeinfo_cast<CCSprite*>(node)) {
                auto* cachedFrames = CCSpriteFrameCache::sharedSpriteFrameCache()->m_pSpriteFrames;
                auto const rect = spriteNode->getTextureRect();
                for (auto [key, frame] : CCDictionaryExt<std::string, CCSpriteFrame*>(cachedFrames)) {
                    if (frame->getTexture() == texture && frame->getRect() == rect) {
                        ret.m_isSpritesheet = true;
                        ret.m_spriteName = key;
                        break;
                    }
                }
            }
    
        }
    }

    // to here
    // is copied from devtools (https://github.com/geode-sdk/DevTools/blob/e605e96cad62059411e00d0eec5158c7305bac5a/src/pages/Attributes.cpp#L152-L173)

    ret.m_color = node->getColor();
    ret.m_opacity = node->getOpacity();

    ret.m_flipX = node->isFlipX();
    ret.m_flipY = node->isFlipY();
    
    return ret;
}
