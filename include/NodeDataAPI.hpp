#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct FloatPair {
    float x;
    float y;
};

namespace NodeDataAPI {

    // base - start 

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
    NodeSubclass createNodeWithUniqueData(UniqueNodeData<NodeSubclass> uniqueData);

    template <class NodeSubclass>
    NodeSubclass createNodeWithData(NodeData<NodeSubclass> data, bool considerChildren = true);


    template <class NodeSubclass>
    UniqueNodeData<NodeSubclass> getUniqueNodeData(NodeSubclass node);

    template <class NodeSubclass>
    NodeData<NodeSubclass> getNodeData(NodeSubclass node, bool considerChildren = true);


    template <class NodeSubclass>
    NodeSubclass cloneNode(NodeSubclass node, bool considerChildren = true);

    // base - end
    // CCNode - start

    template <>
    struct UniqueNodeData<CCNode> {};

    template <>
    CCNode* createNodeWithUniqueData<CCNode*>(UniqueNodeData<CCNode*> data);

    template <>
    UniqueNodeData<CCNode*> getUniqueNodeData<CCNode*>(CCNode* node);

    template <>
    CCNode* cloneNode<CCNode*>(CCNode* node, bool considerChildren = true);

    // CCNode - end
    // CCSprite - start

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

    template <>
    CCSprite* cloneNode<CCSprite*>(CCSprite* node, bool considerChildren = true);

    // CCSprite - end
    
}