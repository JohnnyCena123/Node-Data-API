#include <Geode/Geode.hpp>

#include "../include/NodeDataAPI.hpp"

using namespace geode::prelude;

template <class NodeSubclass>
NodeSubclass NodeDataAPI::createNodeWithUniqueData(UniqueNodeData<NodeSubclass> uniqueData) {
    return nullptr;
}

template <class NodeSubclass>
NodeSubclass NodeDataAPI::createNodeWithData(NodeData<NodeSubclass> data, bool considerChildren) {
    auto ret = NodeDataAPI::createNodeWithUniqueData(data.m_uniqueData);
    
    if (considerChildren) {
        for (NodeDataAPI::NodeData childData : data.m_children) {
            ret->addChild(NodeDataAPI::createNodeWithData(childData));
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
NodeDataAPI::UniqueNodeData<NodeSubclass> NodeDataAPI::getUniqueNodeData(NodeSubclass node) {
    return {};
}

template <class NodeSubclass>
NodeDataAPI::NodeData<NodeSubclass> NodeDataAPI::getNodeData(NodeSubclass node, bool considerChildren) {
    NodeData<NodeSubclass> ret;
    ret.m_uniqueData = NodeDataAPI::getUniqueNodeData<NodeSubclass>(node);

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
NodeSubclass NodeDataAPI::cloneNode(NodeSubclass node, bool considerChildren) {
    return NodeDataAPI::createNodeWithData<NodeSubclass>(
        NodeDataAPI::getNodeData<NodeSubclass>(node, considerChildren), 
        considerChildren
    );
}
