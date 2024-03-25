#pragma once
#include <string>
#include <cstdint>

#include "stack.h"

enum class CommandType
{
    NOTHING,
    BEGIN,
    END,
    PUSH,
    POP,
    PUSHR,
    POPR,
    ADD,
    SUB,
    MUL,
    DIV,
    OUT,
    IN,
    JMP,
    JNE,
    JA,
    JAE,
    JB,
    JBE,
    CALL,
    RET
};

/// @brief for values in stack
typedef int32_t Val_t;
Val_t get_value(std::string str);

/// @brief gets id of command by its name
/// @param str name of command
/// @return command id
CommandType get_command_id(std::string str);


/// @brief for registers
typedef uint8_t Reg_t;


/// @brief gets id of register by its name
/// @param str name of register
/// @return register id
Reg_t get_register_id(std::string str);


void set_register_value(Val_t val, Reg_t reg);
Val_t get_register_value(Reg_t reg);

/// @brief gets name of register by its id
/// @param reg register id
/// @return name of register
std::string get_register_name(Reg_t reg);

extern my_stack::stack<int> program_stack;
