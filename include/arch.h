#pragma once
#include <cstdint>
#include <string>

#include "stack.h"

//----------
// Values
//----------

typedef int32_t Val_t; // тип для красоты

/// @brief превращает строку в число (или выкидывает ошибку, если не число)
Val_t get_value(std::string str);

//----------
// Commands
//----------

/// @brief все возможные команды
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

/// @brief находит id команды по названию (иначе говорит, что это метка и добавляет ее в список меток)
CommandType get_command_id(std::string &str);

//----------
// Registers
//----------

/// @brief устанавливает новое значение в регистре
void set_register_value(Val_t val, std::string reg);

/// @brief получает значение из регистра
Val_t get_register_value(std::string reg);

/// @brief проверяет является ли строка названием регистра
bool is_reg(std::string &str);

//--------
// Labels
//--------

/// @brief получает номер метки в мапе
int get_number_of_label(std::string &name);

/// @brief добавляет новую метку и номер ее команды в список
void add_label(std::string &name, int &number);

//----------
// Other
//----------

extern my_stack::stack<int> program_stack; // стек, используемый программой

extern bool is_running; // нужно для разделения функций от области между BEGIN и END

extern int number_of_command; // номер текущей команды в процессе парсинга (точнее непустой строки в файле)
