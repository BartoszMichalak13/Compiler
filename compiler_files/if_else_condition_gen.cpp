#include "main_header.hpp"


/*
Add jump at the end of while

CHECK if calculated correctly
*/
void while_add_jump(int lines_before_cond, int offset ) {
  line_count++;

  //we create jump to the end of 2nd block of commands 
  //we enter this jump after finishing first block of commands
  std::string jump_str = "JUMP " + std::to_string(lines_before_cond - offset) + "\n";

  //we need to add jump at the end of all commads to go back to condition checker
  add_to_COMMANDS_ASM_CODE_vector(jump_str, line_count-1);
}

/*
Generates ASM code for EQ condition
*/
std::string if_else_gen_EQ_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {


  //it's updated bc of jump
  if (mode != 2) {
    command2_line += 1;
  }  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //we calculate offset for ther rest of the code
  line_count += 6;
  int offset = line_count - lines_before_cond; 

  command1_line += offset;
  command2_line += offset;

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JZERO " + calculate_jump(0, command2_line);// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "DEC a\n";
  cond_string = cond_string + "JPOS " + calculate_jump(0, command2_line);//+  POCZTEK PETLI REPEAT
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI

  //we increment rest of if-else code by offset (len of condition)
  std::string offset_code = incrementNumbersInString(COMMANDS_ASM_CODE_vector.at(code1_index).first,offset);
  COMMANDS_ASM_CODE_vector.at(code1_index).first = offset_code;
 
  //we add jump at the end to condition checker to the begining of while check
  //OSTATNI JUMP ZLE BO, JAK MAMY SPORO KODU WYGENEROWANEGO PRZED NIM, TO LINES BEFORE NIE JEST LINES PRZED ALL EXPRESSINS, 
  //TO COMMAND1 I TO MUSZE ZMODYFIKOWAC O ODPOWIEDNI OFFSET
  if (mode == 3) {
    while_add_jump(command1_line, offset );
  }

  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for NE condition
*/
std::string if_else_gen_NE_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //it's updated bc of jump
  if (mode != 2) {
    command2_line += 1;
  }  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //we calculate offset for ther rest of the code
  line_count += 7;
  int offset = line_count - lines_before_cond; 

  command1_line += offset;
  command2_line += offset;

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;       //chyba 6
  cond_string = cond_string + "JZERO " + calculate_jump(0, command1_line);// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "DEC a\n";
  cond_string = cond_string + "JPOS " + calculate_jump(0, command1_line);//+  POCZTEK PETLI REPEAT
  cond_string = cond_string + "JUMP " + calculate_jump(0, command2_line);//+  POCZTEK PETLI REPEAT

  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI

  //we increment rest of if-else code by offset (len of condition)
  std::string offset_code = incrementNumbersInString(COMMANDS_ASM_CODE_vector.at(code1_index).first,offset);
  COMMANDS_ASM_CODE_vector.at(code1_index).first = offset_code;
 
  //we add jump at the end to condition checker
  //OSTATNI JUMP ZLE BO, JAK MAMY SPORO KODU WYGENEROWANEGO PRZED NIM, TO LINES BEFORE NIE JEST LINES PRZED ALL EXPRESSINS, 
  //TO COMMAND1 I TO MUSZE ZMODYFIKOWAC O ODPOWIEDNI OFFSET
  if (mode == 3) {
    while_add_jump(command1_line, offset );
  }

  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for LT condition
*/
std::string if_else_gen_LT_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //it's updated bc of jump
  if (mode != 2) {
    command2_line += 1;
  }
  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //we calculate offset for ther rest of the code
  line_count += 4;
  int offset = line_count - lines_before_cond; 

  command1_line += offset;
  command2_line += offset;

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JPOS " + calculate_jump(0, command2_line);// + 7(6?) +  KONIEC PETLI REPEAT
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI

  //we increment rest of if-else code by offset (len of condition)
  std::string offset_code = incrementNumbersInString(COMMANDS_ASM_CODE_vector.at(code1_index).first,offset);
  COMMANDS_ASM_CODE_vector.at(code1_index).first = offset_code;
 
  //we add jump at the end to condition checker
  //OSTATNI JUMP ZLE BO, JAK MAMY SPORO KODU WYGENEROWANEGO PRZED NIM, TO LINES BEFORE NIE JEST LINES PRZED ALL EXPRESSINS, 
  //TO COMMAND1 I TO MUSZE ZMODYFIKOWAC O ODPOWIEDNI OFFSET
  if (mode == 3) {
    while_add_jump(command1_line, offset );
  }

  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for GT condition
*/
std::string if_else_gen_GT_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //it's updated bc of jump
  if (mode != 2) {
    command2_line += 1;
  }
  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //we calculate offset for ther rest of the code
  line_count += 4;
  int offset = line_count - lines_before_cond; 

  command1_line += offset;
  command2_line += offset;

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JPOS " + calculate_jump(0, command1_line);// + comment;// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "JUMP " + calculate_jump(0, command2_line);// + comment;// + 7(6?) +  KONIEC PETLI REPEAT
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI

  //we increment rest of if-else code by offset (len of condition)
  std::string offset_code = incrementNumbersInString(COMMANDS_ASM_CODE_vector.at(code1_index).first,offset);
  COMMANDS_ASM_CODE_vector.at(code1_index).first = offset_code;
 
  //we add jump at the end to condition checker
  //OSTATNI JUMP ZLE BO, JAK MAMY SPORO KODU WYGENEROWANEGO PRZED NIM, TO LINES BEFORE NIE JEST LINES PRZED ALL EXPRESSINS, 
  //TO COMMAND1 I TO MUSZE ZMODYFIKOWAC O ODPOWIEDNI OFFSET
  if (mode == 3) {
    while_add_jump(command1_line, offset );
  }
  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for LEQ condition
*/
std::string if_else_gen_LEQ_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //it's updated bc of jump
  if (mode != 2) {
    command2_line += 1;
  }
  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //we calculate offset for ther rest of the code
  line_count += 6;
  int offset = line_count - lines_before_cond; 

  command1_line += offset;
  command2_line += offset;

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;       //chyba 6
  cond_string = cond_string + "JZERO " + calculate_jump(0, command1_line);// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "DEC a\n";
  cond_string = cond_string + "JPOS " + calculate_jump(0, command2_line);//+  POCZTEK PETLI REPEAT
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI

  //we increment rest of if-else code by offset (len of condition)
  std::string offset_code = incrementNumbersInString(COMMANDS_ASM_CODE_vector.at(code1_index).first,offset);
  COMMANDS_ASM_CODE_vector.at(code1_index).first = offset_code;
 
  //we add jump at the end to condition checker
  //OSTATNI JUMP ZLE BO, JAK MAMY SPORO KODU WYGENEROWANEGO PRZED NIM, TO LINES BEFORE NIE JEST LINES PRZED ALL EXPRESSINS, 
  //TO COMMAND1 I TO MUSZE ZMODYFIKOWAC O ODPOWIEDNI OFFSET
  if (mode == 3) {
    while_add_jump(command1_line, offset );
  }

  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for GEQ condition
*/
std::string if_else_gen_GEQ_condition( \
          int mode, \
          int lines_before_cond, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //it's updated bc of jump
  if (mode != 2) {
    command2_line += 1;
  }
  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //we calculate offset for ther rest of the code
  line_count += 4;
  int offset = line_count - lines_before_cond; 

  command1_line += offset;
  command2_line += offset;

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JZERO " + calculate_jump(0, command2_line);// + 7(6?) +  KONIEC PETLI REPEAT
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI

  //we increment rest of if-else code by offset (len of condition)
  std::string offset_code = incrementNumbersInString(COMMANDS_ASM_CODE_vector.at(code1_index).first,offset);
  COMMANDS_ASM_CODE_vector.at(code1_index).first = offset_code;

  //we add jump at the end to condition checker


  //OSTATNI JUMP ZLE BO, JAK MAMY SPORO KODU WYGENEROWANEGO PRZED NIM, TO LINES BEFORE NIE JEST LINES PRZED ALL EXPRESSINS, 
  //TO COMMAND1 I TO MUSZE ZMODYFIKOWAC O ODPOWIEDNI OFFSET
  if (mode == 3) {
    while_add_jump(command1_line, offset );
  }

  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
