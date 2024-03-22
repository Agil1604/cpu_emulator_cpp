#include "arch.h"
#include "command.h"

#include <vector>

static std::vector<std::string> CMD_NAME_TO_CMD_ID = {
    "NOTHING", // CommandType::NOTHING
    "BEGIN",   // CommandType::BEGIN
    "END",     // CommandType::END
    "PUSH",    // CommandType::PUSH
    "POP",     // CommandType::POP
    "PUSHR",   // CommandType::PUSHR
    "POPR",    // CommandType::POPR
    "ADD",     // CommandType::ADD
    "SUB",     // CommandType::SUB
    "MUL",     // CommandType::MUL
    "DIV",     // CommandType::DIV
    "OUT",     // CommandType::OUT
    "IN",      // CommandType::IN
    "JMP",     // CommandType::JMP
    "JNE",     // CommandType::JNE
    "JA",      // CommandType::JA
    "JAE",     // CommandType::JAE
    "JB",      // CommandType::JB
    "JBE",     // CommandType::JBE
    "CALL",    // CommandType::CALL
    "RET"      // CommandType::RET
};

Cmd_t get_command_id(std::string str)
{
    for (size_t id = 0U; id < CMD_NAME_TO_CMD_ID.size(); ++id)
    {
        if (CMD_NAME_TO_CMD_ID[id] == str)
        {
            return id;
        }
    }
    throw std::runtime_error("parse_command_name(): unknown command name!");
}

static std::vector<std::string> REG_NAME_TO_REG_ID = {
    "AX",
    "BX",
    "CX",
    "DX",
    "EX",
    "FX",
    "PC"};

static Val_t REGISTERS[] = {0, 0, 0, 0, 0, 0, 0};

void set_register_value(Val_t val, Reg_t reg) {
    REGISTERS[reg] = val;
}

Val_t get_register_value(Reg_t reg)
{
    return REGISTERS[reg];
}

Reg_t get_register_id(std::string str)
{
    for (size_t id = 0U; id < REG_NAME_TO_REG_ID.size(); ++id)
    {
        if (REG_NAME_TO_REG_ID[id] == str)
        {
            return id;
        }
    }

    throw std::runtime_error("get_register_id(): unknown register name!");
}

std::string get_register_name(Reg_t reg)
{
    return REG_NAME_TO_REG_ID.at(reg);
}

Val_t get_value(std::string str)
{
    Val_t tmp = std::atoi(str.c_str());

    if (!(std::to_string(tmp) == str))
    {
        throw std::runtime_error("get_value(): inputted value isn't a number!");
    }
    return tmp;
}


my_stack::stack<int> program_stack;
