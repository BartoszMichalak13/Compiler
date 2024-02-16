#include "main_header.hpp"


/*
Checks if string is without error
if yes returns 1 if not returns 0
*/
bool check_string(std::string ret_val) {
  //if we find "ERROR" somewhere return it
  if (ret_val.find("ERROR") != std::string::npos) { return 0; } //error
  else { return 1; }  //it's fine
} 

/* 
Checks if register is a,b,.. or h
If yes returns 0 
else returns 1
*/
bool check_reg(std::string reg) {
  if (  reg != "a" &&
        reg != "b" &&
        reg != "c" && 
        reg != "d" && 
        reg != "e" && 
        reg != "f" && 
        reg != "g" &&
        reg != "h"      ) { return 1; }
  else                    { return 0; }
}

/*
Checks ptoken type, 

return 3 if table of index var
returns 2 if table of index num
return 1 if value
returns 0 if identifier
*/
int check_ptoken_type(Parser_token ptok1) {
  if ( ptok1.T_str != nullptr )   { return 3; }       // table[var]
  else if ( ptok1.T_val != -1 )   { return 2; }       // table[num]
  else if (ptok1.str == nullptr)  { return 1; }       // num
  else                            { return 0; }       // var
} 

/*
Checks if variable was initialized
returns 1 if not initilized
returns 0 if initialized
*/
bool check_var_init(int var_mem_index) {
  for (long unsigned int i = 0; i < mem_init_vec.size(); i++) {
    if (mem_init_vec.at(i) == var_mem_index) {
      return 0;
    }
  }
  return 1;
}

/*
Checks if there are no repeats in procedure/main
returns 1 if an error
else 0
*/
bool check_no_repeats_variable(std::string proc_name) {

  for (long unsigned int i = 0; i < variable_vector.size(); i++) {

    if (variable_vector.at(i).first.second.second == proc_name) {

      std::string var_name = variable_vector.at(i).first.first.first;

      for (long unsigned int j = i; j < variable_vector.size(); j++) {

        if (variable_vector.at(i).first.second.second == proc_name) {

          if (var_name == variable_vector.at(j).first.first.first) {
            //error, 2 or more variables of same name
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

/*
Checks if there are no repeats in procedure/main
returns 1 if an error
else 0
*/
bool check_no_repeats_variable(std::string proc_name, std::string var_name) {

  for (long unsigned int i = 0; i < variable_vector.size(); i++) {

    if (variable_vector.at(i).first.second.second == proc_name) {


      if( var_name == variable_vector.at(i).first.first.first) {
        return 1;
      }

      
    }
  }
  return 0;
}
/*
Checks if procedure exists before call
returns 1 if no such a function before
returns 2 if recursive call
else 0
*/
int check_procedure(std::string proc_name, std::string current_proc_name) {

  if (proc_name == current_proc_name) {
    return 2;
  }
  for (long unsigned int i = 0; i < procedures_vector.size(); i++) {

    if (procedures_vector.at(i).second.first == proc_name) {
      return 0;
    }
  }
  //no such procedure
  return 1;
}