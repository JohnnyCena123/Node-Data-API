#include <Geode/Geode.hpp>

#include "../include/functions.hpp"

using namespace geode::prelude;

template <>
CCNode* NodeDataAPI::createNodeWithUniqueData<CCNode*>(NodeDataAPI::UniqueNodeData<CCNode*>* data) {
    return CCNode::create(); 
}

template <>
NodeDataAPI::UniqueNodeData<CCNode*>* NodeDataAPI::getUniqueNodeData<CCNode*>(CCNode* node) {
    return {/* :3 */};
}