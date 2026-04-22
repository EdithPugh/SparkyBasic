#pragma once
// By Edith Pugh on 2026-04-10, a day of no particular significance, or is it?

#include "lexer/token.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <map>

/**
 * A class that contains the state of the currently executing program,
 * including variables and subroutine return addresses. Ideally, it should act
 * as a state machine that can execute a program without any outside help
 * outside a const reference to a map of vectors containing the current
 * program. Advanced through the "do_cycle" command which may return output
 * to be printed to the console, or an error. Does not store its own commands 
 * nor does it store a reference to them, so a reference to the commands must be
 * passed with every step.
 */
class Interpreter {
    std::unordered_map<std::string, int> num_vars;
    std::unordered_map<std::string, std::string> str_vars;
    std::vector<size_t> return_addresses;

    size_t current_line;
public:
    struct Result {
        struct Ok {
            std::string out;
        };
        struct Err {
            std::string err;
            size_t line;
        };
        std::variant<Ok, Err> result;
    };

    /**
     * Wipe the memory, destroying all variables and return addresses. This
     * should be called when the program is ran with the RUN command, in 
     * accordance to the following snippet:
     *
     * > 10 PRINT I
     * 0
     * > I = 5
     * > PRINT I
     * 5
     * RUN
     * 0
     */
    void wipe(void);
    
    void set_num_var(std::string_view name, int value);
    void set_str_var(std::string_view name, std::string value);

    std::optional<int> get_num_var(std::string_view name);
    std::optional<std::string_view> get_str_var(std::string_view name);

    /**
     * Execute a direct command within the Interpreter's current state.
     */
    Result exec_direct_command(std::vector<lexer::Token> cmd);
    
    /**
     * Execute the Interpreter's current state with the following commands. This
     * allows for the program's commands to be changed mid-execution, if
     * necessary.
     */
    Result do_cycle(const std::map<size_t, std::string>& cmds);
};