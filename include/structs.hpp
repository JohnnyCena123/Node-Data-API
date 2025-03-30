#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct FloatPair {
    float x;
    float y;
};

namespace NodeDataAPI {

    inline void logDtor(std::string str) {
        if (Mod::get()->getSettingValue<bool>("logging-destructions-enabled")) log::debug("destructed {}!", str);
    }

    // base

    struct LayoutData {
        bool m_isIgnoreInvisibleChildren;

        virtual ~LayoutData() {logDtor("LayoutData");}
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

        virtual ~AxisLayoutData() override {logDtor("AxisLayoutData");}
    };

    struct AnchorLayoutData : public LayoutData {
        virtual ~AnchorLayoutData() override {logDtor("AnchorLayoutData");}
    };

    
    struct LayoutOptionsData {
        virtual ~LayoutOptionsData() {logDtor("LayoutOptionsData");}
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

        virtual ~AxisLayoutOptionsData() override {logDtor("AxisLayoutOptionsData");}
    };
    

    struct AnchorLayoutOptionsData : public LayoutOptionsData {
        Anchor m_anchor;
        FloatPair m_offset;
    
        virtual ~AnchorLayoutOptionsData() override {logDtor("AnchorLayoutOptionsData!");}
    };
    

    template <class NodeSubclass>
    struct UniqueNodeData {  
        virtual ~UniqueNodeData() {logDtor("UniqueNodeData");}
    };

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
 
        virtual ~NodeData() {logDtor("NodeData");}
    };

    
    // CCNode

    template <>
    struct UniqueNodeData<CCNode*> {  
        virtual ~UniqueNodeData<CCNode*>() {logDtor("UniqueNodeData<CCNode*>");}
    }; 

    template <>
    struct NodeData<CCNode*> : public NodeData {

        UniqueNodeData<CCNode*> m_uniqueData;

        std::vector<NodeData<CCNode*>> m_children;

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

        virtual ~NodeData<CCNode*>() {logDtor("NodeData<CCNode*>");}
    };
    

    // CCSprite

    template <>
    struct UniqueNodeData<CCSprite*> : public UniqueNodeData<CCNode*> {  
        bool m_isSpritesheet; 
        std::string m_spriteName;

        ccColor3B m_color;
        GLubyte m_opacity;

        bool m_flipX;
        bool m_flipY;

        virtual ~UniqueNodeData<CCSprite*>() override {logDtor("UniqueNodeData<CCSprite*>");}
    };

    template <>
    struct NodeData<CCSprite*> : public NodeData<CCNode*> {

        virtual ~NodeData<CCSprite*>() override {logDtor("NodeData<CCSprite*>");}
    };


    // callbacks

    struct CallbackData { // currently the only callback possible is skewing the button, but its just a placeholder so more options are coming soon
        float m_time;
        FloatPair m_skewTo;
        float m_easingRate;
    };
    

    // CCMenuItemSpriteExtra

    template <>
    struct UniqueNodeData<CCMenuItemSpriteExtra*> : public UniqueNodeData<CCNode*> {
        NodeData<CCNode*> m_sprite;

        ccColor3B m_color;
        GLubyte m_opacity;

        CallbackData m_callback;

        virtual ~UniqueNodeData<CCMenuItemSpriteExtra*>() override {logDtor("UniqueNodeData<CCMenuItemSpriteExtra*>");}
    
    };

    template <>
    struct NodeData<CCMenuItemSpriteExtra*> : public NodeData<CCNode*> {
    
        virtual ~NodeData<CCMenuItemSpriteExtra*>() override {logDtor("NodeData<CCMenuItemSpriteExtra*>");}
    };

}
