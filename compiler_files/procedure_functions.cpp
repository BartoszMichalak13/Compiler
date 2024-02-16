#include "main_header.hpp"

/*
Adds variable (name and memory cell index) to procedures_vector
*/
void add_procedure(\
          std::vector<std::pair<std::pair<std::string, int>,int>> proc_in_variables, \
          std::string name, \
          int val) {
  std::pair<std::string, int> proc_pair (name,val);
  std::pair<std::vector<std::pair<std::pair<std::string, int>,int>>,std::pair<std::string,int>> procedure (proc_in_variables, proc_pair);
  procedures_vector.push_back(procedure);
  proc_index++;
}

/*
Searches variable name in procedures_vector, if not in returns -1
*/
int search_var_in_proc_vec(std::string proc_name, std::string var_name) {

  for (std::pair<std::vector<std::pair<std::pair<std::string, int>,int>>,std::pair<std::string,int>> proc : procedures_vector) {
    if (proc.second.first == proc_name) {
      for (std::pair<std::pair<std::string, int>,int> var : proc.first) {
        if (var.first.first == var_name) {
          return var.first.second;
        }
      }
    }
  }
  return -1;
}

/*
Searches procedure name in procedures_vector, if not found ERROR in error vec
if found returns POINTER to var_vec of that porcedure
*/
std::vector<std::pair<std::pair<std::string, int>,int>>* search_procedure(std::string proc_name) {

  for (long unsigned int i = 0; i < procedures_vector.size(); i++) {

    if (procedures_vector.at(i).second.first == proc_name) {
      return &(procedures_vector.at(i).first);
    }
  }
  std::pair<std::string,int> error_pair ("ERROR",INT_MIN);
  std::pair<std::pair<std::string, int>,int> error_pair_size (error_pair,INT_MAX);
  std::vector<std::pair<std::pair<std::string, int>,int>> error_vec;
  error_vec.push_back(error_pair_size);
  return &(error_vec);
}

/*
Searches procedure name in procedures_vector, if not found -1
if found returns beg_line of procedure
*/
int search_procedure_beg_line(std::string proc_name) {
  for (long unsigned int i = 0; i < procedures_vector.size(); i++) {
    if (procedures_vector.at(i).second.first == proc_name) {
      return procedures_vector.at(i).second.second;
    }
  }
  return -1;
}

/*
UPDATES procedure beg_line
*/
int update_procedure_beg_line(std::string proc_name, int beg_line) {
  for (long unsigned int i = 0; i < procedures_vector.size(); i++) {
    if (procedures_vector.at(i).second.first == proc_name) {
      procedures_vector.at(i).second.second = beg_line;
      return 0;
    }
  }
  return -1;
}