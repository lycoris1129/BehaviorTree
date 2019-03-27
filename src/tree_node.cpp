#include <tree_node.h>
#include <string>

BT::TreeNode::TreeNode(std::string name){
    name_ = name;
    is_state_updated_ = false;
    set_status(BT::ReturnStatus::IDLE);
}

BT::TreeNode::~TreeNode() {}

void BT::TreeNode::set_status(BT::ReturnStatus new_status){
    if(new_status != BT::IDLE){
        setColorStatus(new_status);
    }
    // Lock acquisition
    std::unique_lock<std::mutex> UniqueLock(state_mutex_);
    // state_ update
    status_ = new_status;
}

void BT::TreeNode::setColorStatus(BT::ReturnStatus new_color_status){
    // Lock acquistion
    std::lock_guard<std::mutex> LockGuard(color_state_mutex_);
    // state_ update
    color_status_ = new_color_status;
}

BT::ReturnStatus BT::TreeNode::get_status(){
    DEBUG_STDOUT(getNodeName() << " is setting its status to " << status_);
    std::lock_guard<std::mutex> LockGuard(state_mutex_);
    return status_;
}

BT::ReturnStatus BT::TreeNode::get_color_status(){
    std::lock_guard<std::mutex> LockGuard(color_state_mutex_);
    return color_status_;
}

bool BT::TreeNode::is_halted(){
    return get_status() == BT::HALTED;
}

void BT::TreeNode::set_x_shift(float new_x_shift){
    x_shift_ = new_x_shift;
}

float BT::TreeNode::get_x_shift(){
    return x_shift_;
}

void BT::TreeNode::set_x_pose(float new_x_pose){
    x_pose_ = new_x_pose;
}

float BT::TreeNode::get_x_pose(){
    return x_pose_;
}

void BT::TreeNode::setNodeName(std::string new_node_name){
    name_ = new_node_name;
}

std::string BT::TreeNode::getNodeName(){
    return name_;
}

BT::NodeType BT::TreeNode::getNodeType(){
    return type_;
}