#include <string>
#include <vector>
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

unsigned int BT::ControlNode::GetChildrenNumber(){
    return children_nodes_.size();
}

std::vector<BT::TreeNode*> BT::ControlNode::GetChildren(){
    return children_nodes_;
}

void BT::ControlNode::Halt(){
    DEBUG_STDOUT("HALTING: "<< get_name());
    HaltChildren(0);
    set_status(BT::HALTED);
}
void BT::ControlNode::ResetColorState(){
    setColorStatus(BT::IDLE);
    for (unsigned int i = 0; i < children_nodes_.size(); i++)
    {
        children_nodes_[i]->ResetColorState();
    }
}

void BT::ControlNode::HaltChildren(int index){
    for(unsigned i = index; i< children_nodes_.size();i++){
        if(children_nodes_[i]->getNodeType() == BT::CONTROL_NODE){
            children_nodes_[i]->ResetColorState();
        }
        else if(children_nodes_[i]->get_status() == BT::RUNNING){
            DEBUG_STDOUT("sending halt to child " << children_nodes_[j]-> get_name());
            children_nodes_[i]->Halt();
        }
        else{
             DEBUG_STDOUT("no need to halt " << children_nodes_[i]-> get_name()
                             << "status:" << children_nodes_[i]->get_status());
        }
    }
}

int BT::ControlNode::Depth(){
    int depMax = 0, dep = 0;
    for(unsigned int i=0;i<children_nodes_.size();i++){
        dep = children_nodes_[i]->Depth();
        if(dep > depMax){
            depMax = dep;
        }
    }
    return 1+depMax;
}