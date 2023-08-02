#ifndef PARSER_H
#define PARSER_H
#include "../include/Scanner.h"
#include "../include/LogicalPlanNode.h"
#include <memory>


class Parser {
    public:
        std::unique_ptr<LogicalPlanNode> root;
    
        Parser(std::vector<std::pair<Dfa::State, std::string>> & tokens);
        void printParseTree();
};

class SyntaxError{};

#endif