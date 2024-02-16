#include "main_header.hpp"

/*
Adds ASM_CODE (ASM_CODE and command index) to COMMANDS_ASM_CODE_vector
*/
void add_to_COMMANDS_ASM_CODE_vector(std::string asm_code, int val) {
  std::pair<std::string,int> variable (asm_code, val);
  COMMANDS_ASM_CODE_vector.push_back(variable);
}

/*
Searches ASM_CODE in COMMANDS_ASM_CODE_vector, if not in returns ERROR
*/
std::string search_code(int code_index) {
  for (std::pair<std::string, int> i : COMMANDS_ASM_CODE_vector) {
    if (i.second == code_index) {
      return i.first;
    }
  }
  return "ERROR: no code under index " + std::to_string(code_index) + "\n";
}

/*
Searches ASM_CODE index aka .second in COMMANDS_ASM_CODE_vector, if not in returns -1
*/
int search_code_index(int code_index) {
  for (long unsigned int i = 0; i < COMMANDS_ASM_CODE_vector.size(); i++) {
    if (COMMANDS_ASM_CODE_vector.at(i).second == code_index) {
      return i;
    }
  }
  return -1;
}

/*
If we find such an i we should merge all next i's in COMMANDS_ASM_CODE_vector 
and place it in the vector in their place (delete old ones)
*/
void merge_commands(int index) {
  std::string merged_code = "";
  for (long unsigned int i = index; i < COMMANDS_ASM_CODE_vector.size(); i++) {
    merged_code += COMMANDS_ASM_CODE_vector.at(i).first;
  }
  
  // if I think correctly it should be first line before/at this block of code
  int line_number = COMMANDS_ASM_CODE_vector.at(index).second;

  //we remove all code parts that we merged
  for (long unsigned int i = COMMANDS_ASM_CODE_vector.size() - index; i > 0; i--) {
    COMMANDS_ASM_CODE_vector.pop_back();
  }

  std::pair<std::string,int> merged_code_pair (merged_code, line_number);
  //maybe changed later on
  COMMANDS_ASM_CODE_vector.push_back(merged_code_pair);
}
