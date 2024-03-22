#pragma once
#include <cstddef>
#include <string>
#include <cstdint>

#include "stack.h"

/// @brief for commands
typedef uint8_t Cmd_t;

/// @brief gets id of command by its name
/// @param str name of command
/// @return command id
Cmd_t get_command_id(std::string str);


/// @brief for registers
typedef uint8_t Reg_t;


/// @brief gets id of register by its name
/// @param str name of register
/// @return register id
Reg_t get_register_id(std::string str);

/// @brief gets name of register by its id
/// @param reg register id
/// @return name of register
std::string get_register_name(Reg_t reg);

/// @brief for values in stack
typedef int32_t Val_t;

Val_t get_value(std::string str);


extern my_stack::stack<int> program_stack;
