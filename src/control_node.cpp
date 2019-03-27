#include <string>
#include <control_node.h>


BT::ControlNode::ControlNode(std::string name) : TreeNode::TreeNode(name)
{
    type_ = BT::NodeType::CONTROL_NODE;
}

BT::ControlNode::~ControlNode(){}

void BT::ControlNode::AddChild(TreeNode* child){
    children_nodes_.push_back(child);
    children_states_.push_back(BT::IDLE);
}