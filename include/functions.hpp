#pragma once
#include <Geode/Geode.hpp>

#include "structs.hpp"

#include "exceptions.hpp"
#ifndef GEODE_IS_WINDOWS
#include <cxxabi.h>
#endif

using namespace geode::prelude;

namespace NodeDataAPI {

    // utils

    namespace utils {

        // Des = Descendant
        CCNode* getDesByUniqueID(std::string ID, CCNode* node);
        inline CCNode* getNodeByUniqueID(std::string ID) {return getDesByUniqueID(ID, CCScene::get());}

        CCNode* createNodeUniqueExt(UniqueNodeData<CCNode*> data);
        CCNode* createNodeExt(NodeData<CCNode*> data, bool considerChildren = true);

        UniqueNodeData<CCNode*> getUniqueDataExt(CCNode* node);
        NodeData<CCNode*> getDataExt(CCNode* node, bool considerChildren = true);


        inline CCNode* cloneNodeExt(CCNode* node, bool considerChildren = true) {
            return createNodeExt(getDataExt(node, considerChildren), considerChildren);
        }

    }


    
    // base

    template <class NodeSubclass>
    NodeSubclass createNodeWithUniqueData(UniqueNodeData<NodeSubclass> uniqueData) {
        char* className;
        #ifdef GEODE_IS_WINDOWS
        className = const_cast<char*>(typeid(uniqueData).name() + 7);
        #else 
        {
            auto mangled = typeid(uniqueData).name();
            className = const_cast<char*>(mangled);
            int status = 0;
            auto demangled = abi::__cxa_demangle(mangled, 0, 0, &status);
            if (status == 0) {
                className = const_cast<char*>(demangled);
            }
            free(demangled);
        }
        #endif
        throw MissingImplementationException(fmt::format("createNodeWithUniqueData{}", className + 14));
    }

    template <class NodeSubclass>
    NodeSubclass createNodeWithData(NodeData<NodeSubclass> data, bool considerChildren = true) {
        auto ret = createNodeWithUniqueData<NodeSubclass>(reinterpret_cast<UniqueNodeData<NodeSubclass>>(data.m_uniqueData));
    
        if (data.m_layout) {
            if (considerChildren) {
                for (auto childData : data.m_children) {
                    ret->addChild(utils::createNodeExt(childData));
                }
            }

            if (auto axisLayoutData = typeinfo_cast<AxisLayoutData*>(data.m_layout)) {
                ret->setLayout(AxisLayout::create(axisLayoutData->m_axis)
                    ->setAxisAlignment(axisLayoutData->m_axisAlignment)
                    ->setCrossAxisAlignment(axisLayoutData->m_crossAxisAlignment)
                    ->setCrossAxisLineAlignment(axisLayoutData->m_crossAxisLineAlignment)
                    ->setGap(axisLayoutData->m_gap)
                    ->setAxisReverse(axisLayoutData->m_axisReverse)
                    ->setCrossAxisReverse(axisLayoutData->m_crossAxisReverse)
                    ->setAutoScale(axisLayoutData->m_autoScale)
                    ->setGrowCrossAxis(axisLayoutData->m_growCrossAxis)
                    ->setCrossAxisOverflow(axisLayoutData->m_crossAxisOverflow)
                    ->setAutoGrowAxis(axisLayoutData->m_allowAndMinLength)
                    ->setDefaultScaleLimits(axisLayoutData->m_defaultScaleLimits.x, axisLayoutData->m_defaultScaleLimits.y)
                );
            } else if (auto anchorLayoutData = typeinfo_cast<AnchorLayoutData*>(data.m_layout)) {
                ret->setLayout(AnchorLayout::create());
            }

            ret->getLayout()->ignoreInvisibleChildren(data.m_layout->m_isIgnoreInvisibleChildren);
        }

        if (data.m_layoutOptions) {
            if (auto axisLayoutOptionsData = typeinfo_cast<AxisLayoutOptionsData*>(data.m_layoutOptions)) {
                ret->setLayoutOptions(AxisLayoutOptions::create()
                    ->setAutoScale(axisLayoutOptionsData->m_autoScale)
                    ->setScaleLimits(
                        axisLayoutOptionsData->m_scaleLimits.first, 
                        axisLayoutOptionsData->m_scaleLimits.second
                    )
                    ->setRelativeScale(axisLayoutOptionsData->m_relativeScale)
                    ->setLength(axisLayoutOptionsData->m_length)
                    ->setPrevGap(axisLayoutOptionsData->m_prevGap)
                    ->setNextGap(axisLayoutOptionsData->m_nextGap)
                    ->setBreakLine(axisLayoutOptionsData->m_breakLine)
                    ->setSameLine(axisLayoutOptionsData->m_sameLine)
                    ->setScalePriority(axisLayoutOptionsData->m_scalePriority)
                    ->setCrossAxisAlignment(axisLayoutOptionsData->m_crossAxisAlignment)
                );
            } else if (auto anchorLayoutOptionsData = typeinfo_cast<AnchorLayoutOptionsData*>(data.m_layoutOptions)) {
                    ret->setLayoutOptions(AnchorLayoutOptions::create()
                    ->setAnchor(anchorLayoutOptionsData->m_anchor)
                    ->setOffset({anchorLayoutOptionsData->m_offset.x, anchorLayoutOptionsData->m_offset.y})
                );
            }
        }

        ret->setPosition({data.m_position.x, data.m_position.y});
        ret->setAnchorPoint({data.m_anchorPoint.x, data.m_anchorPoint.y});
        ret->setScaleX(data.m_scale.x); ret->setScaleY(data.m_scale.y);
        ret->setContentSize({data.m_contentSize.x, data.m_contentSize.y});
        ret->setRotationX(data.m_rotation.x); ret->setRotationY(data.m_rotation.y);
        ret->setSkewX(data.m_skew.x); ret->setSkewY(data.m_skew.y);

        ret->setZOrder(data.m_zOrder);
        ret->setTag(data.m_tag);

        ret->setVisible(data.m_isVisible);

        ret->ignoreAnchorPointForPosition(data.m_ignoreAnchorPointForPosition);
    
        ret->updateLayout();

        ret->setID(data.m_stringID);
        ret->setUserObject("unique-string-id"_spr, CCString::create(data.m_uniqueStringID));

        return static_cast<NodeSubclass>(ret);
    }


    template <class NodeSubclass>
    UniqueNodeData<NodeSubclass> getUniqueNodeData(NodeSubclass node) {
        char* className;
        #ifdef GEODE_IS_WINDOWS
        className = const_cast<char*>(typeid(*node).name() + 6);
        #else 
        {
            auto mangled = typeid(*node).name();
            className = const_cast<char*>(mangled);
            int status = 0;
            auto demangle = abi::__cxa_demangle(mangled, 0, 0, &status);
            if (status == 0) {
                className = const_cast<char*>(demangle);
            }
            free(demangle);
        }
        #endif
        throw MissingImplementationException(fmt::format("getUniqueNodeData<{}>", className));
    }

    template <class NodeSubclass>
    NodeData<NodeSubclass> getNodeData(NodeSubclass node, bool considerChildren = true) {
        NodeData<NodeSubclass> ret;
        ret.m_uniqueData = getUniqueNodeData<NodeSubclass>(node);

        if (considerChildren) {
            for (auto child : CCArrayExt<CCNode*>(node->getChildren())) {  
                ret.m_children.push_back(utils::getDataExt(child)); 
            }
        }
        if (auto layout = node->getLayout()) {
            if (auto axisLayout = typeinfo_cast<AxisLayout*>(layout)) {
                auto axisLayoutData = new AxisLayoutData();
                axisLayoutData->m_axis = axisLayout->getAxis();
                axisLayoutData->m_axisAlignment = axisLayout->getAxisAlignment();
                axisLayoutData->m_crossAxisAlignment = axisLayout->getCrossAxisAlignment();
                axisLayoutData->m_crossAxisLineAlignment = axisLayout->getCrossAxisLineAlignment();
                axisLayoutData->m_gap = axisLayout->getGap();
                axisLayoutData->m_axisReverse = axisLayout->getAxisReverse();
                axisLayoutData->m_crossAxisReverse = axisLayout->getCrossAxisReverse();
                axisLayoutData->m_autoScale = axisLayout->getAutoScale();
                axisLayoutData->m_growCrossAxis = axisLayout->getGrowCrossAxis();
                axisLayoutData->m_crossAxisOverflow = axisLayout->getCrossAxisOverflow();
                axisLayoutData->m_allowAndMinLength = axisLayout->getAutoGrowAxis();
                axisLayoutData->m_defaultScaleLimits = {axisLayout->getDefaultMinScale(), axisLayout->getDefaultMaxScale()};
                ret.m_layout = axisLayoutData;  
            } else if (auto anchorLayout = typeinfo_cast<AnchorLayout*>(layout)) {
                ret.m_layout = new AnchorLayoutData();
            }   

            ret.m_layout->m_isIgnoreInvisibleChildren = layout->isIgnoreInvisibleChildren();
        }

        if (auto layoutOptions = node->getLayoutOptions()) {
            if (auto axisLayoutOptions = typeinfo_cast<AxisLayoutOptions*>(layoutOptions)) {
                auto axisLayoutOptionsData = new AxisLayoutOptionsData();
                axisLayoutOptionsData->m_autoScale = axisLayoutOptions->getAutoScale();
                axisLayoutOptionsData->m_scaleLimits = std::make_pair(axisLayoutOptions->getMinScale(), axisLayoutOptions->getMaxScale());
                axisLayoutOptionsData->m_relativeScale = axisLayoutOptions->getRelativeScale();
                axisLayoutOptionsData->m_length = axisLayoutOptions->getLength();
                axisLayoutOptionsData->m_prevGap = axisLayoutOptions->getPrevGap();
                axisLayoutOptionsData->m_nextGap = axisLayoutOptions->getNextGap();
                axisLayoutOptionsData->m_breakLine = axisLayoutOptions->getBreakLine();
                axisLayoutOptionsData->m_sameLine = axisLayoutOptions->getSameLine();
                axisLayoutOptionsData->m_scalePriority = axisLayoutOptions->getScalePriority();
                axisLayoutOptionsData->m_crossAxisAlignment = axisLayoutOptions->getCrossAxisAlignment();
                ret.m_layoutOptions = axisLayoutOptionsData;
            } else if (auto anchorLayoutOptions = typeinfo_cast<AnchorLayoutOptions*>(layoutOptions)) {
                auto anchorLayoutOptionsData = new AnchorLayoutOptionsData();
                anchorLayoutOptionsData->m_anchor = anchorLayoutOptions->getAnchor();
                anchorLayoutOptionsData->m_offset = {anchorLayoutOptions->getOffset().x, anchorLayoutOptions->getOffset().y};
                ret.m_layoutOptions = anchorLayoutOptionsData;
            }
        }

        ret.m_position = {node->getPositionX(), node->getPositionY()};
        ret.m_anchorPoint = {node->getAnchorPoint().x, node->getAnchorPoint().y};
        ret.m_scale = {node->getScaleX(), node->getScaleY()};
        ret.m_contentSize = {node->getContentWidth(), node->getContentHeight()};
        ret.m_rotation = {node->getRotationX(), node->getRotationY()};
        ret.m_skew = {node->getSkewX(), node->getSkewY()};

        ret.m_zOrder = node->getZOrder();
        ret.m_tag = node->getTag();

        ret.m_isVisible = node->isVisible();

        ret.m_ignoreAnchorPointForPosition = node->isIgnoreAnchorPointForPosition();

        ret.m_stringID = node->getID();
        auto uniqueStringID = static_cast<CCString*>(node->getUserObject("unique-string-id"_spr));
        ret.m_uniqueStringID = uniqueStringID ? uniqueStringID->getCString() : "";

        return ret;
    }


    template <class NodeSubclass>
    inline NodeSubclass cloneNode(NodeSubclass node, bool considerChildren = true) {
        return createNodeWithData<NodeSubclass>(getNodeData<NodeSubclass>(node, considerChildren));
    }



    // CCNode 

    template <>
    CCNode* createNodeWithUniqueData<CCNode*>(UniqueNodeData<CCNode*> data);

    template <>
    UniqueNodeData<CCNode*> getUniqueNodeData<CCNode*>(CCNode* node);


    // CCSprite

    template <>
    CCSprite* createNodeWithUniqueData<CCSprite*>(UniqueNodeData<CCSprite*> data);

    template <>
    UniqueNodeData<CCSprite*> getUniqueNodeData<CCSprite*>(CCSprite* node);

    
    // CCMenuItemSpriteExtra

    template <>
    CCMenuItemSpriteExtra* createNodeWithUniqueData<CCMenuItemSpriteExtra*>(UniqueNodeData<CCMenuItemSpriteExtra*> data);

    template <>
    UniqueNodeData<CCMenuItemSpriteExtra*> getUniqueNodeData<CCMenuItemSpriteExtra*>(CCMenuItemSpriteExtra* node);


    
}
