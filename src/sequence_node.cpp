#include <sequence.h>
#include <string>

BT::SequenceNode::SequenceNode(std::string name) : ControlNode::ControlNode(name) {};

BT::SequenceNode::~SequenceNode() {};

int BT::SequenceNode::DrawType(){
    return BT::SEQUENCE;
}

BT::ReturnStatus BT::SequenceNode::Tick()
{
    //gets the number of children. The number could change if, at runtime, one edits the tree.
    N_of_children_ = children_nodes_.size();

    for(unsigned int i=0; i<N_of_children_;i++){
        if(children_nodes_[i]->getNodeType() == BT::ACTION_NODE){
            child_i_status_ = children_nodes_[i]->get_status();
            if(child_i_status_ == BT::IDLE || child_i_status_ == BT::HALTED){
                DEBUG_STDOUT(getNodeName() << "needs to tick" << children_nodes_[i]->getNodeName());
                children_nodes_[i]->tick_engine_.Tick();

                do
                {
                    /* code */
                    child_i_status_ = children_nodes_[i]->get_status();
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                } while (/* condition */ child_i_status_ != BT::RUNNING && child_i_status_ != BT::FAILURE && child_i_status_ != BT::SUCCESS);
                
            }
        }
        else
        {
            // if it's not an action:
            child_i_status_ = children_nodes_[i]->Tick();
            children_nodes_[i]->set_status(child_i_status_)
        }
        
        if(child_i_status_ != BT::SUCCESS){
            if(child_i_status_ == BT::FAILURE)
            {
                children_nodes_[i]->set_status(BT::IDLE);
            }
            DEBUG_STDOUT(getNodeName() << "is halting children fron" << (i+1));
            HaltChildren(i+1);
            set_status(child_i_status_);
            return child_i_status_;
        }
        else
        {
            /* code */
            children_nodes_[i]->set_status(BT::IDLE);
            if(i == N_of_children_ - 1)
            {
                set_status(BT::SUCCESS);
                return BT::SUCCESS;
            }
        }
    }
    return BT::EXIT;
}