#ifndef CONTROL_NODE_H
#define CONTROL_NODE_H
#include <vector>
#include <tree_node.h>

namespace BT
{
    class ControlNode : public TreeNode
    {
        protected:
            std::vector<TreeNode*> children_nodes_;
            std::vector<ReturnStatus> children_states_;
            unsigned int N_of_children_;
            ReturnStatus children_i_state;
        public:
            // Constructor
            ControlNode(std::string name);
            ~ControlNode();

            void AddChild(TreeNode* child);
            unsigned int GetChildrenNumber();
            std::vector<TreeNode*> GetChildren();

            void Halt();
            void ResetColorState();
            void HaltChildren(int i);
            int Depth();

            bool WriteState(ReturnStatus new_status);
    };
}
#endif