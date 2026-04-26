// By Edith Pugh on 2026-04-25

#include "command_list.hpp"

auto CommandList::add_command(Command&& command) -> bool {
    std::optional<size_t> line_num = command.get_line_num();
    if (!line_num) {
        return false;
    }

    for (auto iter = commands.begin(); iter != commands.end(); iter++) {
        std::optional<size_t> cur_line_num = iter->get_line_num();
        // cur_line_num should be guaranteed to be indirect, since this method
        // checks. Otherwise, uh oh!
        assert(cur_line_num);
        if (*cur_line_num > *line_num) {
            commands.insert(iter, std::move(command));
            return true;
        }
    }
    commands.push_back(std::move(command));
    return true;
}