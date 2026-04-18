#pragma once
// By Edith Pugh on 2026-04-10, Sparky's third birthday

#include "lexer/token.hpp"
#include "evalenv.hpp"

#include <string>
#include <vector>
#include <variant>

namespace basic {

// a class responsible for taking lexed tokens, parsing them, and passing their
// result onto either the evalenv for indirect commands or the repl for direct
// commands
class Command {
    std::vector<lexer::Token> tokens;
public:
    struct EvalResult {
        struct Ok { std::string out; };
        struct Err { std::string msg; };
        std::variant<Ok, Err> result;
    }; // end struct EvalResult
    // a direct command is immediately executed by the interpreter, whereas
    // an indirect command is saved and executed after the next RUN command.
    bool is_direct_command(void) const;
    // returns the line number if Command is an indirect command
    // PANICS: if Command is in fact a direct command
    unsigned int get_line_number(void) const;
    // executes command on env, may mutate env
    EvalResult eval(EvalEnv& env) const;
    // basic constructor for command
    Command(std::vector<lexer::Token>&& tokens)
        : tokens(std::move(tokens)) {}
}; // End Class Command

} // End namespace basic