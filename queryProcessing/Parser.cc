#include "../include/Parser.h"

void add_cvpairs(size_t & i, std::unique_ptr<LogicalPlanNode> &node, std::vector<std::pair<Dfa::State, std::string>> & tokens) {
    while (i < tokens.size()) {
        // col:value
        if (tokens[i + 2].first == Dfa::DATE) {
            // datetime column
            node->cvpairs.push_back({tokens[i].second, tokens[i + 2].second + " " + tokens[i + 3].second});
            i += 5;
        } else if ( tokens[i + 2].first == Dfa::STRING ) {
            node->cvpairs.push_back({tokens[i].second, tokens[i + 2].second});
            i += 4;
        } else {
            break;
        }
    }
}

Parser::Parser(std::vector<std::pair<Dfa::State, std::string>> & tokens) {
    if ( tokens[0].first == Dfa::UPDATE ) {
        // update
        root = std::make_unique<LogicalPlanNode>(LogicalPlanNode::UPDATE);

        root->children.push_back(std::make_unique<LogicalPlanNode>(LogicalPlanNode::SELECTION));
        size_t i = 3;
        add_cvpairs(i, root->children[0], tokens);

        // db
        root->children[0]->children.push_back(std::make_unique<LogicalPlanNode>(LogicalPlanNode::DB));
        root->children[0]->children[0]->cvpairs.push_back({"DB", tokens[1].second});

        while ( tokens[i].first != Dfa::ID ) {
            i++;
        }
        std::cout << "to " << std::to_string(i) << std::endl;
        add_cvpairs(i, root, tokens);

    } else {
        if ( tokens[0].first == Dfa::GET ) {
            root = std::make_unique<LogicalPlanNode>(LogicalPlanNode::SELECTION);
        } else if ( tokens[0].first == Dfa::ADD ) {
            root = std::make_unique<LogicalPlanNode>(LogicalPlanNode::INSERTE);
        } else if ( tokens[0].first == Dfa::COMPLETE ) {
            root = std::make_unique<LogicalPlanNode>(LogicalPlanNode::DELETE);
        } else {
            throw SyntaxError{};
        }
            
        // DB
        if ( tokens[1].first == Dfa::ID ) {
            root->children.push_back(std::make_unique<LogicalPlanNode>(LogicalPlanNode::DB));
            root->children[0]->cvpairs.push_back({"DB", tokens[1].second});

            // col:val pairs
            size_t i = 3;
            add_cvpairs(i, root, tokens);
            

        } else {
            throw SyntaxError{};
        }
    }
}

void printNode(std::unique_ptr<LogicalPlanNode> & node) {
    for ( auto & child : node->children ) {
        printNode(child);
    }
    
    std::cout << "Type: " << node->type;
    std::cout << " Col value pairs: ";
    for ( auto pair : node->cvpairs ) {
        std::cout << pair.first << " " << pair.second << ", " << std::endl;
    }
}

void Parser::printParseTree() {
    printNode(root);
}




