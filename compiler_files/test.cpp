#include "main_header.hpp"



/*
Calculates to what address jump to based on alg_val and current line
Input: int <alg_val>, int <cur_line>
Output: std::string(sum of input + "\n")
*/
std::string calculate_jump(int alg_val, int cur_line) {
  int jump_val = alg_val + cur_line;
  std::string ret_val = std::to_string(jump_val);
  ret_val += "\n";
  return ret_val;
}


/*
Initializes ptoken with name and current #line
Input: Parser_token &<ptok>, std::string <name>,  uint64_t <cur_line>
*/
void ptok_init(Parser_token &ptok, std::string* name,  uint64_t cur_line) {
  ptok.val = 0;
  ptok.str = name;
  ptok.line = cur_line;
}
/*
Initializes ptoken with name and current #line
Input: Parser_token &<ptok>, std::string <name>, uint64_t <cur_line>, std::string <T_variable>, uint64_t <T_value>
*/
void ptok_init(Parser_token &ptok, std::string* name,  uint64_t cur_line, std::string* T_variable, int T_value) {
  ptok.val = 0;
  ptok.str = name;
  ptok.line = cur_line;
  ptok.T_str = T_variable; 
  ptok.T_val = T_value; 
}
/*
Initializes ptoken with current #line
Input: Parser_token &<ptok>, uint64_t <cur_line>
*/
void ptok_init(Parser_token &ptok, uint64_t cur_line) {
  ptok.val = 0;
  ptok.str = nullptr;
  ptok.line = cur_line;
}

/*
Initializes Comparision struct with current value (type of comparision from 1 to 6)
and ptokens needed to calculate numbers/get variables into comparision
Input: Comparision_struct &cmp_struct, \
          uint64_t value, \
          Parser_token ptoken1, \
          Parser_token ptoken2 
*/
void cmp_struct_init( \
          Comparision_struct &cmp_struct, \
          uint64_t value, \
          Parser_token ptoken1, \
          Parser_token ptoken2 \
          ) {
  cmp_struct.val = value;
  cmp_struct.ptok1 = ptoken1;
  cmp_struct.ptok2 = ptoken2;
}


/*
If variable was not initialized, adds it to mem_init_vec
*/
void add_to_var_init(int var_mem_index) {
  for (long unsigned int i = 0; i < mem_init_vec.size(); i++) {
    if (mem_init_vec.at(i) == var_mem_index) {
      //already initialized - do nothing

    }
  }
  //add this cell to vec
  mem_init_vec.push_back(var_mem_index);
}

/*
Adds variable (name and memory cell index) to variable vector
*/
void add_to_vec(std::string name, int val, bool type, std::string proc_name, int size) {
  std::pair<std::string,int> name_cell_pair (name, val);
  std::pair<bool,std::string> type_proc_name_pair (type, proc_name);
  std::pair<std::pair<std::string,int>,std::pair<bool,std::string>> variable (name_cell_pair, type_proc_name_pair);
  std::pair<bool,int> init_size (0,size);
  std::pair<std::pair<std::pair<std::string,int>,std::pair<bool,std::string>>,std::pair<bool,int>> variable_size(variable,init_size);
  variable_vector.push_back(variable_size);
  mem_index += size;
}

/*
Searches variable name in variable_vetor with given procedure name
  if not in returns ("if proc was found",-1)
  A CO Z TABLICAMI
*/
std::pair<int,bool> search_variable(std::string var_name, std::string proc_name) {
  //if procedure was found
  bool proc_found = false;
  for (long unsigned int  i = 0; i < variable_vector.size(); i++) {
    if (variable_vector.at(i).first.second.second == proc_name) {
      proc_found = true;

      if (variable_vector.at(i).first.first.first == var_name) {
        int mem_cell = variable_vector.at(i).first.first.second;
        bool type =  variable_vector.at(i).first.second.first;
        std::pair<int,bool> variable_data (mem_cell, type);
        return variable_data;
      }
    }
  }
  return std::pair<int,bool> (-1,proc_found);
}

/*
Searches variable name in variable_vetor with given procedure name
  if not in returns -1
*/
int get_variable_size(std::string var_name, std::string proc_name) {
  for (long unsigned int  i = 0; i < variable_vector.size(); i++) {
    if (variable_vector.at(i).first.second.second == proc_name) {
      if (variable_vector.at(i).first.first.first == var_name) {
        return variable_vector.at(i).second.second;
      }
    }
  }
  return -1;
}
/*
Searches variable name in variable_vetor with given procedure name
  if not in returns -1
*/
int get_variable_type(std::string var_name, std::string proc_name) {
  for (long unsigned int  i = 0; i < variable_vector.size(); i++) {
    if (variable_vector.at(i).first.second.second == proc_name) {
      if (variable_vector.at(i).first.first.first == var_name) {
        return variable_vector.at(i).first.second.first;
      }
    }
  }
  return -1;
}

/*
Searches variable name in variable_vetor with given procedure name and stores value in its mem
  if not in returns ("if proc was found",-1)
    TODO: ADD CHECKING IF BOTH TABLE TYPE??

*/
std::string modify_variable_memory(std::string proc_name, std::vector<std::pair<std::pair<int,std::string>,int>> val) {
  //if procedure was found
  int j = 0;
  // bool proc_found = false;
  std::string ret_code = "";
  std::string error_code = "";
  bool was_error_in_modify = 0;
  for (long unsigned int  i = 0; i < variable_vector.size(); i++) {
    if (variable_vector.at(i).first.second.second == proc_name) {
      // proc_found = true;
      //aka is modify'able
      if (variable_vector.at(i).first.second.first == 1) {

          //if mem cell was initialized initialize normal mem cell
          //it works both ways
          if (!check_var_init(variable_vector.at(i).first.first.second)) {
            add_to_var_init(val.at(j).first.first);
          } 
          if (!check_var_init(val.at(j).first.first)) {
            add_to_var_init(variable_vector.at(i).first.first.second);
          } 
          //we initialize this variable
          // add_to_var_init(variable_vector.at(i).first.first.second);

          //what if table size == 1?
          if (variable_vector.at(i).second.second == 0 && val.at(j).second == 1) {
            error_code += "ERROR: passing variable to T variable\n";
            was_error_in_modify = 1;
          } else if (variable_vector.at(i).second.second == 1 && val.at(j).second != 1) {
            error_code += "ERROR: passing T variable to variable\n";
            was_error_in_modify = 1;
          }

          //we generate address where to push number
          std::string reg1 = "e";
          std::string register1 = reg1 + "\n";     
              
          //we generate number to push into addr
          std::string reg2 = "a";
          std::string register2 = reg2 + "\n";

          std::string mem_index_gen = gen_number_into_register(variable_vector.at(i).first.first.second, reg1);
          
          std::string value_gen = "";
          // if (val.at(j).first.first != -1) {
          //   value_gen = gen_number_into_register(val.at(j).first.first, reg2);
          // } else {
          //   value_gen = val.at(j).first.second;
          // }

          if (val.at(j).first.second != "") {
            value_gen = val.at(j).first.second;
          } else {
            value_gen = gen_number_into_register(val.at(j).first.first, reg2);
          }
          ret_code += mem_index_gen;
          ret_code += value_gen;
          //and we push it
          ret_code += "STORE " + register1;

          line_count++;

        j++;

      }
    }
    if (j - val.size() == 0) {
      if (was_error_in_modify) {
        ret_code = error_code;
      }
      return ret_code;
    }
  }
  ret_code = "ERROR in modify_variable_memory:  out of loop, maybe variable_vector.size() = 0";

  return ret_code;

}
/*
Prints var_vec
*/
void print_var_vec(){
  for (long unsigned int  i = 0; i < variable_vector.size(); i++) {
    std::cout << "var_name: " << variable_vector.at(i).first.first.first << std::endl;
    std::cout << "\tmem_cell/value: " << variable_vector.at(i).first.first.second << std::endl;
    std::cout << "\ttype: " << variable_vector.at(i).first.second.first << std::endl;
    std::cout << "\tproc_name: " << variable_vector.at(i).first.second.second << std::endl;
    std::cout << "\twas_initialized: " << variable_vector.at(i).second.first << std::endl;
    std::cout << "\tsize: " << variable_vector.at(i).second.second << std::endl;
    std::cout << std::endl;
  }
}

/*
Adds variable (name and memory cell index) to tmp variable vector
*/
void add_to_tmp_vec(std::string name, int val, int size) {
  std::pair<std::string,int> variable (name, val);
  std::pair<std::pair<std::string,int>,int> variable_size (variable, size);
  tmp_variable_vector.push_back(variable_size);
}

/*
Searches variable name in tmp_variable_vetor, if not in returns -1
CHECK IF OK FOR TABLES
*/
int search_variable_in_tmp(std::string name) {
  for (long unsigned int i = 0; i < tmp_variable_vector.size(); i++) {
    if (tmp_variable_vector.at(i).first.first == name) {
      return tmp_variable_vector.at(i).first.second;
    }
  }
  return -1;
}




/*
Docelowo do procedure val_vector
*/
void add_pair_to_vector(std::vector<std::pair<std::string,int>>* val_vec, std::pair<std::string,int> pair) {
  (*(val_vec)).push_back(pair); 
}
/*
Docelowo do procedure val_vector
*/
void add_str_and_val_to_vector(std::vector<std::pair<std::string,int>>* val_vec, std::string name, int val) {
  std::pair<std::string,int> pair (name, val);
  (*(val_vec)).push_back(pair);
}

/*
Simple function that appends code into ASM_CODE variable
Input: std::string <code>
*/
void write_to_asm(std::string code) {
  ASM_CODE += code;
}