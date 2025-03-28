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

        virtual ~LayoutData() {log::debug("destructed LayoutData!");}
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

        ~AxisLayoutData() override {log::debug("destructed AxisLayoutData!");}
    };

    struct AnchorLayoutData : public LayoutData {
        ~AnchorLayoutData() override {log::debug("destructed AnchorLayoutData!");}
    };

    
    struct LayoutOptionsData {
        virtual ~LayoutOptionsData() {log::debug("destructed LayoutOptionsData!");}
    };

    struct AxisLayoutOptionsData : public LayoutOptionsData {
        std::optional<bool> m_autoScale = std::nullopt;
        std::pair<std::optional<float>, std::optional<float>> m_scaleLimits;
        float m_relativeScale = 1.f;

        std::optional<float> m_length = std::nullopt;
        std::optional<float> m_prevGap = std::nullopt;
        std::optional<float> m_nextGap = std::nullopt;

        bool m_breakLine = false;
        bool m_sameLine = false;

        int m_scalePriority = 0;

        std::optional<AxisAlignment> m_crossAxisAlignment;

        ~AxisLayoutOptionsData() override {log::debug("destructed AxisLayoutOptionsData!");}
    };
    

    struct AnchorLayoutOptionsData : public LayoutOptionsData {
        Anchor m_anchor;
        FloatPair m_offset;
    
        ~AnchorLayoutOptionsData() override {log::debug("destructed AnchorLayoutOptionsData!");}
    };
    

    template <class NodeSubclass>
    struct UniqueNodeData {};

    template <class NodeSubclass>
    struct NodeData {

        UniqueNodeData<NodeSubclass> m_uniqueData;

        std::vector<NodeData> m_children;

        LayoutData* m_layout = nullptr;
        LayoutOptionsData* m_layoutOptions = nullptr;

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
        std::string m_uniqueStringID;

        virtual ~NodeData() {log::debug("destructed NodeData!");}
    };

    
    // CCNode 

    template <>
    struct NodeData<CCNode*> : public NodeData {};

    template <>
    struct UniqueNodeData<CCNode*> {} : public UniqueNodeData;
    

    // CCSprite

    template <>
    struct NodeData<CCSprite*> : public NodeData<CCNode*> {};

    template <>
    struct UniqueNodeData<CCSprite*> : public UniqueNodeData<CCNode*> {
        bool m_isSpritesheet; 
        std::string m_spriteName;

        ccColor3B m_color;
        GLubyte m_opacity;

        bool m_flipX;
        bool m_flipY;
    };


    // callbacks

    struct CallbackData { // currently the only callback possible is skewing the button, but its just a placeholder so more options are coming soon
        float m_time;
        FloatPair m_skewTo;
        float m_easingRate;
    };
    

    // CCMenuItemSpriteExtra

    template <>
    struct NodeData<CCMenuItemSpriteExtra*> : public NodeData<CCNode*> {};

    template <>
    struct UniqueNodeData<CCMenuItemSpriteExtra*> : public UniqueNodeData<CCNode*> {
        NodeData<CCNode*> m_sprite;

        ccColor3B m_color;
        GLubyte m_opacity;

        CallbackData m_callback;
    };



}
