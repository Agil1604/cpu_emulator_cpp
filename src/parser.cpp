#include "parser.h"
#include "arch.h"

Parser::Parser(const char *filename) : file_(std::ifstream(filename, std::ios::in))
{
    if (!file_.good())
    {
        std::cout << "wrong filename\n";
        exit(EXIT_FAILURE);
    }
    // Initialize the first line:
    read_line_from_file();
}

void Parser::read_line_from_file()
{
    file_.getline(line_, MAX_LINE_SIZE);

    if (!(file_.good() || file_.eof()))
    {
        std::cout << "something is wrong\n";
        exit(EXIT_FAILURE);
    }

    pos_ = line_;
    end_ = line_ + std::strlen(line_);
}

bool Parser::parse_pattern(std::regex regexp)
{
    std::cmatch match_result{};
    bool match_status = std::regex_search(
        pos_, end_,                              // The iterators limiting the matched sequence
        match_result,                            // Match result
        regexp,                                  // Regular expression specifying the pattern
        std::regex_constants::match_continuous); // Start matching from the beginning

    // Move the iterator on success:
    if (match_status)
    {
        pos_ = match_result[0].second;
    }

    return match_status;
}

bool Parser::parse_pattern(std::regex regexp, std::string &ret)
{
    std::cmatch match_result{};
    bool match_status = std::regex_search(
        pos_, end_,                              // The iterators limiting the matched sequence
        match_result,                            // Match result
        regexp,                                  // Regular expression specifying the pattern
        std::regex_constants::match_continuous); // Start matching from the beginning

    // Move the iterator on success:
    if (match_status)
    {
        pos_ = match_result[0].second;

        ret = std::string(match_result[0].first, match_result[0].second);
    }

    return match_status;
}

bool Parser::parse_space_sequence()
{
    static const std::regex pattern{"[ \t]+"};

    return parse_pattern(pattern);
}

bool Parser::parse_newline_sequence()
{
    bool success = (pos_ == end_);

    while (pos_ == end_ && !file_.eof())
    {
        read_line_from_file();
    }

    return success;
}

CommandType Parser::parse_command_name()
{
    static const std::regex pattern{"[a-zA-Z]+"};

    // Skip leading whitespaces (may be none):
    parse_space_sequence();

    // Perform parsing:
    std::string cmd_name;
    bool success = parse_pattern(pattern, cmd_name);
    if (!success)
    {
        throw std::runtime_error("Unable to parse command name!\n");
    }

    // Throws an exception:
    return get_command_id(cmd_name);
}

std::string Parser::parse_register_name()
{
    static const std::regex pattern{"[a-zA-Z]+"};

    // Skip leading whitespaces:
    bool success = parse_space_sequence();
    if (!success)
    {
        throw std::runtime_error("Expected a space sequence before command name!\n");
    }

    // Perform parsing:
    std::string reg_name;
    success = parse_pattern(pattern, reg_name);
    if (!success || !is_reg(reg_name))
    {
        throw std::runtime_error("Expected a register name!\n");
    }

    return reg_name;
}

Val_t Parser::parse_integral_value()
{
    static const std::regex pattern{"(\\+|-)?(0|[1-9][0-9]*)"};

    // Skip leading whitespaces:
    bool success = parse_space_sequence();
    if (!success)
    {
        throw std::runtime_error("Expected a space sequence before integral value!\n");
    }

    // Perform parsing:
    std::string val_str;
    success = parse_pattern(pattern, val_str);
    if (!success)
    {
        throw std::runtime_error("Expected an integral value!\n");
    }

    return get_value(val_str);
}

Command *Parser::parse_command_line()
{
    CommandType cmd = parse_command_name();

    Command *to_return{};
    switch (cmd)
    {
    case CommandType::BEGIN:
    {
        to_return = new CommandBegin();
        break;
    }
    case CommandType::END:
    {
        to_return = new CommandEnd();
        break;
    }
    case CommandType::PUSH:
    {
        Val_t val = parse_integral_value();

        to_return = new CommandPush(val);
        break;
    }
    case CommandType::POP:
    {
        to_return = new CommandPop();
        break;
    }
    case CommandType::PUSHR:
    {
        std::string reg = parse_register_name();

        to_return = new CommandPushr(reg);
        break;
    }
    case CommandType::POPR:
    {
        std::string reg = parse_register_name();

        to_return = new CommandPopr(reg);
        break;
    }
    case CommandType::ADD:
    {
        to_return = new CommandAdd();
        break;
    }
    case CommandType::SUB:
    {
        to_return = new CommandSub();
        break;
    }
    case CommandType::MUL:
    {
        to_return = new CommandMul();
        break;
    }
    case CommandType::DIV:
    {
        to_return = new CommandDiv();
        break;
    }
    case CommandType::IN:
    {
        to_return = new CommandIn();
        break;
    }
    case CommandType::OUT:
    {
        to_return = new CommandOut();
        break;
    }
    default:
    {
        throw std::runtime_error("Parser::parse_command_line(): invalid command id");
    }
    }

    parse_newline_sequence();

    return to_return;
}

std::vector<Command *> Parser::parse_command_sequence()
{
    std::vector<Command *> commands{};

    while (!file_.eof())
    {
        commands.push_back(parse_command_line());
    }
    return commands;
}
