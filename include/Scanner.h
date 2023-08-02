#ifndef SCANNER_H
#define SCANNER_H

#include <unordered_set>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

class Dfa {
  public:
    enum State {
        START,
        ID,
        LPAREN,
        RPAREN,
        COLON,
        COMMA,
        SPACE,
        TAB,
        NEWLINE,
        STRING,
        GET,
        ADD,
        COMPLETE,
        UPDATE,
        STRMID,
        TO,
        NUM1,
        NUM2,
        NUM3,
        NUM4, YEAR, NUM5, MONTH, NUM6, NUM7, HOUR, MIN, 
        DATE, 
        TIME
    };

    std::unordered_set<State> acceptingStates = {
        ID, LPAREN, RPAREN, COMMA, SPACE, TAB, NEWLINE, GET, ADD,
        COMPLETE, UPDATE, TO, DATE, TIME, COLON, STRING
    };

    std::map<std::pair<State, char>, State> transitionFunction;

    void registerTransition(State oldState, const std::string &chars, State newState);
    void registerTransitionWhiteSpace(State oldState, int ch, State newState);
    void registerTransitionComment(State oldState, State newState);
    bool accept(State state);
    bool failTransition(State oldState, char ch);

    Dfa();

    std::vector<std::pair<Dfa::State, std::string>> simplifiedMaximalMunch(const std::string &input);
    
};

void printToken(std::vector<std::pair<Dfa::State, std::string>> & tokens);


class InvalidToken {};

#endif