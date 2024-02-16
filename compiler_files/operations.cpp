#include "main_header.hpp"



/*
Generates code for division
Input: int &<current_lines>, std::string <b_reg1>, std::string <b_reg2> 
Returns: Code for division
Note: USES ALL REGS, OUTPUT IN a
Note: Before loading b_reg1 resets f
Note: Before loading b_reg2 above + b,h,a
*/
std::string asm_division_gen( \
        int &current_lines, \
        std::string b_reg1, \
        std::string b_reg2  ) {

  // what if we get that in a and c
  std::string ret_val = "";

  // current_lines += 2;
  ret_val += "RST f   #BEGINING OF DIVISION\n";
  ret_val += "GET "; ret_val += b_reg1; ret_val += "\n"; //LOAD
  // ret_val += "READ \n";//  #instead of read we have 1st num in a
  ret_val += "JZERO "; ret_val += calculate_jump(77, current_lines);     //  #HALT

  // current_lines += 6;
  ret_val += "PUT b\n";// 
  ret_val += "RST h\n";//  
  ret_val += "INC h\n";// 
  ret_val += "INC h\n";//          #F1
  ret_val += "SHR a\n";//                 //5?
  ret_val += "JPOS "; ret_val += calculate_jump(6, current_lines); //          #F1

  // current_lines += 2;
  ret_val += "GET "; ret_val += b_reg2; ret_val += "\n"; //LOAD
  // ret_val += "READ\n";//         #instead of read we have 2nd num in e?
  ret_val += "JZERO "; ret_val += calculate_jump(77, current_lines);//  #HALT

  // current_lines += 7;
  ret_val += "PUT c\n";// 
  ret_val += "PUT d\n";//    # jedna z nich bedziym sziftowac, pewnie d
  ret_val += "RST g\n";//  
  ret_val += "INC g\n";// 
  ret_val += "INC g\n";//          #F2
  ret_val += "SHR a\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(15, current_lines);//          #F2

  // current_lines += 4;
  ret_val += "DEC g\n";//  
  ret_val += "GET h\n";// 
  ret_val += "SUB g\n";//  
  ret_val += "JZERO "; ret_val += calculate_jump(71, current_lines);//          #mamy zero czyli b+1 <= c     ^  h+1(1 liczba) z g(2)


  // current_lines += 4;
  ret_val += "DEC h\n";//  
  ret_val += "GET h\n";//  
  ret_val += "SUB g\n";//  
  ret_val += "JZERO "; ret_val += calculate_jump(67, current_lines);////         #mmmmmm(nizej)       ta sama lizcba bitow l1 i l2 => miesci sie raz lub 0 razy

  // current_lines += 4;
  ret_val += "PUT e\n";//           #obecnie w a mamy roznice bitow miedzy l1 i l2 przesun c zeby byly na tym samym pozimie i patrz czy sie miesci
  ret_val += "SHL d\n";//        #2sste
  ret_val += "DEC a\n";//    
  ret_val += "JPOS "; ret_val += calculate_jump(27, current_lines);//      #2sste

  // current_lines += 4;
  ret_val += "GET b\n";//            #tu kinda to robimy az mamy wynik chyba
  ret_val += "INC a\n";// 
  ret_val += "SUB d\n";//  
  ret_val += "JPOS "; ret_val += calculate_jump(35, current_lines);//        # 1Aaaaa 

  // current_lines += 1;
  ret_val += "JUMP "; ret_val += calculate_jump(58, current_lines);//      #$$$$$$$$$$

  // current_lines += 2;
  ret_val += "DEC a\n";//            # 1Aaaaa 
  ret_val += "JPOS "; ret_val += calculate_jump(47, current_lines);//          #####

  // current_lines += 6;
  ret_val += "INC a\n";// 
  ret_val += "PUT g\n";// 
  ret_val += "GET e\n";// 
  ret_val += "SHL g\n";//   #WAF
  ret_val += "DEC a\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(40, current_lines);//    #WAF

  // current_lines += 4;
  ret_val += "GET g\n";// 
  ret_val += "ADD f\n";// 
  ret_val += "PUT f\n";// 
  ret_val += "JUMP "; ret_val += calculate_jump(77, current_lines);//    #HALT

  // current_lines += 8;
  ret_val += "PUT b\n";//    ##### # do b wrzucamy reszte, patrzymy czy miesci sie 1 mniej #########
  ret_val += "RST a\n";//  
  ret_val += "INC a\n";//  
  ret_val += "PUT g\n";// 
  ret_val += "GET e\n";//  ########e nie potrzeba h i g tylko e od kiedy pol w 25 linijce
  ret_val += "SHL g\n";//   #WAF
  ret_val += "DEC a\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(52, current_lines);//    #WAF

  // current_lines += 5;
  ret_val += "GET g\n";// 
  ret_val += "ADD f\n";// 
  ret_val += "PUT f\n";// 
  ret_val += "GET e\n";//        #$$$$$$$$$$
  ret_val += "JPOS "; ret_val += calculate_jump(62, current_lines);//      #muuu

  // current_lines += 2;
  ret_val += "GET f\n";//       #HALT # SA TEGO SAMEGO ROZMIARU -> WIECEJ NIE WEPCHNE
  ret_val += "JUMP "; ret_val += calculate_jump(77, current_lines);//      #HALT

  // current_lines += 3;
  ret_val += "DEC e\n";//      #muuu #####ponizej muuu zmiana
  ret_val += "GET e\n";// 
  ret_val += "JZERO "; ret_val += calculate_jump(67, current_lines);//     #skacze do mmmmm

  // current_lines += 2;
  ret_val += "SHR d\n";//  
  ret_val += "JUMP "; ret_val += calculate_jump(30, current_lines);//  #tu kinda to robimy az mamy wynik chyba

  // current_lines += 4;
  ret_val += "GET b\n";//  #mmmmm
  ret_val += "INC a\n";// 
  ret_val += "SUB c\n";//  
  ret_val += "JPOS "; ret_val += calculate_jump(74, current_lines);//        # 2Aaaaa 

  // current_lines += 3;
  ret_val += "RST a\n";//       #mamy zero czyli b+1 <= c
  ret_val += "GET f\n";//            
  ret_val += "JUMP "; ret_val += calculate_jump(77, current_lines);//            #HALT

  // current_lines += 6; //if last 2 uncommented then 6
  // current_lines += 4; //jump above + all below 
  ret_val += "RST a\n";//            # 2Aaaaa 
  ret_val += "INC a\n";// 
  ret_val += "ADD f   #END OF DIVISION\n";// 
  // ret_val += "WRITE\n";//            #HALT
  // ret_val += "HALT\n";//               
  current_lines += 77;
  return ret_val;
}



/*
Generates code for multiplication
Input: int &<current_lines>, std::string <b_reg1>, std::string <b_reg2> 
Returns: Code for multiplication
Note: USES ALL REGS EXCEPT h, OUTPUT IN a
Note: Before loading b_reg2 resets f,e
Note: Before loading b_reg1 above + d
*/
std::string asm_multiplication_gen( \
        int &current_lines, \
        std::string b_reg1, \
        std::string b_reg2  ) {

    // inverse regs bc of "PUT d"
  // what if we get that in a and c
  std::string ret_val = "";
  
  // current_lines += 11;
  ret_val += "RST f   #BEGINING OF MULTIPLICATION\n";//
  ret_val += "RST e\n";//
  // ret_val += "READ ";//#/ LOAD  
  ret_val += "GET "; ret_val += b_reg2; ret_val += "\n"; //LOAD
  ret_val += "PUT d\n";//
  // ret_val += "READ ";// # do 12 sprawdzamy czy np
  ret_val += "GET "; ret_val += b_reg1; ret_val += "\n"; //LOAD
  ret_val += "PUT b\n";//
  ret_val += "SHR a\n";//
  ret_val += "SHL a\n";//
  ret_val += "PUT c\n";//
  ret_val += "GET b\n";//
  ret_val += "SUB c\n";//
  ret_val += "JZERO "; ret_val += calculate_jump(29, current_lines);//29 #GDZIES #//7 WRITE

  // current_lines += 3;
  ret_val += "GET f\n";//
  ret_val += "PUT g\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(18, current_lines);//18 #GDZIES2 #//f == 0 to dodaj do e d

  // current_lines += 3;
  ret_val += "GET d\n";//
  ret_val += "PUT e\n";//
  ret_val += "JUMP "; ret_val += calculate_jump(29, current_lines);//29

  // current_lines += 8;
  ret_val += "GET d\n";//   #GDZIES2
  ret_val += "PUT c\n";//
  ret_val += "GET c\n";//   #NIEDZWIEDZ
  ret_val += "SHL a\n";//
  ret_val += "PUT c\n";//
  ret_val += "DEC g\n";//
  ret_val += "GET g\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(20, current_lines);//20 #NIEDZWIEDZ

  // current_lines += 7;
  ret_val += "GET c\n";//
  ret_val += "ADD e\n";//  
  ret_val += "PUT e\n";// 
  ret_val += "SHR b\n";//   #GDZIES
  ret_val += "GET b\n";//
  ret_val += "INC f\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(6, current_lines);//6 #(2 in base )
  
  // current_lines += 4;
  // current_lines += 2;
  ret_val += "GET e   #END OF MULTIPLICATION\n";// 
  // ret_val += "WRITE";//
  // ret_val += "HALT";//
  current_lines += 34;

  return ret_val;
}

/*
Generates code for modulo
Input: int &<current_lines>, std::string <b_reg1>, std::string <b_reg2> 
Returns: Code for modulo
Note: USES ALL REGS, OUTPUT IN a
Note: Before loading b_reg2 resets f
Note: Before loading b_reg1 above + d,b,h,a
*/
std::string asm_modulo_gen( \
        int &current_lines, \
        std::string b_reg1, \
        std::string b_reg2  ) {

  std::string ret_val = "";

  //here as in multiplication we do first d then c
  //WE NEED TO MAKE switch in expression, not here
  //REM IS NOT PRZEMINNE
  ret_val += "RST f #REMAINDER BEG\n";//
  // ret_val += "READ \n";//
  ret_val += "GET "; ret_val += b_reg1; ret_val += "\n"; //LOAD
  ret_val += "JZERO "; ret_val += calculate_jump(130, current_lines);//130 #HALT

  ret_val += "PUT b\n";// 
  ret_val += "PUT d\n";//
  ret_val += "RST h\n";// 
  ret_val += "INC h\n";//
  ret_val += "INC h\n";//         #F1
  ret_val += "SHR a\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(6, current_lines);//6         #F1

  // ret_val += "READ \n";//
  ret_val += "GET "; ret_val += b_reg2; ret_val += "\n"; //LOAD
  ret_val += "JZERO "; ret_val += calculate_jump(130, current_lines);//130 #HALT

  ret_val += "PUT c\n";// #PUT d  # jedna z nich bedziym sziftowac, pewnie d
  ret_val += "RST g\n";// 
  ret_val += "INC g\n";//
  ret_val += "INC g\n";//         #F2
  ret_val += "SHR a\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(15, current_lines);//15         #F2

  ret_val += "DEC g\n";// 
  ret_val += "GET h\n";// 
  ret_val += "SUB g\n";// 
  ret_val += "JZERO "; ret_val += calculate_jump(86, current_lines);//86         #mamy zero czyli b+1 <= c     ^  h+1(1 liczba) z g(2)    #optymializacja - zworc b

  ret_val += "DEC h\n";// 
  ret_val += "GET h\n";// 
  ret_val += "SUB g\n";//           #optymializacja - (nizej) albo b albo roznice b i c zwroc
  ret_val += "JZERO "; ret_val += calculate_jump(82, current_lines);//82        #mmmmmm(nizej)       ta sama lizcba bitow l1 i l2 => miesci sie raz lub 0 razy

  ret_val += "PUT e\n";//          #obecnie w a mamy roznice bitow miedzy l1 i l2 przesun c zeby byly na tym samym pozimie i patrz czy sie miesci
  ret_val += "GET d\n";// 
  ret_val += "PUT h\n";//
  ret_val += "GET c\n";// 
  ret_val += "PUT d\n";//
  ret_val += "GET e\n";//
  ret_val += "SHL d\n";//       #2sste
  ret_val += "DEC a\n";//   
  ret_val += "JPOS "; ret_val += calculate_jump(32, current_lines);//32     #2sste

  ret_val += "GET b\n";//           #tu kinda to robimy az mamy wynik chyba
  ret_val += "INC a\n";//
  ret_val += "SUB d\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(40, current_lines);//40       # 1Aaaaa 

  ret_val += "JUMP "; ret_val += calculate_jump(63, current_lines);//63     #$$$$$$$$$$

  ret_val += "DEC a\n";//           # 1Aaaaa 
  ret_val += "JPOS "; ret_val += calculate_jump(52, current_lines);//52         #####

  ret_val += "INC a\n";//
  ret_val += "PUT g\n";//
  ret_val += "GET e\n";//
  ret_val += "SHL g\n";//  #WAF
  ret_val += "DEC a\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(45, current_lines);//45   #WAF

  ret_val += "GET g\n";//
  ret_val += "ADD f\n";//
  ret_val += "PUT f\n";//
  ret_val += "JUMP "; ret_val += calculate_jump(95, current_lines);//95   #HALT

  ret_val += "PUT b\n";//   ##### # do b wrzucamy reszte, patrzymy czy miesci sie 1 mniej #########
  ret_val += "RST a\n";// 
  ret_val += "INC a\n";// 
  ret_val += "PUT g\n";//
  ret_val += "GET e\n";// ########e nie potrzeba h i g tylko e od kiedy pol w 25 linijce
  ret_val += "SHL g\n";//  #WAF
  ret_val += "DEC a\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(57, current_lines);//57   #WAF

  ret_val += "GET g\n";//
  ret_val += "ADD f\n";//
  ret_val += "PUT f\n";//
  ret_val += "GET e\n";//       #$$$$$$$$$$
  ret_val += "JPOS "; ret_val += calculate_jump(67, current_lines);//67     #muuu

  ret_val += "GET f\n";//      #HALT # SA TEGO SAMEGO ROZMIARU -> WIECEJ NIE WEPCHNE
  ret_val += "JUMP "; ret_val += calculate_jump(95, current_lines);//95     #HALT

  ret_val += "DEC e\n";//     #muuu #####ponizej muuu zmiana
  ret_val += "GET e\n";//
  ret_val += "JZERO "; ret_val += calculate_jump(72, current_lines);// 72    #skacze do mmmmm

  ret_val += "SHR d\n";// 
  ret_val += "JUMP "; ret_val += calculate_jump(35, current_lines);//35 #tu kinda to robimy az mamy wynik chyba

  ret_val += "GET b\n";// #mmmmm              #########BELOW
  ret_val += "INC a\n";//
  ret_val += "SUB c\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(78, current_lines);//78       # 2Aaaaa 

  ret_val += "GET f\n";//           
  ret_val += "JUMP "; ret_val += calculate_jump(95, current_lines);//95           #HALT

  ret_val += "RST a\n";//           # 2Aaaaa 
  ret_val += "INC a\n";//
  ret_val += "ADD f\n";//
  ret_val += "JUMP "; ret_val += calculate_jump(95, current_lines);//95 #HALT TU JEST

  ret_val += "GET b\n";// #3mmmmm              #########BELOW
  ret_val += "INC a\n";//
  ret_val += "SUB c\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(90, current_lines);//90       # 32Aaaaa 

  ret_val += "GET b\n";//

  ret_val += "RST b\n";//           zapelniacz zeby nie liczyc od nowa, mozna wyciac in the future
  ret_val += "JUMP ";ret_val += calculate_jump(130, current_lines);//HALT //            zamiast write i halt to jump na sam koniec
  // ret_val += "WRITE\n";//            zamiast write i halt to jump na sam koniec
  // ret_val += "HALT \n";//

  ret_val += "JUMP "; ret_val += calculate_jump(95, current_lines);//95           #3HALT

  ret_val += "GET b\n";// 
  ret_val += "PUT h\n";//
  ret_val += "RST a\n";//           # 32Aaaaa 
  ret_val += "INC a\n";//
  ret_val += "ADD f\n";//
  ret_val += "PUT d\n";//     #HALT TU JEST
  ret_val += "RST f\n";//     ########## was 0 
  ret_val += "RST e\n";//
  ret_val += "GET c\n";//
  ret_val += "PUT b\n";//
  ret_val += "SHR a\n";//
  ret_val += "SHL a\n";//
  ret_val += "PUT c\n";//
  ret_val += "GET b\n";//
  ret_val += "SUB c\n";//
  ret_val += "JZERO "; ret_val += calculate_jump(123, current_lines);//123 #GDZIES #//7 WRITE

  ret_val += "GET f\n";//
  ret_val += "PUT g\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(112, current_lines);//112 #GDZIES2 #//f == 0 to dodaj do e d

  ret_val += "GET d\n";//
  ret_val += "PUT e\n";//
  ret_val += "JUMP "; ret_val += calculate_jump(123, current_lines);//123 #GDZIES

  ret_val += "GET d\n";//   #GDZIES2
  ret_val += "PUT c\n";//
  ret_val += "GET c\n";//   #NIEDZWIEDZ
  ret_val += "SHL a\n";//
  ret_val += "PUT c\n";//
  ret_val += "DEC g\n";//
  ret_val += "GET g\n";// 
  ret_val += "JPOS "; ret_val += calculate_jump(114, current_lines);//114 #NIEDZWIEDZ

  ret_val += "GET c\n";//
  ret_val += "ADD e\n";//  
  ret_val += "PUT e\n";// 
  ret_val += "SHR b\n";//   #GDZIES
  ret_val += "GET b\n";//
  ret_val += "INC f\n";//
  ret_val += "JPOS "; ret_val += calculate_jump(100, current_lines);//100 #(2 in base )

  ret_val += "GET e\n";// 
  ret_val += "GET h\n";// 
  ret_val += "SUB e #REMAINDER END\n";//
  // ret_val += "WRITE\n";//
  // ret_val += "HALT \n";//

  current_lines += 130;

  return ret_val;
}

