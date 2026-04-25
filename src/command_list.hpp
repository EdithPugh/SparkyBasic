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
    bool add_command(Command&& command);

    const_iterator begin(void) const { return commands.begin(); }
    const_iterator end(void) const { return commands.end(); }
};