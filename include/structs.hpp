#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct FloatPair {
    float x;
    float y;
};

#define DTOR_STRUCT(structName) struct structName {\
    virtual ~structName() {\
        if (Mod::get()->getSettingValue<bool>("logging-destructions-enabled")) log::debug("destructed {}!", #structName);\
    }
#define DTOR_STRUCT_DERIVE(structName, baseStruct) struct structName : public baseStruct {\
    virtual ~structName() {\
        if (Mod::get()->getSettingValue<bool>("logging-destructions-enabled")) log::debug("destructed {}!", #structName);\
    }     
#define STRUCT_END };

namespace NodeDataAPI {


    // base

    DTOR_STRUCT(LayoutData)
        bool m_isIgnoreInvisibleChildren;
    };

    DTOR_STRUCT_DERIVE(AxisLayoutData, LayoutData)
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
    STRUCT_END

    DTOR_STRUCT_DERIVE(AnchorLayoutData, LayoutData) STRUCT_END

    
    DTOR_STRUCT(LayoutOptionsData) STRUCT_END

    DTOR_STRUCT_DERIVE(AxisLayoutOptionsData, LayoutOptionsData)
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
    STRUCT_END
    

    DTOR_STRUCT_DERIVE(AnchorLayoutOptionsData, LayoutOptionsData)
        Anchor m_anchor;
        FloatPair m_offset;
    STRUCT_END
    

    template <class NodeSubclass>
    DTOR_STRUCT(UniqueNodeData) STRUCT_END

    template <class NodeSubclass>
    DTOR_STRUCT(NodeData) 

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
    STRUCT_END

    
    // CCNode

    template <>
    DTOR_STRUCT(UniqueNodeData<CCNode*>) STRUCT_END 

    // template <>
    // DTOR_STRUCT(NodeData<CCNode*>)

    //     UniqueNodeData<CCNode*> m_uniqueData;

    //     std::vector<NodeData<CCNode*>> m_children;

    //     LayoutData* m_layout = nullptr;
    //     LayoutOptionsData* m_layoutOptions = nullptr;

    //     FloatPair m_position;
    //     FloatPair m_anchorPoint = {.5f, .5f};
    //     FloatPair m_scale = {1.f, 1.f};
    //     FloatPair m_contentSize;
    //     FloatPair m_rotation;
    //     FloatPair m_skew;

    //     int m_zOrder;
    //     int m_tag;

    //     bool m_isVisible = true;

    //     bool m_ignoreAnchorPointForPosition;

    //     std::string m_stringID;
    //     std::string m_uniqueStringID;
    // };
    

    // CCSprite

    template <>
    DTOR_STRUCT_DERIVE(UniqueNodeData<CCSprite*>, UniqueNodeData<CCNode*>) 

        bool m_isSpritesheet; 
        std::string m_spriteName;

        ccColor3B m_color;
        GLubyte m_opacity;

        bool m_flipX;
        bool m_flipY;
    STRUCT_END

    template <>
    DTOR_STRUCT_DERIVE(NodeData<CCSprite*>, NodeData<CCNode*>) STRUCT_END


    // callbacks

    struct CallbackData { 
        float m_time;
        FloatPair m_skewTo; // currently the only callback possible is skewing the button, but its just a placeholder so more options are coming soon
        float m_easingRate;
    };
    

    // CCMenuItemSpriteExtra

    template <>
    DTOR_STRUCT_DERIVE(UniqueNodeData<CCMenuItemSpriteExtra*>, UniqueNodeData<CCNode*>) 
        NodeData<CCNode*> m_sprite;

        ccColor3B m_color;
        GLubyte m_opacity;

        CallbackData m_callback;

    STRUCT_END

    template <>
    DTOR_STRUCT_DERIVE(NodeData<CCMenuItemSpriteExtra*>, NodeData<CCNode*>) STRUCT_END

}
