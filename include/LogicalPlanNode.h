#ifndef LOGICALPLANNODE_H
#define LOGICALPLANNODE_H
#include "../include/Scanner.h"
#include <memory>

class LogicalPlanNode {
    public:
        enum Type {
            SELECTION,
            INSERTE,
            DELETE,
            UPDATE,
            DB
        };

        Type type;
        std::vector<std::pair<std::string, std::string>> cvpairs;
        std::vector<std::unique_ptr<LogicalPlanNode>> children;

        LogicalPlanNode(Type type);

        void semantic_checking();
};


#endif