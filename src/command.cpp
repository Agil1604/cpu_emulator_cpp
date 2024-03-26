#include "command.h"
#include "arch.h"

CommandPush::CommandPush(Val_t val) : val_(val) {}

CommandPushr::CommandPushr(std::string reg) : reg_(reg) {}

CommandPopr::CommandPopr(std::string reg) : reg_(reg) {}

void Nothing::execute() {}

void CommandBegin::execute()
{
    is_running = true;
}

void CommandEnd::execute()
{
    is_running = false;
}

void CommandPush::execute()
{
    if (is_running)
    {
        program_stack.push(val_);
    }
}

void CommandPop::execute()
{
    if (is_running)
    {
        program_stack.pop();
    }
}

void CommandPushr::execute()
{
    if (is_running)
    {
        program_stack.push(get_register_value(reg_));
    }
}

void CommandPopr::execute()
{
    if (is_running)
    {
        set_register_value(program_stack.pop(), reg_);
    }
}

void CommandAdd::execute()
{
    if (is_running)
    {
        Val_t op1 = program_stack.pop();
        Val_t op2 = program_stack.pop();
        program_stack.push(op1 + op2);
    }
}

void CommandSub::execute()
{
    if (is_running)
    {
        Val_t op1 = program_stack.pop();
        Val_t op2 = program_stack.pop();
        program_stack.push(op2 - op1);
    }
}

void CommandMul::execute()
{
    if (is_running)
    {
        Val_t op1 = program_stack.pop();
        Val_t op2 = program_stack.pop();
        program_stack.push(op1 * op2);
    }
}

void CommandDiv::execute()
{
    if (is_running)
    {
        Val_t op1 = program_stack.pop();
        Val_t op2 = program_stack.pop();
        program_stack.push(op2 / op1);
    }
}

void CommandOut::execute()
{
    if (is_running)
    {
        std::cout << program_stack.pop() << std::endl;
    }
}

void CommandIn::execute()
{
    if (is_running)
    {
        std::string tmp;
        std::cin >> tmp;
        program_stack.push(get_value(tmp));
    }
}

Command::Command() : ptr_(nullptr) {}

Command::Command(Command &&that) : ptr_(that.ptr_)
{
    that.ptr_ = nullptr;
}

Command &Command::operator=(Command &&that)
{
    delete this->ptr_;
    ptr_ = that.ptr_;
    that.ptr_ = nullptr;

    return *this;
}

void Command::execute()
{
    ptr_->execute();
}

Command::~Command()
{
    delete ptr_;
    ptr_ = nullptr;
}
