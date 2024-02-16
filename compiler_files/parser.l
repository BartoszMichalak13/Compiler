/* %option noyywrap */
/***Definitions ***/
%{

#define YY_NO_UNPUT

#include <cstdint>
#include <cstdio>


#include <stdio.h>
#include <math.h>
#include "parser_tab.h"

// static int lex(int token);
static int lex_num(int token);
static int lex_var(int token);


uint64_t lines = 1;

#ifdef LEX_DEBUG
#define pr_dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define pr_dbg(...)
#endif


/*#define lex_dbg(token) \
    ({ \
        pr_dbg("LEX: " #token "\n"); \
        lex(token); \
    })
*/
#define lex_num_dbg(token) \
    ({ \
        pr_dbg("LEX: " #token "\n"); \
        lex_num(token); \
    })

#define lex_var_dbg(token) \
    ({ \
        pr_dbg("LEX: " #token "\n"); \
        lex_var(token); \
    })

%}

%%
\#.*\n              { lines++;/*printf("hello %d\n",lines);lines++;return COM;*/};

[0-9]+            {
    return lex_num_dbg(num);
};

"="               {return EQ;}; 
"<="              {return LEQ;};
">="              {return GEQ;};
"!="              {return NE;};
"<"               {return LT;};
">"               {return GT;};

"+"               {return ADD;};
"-"               {return SUB;};
"*"               {return MUL;};
"/"               {return DIV;};
"%"               {return MOD;};

"("               {return LBR;};
")"               {return RBR;};
"["               {return LSBR;};
"]"               {return RSBR;};

"PROCEDURE"       {return PROCEDURE;};
"PROGRAM"         {return PROGRAM;};
"IN"              {return IN;};
"END"             {return END;};
"IS"              {return IS;};
"IF"              {return IF;};
"THEN"            {return THEN;};
"ENDIF"           {return ENDIF;};
"ELSE"            {return ELSE;};
"WHILE"           {return WHILE;};
"DO"              {return DO;};
"ENDWHILE"        {return ENDWHILE;};
"REPEAT"          {return REPEAT;};
"UNTIL"           {return UNTIL;};
"READ"            {return READ;};
"WRITE"           {return WRITE;};

[_a-z]+           {
  return lex_var_dbg(pidentifier);
};

"T"               {return T;};

";"               {return SEMI_COLON;};
":="              {return ASSIGNMENT;};
","               {return COMMA;};







[ ]+              {}
\n                {lines++;}
[\t\r ]+             {}
.       {return ERR;};

%%
/* static int lex(int token)
{
    yylval.ptoken.line = lines;
    yylval.ptoken.val = 0;
    yylval.ptoken.str = nullptr;
    yylval.ptoken.T_str = nullptr;
    yylval.ptoken.T_val = -1;

    return token;
} */

static int lex_num(int token)
{
    yylval.ptoken.line = lines;
    yylval.ptoken.val = strtoull(yytext, nullptr, 10);
    yylval.ptoken.str = nullptr;
    yylval.ptoken.T_str = nullptr;
    yylval.ptoken.T_val = -1;

    return token;
}

static int lex_var(int token)
{
    yylval.ptoken.line = lines;
    yylval.ptoken.val = 0;
    yylval.ptoken.str = new std::string(yytext);
    yylval.ptoken.T_str = nullptr;
    yylval.ptoken.T_val = -1;

    return token;
}
int yywrap()
{
    return 1;
}