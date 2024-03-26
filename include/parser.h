#pragma once
#include "arch.h"
#include "command.h"

#include <fstream>
#include <regex>

#define MAX_LINE_SIZE 120U

class Parser
{
public:
    Parser() = delete;
    explicit Parser(const char *filename);

    ~Parser() = default;

    Parser(const Parser &) = delete;
    Parser(Parser &&) = default;

    Parser &operator=(const Parser &) = delete;
    Parser &operator=(Parser &&) = default;

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

    std::vector<Command *> parse_command_sequence();

    std::ifstream file_;
    char line_[MAX_LINE_SIZE];
    const char *pos_;
    const char *end_;
    // bool is_running = false;
};
