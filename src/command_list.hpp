#pragma once
// By Edith Pugh on 2026-04-25

#include "command.hpp"

#include <list>

class CommandList {
    std::list<Command> commands;
public:
    using const_iterator = typename std::list<Command>::const_iterator;

    /**
     * Add a command to the internal list, sorted by its line number.
     */
    auto add_command(Command&& command) -> bool;

    auto begin(void) -> const_iterator const { return commands.begin(); }
    auto end(void) -> const_iterator const { return commands.end(); }
};