#ifndef EvaluationPlanNode_H
#define EvaluationPlanNode_H
#include "../include/LogicalPlanNode.h"
#include <memory>

template<typename T>
class EvaluationPlanNode {
        std::vector<std::unique_ptr<EvalueationPlanNode>> input;

    public:
        virtual void open() = 0;
        virtual std::tuple<T> getNext() = 0;
        virtual void close() = 0;
};


#endif