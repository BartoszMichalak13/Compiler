#include "main_header.hpp"
#include <sstream>
#include <cctype>

/*
Generates condition code for repeat loop
*/
std::string gen_repeat_condition(int beg_line, Comparision_struct cmp_struct) {
  int condition_number = cmp_struct.val;
  Parser_token ptok1 = cmp_struct.ptok1;
  Parser_token ptok2 = cmp_struct.ptok2;
  std::string ret_val = "ERROR";
  switch (condition_number)
  {
  case 1:
      ret_val = repeat_gen_EQ_condition(beg_line, ptok1, ptok2);
    break;
  case 2:
      ret_val = repeat_gen_NE_condition(beg_line, ptok1, ptok2);
    break;
  case 3:
      ret_val = repeat_gen_LT_condition(beg_line, ptok1, ptok2);
    break;
  case 4:
      ret_val = repeat_gen_GT_condition(beg_line, ptok1, ptok2);
    break;
  case 5:
      ret_val = repeat_gen_LEQ_condition(beg_line, ptok1, ptok2);
    break;
  case 6:
      ret_val = repeat_gen_GEQ_condition(beg_line, ptok1, ptok2);
    break;

  default:
      ret_val = "ERROR";
    break;
  }
  return ret_val;
}

/*
Generates condition code for if-else
Updates rest of code (already generated for if-else loop)
by adding offset of condition length
MODE:   
  1 if-else
  2 if
  3 while
*/
std::string gen_if_else_condition( \
          int mode, \
          int code1_index, \
          int command1_line, \
          int command2_line, \
          Comparision_struct cmp_struct) {

  // line count before cond, it contains commands after cond, but it doesnt matter
  int lines_before_cond = line_count;
  int condition_number = cmp_struct.val;
  Parser_token ptok1 = cmp_struct.ptok1;
  Parser_token ptok2 = cmp_struct.ptok2;

  std::string ret_val = "ERROR";
  switch (condition_number)
  {
  case 1:
      ret_val = if_else_gen_EQ_condition(mode, lines_before_cond, code1_index, command1_line, command2_line, ptok1, ptok2);
    break;
  case 2:
      ret_val = if_else_gen_NE_condition(mode, lines_before_cond, code1_index, command1_line, command2_line, ptok1, ptok2);
    break;
  case 3:
      ret_val = if_else_gen_LT_condition(mode, lines_before_cond, code1_index, command1_line, command2_line, ptok1, ptok2);
    break;
  case 4:
      ret_val = if_else_gen_GT_condition(mode, lines_before_cond, code1_index, command1_line, command2_line, ptok1, ptok2);
    break;
  case 5:
      ret_val = if_else_gen_LEQ_condition(mode, lines_before_cond, code1_index, command1_line, command2_line, ptok1, ptok2);
    break;
  case 6:
      ret_val = if_else_gen_GEQ_condition(mode, lines_before_cond, code1_index, command1_line, command2_line, ptok1, ptok2);
    break;

  default:
      ret_val = "ERROR";
    break;
  }
  return ret_val;
}

/*
Generates index where to store variable according to variable_vector 
(var_index was calculated by searching name of variable in variable_vector)

Posible rename this function as it generates any number:
we may also pass register name to know which reg to push number into

Input: int <var_ind>,  std::string <reg>
Returns: std::string ret_val (code that puts var_index into reg)

CHECK IF WORKS CORRECTLY!!!!
*/
std::string gen_number_into_register(uint64_t var_ind,  std::string reg) {

  //CHANGES uint64_t in var_ind and FLOAT64 nsest of float

  // we cast it to float for correct calculations
  _Float64 var_index = (_Float64)var_ind;

  // variable that keeps reg name + \n
  std::string register1 = reg + "\n"; 

  // checks if given reg is correct
  if ( check_reg(reg) ) { return "ERROR no such register: " + register1; }

  // variable that keeps instruction + reg name + \n
  std::string tmp_str = "";

  // generate 0
  if (var_index == 0) {
    line_count++;
    tmp_str = "RST "+ register1;
    return tmp_str;
  }

  // sequance of return instructions
  std::string ret_val = "";

  var_index /= 2;
  // checks if number is even or odd
  if (var_index == std::floor(var_index)) { // 0
  } else {                                  //1 
    line_count++;
    tmp_str = "INC " + register1;
    ret_val.insert(0,tmp_str);
    var_index = std::floor(var_index);
  }

  // generates sequence of instructions
  while (var_index > 0.5) {

    var_index /= 2;

    if (var_index == std::floor(var_index)) { // 0

      line_count++;
      tmp_str = "SHL " + register1;
      ret_val.insert(0,tmp_str);

    } else {                                  //1 
    
      line_count += 2;
      tmp_str = "INC " + register1 + "SHL " + register1;
      ret_val.insert(0,tmp_str);
      var_index = std::floor(var_index);

    } 
  }

  // finally we generate first instruction (start at 0)
  line_count++;
  tmp_str = "RST " + register1;
  ret_val.insert(0,tmp_str);

  return ret_val;
}

/*
Generates code to get value either Read and Stored to or Loaded from location
MODES:
  LOAD
  LOAD PUT
  READ STORE
  NONE (does nothing)
  WRITE (deprecated)

Input: std::string <name>, std::string <reg>, std::string <mode>
Returns: std::string ret_val (code to gen value into reg + mode operation)

Note: may clear info in a based on mode
*/
std::string gen_val_to_reg(std::string name, std::string reg, std::string mode) {

  // variable that keeps reg name + \n
  std::string _register = reg + "\n"; 

  // checks if given reg is correct
  if ( check_reg(reg) ) { return "ERROR no such register: " + _register; }

  // find var index
  std::pair<int,bool> var_data = search_variable(name, PROC_NAME);
  int var_index = var_data.first;
  bool var_type = var_data.second;

  // return string of commands
  std::string ret_val = "ERROR";

  // no such a variable
  if (var_index < 0) {
    if (var_type == false) {
      return "Nie znaleziono procedury: " + PROC_NAME + " ERROR";
    }
    return "Nie można znaleźć zmiennej " + name + " ERROR";
  } 
  
  mem_index_counter = var_index;

  // generates value into register
  ret_val = gen_number_into_register(var_index, reg);
  // check_string
  if (!check_string(ret_val)) {
    // yyerror(ret_val.c_str()); 
    return "Generowanie liczb do " + name + " ERROR";;
  }


    
    //Load p_reg to a and PUT to reg
    if (mode == "LOAD PUT") {

      line_count++;
      ret_val += "LOAD ";      
      ret_val += _register;

      //procedure proc_head var
      if (var_type == 1) {
        line_count++;
        ret_val += "LOAD a\n";      
      }

      line_count++;
      ret_val += "PUT ";      
      ret_val += _register;

    //Load p_reg to a
    } else if (mode == "LOAD") {

      line_count++;
      ret_val += "LOAD ";      
      ret_val += _register;

      //procedure proc_head var
      if (var_type == 1) {
        line_count++;
        ret_val += "LOAD a\n";      
      }

    //Read to a and store to p_reg
    } else if (mode == "READ STORE") {
      
      line_count += 2;
      if (var_type == 1) {

        //load var_mem_cell
        ret_val += "LOAD ";      
        ret_val += _register;

        ret_val += "PUT " + _register;      
        line_count += 2;

      }
      ret_val += "READ \n";

      ret_val += "STORE ";
      ret_val += _register;

    } else if (mode == "NONE") {
    //store for assignment 
    } else if (mode == "STORE") {
      
      //procedure proc_head var
      if (var_type == 1) {
        line_count += 5;

        //for now c, but we need to store answ from expression somwhere
        ret_val += "PUT c\n";      

        //load var_mem_cell
        ret_val += "LOAD ";      
        ret_val += _register;

        //store where is mem cell of var (for eg) in d
        ret_val += "PUT d\n"; 

        //get answ saved in c
        ret_val += "GET c\n";

        //store it in mem_cell saved in d
        ret_val += "STORE d\n";

      } else {

        line_count++;
        ret_val += "STORE ";
        ret_val += _register;
      }

    //unknown mode
    } else {

      return "ERROR Mode: " + mode;

    }

  return ret_val;
}

/*
Gets ptoken into register
Input: Parser_token <ptok1>, std::string <reg1>
Returns: std::string number1 (code to put ptok1 into reg1)
*/
std::string get_ptoken_to_reg(Parser_token ptok1, std::string reg1, std::string mode) {
  //1st number
  std::string number1 = "ERROR";
  std::string register1 = reg1 + "\n";

  // neede for tables
  std::string tmp_reg = "h";
  std::string tmp_register = tmp_reg + "\n";

  //make 3 and 2 compatible with procedures
  int p_type = check_ptoken_type(ptok1);

  //CHECK IF odwoluje sie do elemntu zgodnego z romzmiarem tablicy

  //check type of ptoken 
  if ( p_type == 3 ) {            // table[var]
  
    std::string var_name = *(ptok1.str);
    std::string table_index = *(ptok1.T_str);

    //gramatyka nie pozwala na T[T[T[..[var/num]]]]
    std::pair<int,bool> var_data = search_variable(var_name, PROC_NAME);
    int var_index = var_data.first;
    bool var_type = var_data.second;

    // no such a variable
    if (var_index < 0) {
      if (var_type == false) {
        return "Nie znaleziono procedury: " + PROC_NAME + " ERROR";
      }
      return "Nie można znaleźć zmiennej " + var_name+ " ERROR";
    } 

    std::pair<int,bool> table_index_data = search_variable(table_index, PROC_NAME);
    int table_index_index = table_index_data.first;
    bool table_index_type = table_index_data.second;

    // no such a variable
    if (table_index_index < 0) {
      if (table_index_type == false) {
        return "Nie znaleziono procedury: " + PROC_NAME + " ERROR";
      }
      return "Nie można znaleźć zmiennej " + var_name+ " ERROR";
    } 
    
    //if we want to store value/expression, save it for later in c
    if (mode == "STORE") {
      number1 = "PUT c\n";
      line_count++;
    } else {
      number1 = "";
    }

    number1 += gen_number_into_register(table_index_index, tmp_reg);
    if (table_index_type == true) {
      number1 += "LOAD "; number1 += tmp_register;
      //puhs in tmp_register
      number1 += "PUT " + tmp_register;
      line_count += 2;
    }
    number1 += "LOAD "; number1 += tmp_register;
    number1 += "PUT " + tmp_register;
    line_count += 2;

    number1 += gen_number_into_register(var_index, reg1);
    if (var_type == true) {
      number1 += "LOAD "; number1 += register1;
      //puhs in reg1
      number1 += "PUT " + register1;
      line_count += 2;
    }

    //we push reg1 into a
    number1 += "GET " + register1;
    // we add second part
    number1 += "ADD " + tmp_register;
    line_count += 2;


    if (mode != "LOAD PUT") {

      number1 += "PUT " + register1;
      if (mode == "READ STORE") {
        number1 += "READ \n";
      } else {
        //for now supppose it's always c
        number1 += "GET c\n";
      }
      number1 += "STORE " + register1;
      line_count += 3;

    } else {

      //we load given mem cell
      number1 += "LOAD a\n";
      //puhs in reg1
      number1 += "PUT " + register1;
      line_count += 2;

    }

    //nie table_index_index, tylko value w tym indexie
    //NIE MOZNA DOBRZE OCENIC CZY KOM ZOSTALA ZAINICJALIZOWANA
    // mem_index_counter = var_index;//table_index_index + var_index;
    mem_index_counter = table_index_index;//table_index_index + var_index;

  } else if ( p_type == 2 ) {     // table[num]
  
    std::string var_name = *(ptok1.str);
    int table_index = ptok1.T_val;

    std::pair<int,bool> var_data = search_variable(var_name, PROC_NAME);
    int var_index = var_data.first;
    bool var_type = var_data.second;

    // no such a variable
    if (var_index < 0) {
      if (var_type == false) {
        return "Nie znaleziono procedury: " + PROC_NAME + " ERROR";
      }
      return "Nie można znaleźć zmiennej " + var_name+ " ERROR";
    } 


    //if we want to store value/expression, save it for later in c
    if (mode == "STORE") {
      number1 = "PUT c\n";
      line_count++;
    } else {
      number1 = "";
    }

    //gen val index into reg1
    number1 += gen_number_into_register(var_index, tmp_reg);
    if (var_type == true) {
      number1 += "LOAD "; number1 += tmp_register;
      //puhs in reg1
      number1 += "PUT " + tmp_register;
      line_count += 2;
    }

    //gen table cell into tmp_reg
    number1 += gen_number_into_register(table_index, reg1);

    //we push reg1 into a
    number1 += "GET " + register1;
    // we add second part
    number1 += "ADD " + tmp_register;
    line_count += 2;



    if (mode != "LOAD PUT") {

      number1 += "PUT " + register1;
      if (mode == "READ STORE") {
        number1 += "READ \n";
      } else {
        //for now supppose it's always c
        number1 += "GET c\n";
      }
      number1 += "STORE " + register1;
      line_count += 3;

    } else {
      //we load given mem cell
      number1 += "LOAD a\n";
      //puhs in reg1
      number1 += "PUT " + register1;
      line_count += 2;
    }

    mem_index_counter = table_index + var_index;

  } else if ( p_type == 1 ) {     // num
  
    //gen code to get number
    number1 = gen_number_into_register(ptok1.val, reg1);

  } else if( p_type == 0 ) {      // var

    // find var index
    number1 = gen_val_to_reg(*(ptok1.str), reg1, mode);

    //mem index generated in gen_val
  } 
  return number1;
}

/*
Gets Parser_tokens into regs for comparision purpose
Input: Parser_token <PTOK1>, Parser_token <PTOK2>
Input: std::string <reg1>, std::string <reg2>

Returns std::pair<std::string,std::string>
with first element being code that puts PTOK1 into reg1
and second doing the same for PTOK2 and reg2
*/
std::pair<std::string,std::string> get_number_for_cmp( \
          Parser_token ptok1, \
          Parser_token ptok2, \
          std::string reg1, \
          std::string reg2  ) {

  //get 1st number into reg
  std::string number1 = get_ptoken_to_reg(ptok1, reg1, "LOAD PUT");

  //get 2nd number into reg
  std::string number2 = get_ptoken_to_reg(ptok2, reg2, "LOAD PUT");
  
  std::pair<std::string,std::string> ret_val;
  ret_val.first     =   number1;
  ret_val.second    =   number2;

  return ret_val;
}

/*
It increments all numbers in string

Usefull for while and if else commands as inner commands codes are generated 
before condition codes
*/
std::string incrementNumbersInString(const std::string& input, int incrementBy) {
  std::string result;
  std::istringstream iss(input);
  char ch;

  while (iss.get(ch)) {
    if (isdigit(ch)) {
      std::string number;
      number += ch;

      while (iss.get(ch) && isdigit(ch)) {
        number += ch;
      }

      int originalNumber = std::stoi(number);
      int incrementedNumber = originalNumber + incrementBy;

      // Append the incremented number to the result string
      result += std::to_string(incrementedNumber);

      // Append the remaining non-digit characters
      result += ch;
    } else {
      result += ch;
    }
  }

  return result;
}
