#include "../include/Scanner.h"

const std::string alpha =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string num = "0123456789";

void Dfa::registerTransition(Dfa::State oldState, const std::string &chars, Dfa::State newState) {
    for (char c : chars) {
        transitionFunction[{oldState, c}] = newState;
    }
}

void Dfa::registerTransitionWhiteSpace(State oldState, int ch, State newState) {
    transitionFunction[{oldState, ch}] = newState;
}

void Dfa::registerTransitionComment(State oldState, State newState) {
    for (int c = 0; c < 128; ++c) {
        if ( c != 10 ) {
            transitionFunction[{oldState, c}] = newState;
        }
    }
}

Dfa::Dfa() {
    // ID (GET, ADD, COMPLETE, UPDATE, TO)
    registerTransition(START, alpha, ID);
    registerTransition(ID, alpha, ID);

    // STRING
    registerTransition(START, "`" , STRMID);
    registerTransition(STRMID, alpha + num + " ", STRMID);
    registerTransition(STRMID, "`", STRING);

    // DATE TIME
    registerTransition(START, num, NUM1);
    registerTransition(NUM1, num, NUM2);

    registerTransition(NUM2, ":", HOUR);
    registerTransition(HOUR, num, MIN);
    registerTransition(MIN, num, TIME);

    registerTransition(NUM2, num, NUM3);
    registerTransition(NUM3, num, NUM4);

    registerTransition(NUM4, "-", YEAR);
    registerTransition(YEAR, num, NUM5);
    registerTransition(NUM5, num, NUM6);

    registerTransition(NUM6, "-", MONTH);
    registerTransition(MONTH, num, NUM7);
    registerTransition(NUM7, num, DATE);

    // ()
    registerTransition(START, "(", LPAREN);
    registerTransition(START, ")", RPAREN);

    // : ,
    registerTransition(START, ":", COLON);
    registerTransition(START, ",", COMMA);

    // SPACE TAB NEWLINE
    registerTransitionWhiteSpace(START, 32, SPACE);
    registerTransitionWhiteSpace(START, 9, TAB);
    registerTransitionWhiteSpace(START, 10, NEWLINE);

}

bool Dfa::accept(State state) {
    return acceptingStates.count(state);
}

bool Dfa::failTransition(State oldState, char ch) {
    return (! transitionFunction.count({oldState, ch}));
}


Dfa::State produceIDType(std::string &lexeme) {
    if ( lexeme == "get" )
        return Dfa::GET;
    else if ( lexeme == "add" )
        return Dfa::ADD;
    else if ( lexeme == "complete" )
        return Dfa::COMPLETE;
    else if ( lexeme == "update" )
        return Dfa::UPDATE;
    else if ( lexeme == "to" )
        return Dfa::TO;
    
    return Dfa::ID;
}


std::vector<std::pair<Dfa::State, std::string>> Dfa::simplifiedMaximalMunch(const std::string &input) {
    State state = START;
    std::string munchedInput = "";
    std::vector<std::pair<Dfa::State, std::string>> ans;

    // We can't use a range-based for loop effectively here
    // since the iterator doesn't always increment.
    for (std::string::const_iterator inputPosn = input.begin();
           inputPosn != input.end();) {

        if ( ! failTransition(state, *inputPosn) ) {
          munchedInput += *inputPosn;
          state = transitionFunction[{state, *inputPosn}];

          ++inputPosn;
        }

        if ( inputPosn == input.end() || failTransition(state, *inputPosn) ) {
          if ( accept(state) ) {
            if ( state == ID ) state = produceIDType(munchedInput); 

            if ( state != SPACE && state != TAB && state != NEWLINE )
                ans.push_back({state, munchedInput});
            munchedInput = "";
            state = START;
          } else {
            std::cerr << "ERROR: not end with a valid state " << state << " for " << munchedInput << std::endl;
            throw InvalidToken{};
          }
        }
      }

      return ans;
}

void printToken(std::vector<std::pair<Dfa::State, std::string>> & tokens) {
    for ( auto pair: tokens ) {
        std::cout << "Type: " << pair.first << " Lexeme: " << pair.second << std::endl;
    }
}
