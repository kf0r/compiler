/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.ypp"
    
    #include <iostream>
    #include <string>
    #include <map>
    #include <vector>
    #include "./Vertex.hpp"
    #include "./Types.hpp"
    #include "parser.tab.hpp"
    #include "ProgramStructure.hpp"
    #include "./LowBlock.hpp"
    extern int yylex();
    extern int yyparse();
    int yyerror(std::string s);


#line 87 "parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_PLUS = 4,                       /* PLUS  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_MULT = 6,                       /* MULT  */
  YYSYMBOL_DIV = 7,                        /* DIV  */
  YYSYMBOL_MOD = 8,                        /* MOD  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_ASSIGN = 10,                    /* ASSIGN  */
  YYSYMBOL_COMMA = 11,                     /* COMMA  */
  YYSYMBOL_NEQ = 12,                       /* NEQ  */
  YYSYMBOL_LESS = 13,                      /* LESS  */
  YYSYMBOL_LEQ = 14,                       /* LEQ  */
  YYSYMBOL_MORE = 15,                      /* MORE  */
  YYSYMBOL_MEQ = 16,                       /* MEQ  */
  YYSYMBOL_LSQ = 17,                       /* LSQ  */
  YYSYMBOL_RSQ = 18,                       /* RSQ  */
  YYSYMBOL_LBR = 19,                       /* LBR  */
  YYSYMBOL_RBR = 20,                       /* RBR  */
  YYSYMBOL_NUM = 21,                       /* NUM  */
  YYSYMBOL_PIDENTIFIER = 22,               /* PIDENTIFIER  */
  YYSYMBOL_PROCEDURE = 23,                 /* PROCEDURE  */
  YYSYMBOL_IS = 24,                        /* IS  */
  YYSYMBOL_IN = 25,                        /* IN  */
  YYSYMBOL_END = 26,                       /* END  */
  YYSYMBOL_IF = 27,                        /* IF  */
  YYSYMBOL_THEN = 28,                      /* THEN  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_ENDIF = 30,                     /* ENDIF  */
  YYSYMBOL_WHILE = 31,                     /* WHILE  */
  YYSYMBOL_DO = 32,                        /* DO  */
  YYSYMBOL_ENDWHILE = 33,                  /* ENDWHILE  */
  YYSYMBOL_REPEAT = 34,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 35,                     /* UNTIL  */
  YYSYMBOL_READ = 36,                      /* READ  */
  YYSYMBOL_WRITE = 37,                     /* WRITE  */
  YYSYMBOL_PROGRAM = 38,                   /* PROGRAM  */
  YYSYMBOL_T = 39,                         /* T  */
  YYSYMBOL_INVALID_KEYWORD = 40,           /* INVALID_KEYWORD  */
  YYSYMBOL_ERROR_INVALID_CHAR = 41,        /* ERROR_INVALID_CHAR  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_program_all = 43,               /* program_all  */
  YYSYMBOL_procedures = 44,                /* procedures  */
  YYSYMBOL_main = 45,                      /* main  */
  YYSYMBOL_commands = 46,                  /* commands  */
  YYSYMBOL_command = 47,                   /* command  */
  YYSYMBOL_proc_head = 48,                 /* proc_head  */
  YYSYMBOL_proc_call = 49,                 /* proc_call  */
  YYSYMBOL_declarations = 50,              /* declarations  */
  YYSYMBOL_args_decl = 51,                 /* args_decl  */
  YYSYMBOL_args = 52,                      /* args  */
  YYSYMBOL_expression = 53,                /* expression  */
  YYSYMBOL_condition = 54,                 /* condition  */
  YYSYMBOL_value = 55,                     /* value  */
  YYSYMBOL_identifier = 56                 /* identifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   207

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   170,   170,   185,   193,   201,   206,   212,   220,   224,
     230,   236,   248,   257,   268,   282,   285,   290,   296,   303,
     310,   316,   323,   330,   339,   345,   351,   358,   366,   372,
     380,   385,   392,   399,   406,   413,   421,   428,   435,   442,
     449,   456,   464,   469,   471,   476,   482
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "PLUS",
  "MINUS", "MULT", "DIV", "MOD", "EQ", "ASSIGN", "COMMA", "NEQ", "LESS",
  "LEQ", "MORE", "MEQ", "LSQ", "RSQ", "LBR", "RBR", "NUM", "PIDENTIFIER",
  "PROCEDURE", "IS", "IN", "END", "IF", "THEN", "ELSE", "ENDIF", "WHILE",
  "DO", "ENDWHILE", "REPEAT", "UNTIL", "READ", "WRITE", "PROGRAM", "T",
  "INVALID_KEYWORD", "ERROR_INVALID_CHAR", "$accept", "program_all",
  "procedures", "main", "commands", "command", "proc_head", "proc_call",
  "declarations", "args_decl", "args", "expression", "condition", "value",
  "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-28)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -28,    14,   -20,   -28,    -3,    15,   -28,    17,    19,   -15,
     -17,    12,    13,   165,     0,   -28,    28,    -7,   165,     6,
      34,    27,    31,    31,   165,    38,    31,    88,   -28,    58,
      53,    42,   165,   -28,   -10,   -28,   101,   165,    47,    36,
      51,   -28,    64,    54,    76,   -28,    52,   109,    80,    90,
     -28,   -28,   -28,    31,    77,   125,   -28,    73,   -28,   138,
     -28,    78,    84,   -28,    -5,   165,    31,    31,    31,    31,
      31,    31,   165,    31,   -28,   -28,   100,   199,    83,   -28,
     -28,   -28,   -28,   -28,    89,   -28,    11,   -28,   -28,   -28,
     -28,   -28,   -28,   146,   110,   -28,    31,    31,    31,    31,
      31,    94,   -28,   165,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   154,   -28
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     2,     0,     0,     0,
       0,     0,    22,     0,     0,    26,     0,     0,     0,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     9,     0,
       0,     0,     0,    27,     0,    18,     0,     0,     0,     0,
       0,    42,    44,     0,     0,    43,     0,     0,     0,     0,
       7,     8,    15,     0,    20,     0,    24,     0,     4,     0,
      23,     0,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,     0,    30,     0,     6,
      25,     3,    45,    46,     0,    19,     0,    36,    37,    38,
      40,    39,    41,     0,     0,    10,     0,     0,     0,     0,
       0,     0,    28,     0,    12,    13,    14,    31,    32,    33,
      34,    35,    21,     0,    11
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,   -28,   -28,   -16,   -27,   -28,   -28,   105,   -28,
     -28,   -28,   -22,     9,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,    27,    28,     8,    29,    14,    17,
      64,    76,    43,    44,    30
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      51,    46,    36,     4,    34,    15,    84,    12,    47,    51,
      13,    31,    56,    35,     3,    85,    55,    31,     5,     7,
      51,    59,    16,    45,    45,    32,    48,    45,    51,    57,
      20,    37,    51,    21,    12,    49,    10,    18,    22,     9,
     103,   104,    23,    11,    39,    24,    40,    25,    26,    86,
      33,    94,    41,    42,    45,    38,    93,    61,    62,    51,
      42,    52,    77,    53,    54,    60,    51,    45,    45,    45,
      45,    45,    45,    63,    45,    87,    88,    89,    90,    91,
      92,    39,    65,    74,    72,    66,    51,   113,    67,    68,
      69,    70,    71,    75,    78,    80,    82,    45,    45,    45,
      45,    45,    83,    95,   101,   107,   108,   109,   110,   111,
      21,   102,   112,   106,    50,    22,    19,     0,     0,    23,
       0,     0,    24,    21,    25,    26,     0,    58,    22,     0,
       0,    21,    23,     0,     0,    24,    22,    25,    26,     0,
      23,     0,     0,    24,    73,    25,    26,    21,     0,     0,
       0,    79,    22,     0,     0,     0,    23,     0,     0,    24,
      21,    25,    26,     0,    81,    22,     0,     0,    21,    23,
       0,     0,    24,    22,    25,    26,    21,    23,     0,   105,
      24,    22,    25,    26,   114,    23,     0,    21,    24,     0,
      25,    26,    22,     0,     0,     0,    23,     0,     0,    24,
       0,    25,    26,    96,    97,    98,    99,   100
};

static const yytype_int8 yycheck[] =
{
      27,    23,    18,    23,    11,    22,    11,    22,    24,    36,
      25,    11,    22,    20,     0,    20,    32,    11,    38,    22,
      47,    37,    39,    22,    23,    25,    25,    26,    55,    39,
      17,    25,    59,    22,    22,    26,    19,    25,    27,    24,
      29,    30,    31,    24,    17,    34,    19,    36,    37,    65,
      22,    73,    21,    22,    53,    21,    72,    21,    22,    86,
      22,     3,    53,    10,    22,    18,    93,    66,    67,    68,
      69,    70,    71,    22,    73,    66,    67,    68,    69,    70,
      71,    17,    28,     3,    32,     9,   113,   103,    12,    13,
      14,    15,    16,     3,    17,    22,    18,    96,    97,    98,
      99,   100,    18,     3,    21,    96,    97,    98,    99,   100,
      22,    22,    18,     3,    26,    27,    11,    -1,    -1,    31,
      -1,    -1,    34,    22,    36,    37,    -1,    26,    27,    -1,
      -1,    22,    31,    -1,    -1,    34,    27,    36,    37,    -1,
      31,    -1,    -1,    34,    35,    36,    37,    22,    -1,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      22,    36,    37,    -1,    26,    27,    -1,    -1,    22,    31,
      -1,    -1,    34,    27,    36,    37,    22,    31,    -1,    33,
      34,    27,    36,    37,    30,    31,    -1,    22,    34,    -1,
      36,    37,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    37,     4,     5,     6,     7,     8
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    44,     0,    23,    38,    45,    22,    48,    24,
      19,    24,    22,    25,    50,    22,    39,    51,    25,    50,
      17,    22,    27,    31,    34,    36,    37,    46,    47,    49,
      56,    11,    25,    22,    11,    20,    46,    25,    21,    17,
      19,    21,    22,    54,    55,    56,    54,    46,    56,    55,
      26,    47,     3,    10,    22,    46,    22,    39,    26,    46,
      18,    21,    22,    22,    52,    28,     9,    12,    13,    14,
      15,    16,    32,    35,     3,     3,    53,    55,    17,    26,
      22,    26,    18,    18,    11,    20,    46,    55,    55,    55,
      55,    55,    55,    46,    54,     3,     4,     5,     6,     7,
       8,    21,    22,    29,    30,    33,     3,    55,    55,    55,
      55,    55,    18,    46,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    47,    47,    47,    47,    48,    49,
      50,    50,    50,    50,    51,    51,    51,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    55,    55,    56,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     8,     7,     0,     6,     5,     2,     1,
       4,     7,     5,     5,     5,     2,     3,     3,     4,     4,
       3,     6,     1,     4,     3,     4,     1,     2,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program_all: procedures main  */
#line 170 "parser.ypp"
                             {
                    Program* program = new Program();
                    program->main = (yyvsp[0].mainPoint);
                    program->procedures = (yyvsp[-1].procAllPointer);
                    (yyval.programPointer)=program;
                    if(program->semantic()){
                        program->generateBB();
                        program->printBBs();
                        LowLevelProgram* lowProgram = new LowLevelProgram(program);
                        
                    }else{
                        std::cout<<"Kompilacja zakonczona niepowodzeniem";
                    }
                }
#line 1227 "parser.tab.cpp"
    break;

  case 3: /* procedures: procedures PROCEDURE proc_head IS declarations IN commands END  */
#line 185 "parser.ypp"
                                                                           {
                    ProcedureComplex* proc = new ProcedureComplex();
                    proc->head = (yyvsp[-5].procHeadPointer);
                    proc->comms = (yyvsp[-1].linkedPointer);
                    proc->decs = (yyvsp[-3].declarationPointer);
                    (yyvsp[-7].procAllPointer)->addProc(proc);
                    (yyval.procAllPointer)=(yyvsp[-7].procAllPointer);
                }
#line 1240 "parser.tab.cpp"
    break;

  case 4: /* procedures: procedures PROCEDURE proc_head IS IN commands END  */
#line 193 "parser.ypp"
                                                                {
                    Procedure* proc = new Procedure();
                    proc->head = (yyvsp[-4].procHeadPointer);
                    proc->comms = (yyvsp[-1].linkedPointer);
                    proc->decs=nullptr;
                    (yyvsp[-6].procAllPointer)->addProc(proc);
                    (yyval.procAllPointer)=(yyvsp[-6].procAllPointer);
                }
#line 1253 "parser.tab.cpp"
    break;

  case 5: /* procedures: %empty  */
#line 201 "parser.ypp"
                     {
                    ProceduresAll* proc = new ProceduresAll;
                    (yyval.procAllPointer)=proc;
                }
#line 1262 "parser.tab.cpp"
    break;

  case 6: /* main: PROGRAM IS declarations IN commands END  */
#line 206 "parser.ypp"
                                                    {
                    Main* main = new Main();
                    main->decs = (yyvsp[-3].declarationPointer);
                    main->comms = (yyvsp[-1].linkedPointer);
                    (yyval.mainPoint)=main;
                }
#line 1273 "parser.tab.cpp"
    break;

  case 7: /* main: PROGRAM IS IN commands END  */
#line 212 "parser.ypp"
                                         {
                    Main* main = new Main();
                    //Declaration* dec = new Declaration();
                    main->decs = nullptr;
                    main->comms = (yyvsp[-1].linkedPointer);
                    (yyval.mainPoint)=main;
                }
#line 1285 "parser.tab.cpp"
    break;

  case 8: /* commands: commands command  */
#line 220 "parser.ypp"
                             {
                    (yyvsp[-1].linkedPointer)->addInst((yyvsp[0].instPointer));
                    (yyval.linkedPointer) = (yyvsp[-1].linkedPointer);
                }
#line 1294 "parser.tab.cpp"
    break;

  case 9: /* commands: command  */
#line 224 "parser.ypp"
                      {
                    LinkedCommands *linkedCommand = new LinkedCommands();
                    linkedCommand->addInst((yyvsp[0].instPointer));
                    (yyval.linkedPointer) = linkedCommand;
                }
#line 1304 "parser.tab.cpp"
    break;

  case 10: /* command: identifier ASSIGN expression SEMICOLON  */
#line 230 "parser.ypp"
                                                   {
                    Assignment* assign = new Assignment();
                    assign->expression = (yyvsp[-1].exprPoint);
                    assign->identifier = (yyvsp[-3].identPointer);
                    (yyval.instPointer) = assign;
                }
#line 1315 "parser.tab.cpp"
    break;

  case 11: /* command: IF condition THEN commands ELSE commands ENDIF  */
#line 236 "parser.ypp"
                                                             {
                    Conditional *conditional = new Conditional();
                    Merger *merger = new Merger();
                    conditional->cond = (yyvsp[-5].condPoint);
                    conditional->nextIfTrue = (yyvsp[-3].linkedPointer)->getHead();
                    conditional->nextIfFalse = (yyvsp[-1].linkedPointer)->getHead();
                    
                    (yyvsp[-3].linkedPointer)->getTail()->next = merger;
                    (yyvsp[-1].linkedPointer)->getTail()->next = merger;
                    conditional->next = merger;
                    (yyval.instPointer) = conditional;
                }
#line 1332 "parser.tab.cpp"
    break;

  case 12: /* command: IF condition THEN commands ENDIF  */
#line 248 "parser.ypp"
                                               {
                    ConditionalSimple *simp = new ConditionalSimple();
                    simp->cond = (yyvsp[-3].condPoint);
                    Merger *merger = new Merger();
                    simp->nextIfTrue = (yyvsp[-1].linkedPointer)->getHead();
                    simp->next = merger;
                    (yyvsp[-1].linkedPointer)->getTail()->next = merger;
                    (yyval.instPointer) = simp;
                }
#line 1346 "parser.tab.cpp"
    break;

  case 13: /* command: WHILE condition DO commands ENDWHILE  */
#line 257 "parser.ypp"
                                                   {
                    ConditionalWhile *loop = new ConditionalWhile();
                    loop->cond = (yyvsp[-3].condPoint);
                    Merger *mergerEntry = new Merger();
                    Merger *mergerExit = new Merger();
                    mergerEntry->next = loop;
                    loop->nextIfTrue = (yyvsp[-1].linkedPointer)->getHead();
                    (yyvsp[-1].linkedPointer)->getTail()->next = mergerEntry;
                    loop->next = mergerExit;
                    (yyval.instPointer) = mergerEntry;
                }
#line 1362 "parser.tab.cpp"
    break;

  case 14: /* command: REPEAT commands UNTIL condition SEMICOLON  */
#line 268 "parser.ypp"
                                                        {
                    ConditionalRepeat *loop = new ConditionalRepeat();
                    Merger *mergerEntry = new Merger();
                    Merger *mergerExit = new Merger();
                    loop->cond = (yyvsp[-1].condPoint);
                    mergerEntry->next = (yyvsp[-3].linkedPointer)->getHead();
                    (yyvsp[-3].linkedPointer)->getTail()->next = loop;
                    // to keep walking on linked list simple. It will be ignored in next steps
                    loop->next = mergerExit;
                    //loop is until, so goes on if condition isnt met
                    loop->nextIfTrue = mergerExit;
                    loop->nextIfFalse = mergerEntry;
                    (yyval.instPointer) = mergerEntry;
                }
#line 1381 "parser.tab.cpp"
    break;

  case 15: /* command: proc_call SEMICOLON  */
#line 282 "parser.ypp"
                                  {
                    (yyval.instPointer) = (yyvsp[-1].callPointer);
                }
#line 1389 "parser.tab.cpp"
    break;

  case 16: /* command: READ identifier SEMICOLON  */
#line 285 "parser.ypp"
                                        {
                    Read* reader = new Read();
                    reader->ident = (yyvsp[-1].identPointer);
                    (yyval.instPointer)=reader;
                }
#line 1399 "parser.tab.cpp"
    break;

  case 17: /* command: WRITE value SEMICOLON  */
#line 290 "parser.ypp"
                                    {
                    Write* writer = new Write();
                    writer->val = (yyvsp[-1].valuePointer);
                    (yyval.instPointer) = writer;
                }
#line 1409 "parser.tab.cpp"
    break;

  case 18: /* proc_head: PIDENTIFIER LBR args_decl RBR  */
#line 296 "parser.ypp"
                                          {
                    Procedure_head* head = new Procedure_head();
                    head->args = (yyvsp[-1].argPointer);
                    head->name = *(yyvsp[-3].ptoken).str;
                    (yyval.procHeadPointer)=head;
                }
#line 1420 "parser.tab.cpp"
    break;

  case 19: /* proc_call: PIDENTIFIER LBR args RBR  */
#line 303 "parser.ypp"
                                     {
                    Procedure_call* call = new Procedure_call();
                    call->args = (yyvsp[-1].argPointer);
                    call->name = *(yyvsp[-3].ptoken).str;
                    (yyval.callPointer)=call;
                }
#line 1431 "parser.tab.cpp"
    break;

  case 20: /* declarations: declarations COMMA PIDENTIFIER  */
#line 310 "parser.ypp"
                                             {
                    Identifier* ident = new Identifier();
                    ident->val = *(yyvsp[0].ptoken).str;
                    (yyvsp[-2].declarationPointer)->declare(ident);
                    (yyval.declarationPointer)=(yyvsp[-2].declarationPointer);
                }
#line 1442 "parser.tab.cpp"
    break;

  case 21: /* declarations: declarations COMMA PIDENTIFIER LSQ NUM RSQ  */
#line 316 "parser.ypp"
                                                           {
                    IndentifierArrNumber* ident = new IndentifierArrNumber();
                    ident->address = std::to_string((yyvsp[-1].ptoken).val);
                    ident->val = *(yyvsp[-3].ptoken).str;
                    (yyvsp[-5].declarationPointer)->declare(ident);
                    (yyval.declarationPointer)=(yyvsp[-5].declarationPointer);
                }
#line 1454 "parser.tab.cpp"
    break;

  case 22: /* declarations: PIDENTIFIER  */
#line 323 "parser.ypp"
                            {
                    Identifier* ident = new Identifier();
                    ident->val = *(yyvsp[0].ptoken).str;
                    Declaration* dec = new Declaration();
                    dec->declare(ident);
                    (yyval.declarationPointer)=dec;
                }
#line 1466 "parser.tab.cpp"
    break;

  case 23: /* declarations: PIDENTIFIER LSQ NUM RSQ  */
#line 330 "parser.ypp"
                                        {
                    IndentifierArrNumber* ident = new IndentifierArrNumber();
                    ident->address = std::to_string((yyvsp[-1].ptoken).val);
                    ident->val = *(yyvsp[-3].ptoken).str;
                    Declaration* dec = new Declaration();
                    dec->declare(ident);
                    (yyval.declarationPointer)=dec;
                }
#line 1479 "parser.tab.cpp"
    break;

  case 24: /* args_decl: args_decl COMMA PIDENTIFIER  */
#line 339 "parser.ypp"
                                        {
                    Identifier* ident = new Identifier();
                    ident->val = *(yyvsp[0].ptoken).str;
                    (yyvsp[-2].argPointer)->addArg(ident);
                    (yyval.argPointer) = (yyvsp[-2].argPointer);
                }
#line 1490 "parser.tab.cpp"
    break;

  case 25: /* args_decl: args_decl COMMA T PIDENTIFIER  */
#line 345 "parser.ypp"
                                            {
                    IndentifierArrNumber* ident = new IndentifierArrNumber();
                    ident->val = *(yyvsp[0].ptoken).str;
                    (yyvsp[-3].argPointer)->addArg(ident);
                    (yyval.argPointer) = (yyvsp[-3].argPointer);
                }
#line 1501 "parser.tab.cpp"
    break;

  case 26: /* args_decl: PIDENTIFIER  */
#line 351 "parser.ypp"
                          {
                    Identifier* ident = new Identifier();
                    ident->val = *(yyvsp[0].ptoken).str;
                    Args* args = new Args();
                    args->addArg(ident);
                    (yyval.argPointer) = args;
                }
#line 1513 "parser.tab.cpp"
    break;

  case 27: /* args_decl: T PIDENTIFIER  */
#line 358 "parser.ypp"
                            {
                    IndentifierArrNumber* ident = new IndentifierArrNumber();
                    ident->val = *(yyvsp[0].ptoken).str;
                    Args* args = new Args();
                    args->addArg(ident);
                    (yyval.argPointer) = args;
                }
#line 1525 "parser.tab.cpp"
    break;

  case 28: /* args: args COMMA PIDENTIFIER  */
#line 366 "parser.ypp"
                                   {
                    Identifier* ident = new Identifier();
                    ident->val = *(yyvsp[0].ptoken).str;
                    (yyvsp[-2].argPointer)->addArg(ident);
                    (yyval.argPointer)=(yyvsp[-2].argPointer);
                }
#line 1536 "parser.tab.cpp"
    break;

  case 29: /* args: PIDENTIFIER  */
#line 372 "parser.ypp"
                          {
                    Identifier* ident = new Identifier();
                    ident->val = *(yyvsp[0].ptoken).str;
                    Args* args = new Args();
                    args->addArg(ident);
                    (yyval.argPointer)=args;
                }
#line 1548 "parser.tab.cpp"
    break;

  case 30: /* expression: value  */
#line 380 "parser.ypp"
                  {
                ExprSimple* simp = new ExprSimple();
                simp->left = (yyvsp[0].valuePointer);
                (yyval.exprPoint) = simp;
            }
#line 1558 "parser.tab.cpp"
    break;

  case 31: /* expression: value PLUS value  */
#line 385 "parser.ypp"
                               {
                ExprComplex* comp = new ExprComplex();
                comp->left = (yyvsp[-2].valuePointer);
                comp->right = (yyvsp[0].valuePointer);
                comp->operand = "+";
                (yyval.exprPoint) = comp;
            }
#line 1570 "parser.tab.cpp"
    break;

  case 32: /* expression: value MINUS value  */
#line 392 "parser.ypp"
                                {
                ExprComplex* comp = new ExprComplex();
                comp->left = (yyvsp[-2].valuePointer);
                comp->right = (yyvsp[0].valuePointer);
                comp->operand = "-";
                (yyval.exprPoint) = comp;
            }
#line 1582 "parser.tab.cpp"
    break;

  case 33: /* expression: value MULT value  */
#line 399 "parser.ypp"
                               {
                ExprComplex* comp = new ExprComplex();
                comp->left = (yyvsp[-2].valuePointer);
                comp->right = (yyvsp[0].valuePointer);
                comp->operand = "*";
                (yyval.exprPoint) = comp;
            }
#line 1594 "parser.tab.cpp"
    break;

  case 34: /* expression: value DIV value  */
#line 406 "parser.ypp"
                              {
                ExprComplex* comp = new ExprComplex();
                comp->left = (yyvsp[-2].valuePointer);
                comp->right = (yyvsp[0].valuePointer);
                comp->operand = "/";
                (yyval.exprPoint) = comp;
            }
#line 1606 "parser.tab.cpp"
    break;

  case 35: /* expression: value MOD value  */
#line 413 "parser.ypp"
                              {
                ExprComplex* comp = new ExprComplex();
                comp->left = (yyvsp[-2].valuePointer);
                comp->right = (yyvsp[0].valuePointer);
                comp->operand = "%";
                (yyval.exprPoint) = comp;
            }
#line 1618 "parser.tab.cpp"
    break;

  case 36: /* condition: value EQ value  */
#line 421 "parser.ypp"
                           {
                Condition* cond = new Condition();
                cond->leftVal = (yyvsp[-2].valuePointer);
                cond->rightVal = (yyvsp[0].valuePointer);
                cond->operand = "=";
                (yyval.condPoint) = cond;
            }
#line 1630 "parser.tab.cpp"
    break;

  case 37: /* condition: value NEQ value  */
#line 428 "parser.ypp"
                              {
                Condition* cond = new Condition();
                cond->leftVal = (yyvsp[-2].valuePointer);
                cond->rightVal = (yyvsp[0].valuePointer);
                cond->operand = "!=";
                (yyval.condPoint) = cond;
            }
#line 1642 "parser.tab.cpp"
    break;

  case 38: /* condition: value LESS value  */
#line 435 "parser.ypp"
                               {
                Condition* cond = new Condition();
                cond->leftVal = (yyvsp[-2].valuePointer);
                cond->rightVal = (yyvsp[0].valuePointer);
                cond->operand = "<";
                (yyval.condPoint) = cond;
            }
#line 1654 "parser.tab.cpp"
    break;

  case 39: /* condition: value MORE value  */
#line 442 "parser.ypp"
                               {
                Condition* cond = new Condition();
                cond->leftVal = (yyvsp[-2].valuePointer);
                cond->rightVal = (yyvsp[0].valuePointer);
                cond->operand = ">";
                (yyval.condPoint) = cond;
            }
#line 1666 "parser.tab.cpp"
    break;

  case 40: /* condition: value LEQ value  */
#line 449 "parser.ypp"
                              {
                Condition* cond = new Condition();
                cond->leftVal = (yyvsp[-2].valuePointer);
                cond->rightVal = (yyvsp[0].valuePointer);
                cond->operand = "<=";
                (yyval.condPoint) = cond;
            }
#line 1678 "parser.tab.cpp"
    break;

  case 41: /* condition: value MEQ value  */
#line 456 "parser.ypp"
                              {
                Condition* cond = new Condition();
                cond->leftVal = (yyvsp[-2].valuePointer);
                cond->rightVal = (yyvsp[0].valuePointer);
                cond->operand = ">=";
                (yyval.condPoint) = cond;
            }
#line 1690 "parser.tab.cpp"
    break;

  case 42: /* value: NUM  */
#line 464 "parser.ypp"
                {
                Number* num = new Number();
                num->val = std::to_string((yyvsp[0].ptoken).val);
                (yyval.valuePointer)=num;
            }
#line 1700 "parser.tab.cpp"
    break;

  case 43: /* value: identifier  */
#line 469 "parser.ypp"
                        { (yyval.valuePointer) = (yyvsp[0].identPointer); }
#line 1706 "parser.tab.cpp"
    break;

  case 44: /* identifier: PIDENTIFIER  */
#line 471 "parser.ypp"
                        {
                    Identifier* ident = new Identifier();
                    ident->val = *(yyvsp[0].ptoken).str;
                    (yyval.identPointer)=ident;
                }
#line 1716 "parser.tab.cpp"
    break;

  case 45: /* identifier: PIDENTIFIER LSQ NUM RSQ  */
#line 476 "parser.ypp"
                                      {
                    IndentifierArrNumber* ident = new IndentifierArrNumber();
                    ident->val = *(yyvsp[-3].ptoken).str;
                    ident->address = std::to_string((yyvsp[-1].ptoken).val);
                    (yyval.identPointer) = ident;
                }
#line 1727 "parser.tab.cpp"
    break;

  case 46: /* identifier: PIDENTIFIER LSQ PIDENTIFIER RSQ  */
#line 482 "parser.ypp"
                                              {
                    IndentifierArrPid* ident = new IndentifierArrPid();
                    ident->val = *(yyvsp[-3].ptoken).str;
                    ident->address = *(yyvsp[-1].ptoken).str;
                    (yyval.identPointer) = ident;
                }
#line 1738 "parser.tab.cpp"
    break;


#line 1742 "parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 489 "parser.ypp"


int yyerror(std::string s) {
    std::cerr << "Error: " << s << std::endl;
}

int main() {
    yyparse();
    return 0;
}
