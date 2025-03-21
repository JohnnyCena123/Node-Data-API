#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct FloatPair {
    float x;
    float y;
};

namespace NodeDataAPI {

    // base

    struct LayoutData {
        bool m_isIgnoreInvisibleChildren;
    };

    struct AxisLayoutData : public LayoutData {
        Axis m_axis;
        AxisAlignment m_axisAlignment;
        AxisAlignment m_crossAxisAlignment;
        AxisAlignment m_crossAxisLineAlignment;

        float m_gap;

        bool m_axisReverse;
        bool m_crossAxisReverse;
        bool m_autoScale;
        bool m_growCrossAxis;
        bool m_crossAxisOverflow;

        std::optional<float> m_allowAndMinLength = std::nullopt;

        FloatPair m_defaultScaleLimits;
    };

    struct AnchorLayoutData : public LayoutData {};

    
    struct LayoutOptionsData {};

    struct AxisLayoutOptionsData : public LayoutOptionsData {
        std::optional<bool> m_autoScale = std::nullopt;
        std::pair<std::optional<float>, std::optional<float>> m_scaleLimits;
        float m_relativeScale = 1.f;

        std::optional<float> m_length = std::nullopt;
        std::optional<float> m_prevGap = std::nullopt;
        std::optional<float> m_nextGap = std::nullopt;

        bool m_breakLine = false;
        bool m_sameLine = false;

        int m_scalePriority = AXISLAYOUT_DEFAULT_PRIORITY;

        std::optional<AxisAlignment> m_crossAxisAlignment;
    };

    struct AnchorLayoutOptionsData : public LayoutOptionsData {
        Anchor m_anchor;
        FloatPair m_offset;
    };
    

    template <class NodeSubclass>
    struct UniqueNodeData {};

    template <class NodeSubclass>
    struct NodeData {

        UniqueNodeData<NodeSubclass> m_uniqueData;

        std::vector<NodeData> m_children;

        LayoutData* m_layout;
        LayoutOptionsData* m_layoutOptions;

        FloatPair m_position;
        FloatPair m_anchorPoint = {.5f, .5f};
        FloatPair m_scale = {1.f, 1.f};
        FloatPair m_contentSize;
        FloatPair m_rotation;
        FloatPair m_skew;

        int m_zOrder;
        int m_tag;

        bool m_isVisible = true;

        bool m_ignoreAnchorPointForPosition;

        std::string m_stringID;

    };

    template <class NodeSubclass>
    NodeSubclass createNodeWithUniqueData(UniqueNodeData<NodeSubclass> uniqueData) {
        return nullptr;
    }

    template <class NodeSubclass>
    NodeSubclass createNodeWithData(NodeData<NodeSubclass> data, bool considerChildren = true) {
        auto ret = createNodeWithUniqueData(data.m_uniqueData);
    
        if (considerChildren) {
            for (NodeData childData : data.m_children) {
                ret->addChild(createNodeWithData(childData));
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
        } 
        else if (auto anchorLayoutData = typeinfo_cast<AnchorLayoutData*>(data.m_layout)) {
            ret->setLayout(AnchorLayout::create());
        }

        if (data.m_layout) ret->getLayout()->ignoreInvisibleChildren(data.m_layout->m_isIgnoreInvisibleChildren);
    

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
        } 
        else if (auto anchorLayoutOptionsData = typeinfo_cast<AnchorLayoutOptionsData*>(data.m_layoutOptions)) {
                ret->setLayoutOptions(AnchorLayoutOptions::create()
                ->setAnchor(anchorLayoutOptionsData->m_anchor)
                ->setOffset({anchorLayoutOptionsData->m_offset.x, anchorLayoutOptionsData->m_offset.y})
            );
        }


        ret->setPosition({data.m_position.x, data.m_position.y});
        ret->setAnchorPoint({data.m_anchorPoint.x, data.m_anchorPoint.y});
        ret->setScale(data.m_scale.x, data.m_scale.y);
        ret->setContentSize({data.m_contentSize.x, data.m_contentSize.y});
        ret->setRotationX(data.m_rotation.x); ret->setRotationY(data.m_rotation.y);
        ret->setSkewX(data.m_skew.x); ret->setSkewY(data.m_skew.y);

        ret->setZOrder(data.m_zOrder);
        ret->setTag(data.m_tag);

        ret->setVisible(data.m_isVisible);

        ret->ignoreAnchorPointForPosition(data.m_ignoreAnchorPointForPosition);
    
        ret->updateLayout();

        ret->setID(data.m_stringID);

        return ret;
    }


    template <class NodeSubclass>
    UniqueNodeData<NodeSubclass> getUniqueNodeData(NodeSubclass node) {
        return {};
    }

    template <class NodeSubclass>
    NodeData<NodeSubclass> getNodeData(NodeSubclass node, bool considerChildren = true) {
        NodeData<NodeSubclass> ret;
        ret.m_uniqueData = getUniqueNodeData<NodeSubclass>(node);

        if (considerChildren) {
            for (NodeSubclass* child : node->getChildren()) {  
                ret.children.push_back(getNodeData(child)); 
            }
        }

        if (auto axisLayout = typeinfo_cast<AxisLayout*>(node->getLayout())) {
            ret.m_layout = new AxisLayoutData();
            ret.m_layout->m_axis = axisLayout->getAxis();
            ret.m_layout->m_axisAlignment = axisLayout->getAxisAlignment();
            ret.m_layout->m_crossAxisAlignment = axisLayout->getCrossAxisAlignment();
            ret.m_layout->m_crossAxisLineAlignment = axisLayout->getCrossAxisLineAlignment();
            ret.m_layout->m_gap = axisLayout->getGap();
            ret.m_layout->m_axisReverse = axisLayout->getAxisReverse();
            ret.m_layout->m_crossAxisReverse = axisLayout->getCrossAxisReverse();
            ret.m_layout->m_autoScale = axisLayout->getAutoScale();
            ret.m_layout->m_growCrossAxis = axisLayout->getGrowCrossAxis();
            ret.m_layout->m_crossAxisOverflow = axisLayout->getCrossAxisOverflow();
            ret.m_layout->m_allowAndMinLength = axisLayout->getAutoGrowAxis();
            ret.m_layout->m_defaultScaleLimits = {axisLayout->getDefaultMinScale(), axisLayout->getDefaultMaxScale()};
        } 
        else if (auto anchorLayout = typeinfo_cast<AnchorLayout*>(node->getLayout())) {
            ret.m_layout = new AnchorLayoutData();
        }

        if (auto layout = node->getLayout()) ret.m_layout->m_isIgnoreInvisibleChildren = layout->isIgnoreInvisibleChildren();


        if (auto axisLayoutOptions = typeinfo_cast<AxisLayoutOptions>(node->getLayoutOptions())) {
            ret.m_layout = new AxisLayoutOptionsData();
            ret.m_layout->m_autoScale = axisLayoutOptions->getAutoScale();
            ret.m_layout->m_scaleLimits = std::make_pair(axisLayoutOptions->getMinScale(), axisLayoutOptions->getMaxScale());
            ret.m_layout->m_relativeScale = axisLayoutOptions->getRelativeScale();
            ret.m_layout->m_length = axisLayoutOptions->getLength();
            ret.m_layout->m_prevGap = axisLayoutOptions->getPrevGap();
            ret.m_layout->m_nextGap = axisLayoutOptions->getNextGap();
            ret.m_layout->m_breakLine = axisLayoutOptions->getBreakLine();
            ret.m_layout->m_sameLine = axisLayoutOptions->getSameLine();
            ret.m_layout->m_scalePriority = axisLayoutOptions->getScalePriority();
            ret.m_layout->m_crossAxisAlignment = axisLayoutOptions->getCrossAxisAlignment();
        } 
        else if (auto anchorLayoutOptions = typeinfo_cast<AnchorLayoutOptions>(node->getLayoutOptions())) {
            ret.m_layoutOptions = new AnchorLayoutOptionsData();
            ret.m_layoutOptions->m_anchor = anchorLayoutOptions->getAnchor();
            ret.m_layoutOptions->m_offset = {anchorLayoutOptions->getOffset().x, anchorLayoutOptions->getOffset().y};
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

        return ret;
    }


    template <class NodeSubclass>
    inline NodeSubclass cloneNode(NodeSubclass node, bool considerChildren = true) {
    return createNodeWithData<NodeSubclass>(
        getNodeData<NodeSubclass>(node, considerChildren), 
        considerChildren
    );
}

    // CCNode 

    template <>
    struct UniqueNodeData<CCNode> {};

    template <>
    CCNode* createNodeWithUniqueData<CCNode*>(UniqueNodeData<CCNode*> data);

    template <>
    UniqueNodeData<CCNode*> getUniqueNodeData<CCNode*>(CCNode* node);

    // CCSprite

    template <>
    struct UniqueNodeData<CCSprite*> {
        bool m_isSpritesheet;
        const char* m_spriteName;

        ccColor3B m_color;
        GLubyte m_opacity;

        bool m_flipX;
        bool m_flipY;
    };

    template <>
    CCSprite* createNodeWithUniqueData<CCSprite*>(UniqueNodeData<CCSprite*> data);

    template <>
    UniqueNodeData<CCSprite*> getUniqueNodeData<CCSprite*>(CCSprite* node);
    
}