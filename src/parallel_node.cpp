#include <parallel_node.h>

BT::ParallelNode::ParallelNode(std::string name, int threshold_M) : ControlNode::ControlNode(name)
{
    threshold_M_ = threshold_M;
}

BT::ParallelNode::~ParallelNode() {}

int BT::ParallelNode::DrawType()
{
    return BT::PARALLEL;
}

BT::ReturnStatus BT::ParallelNode::Tick()
{
    initNum();
    N_of_children_ = children_nodes_.size();
    for(unsigned int i=0;i < N_of_children_; i++)
    {
        DEBUG_STDOUT(getNodeName() << "ticking " << children_nodes_[i]->getNodeName());
        if(children_nodes_[i]->getNodeType() == BT::ACTION_NODE){
            // if it is action node. Reading its status
            child_i_status_ = children_nodes_[i]->get_status();
            if(child_i_status_ == BT::IDLE || child_i_status_ == BT::HALTED)
            {
                // the action node status is not running, the sequence node sends a tick to it.
                DEBUG_STDOUT(getNodeName() << "needs to tick " << children_nodes_[i]->getNodeName());
                children_nodes_[i]->tick_engine_.Tick();

                do
                {
                    /* code */
                    child_i_status_ = children_nodes_[i]->get_status();
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                } while (/* condition */ child_i_status_ != BT::RUNNING && child_i_status_ != BT::SUCCESS && child_i_status_ != BT::FAILURE);
                
            }
        }
        else
        {
            child_i_status_ = children_nodes_[i]->Tick();
        }
        if(child_i_status_ == BT::SUCCESS)
        {
            children_nodes_[i]->set_status(BT::IDLE);
            if(++success_children_num_ == threshold_M_)
            {
                initNum();
                HaltChildren(0);
                set_status(child_i_status_);
                return child_i_status_;
            }

        }
        else if(child_i_status_ == BT::FAILURE)
        {
            children_nodes_[i]->set_status(BT::IDLE);
            if(++failure_children_num_ == threshold_M_)
            {
                initNum();
                HaltChildren(0);
                set_status(child_i_status_);
                return child_i_status_;
            }
        }
        else if(child_i_status_ == BT::RUNNING){
            set_status(child_i_status_);
        }
    }
    return BT::RUNNING;
}

void BT::ParallelNode::Halt()
{
    initNum();
    BT::ControlNode::Halt();
}

unsigned int BT::ParallelNode::getThreSholdM()
{
    return threshold_M_;
}

void BT::ParallelNode::setThresholdM(unsigned int threshold_M)
{
    threshold_M_ = threshold_M;
}

void BT::ParallelNode::initNum()
{
    success_children_num_ = 0;
    failure_children_num_ = 0;
}