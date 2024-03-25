#include "command.h"
#include "arch.h"

CommandPush::CommandPush(Val_t val) : val_(val) {}

CommandPushr::CommandPushr(std::string reg) : reg_(reg) {}

CommandPopr::CommandPopr(std::string reg) : reg_(reg) {}

void CommandBegin::execute()
{
    std::cout << "BEGIN" << std::endl;
}

void CommandEnd::execute()
{
    std::cout << "END" << std::endl;
}

void CommandPush::execute()
{
    program_stack.push(val_);
}

void CommandPop::execute()
{
    program_stack.pop();
}

void CommandPushr::execute()
{
    program_stack.push(get_register_value(reg_));
}

void CommandPopr::execute()
{
    set_register_value(program_stack.pop(), reg_);
}

void CommandAdd::execute()
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op1 + op2);
}

void CommandSub::execute()
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op2 - op1);
}

void CommandMul::execute()
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op1 * op2);
}

void CommandDiv::execute()
{
    Val_t op1 = program_stack.pop();
    Val_t op2 = program_stack.pop();
    program_stack.push(op2 / op1);
}

void CommandOut::execute()
{
    std::cout << program_stack.pop() << std::endl;
}

void CommandIn::execute()
{
    Val_t tmp;
    std::cin >> tmp;
    program_stack.push(tmp);
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
