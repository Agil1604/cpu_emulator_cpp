#include "arch.h"
#include "command.h"

#include <cstdio>
#include <stdexcept>

//----------------------
// Command construction
//----------------------

CommandPush::CommandPush(Val_t val) : val_(val)
{
}

CommandPushr::CommandPushr(Reg_t reg) : reg_(reg)
{
}

CommandPopr::CommandPopr(Reg_t reg) : reg_(reg)
{
}

//-------------------
// Command execution
//-------------------

void CommandBegin::execute() const
{
    printf("BEGIN\n");
}

void CommandEnd::execute() const
{
    printf("END\n");
}

void CommandPush::execute() const
{
    program_stack.push(val_);
    printf("PUSH %d\n", val_);
}

void CommandPop::execute() const
{
    program_stack.pop();
    printf("POP\n");
}

void CommandPushr::execute() const
{
    printf("PUSHR %s\n", get_register_name(reg_).c_str());
}

void CommandPopr::execute() const
{
    printf("POPR %s\n", get_register_name(reg_).c_str());
}

void CommandAdd::execute() const
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op1 + op2);
    printf("ADD\n");
}

void CommandSub::execute() const
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op1 - op2);
    printf("SUB\n");
}

void CommandMul::execute() const
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op1 * op2);
    printf("MUL\n");
}

void CommandDiv::execute() const
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op1 / op2);
    printf("DIV\n");
}

void CommandOut::execute() const
{
    std::cout << program_stack.pop() << std::endl;
    printf("Out\n");
}

void CommandIn::execute() const
{
    Val_t tmp;
    std::cin >> tmp;
    program_stack.push(tmp);
    printf("IN\n");
}

//--------------------------
// Polymorphic command type
//--------------------------

Command::Command() : type_(CommandType::NOTHING),
                     ptr_(nullptr)
{
}

Command::Command(CommandBegin *cmd) : type_(CommandType::BEGIN),
                                      ptr_(cmd)
{
}

Command::Command(CommandEnd *cmd) : type_(CommandType::END),
                                    ptr_(cmd)
{
}

Command::Command(CommandPush *cmd) : type_(CommandType::PUSH),
                                     ptr_(cmd)
{
}

Command::Command(CommandPop *cmd) : type_(CommandType::POP),
                                    ptr_(cmd)
{
}

Command::Command(CommandPushr *cmd) : type_(CommandType::PUSHR),
                                      ptr_(cmd)
{
}

Command::Command(CommandPopr *cmd) : type_(CommandType::POPR),
                                     ptr_(cmd)
{
}

Command::Command(CommandAdd *cmd) : type_(CommandType::ADD),
                                     ptr_(cmd)
{
}

Command::Command(CommandSub *cmd) : type_(CommandType::SUB),
                                     ptr_(cmd)
{
}

Command::Command(CommandMul *cmd) : type_(CommandType::MUL),
                                     ptr_(cmd)
{
}

Command::Command(CommandDiv *cmd) : type_(CommandType::DIV),
                                     ptr_(cmd)
{
}

Command::Command(CommandOut *cmd) : type_(CommandType::OUT),
                                     ptr_(cmd)
{
}

Command::Command(CommandIn *cmd) : type_(CommandType::IN),
                                     ptr_(cmd)
{
}

Command::Command(Command &&that) : type_(that.type_),
                                   ptr_(that.ptr_)
{
    that.type_ = CommandType::NOTHING;
    that.ptr_ = nullptr;
}

Command &Command::operator=(Command &&that)
{
    this->release();

    type_ = that.type_;
    ptr_ = that.ptr_;

    that.type_ = CommandType::NOTHING;
    that.ptr_ = nullptr;

    return *this;
}

void Command::execute() const
{
    switch (type_)
    {
    case CommandType::BEGIN:
    {
        CommandBegin *ptr = static_cast<CommandBegin *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::END:
    {
        CommandEnd *ptr = static_cast<CommandEnd *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::PUSH:
    {
        CommandPush *ptr = static_cast<CommandPush *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::POP:
    {
        CommandPop *ptr = static_cast<CommandPop *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::PUSHR:
    {
        CommandPushr *ptr = static_cast<CommandPushr *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::POPR:
    {
        CommandPopr *ptr = static_cast<CommandPopr *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::ADD:
    {
        CommandAdd *ptr = static_cast<CommandAdd *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::SUB:
    {
        CommandSub *ptr = static_cast<CommandSub *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::MUL:
    {
        CommandMul *ptr = static_cast<CommandMul *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::DIV:
    {
        CommandDiv *ptr = static_cast<CommandDiv *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::OUT:
    {
        CommandOut *ptr = static_cast<CommandOut *>(ptr_);
        ptr->execute();
        break;
    }
    case CommandType::IN:
    {
        CommandIn *ptr = static_cast<CommandIn *>(ptr_);
        ptr->execute();
        break;
    }
    default:
    {
        throw std::runtime_error("Command::execute(): invalid Command type");
    }
    }
}

void Command::release()
{
    if (type_ == CommandType::NOTHING)
    {
        return;
    }

    switch (type_)
    {
    case CommandType::BEGIN:
    {
        CommandBegin *ptr = static_cast<CommandBegin *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::END:
    {
        CommandEnd *ptr = static_cast<CommandEnd *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::PUSH:
    {
        CommandPush *ptr = static_cast<CommandPush *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::POP:
    {
        CommandPop *ptr = static_cast<CommandPop *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::PUSHR:
    {
        CommandPushr *ptr = static_cast<CommandPushr *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::POPR:
    {
        CommandPopr *ptr = static_cast<CommandPopr *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::ADD:
    {
        CommandAdd *ptr = static_cast<CommandAdd *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::SUB:
    {
        CommandSub *ptr = static_cast<CommandSub *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::MUL:
    {
        CommandMul *ptr = static_cast<CommandMul *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::DIV:
    {
        CommandDiv *ptr = static_cast<CommandDiv *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::OUT:
    {
        CommandOut *ptr = static_cast<CommandOut *>(ptr_);
        delete ptr;
        break;
    }
    case CommandType::IN:
    {
        CommandIn *ptr = static_cast<CommandIn *>(ptr_);
        delete ptr;
        break;
    }
    default:
    {
        // NOTE: from C++11 destructors are ‘noexcept’ by default
        // throw std::runtime_error("Command::~Command(): invalid Command type");
    }
    }

    type_ = CommandType::NOTHING;
    ptr_ = nullptr;
}

Command::~Command()
{
    release();
}
