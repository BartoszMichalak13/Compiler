#ifndef MAIN_HEADER_HPP
#define MAIN_HEADER_HPP

#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

/*
Custom parser token,
Usefull way to keep line number and string info
Contains: 
    uint64_t val;
    uint64_t line;
    std::string* str;
*/
typedef struct Parser_token
{
    uint64_t val;
    uint64_t line;
    std::string* str; // Yacc needs pointer instead of class
    std::string* T_str; 
    int T_val; //base is -1


} Parser_token;

/*
Struct that returns/keeps valueable info about comparision
Needed for creation of comparisions
Contains :
    Parser_token ptok1;
    Parser_token ptok2;
    uint64_t val;
*/
typedef struct Comparision_struct
{
    Parser_token ptok1;
    Parser_token ptok2;
    uint64_t val;

} Comparision_struct;

/*
Most of externs is in parser.ypp
*/
extern std::string ASM_CODE;
extern std::string EXPRESSION_ASM_CODE;
extern std::string CONDITION_ASM_CODE;
extern std::string COMMANDS_ASM_CODE;
extern std::string PROC_NAME;
extern int declaration_counter;
extern int line_count; // if procedury to 1 chyba
extern int mem_index;

extern int proc_index;
inline int mem_index_counter;
//if vec contains 5, that means cell 5 was initialized if not, then not
inline std::vector<int> mem_init_vec;


/*
  1.variable name
  2.varaible mem_cell
  3.variable type 
        (passed as arg) => 1
        "normal"        => 0
  4.procedure name/MAIN
  5.if was initialized
  6.size
*/
inline std::vector<\
          std::pair<\
              std::pair<\
                  std::pair<\
                      std::string,\
                      int>,\
                  std::pair<\
                      bool,\
                      std::string>>,\
              std::pair<\
                  bool,\
                  int>>> variable_vector;

//tmp var_vector, needed for procedure vector, var_name,mem_cell, size
extern std::vector<std::pair<\
                      std::pair<\
                          std::string,\
                          int>,\
                      int>> tmp_variable_vector;

/* 
1. var_name
2. mem_cell
3. size
4. proc name
5. proc beg_line

*/
inline std::vector<std::pair<\
                      std::vector<\
                          std::pair<\
                              std::pair<\
                                  std::string,\
                                  int>,\
                              int>>,\
                      std::pair<\
                          std::string,\
                          int>>> procedures_vector;

extern std::vector<std::pair<std::string, int>> COMMANDS_ASM_CODE_vector;


/*
Functions defined in operations.cpp
*/
std::string asm_division_gen( \
        int &current_lines, \
        std::string b_reg1, \
        std::string b_reg2  );
std::string asm_multiplication_gen( \
        int &current_lines, \
        std::string b_reg1, \
        std::string b_reg2  );
std::string asm_modulo_gen( \
        int &current_lines, \
        std::string b_reg1, \
        std::string b_reg2  );
/*
Functions defined in compi
*/
std::string gen_number_into_register(uint64_t var_ind, std::string reg);
std::string gen_val_to_reg(std::string name, std::string reg, std::string mode);
std::string gen_repeat_condition(int beg_line, Comparision_struct cmp_struct);
std::string gen_if_else_condition(
          int mode, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Comparision_struct cmp_struct);
std::string get_ptoken_to_reg(Parser_token ptok1, std::string reg1, std::string mode);
std::pair<std::string,std::string> get_number_for_cmp( \
          Parser_token ptok1, \
          Parser_token ptok2, \
          std::string reg1, \
          std::string reg2);
std::string incrementNumbersInString(const std::string& input, int incrementBy);

/*
Functions defined in check_functions
*/
int check_ptoken_type(Parser_token ptok1);
bool check_string(std::string ret_val);
bool check_reg(std::string reg);
bool check_var_init(int var_mem_index);
bool check_no_repeats_variable(std::string proc_name);
bool check_no_repeats_variable(std::string proc_name, std::string var_name);
int check_procedure(std::string proc_name,std::string current_proc_name);

/*
Functions defined in command_code_handler
*/
void add_to_COMMANDS_ASM_CODE_vector(std::string asm_code, int val);
std::string search_code(int code_index);
int search_code_index(int code_index);
void merge_commands(int index);

/*
Functions defined in repeat_condition_gen.cpp
*/
std::string repeat_gen_EQ_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string repeat_gen_NE_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string repeat_gen_LT_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string repeat_gen_GT_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string repeat_gen_LEQ_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string repeat_gen_GEQ_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2);



/*
Functions defined in if_else_condition_gen.cpp
*/
std::string if_else_gen_EQ_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string if_else_gen_NE_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string if_else_gen_LT_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string if_else_gen_GT_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string if_else_gen_LEQ_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2);
std::string if_else_gen_GEQ_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2);

/*
Definded "test.cpp" aka temp_file
*/
std::string calculate_jump(int alg_val, int cur_line);
void ptok_init(Parser_token &ptok, std::string* name,  uint64_t cur_line);
void ptok_init(Parser_token &ptok, uint64_t cur_line);
void ptok_init(Parser_token &ptok, std::string* name,  uint64_t cur_line, std::string* T_variable, int T_value);
void cmp_struct_init( \
          Comparision_struct &cmp_struct, \
          uint64_t value, \
          Parser_token ptoken1, \
          Parser_token ptoken2 \
          );
void add_to_vec(std::string name, int val, bool type, std::string proc_name, int size);
std::pair<int,bool> search_variable(std::string var_name, std::string proc_name);
void write_to_asm(std::string code);
void add_str_and_val_to_vector(std::vector<std::pair<std::string,int>>* val_vec, std::string name, int val);
void add_pair_to_vector(std::vector<std::pair<std::string,int>>* val_vec, std::pair<std::string,int> pair);
int search_variable_in_tmp(std::string name);
void add_to_tmp_vec(std::string name, int val, int size);
void print_var_vec();
std::string modify_variable_memory(std::string proc_name, std::vector<std::pair<std::pair<int,std::string>,int>> val);
void add_to_var_init(int var_mem_index);
int get_variable_size(std::string var_name, std::string proc_name);
int get_variable_type(std::string var_name, std::string proc_name);


/*
Defined in procedure_functions
*/
std::vector<std::pair<std::pair<std::string, int>,int>>* search_procedure(std::string proc_name);
int search_var_in_proc_vec(std::string proc_name, std::string var_name);
void add_procedure(\
          std::vector<std::pair<std::pair<std::string, int>,int>> proc_in_variables, \
          std::string name, \
          int val);
int update_procedure_beg_line(std::string proc_name, int beg_line);
int search_procedure_beg_line(std::string proc_name);

#endif