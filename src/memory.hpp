#pragma once
// By Edith Pugh on 2026-04-10, a day of no particular significance, or is it?

#include <unordered_map>
#include <vector>
#include <string>
#include <optional>

/**
 * A class that contains the memory state of the currently executing program,
 * including variables and subroutine return addresses.
 */
class Memory {
    std::unordered_map<std::string, int> num_vars;
    std::unordered_map<std::string, std::string> str_vars;
    std::vector<size_t> return_addresses;
public:
    /**
     * Wipe the memory, destroying all variables and return addresses.
     */
    void wipe(void);
    
    void set_num_var(std::string_view name, int value);
    void set_str_var(std::string_view name, std::string value);

    std::optional<int> get_num_var(std::string_view name);
    std::optional<std::string_view> get_str_var(std::string_view name);
};