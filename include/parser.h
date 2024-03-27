#pragma once
#include "arch.h"
#include "command.h"

#include <fstream>
#include <regex>
#include <string>

#define MAX_LINE_SIZE 120U

class Parser
{
public:
    Parser() = delete;
    explicit Parser(std::string filename);

    ~Parser() = default;

    Parser(const Parser &) = delete;
    Parser(Parser &&) = default;

    Parser &operator=(const Parser &) = delete;
    Parser &operator=(Parser &&) = default;

    /// @brief функция, которая запускает отпарсенную программу
    void run();

private:
    void read_line_from_file();

    bool parse_pattern(const std::regex &regexp);
    bool parse_pattern(const std::regex &regexp, std::string &ret);

    bool parse_space_sequence();
    bool parse_newline_sequence();

    CommandType parse_command_name();
    std::string parse_register_name();
    Val_t parse_integral_value();
    Command *parse_command_line();

    void parse_command_sequence();

    std::vector<Command *> commands = {}; // вектор получившихся команд
    bool is_parsed = false;               // благодаря этой переменной можно делать сколько угодно раз run()

    std::ifstream file_;       // файл с программой
    char line_[MAX_LINE_SIZE]; // текущая линия
    const char *pos_;          // текущая позиция в строке
    const char *end_;          // конец строки
};
