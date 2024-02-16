#include "main_header.hpp"



/*
Generates ASM code for EQ condition
*/
std::string repeat_gen_EQ_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //string with condition value commands
  std::string cond_string = "";   //MAYBE LOAD?
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JZERO " + calculate_jump(0, beg_line);// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "DEC a\n";
  cond_string = cond_string + "JPOS " + calculate_jump(0, beg_line);//+  POCZTEK PETLI REPEAT
  line_count += 6;
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI
  
  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for NE condition
*/
std::string repeat_gen_NE_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JZERO " + calculate_jump(7, line_count);// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "DEC a\n";
  cond_string = cond_string + "JZERO " + calculate_jump(0, beg_line);//+  POCZTEK PETLI REPEAT
  line_count += 6;
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI
  
  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for LT condition
*/
std::string repeat_gen_LT_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;

  cond_string = cond_string + "JZERO " + calculate_jump(6, line_count);// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "JUMP " + calculate_jump(0, beg_line);// + 7(6?) +  KONIEC PETLI REPEAT


  line_count += 5;
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI
  
  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for GT condition
*/
std::string repeat_gen_GT_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JZERO " + calculate_jump(0, beg_line);// + 7(6?) +  KONIEC PETLI REPEAT
  line_count += 3;
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI
  
  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for LEQ condition
*/
std::string repeat_gen_LEQ_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JZERO " + calculate_jump(7, line_count);// + 7(6?) +  KONIEC PETLI REPEAT
  cond_string = cond_string + "DEC a\n";
  cond_string = cond_string + "JPOS " + calculate_jump(0, beg_line);//+  POCZTEK PETLI REPEAT
  line_count += 6;
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI
  
  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
/*
Generates ASM code for GEQ condition
*/
std::string repeat_gen_GEQ_condition( \
          int beg_line, \
          Parser_token ptok1, \
          Parser_token ptok2) {

  //our regs to write values to
  std::string reg1 = "c";
  std::string reg2 = "d";
  std::string register1 = reg1 + "\n";
  std::string register2 = reg2 + "\n";

  //returns strings needed to get number1 and number2 into reg1 and reg2
  auto[number1, number2] = get_number_for_cmp(ptok1, ptok2, reg1, reg2);

  //string with condition value commands
  std::string cond_string = "";
  cond_string = cond_string + "GET " + register1;
  cond_string = cond_string + "INC a\n";
  cond_string = cond_string + "SUB " + register2;
  cond_string = cond_string + "JZERO " + calculate_jump(0, beg_line);// + 7(6?) +  KONIEC PETLI REPEAT
  line_count += 4;
  //TU MAMY DALSZA CZESC KODU AKA WYSZLISY Z PETLI
  
  std::string ret_val = "";

  ret_val += number1; 
  ret_val += number2; 
  ret_val += cond_string; 

  return ret_val;
}
