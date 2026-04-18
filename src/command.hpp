#pragma once
// By Edith Pugh on 2026-04-10, Sparky's third birthday

#include "lexer/token.hpp"
#include "evalenv.hpp"

#include <string>
#include <vector>
#include <variant>
#include <optional>

namespace basic {

// a class responsible for taking lexed tokens, parsing them, and passing their
// result onto either the evalenv for indirect commands or the repl for direct
// commands
class Command {
    std::vector<lexer::Token> tokens;
public:
    /**
     * A struct that wraps a variant either containing an EvalResult::Ok or
     * EvalResult::Err
     */
    struct EvalResult {
        /**
         * The successful variant of EvalResult that contains the message that
         * is to be printed onto the screen, empty if the command does not 
         * print anything.
         */
        struct Ok { std::string out; };
        /**
         * The failed variant of EvalResult that contains the error message for
         * the syntax or runtime error.
         */
        struct Err { std::string msg; };
        std::variant<Ok, Err> result;
    }; // end struct EvalResult
    
    /**
     * Returns whether or not the command is a direct command, this is, if it
     * does *not* have a line number. 
     *
     * @return: Returns nullopt if there are no tokens in the vector.
     */
    std::optional<bool> is_direct_command(void) const;
    
    /**
     * Returns the line number of an indirect command
     *
     * @return: Returns the line number if there is one, returns nullopt if
     * Command is a direct command or if there are no tokens in the vector.
     */
    std::optional<size_t> get_line_number(void) const;
    
    /**
     * Evaluates the command within a specific environment, potentially mutating
     * it.
     *
     * @param env: A mutable reference to the EvalEnv in which the command is
     * executed
     * @return: Returns an EvalResult containing either the message to print 
     * out to the console, or an error message.
     */
    EvalResult eval(EvalEnv& env) const;
    // basic constructor for command
    Command(std::vector<lexer::Token>&& tokens)
        : tokens(std::move(tokens)) {}
}; // End Class Command

} // End namespace basic