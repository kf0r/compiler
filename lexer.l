%option noyywrap

%{

#define YY_NO_UNPUT
#include <iostream>
#include <string>
#include "parser.tab.hpp"

static int lex(int token);
static int lex_num(int token);
static int lex_var(int token);
extern int yylex();

int lines = 1;
%}

%x comment

%%
\; {return lex(SEMICOLON);};
\+ {return lex(PLUS);};
\- {return lex(MINUS);};
\* {return lex(MULT);};
\/ {return lex(DIV);};
\% {return lex(MOD);};
:= {return lex(ASSIGN);};
, {return lex(COMMA);};
\= {return lex(EQ);};
!= {return lex(NEQ);};
"<" {return lex(LESS);};
"<=" {return lex(LEQ);};
">" {return lex(MORE);};
">=" {return lex(MEQ);};
\[ {return lex(LSQ);};
\] {return lex(RSQ);};
"(" {return lex(LBR);};
")" {return lex(RBR);};

# {BEGIN(comment);};
<comment>\\\n {lines++;};
<comment>. {};
<comment>\n {BEGIN(INITIAL);}

PROCEDURE {return lex(PROCEDURE);};
IS {return lex(IS);};
IN {return lex(IN);};
END {return lex(END);};
IF {return lex(IF);};
THEN {return lex(THEN);};
ELSE {return lex(ELSE);};
ENDIF {return lex(ENDIF);};
WHILE {return lex(WHILE);};
DO {return lex(DO);};
ENDWHILE {return lex(ENDWHILE);};
REPEAT {return lex(REPEAT);};
UNTIL {return lex(UNTIL);};
READ {return lex(READ);};
WRITE {return lex(WRITE);};
PROGRAM {return lex(PROGRAM);};
T {return lex(T);};

[A-Z]+ {return lex(INVALID_KEYWORD);};

[[:digit:]]+ {return lex_num(NUM);};

[_a-z]+ {return lex_var(PIDENTIFIER);};

\n {lines++;}

[[:space:]] {}

. {return ERROR_INVALID_CHAR;};

%%

static int lex(int token)
{
    yylval.ptoken.line = lines;
    yylval.ptoken.val = 0;
    yylval.ptoken.str = nullptr;

    return token;
}

static int lex_num(int token)
{
    yylval.ptoken.line = lines;
    yylval.ptoken.val = strtoull(yytext, nullptr, 10);
    yylval.ptoken.str = nullptr;

    return token;
}

static int lex_var(int token)
{
    yylval.ptoken.val = 0;
    yylval.ptoken.line = lines;
    yylval.ptoken.str = new std::string(yytext);

    return token;
}