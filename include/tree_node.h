#ifndef BEHAVIORTREE_CORE_TREE_NODE_H
#define BEHAVIORTREE_CORE_TREE_NODE_H

#ifndef _COLORS_
#define _COLORS_

//FOREGROUND
#define RST "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif

#ifndef DEBUG
#define DEBUG_STDOUT(str) do { std:cout << str << std:endl; } while(false)

#else
#define DEBUG_STDOUT(str)
#endif

#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include <tick_engine.h>
#include <exceptions.h>

namespace BT
{
    // Enumerates the possible types of a node
    enum NodeType {CONTROL_NODE, CONDITION_NODE, ACTION_NODE};
    // enum NodeType {COMPOSITE_NODE, TASK_NODE, DECORATOR_NODE, SERVICE_NODE, ROOT_NODE};
    // Only Composite nodes can be attached to the Root node of a Behavior Tree. 
    
    enum DrawNodeType {SELECTOR, SEQUENCE, PARALLEL, SELECTORSTAR, SEQUENCESTAR, ACTION, CONDITION, DECORATOR };
    // status:
    //        Running
    //        Success
    enum ReturnStatus {RUNNING, SUCCESS, FAILURE, IDLE, HALTED, EXIT};
    enum FailurePolicy {FAIL_ON_ONE, FAIL_ON_ALL};
    enum ResetPolity   {ON_SUCCESS_OR_FAILURE,ON_SUCCESS, ON_FAILURE};
    enum SuccessPolicy {SUCCEED_ON_ONE, SUCCEED_ON_ALL};

    class TreeNode
    {
        private:
            // node name
            std::string name_;
        protected:
            bool is_state_updated_;
            ReturnStatus status_;
            ReturnStatus color_status_;

            std::mutex state_mutex_;
            std::mutex color_state_mutex_;
            std::condition_variable state_condition_variable_;

            NodeType type_;
            float x_shift_, x_pose_;
        public:
            std::thread thread_;
            // Node semaphore to simulate the tick
            TickEngine tick_engine_;
        // Constructor and the distructor
        TreeNode( std::string name );
        ~TreeNode();
        // The method that is going to be executed when the node receive a tick
        virtual BT::ReturnStatus Tick() = 0;
        // interrupt the execution
        virtual void Halt() = 0;

        void setNodeState(ReturnStatus new_state);

        void setColorStatus(ReturnStatus new_color_status);

        ReturnStatus readState();
        ReturnStatus get_color_status();

        virtual int DrawType() = 0; 
        virtual int ResetColorState() = 0;
        virtual int Depth() = 0;
        bool is_halted();

        void set_x_shift(float new_x_shift);
        float get_x_shift();

        void set_x_pose(float new_x_pose);
        float get_x_pose();

        void setNodeName(std::string new_node_name);
        std::string getNodeName();

        NodeType getNodeType();
        ReturnStatus get_status();
        void set_status(ReturnStatus new_status);

    } 
}