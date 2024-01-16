/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 18 "parser.ypp"

    #include "./Vertex.hpp"
    #include "./Types.hpp"
    #include "ProgramStructure.hpp"
    #include "./LowBlock.hpp"
    typedef struct Parser_token
    {
        uint64_t val;
        uint64_t line;
        std::string* str; 
    } Parser_token;

#line 62 "parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    PLUS = 259,                    /* PLUS  */
    MINUS = 260,                   /* MINUS  */
    MULT = 261,                    /* MULT  */
    DIV = 262,                     /* DIV  */
    MOD = 263,                     /* MOD  */
    EQ = 264,                      /* EQ  */
    ASSIGN = 265,                  /* ASSIGN  */
    COMMA = 266,                   /* COMMA  */
    NEQ = 267,                     /* NEQ  */
    LESS = 268,                    /* LESS  */
    LEQ = 269,                     /* LEQ  */
    MORE = 270,                    /* MORE  */
    MEQ = 271,                     /* MEQ  */
    LSQ = 272,                     /* LSQ  */
    RSQ = 273,                     /* RSQ  */
    LBR = 274,                     /* LBR  */
    RBR = 275,                     /* RBR  */
    NUM = 276,                     /* NUM  */
    PIDENTIFIER = 277,             /* PIDENTIFIER  */
    PROCEDURE = 278,               /* PROCEDURE  */
    IS = 279,                      /* IS  */
    IN = 280,                      /* IN  */
    END = 281,                     /* END  */
    IF = 282,                      /* IF  */
    THEN = 283,                    /* THEN  */
    ELSE = 284,                    /* ELSE  */
    ENDIF = 285,                   /* ENDIF  */
    WHILE = 286,                   /* WHILE  */
    DO = 287,                      /* DO  */
    ENDWHILE = 288,                /* ENDWHILE  */
    REPEAT = 289,                  /* REPEAT  */
    UNTIL = 290,                   /* UNTIL  */
    READ = 291,                    /* READ  */
    WRITE = 292,                   /* WRITE  */
    PROGRAM = 293,                 /* PROGRAM  */
    T = 294,                       /* T  */
    INVALID_KEYWORD = 295,         /* INVALID_KEYWORD  */
    ERROR_INVALID_CHAR = 296       /* ERROR_INVALID_CHAR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "parser.ypp"

    int intVal;

    Parser_token ptoken;

    Instruction* instPointer;
    LinkedCommands* linkedPointer;

    Procedure_head* procHeadPointer;

    Value* valuePointer;
    Declaration* declarationPointer;

    Identifier* identPointer;

    IndentifierArrNumber* arrNumPoint;
    IndentifierArrPid* arrPidPoint;
    Expression* exprPoint;
    Condition* condPoint;
    Main* mainPoint;

    Args* argPointer;
    Procedure_call* callPointer;
    ProceduresAll* procAllPointer;

    Program* programPointer;

#line 148 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
