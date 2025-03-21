#include <Geode/Geode.hpp>

#include "../include/NodeDataAPI.hpp"

using namespace geode::prelude;

template <>
CCNode* NodeDataAPI::createNodeWithUniqueData<CCNode*>(NodeDataAPI::UniqueNodeData<CCNode*> data) {
    return CCNode::create(); 
}

template <>
NodeDataAPI::UniqueNodeData<CCNode*> NodeDataAPI::getUniqueNodeData<CCNode*>(CCNode* node) {
    return {/* :3 */};
}

template <>
CCNode* NodeDataAPI::cloneNode(CCNode* node, bool considerChildren) {
    return NodeDataAPI::createNodeWithData<CCNode*>(
        NodeDataAPI::getNodeData<CCNode*>(node, considerChildren), 
        considerChildren
    );
}