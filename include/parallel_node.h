#ifndef PARALLEL_NODE_H
#define PARALLEL_NODE_H

#include <control_node.h>

namespace BT
{
    class ParallelNode : public ControlNode
    {
        public:
            ParallelNode(std::string name, int threshold_M);
            ~ParallelNode();
            int DrawType();
            BT::ReturnStatus Tick();
            void Halt();

            unsigned int getThreSholdM();
            void setThresholdM(unsigned int threshold_M);
            
        private:
            unsigned int threshold_M_;
            unsigned int success_children_num_;
            unsigned int failure_children_num_;
            void initNum();
    };
}
#endif