#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include<memory>

template<typename T>
class Optimizer {
    std::unique_ptr<EvaluationNode> createPhysicalPlan(std::unique_ptr<LogicalPlanNode> &node);
};

#endif