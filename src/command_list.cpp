// By Edith Pugh on 2026-04-25

#include "command_list.hpp"

bool CommandList::add_command(Command&& command) {
    std::optional<size_t> line_num = command.get_line_num();
    if (!line_num) {
        return false;
    }

    for (auto iter = commands.begin(); iter != commands.end(); iter++) {
        std::optional<size_t> cur_line_num = iter->get_line_num();
        if (*cur_line_num > *line_num) {
            commands.insert(iter, command);
            return true;
        }
    }
    commands.push_back(command);
    return true;
}