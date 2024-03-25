#pragma once
#include "arch.h"

class Command
{
public:
    Command();

    ~Command();

    Command(const Command &) = delete;
    Command(Command &&);

    Command &operator=(const Command &) = delete;
    Command &operator=(Command &&);

    virtual void execute();

private:
    CommandType type_;

    Command *ptr_;
};

class CommandBegin : public Command
{
public:
    CommandBegin() = default;

    void execute() override;
};

class CommandEnd : public Command
{
public:
    CommandEnd() = default;

    void execute() override;
};

class CommandPush : public Command
{
public:
    CommandPush(Val_t val);

    void execute() override;

private:
    Val_t val_;
};

class CommandPop : public Command
{
public:
    CommandPop() = default;

    void execute() override;
};

class CommandPushr : public Command
{
public:
    CommandPushr(Reg_t reg);

    void execute() override;

private:
    Reg_t reg_;
};

class CommandPopr : public Command
{
public:
    CommandPopr(Reg_t reg);

    void execute() override;

private:
    Reg_t reg_;
};

class CommandAdd : public Command
{
public:
    CommandAdd() = default;

    void execute() override;
};

class CommandSub : public Command
{
public:
    CommandSub() = default;

    void execute() override;
};

class CommandMul : public Command
{
public:
    CommandMul() = default;

    void execute() override;
};

class CommandDiv : public Command
{
public:
    CommandDiv() = default;

    void execute() override;
};

class CommandOut : public Command
{
public:
    CommandOut() = default;

    void execute() override;
};

class CommandIn : public Command
{
public:
    CommandIn() = default;

    void execute() override;
};
