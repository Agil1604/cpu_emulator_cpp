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

typedef int32_t Val_t;
Val_t get_value(std::string str);

CommandType get_command_id(std::string &str);

void set_register_value(Val_t val, std::string reg);
Val_t get_register_value(std::string reg);
bool is_reg(std::string &str);

extern my_stack::stack<int> program_stack;
