#include "arch.h"
#include "command.h"

#include <map>
#include <vector>

//----------
// Commands
//----------

/// @brief связь между id команд и их названиями
const std::map<std::string, CommandType> CMD = {
    {"NOTHING", CommandType::NOTHING},
    {"BEGIN", CommandType::BEGIN},
    {"END", CommandType::END},
    {"PUSH", CommandType::PUSH},
    {"POP", CommandType::POP},
    {"PUSHR", CommandType::PUSHR},
    {"POPR", CommandType::POPR},
    {"ADD", CommandType::ADD},
    {"SUB", CommandType::SUB},
    {"MUL", CommandType::MUL},
    {"DIV", CommandType::DIV},
    {"OUT", CommandType::OUT},
    {"IN", CommandType::IN},
    {"JMP", CommandType::JMP},
    {"JNE", CommandType::JNE},
    {"JA", CommandType::JA},
    {"JAE", CommandType::JAE},
    {"JB", CommandType::JB},
    {"JBE", CommandType::JBE},
    {"CALL", CommandType::CALL},
    {"RET", CommandType::RET},
};

CommandType get_command_id(std::string &str)
{
    for (auto id = CMD.begin(); id != CMD.end(); ++id)
    {
        if (id->first == str)
        {
            return id->second;
        }
    }

    add_label(str, number_of_command);
    return CommandType::NOTHING;
}

//----------
// Registers
//----------

/// @brief хранимые в регистрах значения
std::map<std::string, Val_t> REG = {
    {"AX", 0},
    {"BX", 0},
    {"CX", 0},
    {"DX", 0},
    {"EX", 0},
    {"FX", 0},
    {"PC", 0}};

void set_register_value(Val_t val, std::string reg)
{
    REG[reg] = val;
}

Val_t get_register_value(std::string reg)
{
    return REG[reg];
}

bool is_reg(std::string &str)
{
    for (auto id = REG.begin(); id != REG.end(); ++id)
    {
        if (id->first == str)
        {
            return true;
        }
    }
    return false;
}

//-------
// Labels
//-------

/// @brief мапа всех хранимых меток
std::map<std::string, int> labels = {};

void add_label(std::string &name, int &number)
{
    labels[name] = number;
}

int get_number_of_label(std::string &name)
{
    for (auto id = labels.begin(); id != labels.end(); ++id)
    {
        if (id->first == name)
        {
            return id->second;
        }
    }
    throw std::runtime_error("NO such label!");
}

//-------
// Other
//-------

Val_t get_value(std::string str)
{
    Val_t tmp = std::atoi(str.c_str());

    if (!(std::to_string(tmp) == str))
    {
        throw std::runtime_error("get_value(): inputted value isn't an integer!");
    }
    return tmp;
}

my_stack::stack<int> program_stack;

bool is_running = false;

int number_of_command = 0;
