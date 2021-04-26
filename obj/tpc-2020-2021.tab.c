/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/tpc-2020-2021.y"

/* tpc-2020-2021.y */
/* Syntaxe du TPC pour le projet d'analyse syntaxique de 2020-2021*/
/* Projet d'analyse synthaxique Arthur PAIRAUD*/
#include <stdio.h>
#include "../src/abstract-tree.h"
#include "../src/decl-var.h"
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#define YYERROR_VERBOSE 1
extern FILE *yyin;
int yyparse();
int yylex();
int yyerror(const char *s);
Node* abs_tree;
extern char line[200];
extern int yylineno;
extern int column;
extern char* yytext;

#line 93 "./obj/tpc-2020-2021.tab.c"

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

#include "tpc-2020-2021.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_IDENT = 5,                      /* IDENT  */
  YYSYMBOL_PRINT = 6,                      /* PRINT  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_ORDER = 12,                     /* ORDER  */
  YYSYMBOL_ADDSUB = 13,                    /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 14,                   /* DIVSTAR  */
  YYSYMBOL_NUM = 15,                       /* NUM  */
  YYSYMBOL_CHARACTER = 16,                 /* CHARACTER  */
  YYSYMBOL_TYPE = 17,                      /* TYPE  */
  YYSYMBOL_VOID = 18,                      /* VOID  */
  YYSYMBOL_READE = 19,                     /* READE  */
  YYSYMBOL_READC = 20,                     /* READC  */
  YYSYMBOL_STRUCT = 21,                    /* STRUCT  */
  YYSYMBOL_22_ = 22,                       /* ')'  */
  YYSYMBOL_23_ = 23,                       /* ';'  */
  YYSYMBOL_24_ = 24,                       /* '{'  */
  YYSYMBOL_25_ = 25,                       /* '}'  */
  YYSYMBOL_26_ = 26,                       /* ','  */
  YYSYMBOL_27_ = 27,                       /* '('  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* '!'  */
  YYSYMBOL_30_ = 30,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_Prog = 32,                      /* Prog  */
  YYSYMBOL_TypesVars = 33,                 /* TypesVars  */
  YYSYMBOL_Type = 34,                      /* Type  */
  YYSYMBOL_DeclChamps = 35,                /* DeclChamps  */
  YYSYMBOL_Declarateurs = 36,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 37,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 38,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 39,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 40,                /* Parametres  */
  YYSYMBOL_ListTypVar = 41,                /* ListTypVar  */
  YYSYMBOL_Corps = 42,                     /* Corps  */
  YYSYMBOL_DeclVars = 43,                  /* DeclVars  */
  YYSYMBOL_SuiteInstr = 44,                /* SuiteInstr  */
  YYSYMBOL_Instr = 45,                     /* Instr  */
  YYSYMBOL_Exp = 46,                       /* Exp  */
  YYSYMBOL_TB = 47,                        /* TB  */
  YYSYMBOL_FB = 48,                        /* FB  */
  YYSYMBOL_M = 49,                         /* M  */
  YYSYMBOL_E = 50,                         /* E  */
  YYSYMBOL_T = 51,                         /* T  */
  YYSYMBOL_F = 52,                         /* F  */
  YYSYMBOL_LValue = 53,                    /* LValue  */
  YYSYMBOL_Arguments = 54,                 /* Arguments  */
  YYSYMBOL_ListExp = 55                    /* ListExp  */
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
typedef yytype_uint8 yy_state_t;

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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYLAST   169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,    29,     2,     2,     2,     2,     2,     2,
      27,    22,     2,     2,    26,     2,    30,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,    25,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    48,    48,    56,    61,    67,    70,    73,    79,    84,
      91,    95,   100,   104,   109,   116,   121,   128,   132,   138,
     143,   148,   155,   160,   165,   169,   174,   179,   183,   187,
     191,   196,   203,   208,   211,   215,   218,   221,   225,   230,
     234,   239,   243,   248,   252,   257,   261,   266,   270,   275,
     279,   283,   287,   290,   293,   296,   299,   305,   308,   315,
     318,   323,   328
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "IDENT",
  "PRINT", "WHILE", "RETURN", "OR", "AND", "EQ", "ORDER", "ADDSUB",
  "DIVSTAR", "NUM", "CHARACTER", "TYPE", "VOID", "READE", "READC",
  "STRUCT", "')'", "';'", "'{'", "'}'", "','", "'('", "'='", "'!'", "'.'",
  "$accept", "Prog", "TypesVars", "Type", "DeclChamps", "Declarateurs",
  "DeclFoncts", "DeclFonct", "EnTeteFonct", "Parametres", "ListTypVar",
  "Corps", "DeclVars", "SuiteInstr", "Instr", "Exp", "TB", "FB", "M", "E",
  "T", "F", "LValue", "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    41,    59,   123,   125,    44,    40,    61,    33,
      46
};
#endif

#define YYPACT_NINF (-116)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -116,    15,    24,  -116,  -116,     4,    11,    33,    61,  -116,
      19,     6,    35,    21,    34,    60,    69,  -116,  -116,  -116,
      99,    49,    99,  -116,    78,  -116,    21,    59,  -116,    86,
      70,    72,    98,   -11,    85,  -116,    98,    48,  -116,  -116,
      59,  -116,    67,    98,  -116,  -116,    76,    96,    88,   104,
     105,     7,   123,  -116,  -116,   107,   110,  -116,  -116,  -116,
     123,   123,  -116,    -4,   130,   131,   129,   132,   133,  -116,
     115,   139,  -116,   101,  -116,   123,   123,   141,   123,   123,
    -116,     9,  -116,  -116,   143,   144,    81,     2,  -116,   123,
    -116,   123,   123,   123,   123,   123,   123,  -116,  -116,    22,
     142,   134,   127,  -116,    28,    30,  -116,   135,   136,  -116,
    -116,   130,   131,   129,   132,   133,  -116,    12,   106,  -116,
     123,   137,   106,   138,   140,  -116,   150,   142,  -116,  -116,
    -116,  -116,   106,  -116
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     6,     0,     0,     0,     2,    13,
       0,     0,     7,    11,     0,     0,     0,    12,    23,    14,
       0,     0,     0,     3,     0,     7,     0,    25,    17,     0,
       0,    18,     0,     0,     0,    10,     0,     0,    20,    16,
       0,    11,     0,     0,     4,    15,     0,     0,    57,     0,
       0,     0,     0,    53,    54,     0,     0,    37,    25,    21,
       0,     0,    24,     0,    39,    41,    43,    45,    47,    49,
      55,     0,     9,     0,    22,     0,    60,     0,     0,     0,
      35,     0,    55,    50,     0,     0,     0,     0,    51,     0,
      33,     0,     0,     0,     0,     0,     0,    19,     8,     0,
      62,     0,    59,    58,     0,     0,    34,     0,     0,    36,
      52,    38,    40,    42,    44,    46,    48,     0,     0,    56,
       0,     0,     0,     0,     0,    26,    30,    61,    29,    32,
      27,    28,     0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -116,  -116,  -116,     0,  -116,    26,  -116,   147,  -116,   145,
    -116,  -116,  -116,   108,  -115,   -50,    73,    68,    77,    71,
      74,   -48,   -37,  -116,  -116
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    29,    33,    14,     8,     9,    10,    30,
      31,    19,    27,    37,    62,    63,    64,    65,    66,    67,
      68,    69,    82,   101,   102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      70,    81,     7,   126,    83,    89,    43,   129,    16,    11,
      87,    89,    48,    88,    44,     3,    12,   133,    89,    90,
      52,    89,    53,    54,   110,    99,   100,    36,   104,   105,
      80,    89,   106,    20,    60,   125,    61,    89,    13,    89,
      71,     4,     5,    18,   118,     6,   117,   116,    22,    70,
     121,    47,   122,    48,    49,    50,    51,    23,    42,    21,
      24,    52,    46,    53,    54,    25,    32,    55,    56,    73,
     127,    57,    58,    59,    26,    60,     4,    61,     4,     5,
      15,    70,    15,    35,    47,    70,    48,    49,    50,    51,
      72,    38,    39,    24,    52,    70,    53,    54,    40,    74,
      55,    56,    24,    41,    57,    58,   109,    45,    60,    47,
      61,    48,    49,    50,    51,    76,     4,    28,    77,    52,
      15,    53,    54,    75,    98,    55,    56,    24,    48,    57,
      58,    78,    79,    60,    84,    61,    52,    85,    53,    54,
      91,    93,    92,    96,    97,    94,   103,    95,   107,   108,
      60,    89,    61,   120,   132,    17,   119,   123,   124,   112,
     128,   130,   111,   131,   114,     0,    86,    34,   115,   113
};

static const yytype_int16 yycheck[] =
{
      37,    51,     2,   118,    52,     9,    17,   122,     8,     5,
      60,     9,     5,    61,    25,     0,     5,   132,     9,    23,
      13,     9,    15,    16,    22,    75,    76,    27,    78,    79,
      23,     9,    23,    27,    27,    23,    29,     9,     5,     9,
      40,    17,    18,    24,    22,    21,    96,    95,    27,    86,
      22,     3,    22,     5,     6,     7,     8,    23,    32,    24,
      26,    13,    36,    15,    16,     5,    17,    19,    20,    43,
     120,    23,    24,    25,     5,    27,    17,    29,    17,    18,
      21,   118,    21,     5,     3,   122,     5,     6,     7,     8,
      23,     5,    22,    26,    13,   132,    15,    16,    26,    23,
      19,    20,    26,     5,    23,    24,    25,    22,    27,     3,
      29,     5,     6,     7,     8,    27,    17,    18,    30,    13,
      21,    15,    16,    27,    23,    19,    20,    26,     5,    23,
      24,    27,    27,    27,    27,    29,    13,    27,    15,    16,
      10,    12,    11,    28,     5,    13,     5,    14,     5,     5,
      27,     9,    29,    26,     4,     8,    22,    22,    22,    91,
      23,    23,    89,    23,    93,    -1,    58,    22,    94,    92
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    32,    33,     0,    17,    18,    21,    34,    37,    38,
      39,     5,     5,     5,    36,    21,    34,    38,    24,    42,
      27,    24,    27,    23,    26,     5,     5,    43,    18,    34,
      40,    41,    17,    35,    40,     5,    34,    44,     5,    22,
      26,     5,    36,    17,    25,    22,    36,     3,     5,     6,
       7,     8,    13,    15,    16,    19,    20,    23,    24,    25,
      27,    29,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    34,    23,    36,    23,    27,    27,    30,    27,    27,
      23,    46,    53,    52,    27,    27,    44,    46,    52,     9,
      23,    10,    11,    12,    13,    14,    28,     5,    23,    46,
      46,    54,    55,     5,    46,    46,    23,     5,     5,    25,
      22,    47,    48,    49,    50,    51,    52,    46,    22,    22,
      26,    22,    22,    22,    22,    23,    45,    46,    23,    45,
      23,    23,     4,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    33,    34,    34,    35,    35,
      36,    36,    37,    37,    38,    39,    39,    40,    40,    41,
      41,    42,    43,    43,    44,    44,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    46,    46,
      47,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    52,    52,    52,    52,    52,    53,    53,    54,
      54,    55,    55
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     6,     0,     1,     2,     4,     3,
       3,     1,     2,     1,     2,     5,     5,     1,     1,     4,
       2,     4,     4,     0,     2,     0,     4,     5,     5,     5,
       5,     7,     5,     2,     3,     2,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     2,     3,     1,     1,     1,     4,     1,     3,     1,
       0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
  case 2: /* Prog: TypesVars DeclFoncts  */
#line 48 "src/tpc-2020-2021.y"
                                                    {   (yyval.tree) = makeNode(Prog);
                                                        addChild((yyval.tree), (yyvsp[-1].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                        make_Symbole_table((yyval.tree));
                                                        abs_tree = (yyval.tree);
                                                    }
#line 1237 "./obj/tpc-2020-2021.tab.c"
    break;

  case 3: /* TypesVars: TypesVars Type Declarateurs ';'  */
#line 56 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-3].tree); 
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyvsp[-2].tree), (yyvsp[-1].tree));
                                                    }
#line 1247 "./obj/tpc-2020-2021.tab.c"
    break;

  case 4: /* TypesVars: TypesVars STRUCT IDENT '{' DeclChamps '}'  */
#line 61 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-5].tree);
                                                        addChild((yyval.tree), (yyvsp[-4].tree));
                                                        strcpy((yyvsp[-4].tree)->u.identifier, (yyvsp[-3].tree)->u.identifier);
                                                        addChild((yyvsp[-4].tree), (yyvsp[-1].tree));
                                                    }
#line 1258 "./obj/tpc-2020-2021.tab.c"
    break;

  case 5: /* TypesVars: %empty  */
#line 67 "src/tpc-2020-2021.y"
                                                    { (yyval.tree) = makeNode(TypesVars); }
#line 1264 "./obj/tpc-2020-2021.tab.c"
    break;

  case 6: /* Type: TYPE  */
#line 70 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1272 "./obj/tpc-2020-2021.tab.c"
    break;

  case 7: /* Type: STRUCT IDENT  */
#line 73 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree); 
                                                        strcpy((yyvsp[-1].tree)->u.identifier, (yyvsp[0].tree)->u.identifier);
                                                    }
#line 1281 "./obj/tpc-2020-2021.tab.c"
    break;

  case 8: /* DeclChamps: DeclChamps TYPE Declarateurs ';'  */
#line 79 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-3].tree); 
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyvsp[-2].tree), (yyvsp[-1].tree));  
                                                    }
#line 1291 "./obj/tpc-2020-2021.tab.c"
    break;

  case 9: /* DeclChamps: TYPE Declarateurs ';'  */
#line 84 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(DeclChamps); 
                                                        addChild((yyval.tree), (yyvsp[-2].tree)); 
                                                        addChild((yyvsp[-2].tree), (yyvsp[-1].tree));
                                                    }
#line 1301 "./obj/tpc-2020-2021.tab.c"
    break;

  case 10: /* Declarateurs: Declarateurs ',' IDENT  */
#line 91 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-2].tree); 
                                                        addSibling((yyval.tree), (yyvsp[0].tree));  
                                                    }
#line 1310 "./obj/tpc-2020-2021.tab.c"
    break;

  case 11: /* Declarateurs: IDENT  */
#line 95 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);  
                                                    }
#line 1318 "./obj/tpc-2020-2021.tab.c"
    break;

  case 12: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 100 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);  
                                                        addSibling((yyval.tree), (yyvsp[0].tree)); 
                                                    }
#line 1327 "./obj/tpc-2020-2021.tab.c"
    break;

  case 13: /* DeclFoncts: DeclFonct  */
#line 104 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);  
                                                    }
#line 1335 "./obj/tpc-2020-2021.tab.c"
    break;

  case 14: /* DeclFonct: EnTeteFonct Corps  */
#line 109 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(DeclFonct); 
                                                        addChild((yyval.tree), (yyvsp[-1].tree));  
                                                        addChild((yyval.tree), (yyvsp[0].tree)); 
                                                    }
#line 1345 "./obj/tpc-2020-2021.tab.c"
    break;

  case 15: /* EnTeteFonct: Type IDENT '(' Parametres ')'  */
#line 116 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-4].tree);  
                                                        addChild((yyval.tree), (yyvsp[-3].tree)); 
                                                        addChild((yyval.tree), (yyvsp[-1].tree)); 
                                                    }
#line 1355 "./obj/tpc-2020-2021.tab.c"
    break;

  case 16: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 121 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-4].tree);  
                                                        addChild((yyval.tree), (yyvsp[-3].tree)); 
                                                        addChild((yyval.tree), (yyvsp[-1].tree)); 
                                                    }
#line 1365 "./obj/tpc-2020-2021.tab.c"
    break;

  case 17: /* Parametres: VOID  */
#line 128 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(Parametres);
                                                        addChild((yyval.tree), (yyvsp[0].tree));  
                                                    }
#line 1374 "./obj/tpc-2020-2021.tab.c"
    break;

  case 18: /* Parametres: ListTypVar  */
#line 132 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(Parametres);
                                                        addChild((yyval.tree), (yyvsp[0].tree));  
                                                    }
#line 1383 "./obj/tpc-2020-2021.tab.c"
    break;

  case 19: /* ListTypVar: ListTypVar ',' Type IDENT  */
#line 138 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-3].tree);  
                                                        addSibling((yyval.tree), (yyvsp[-1].tree));  
                                                        addChild((yyvsp[-1].tree), (yyvsp[0].tree));  
                                                    }
#line 1393 "./obj/tpc-2020-2021.tab.c"
    break;

  case 20: /* ListTypVar: Type IDENT  */
#line 143 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);  
                                                        addChild((yyvsp[-1].tree), (yyvsp[0].tree));    
                                                    }
#line 1402 "./obj/tpc-2020-2021.tab.c"
    break;

  case 21: /* Corps: '{' DeclVars SuiteInstr '}'  */
#line 148 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(Corps); 
                                                        addChild((yyval.tree), (yyvsp[-2].tree));  
                                                        addChild((yyval.tree), (yyvsp[-1].tree));    
                                                    }
#line 1412 "./obj/tpc-2020-2021.tab.c"
    break;

  case 22: /* DeclVars: DeclVars Type Declarateurs ';'  */
#line 155 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-3].tree);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));  
                                                        addChild((yyvsp[-2].tree), (yyvsp[-1].tree));    
                                                    }
#line 1422 "./obj/tpc-2020-2021.tab.c"
    break;

  case 23: /* DeclVars: %empty  */
#line 160 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(DeclVars);    
                                                    }
#line 1430 "./obj/tpc-2020-2021.tab.c"
    break;

  case 24: /* SuiteInstr: SuiteInstr Instr  */
#line 165 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[0].tree));   
                                                    }
#line 1439 "./obj/tpc-2020-2021.tab.c"
    break;

  case 25: /* SuiteInstr: %empty  */
#line 169 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(SuiteInstr);    
                                                    }
#line 1447 "./obj/tpc-2020-2021.tab.c"
    break;

  case 26: /* Instr: LValue '=' Exp ';'  */
#line 174 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(Asignment); 
                                                        addChild((yyval.tree), (yyvsp[-3].tree));
                                                        addChild((yyval.tree), (yyvsp[-1].tree));   
                                                    }
#line 1457 "./obj/tpc-2020-2021.tab.c"
    break;

  case 27: /* Instr: READE '(' IDENT ')' ';'  */
#line 179 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-4].tree);
                                                        addChild((yyvsp[-4].tree), (yyvsp[-2].tree));   
                                                    }
#line 1466 "./obj/tpc-2020-2021.tab.c"
    break;

  case 28: /* Instr: READC '(' IDENT ')' ';'  */
#line 183 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-4].tree);
                                                        addChild((yyvsp[-4].tree), (yyvsp[-2].tree));   
                                                    }
#line 1475 "./obj/tpc-2020-2021.tab.c"
    break;

  case 29: /* Instr: PRINT '(' Exp ')' ';'  */
#line 187 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-4].tree);
                                                        addChild((yyvsp[-4].tree), (yyvsp[-2].tree));   
                                                    }
#line 1484 "./obj/tpc-2020-2021.tab.c"
    break;

  case 30: /* Instr: IF '(' Exp ')' Instr  */
#line 191 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-4].tree);
                                                        addChild((yyvsp[-4].tree), (yyvsp[-2].tree));  
                                                        addChild((yyvsp[-4].tree), (yyvsp[0].tree)); 
                                                    }
#line 1494 "./obj/tpc-2020-2021.tab.c"
    break;

  case 31: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 196 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-6].tree);
                                                        addChild((yyvsp[-6].tree), (yyvsp[-4].tree));  
                                                        addChild((yyvsp[-6].tree), (yyvsp[-2].tree));
                                                        addChild((yyvsp[-6].tree), (yyvsp[-1].tree));
                                                        addChild((yyvsp[-1].tree), (yyvsp[0].tree)); 
                                                    }
#line 1506 "./obj/tpc-2020-2021.tab.c"
    break;

  case 32: /* Instr: WHILE '(' Exp ')' Instr  */
#line 203 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-4].tree);
                                                        addChild((yyvsp[-4].tree), (yyvsp[-2].tree));  
                                                        addChild((yyvsp[-4].tree), (yyvsp[0].tree)); 
                                                    }
#line 1516 "./obj/tpc-2020-2021.tab.c"
    break;

  case 33: /* Instr: Exp ';'  */
#line 208 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree); 
                                                    }
#line 1524 "./obj/tpc-2020-2021.tab.c"
    break;

  case 34: /* Instr: RETURN Exp ';'  */
#line 211 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-2].tree);
                                                        addChild((yyval.tree), (yyvsp[-1].tree));
                                                    }
#line 1533 "./obj/tpc-2020-2021.tab.c"
    break;

  case 35: /* Instr: RETURN ';'  */
#line 215 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                    }
#line 1541 "./obj/tpc-2020-2021.tab.c"
    break;

  case 36: /* Instr: '{' SuiteInstr '}'  */
#line 218 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                    }
#line 1549 "./obj/tpc-2020-2021.tab.c"
    break;

  case 37: /* Instr: ';'  */
#line 221 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(Instr);
                                                    }
#line 1557 "./obj/tpc-2020-2021.tab.c"
    break;

  case 38: /* Exp: Exp OR TB  */
#line 225 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1567 "./obj/tpc-2020-2021.tab.c"
    break;

  case 39: /* Exp: TB  */
#line 230 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1575 "./obj/tpc-2020-2021.tab.c"
    break;

  case 40: /* TB: TB AND FB  */
#line 234 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1585 "./obj/tpc-2020-2021.tab.c"
    break;

  case 41: /* TB: FB  */
#line 239 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1593 "./obj/tpc-2020-2021.tab.c"
    break;

  case 42: /* FB: FB EQ M  */
#line 243 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1603 "./obj/tpc-2020-2021.tab.c"
    break;

  case 43: /* FB: M  */
#line 248 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1611 "./obj/tpc-2020-2021.tab.c"
    break;

  case 44: /* M: M ORDER E  */
#line 252 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1621 "./obj/tpc-2020-2021.tab.c"
    break;

  case 45: /* M: E  */
#line 257 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1629 "./obj/tpc-2020-2021.tab.c"
    break;

  case 46: /* E: E ADDSUB T  */
#line 261 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1639 "./obj/tpc-2020-2021.tab.c"
    break;

  case 47: /* E: T  */
#line 266 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1647 "./obj/tpc-2020-2021.tab.c"
    break;

  case 48: /* T: T DIVSTAR F  */
#line 270 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1657 "./obj/tpc-2020-2021.tab.c"
    break;

  case 49: /* T: F  */
#line 275 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1665 "./obj/tpc-2020-2021.tab.c"
    break;

  case 50: /* F: ADDSUB F  */
#line 279 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1674 "./obj/tpc-2020-2021.tab.c"
    break;

  case 51: /* F: '!' F  */
#line 283 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(Not);
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1683 "./obj/tpc-2020-2021.tab.c"
    break;

  case 52: /* F: '(' Exp ')'  */
#line 287 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-1].tree);
                                                    }
#line 1691 "./obj/tpc-2020-2021.tab.c"
    break;

  case 53: /* F: NUM  */
#line 290 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1699 "./obj/tpc-2020-2021.tab.c"
    break;

  case 54: /* F: CHARACTER  */
#line 293 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1707 "./obj/tpc-2020-2021.tab.c"
    break;

  case 55: /* F: LValue  */
#line 296 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1715 "./obj/tpc-2020-2021.tab.c"
    break;

  case 56: /* F: IDENT '(' Arguments ')'  */
#line 299 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[-3].tree);
                                                        addChild((yyvsp[-3].tree), (yyvsp[-1].tree));
                                                    }
#line 1724 "./obj/tpc-2020-2021.tab.c"
    break;

  case 57: /* LValue: IDENT  */
#line 305 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1732 "./obj/tpc-2020-2021.tab.c"
    break;

  case 58: /* LValue: IDENT '.' IDENT  */
#line 308 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(LValue);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1742 "./obj/tpc-2020-2021.tab.c"
    break;

  case 59: /* Arguments: ListExp  */
#line 315 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1750 "./obj/tpc-2020-2021.tab.c"
    break;

  case 60: /* Arguments: %empty  */
#line 318 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(Arguments);
                                                    }
#line 1758 "./obj/tpc-2020-2021.tab.c"
    break;

  case 61: /* ListExp: ListExp ',' Exp  */
#line 323 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = makeNode(ListExp);
                                                        addChild((yyval.tree), (yyvsp[-2].tree));
                                                        addChild((yyval.tree), (yyvsp[0].tree));
                                                    }
#line 1768 "./obj/tpc-2020-2021.tab.c"
    break;

  case 62: /* ListExp: Exp  */
#line 328 "src/tpc-2020-2021.y"
                                                    {   
                                                        (yyval.tree) = (yyvsp[0].tree);
                                                    }
#line 1776 "./obj/tpc-2020-2021.tab.c"
    break;


#line 1780 "./obj/tpc-2020-2021.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 332 "src/tpc-2020-2021.y"


int yyerror(const char *s) {
    fprintf(stderr, "%s near line %d column %d\n", s, yylineno, column);
    fprintf(stderr, "%s\n", line);
    for(int i = 0; i < column - 1; i++)
        fprintf(stderr," ");
    fprintf(stderr,"^\n");
    return 0;
}

int main(int argc, char *argv[]) {
    int help_flag = 0;
    int tree_flag = 0;
    int symb_flag = 0;
    int opt;
    int option_index = 0;
    int nb_opt = 0;
    struct option longopts[] = {
        { "help", no_argument, &help_flag, 1 },
        { "tree", no_argument, &tree_flag, 1 },
        { "symtabs", no_argument, &symb_flag, 1 },
        {0, 0, 0, 0 }
    };

    while ((opt = getopt_long(argc, argv, "-t-s-h", longopts, &option_index)) != -1) {
        nb_opt++;
        switch (opt) {
            case 't':
                tree_flag = 1;
                //printf("%s\n", optarg);
                break;
            case 's':
                symb_flag = 1;
                break;
            case '?':
                fprintf(stderr, "Erreur : Option invalide\n");
            case 'h':
                help_flag = 1;
                break;
            default: 
                break;
        }
    }

    if (nb_opt < argc) {
        yyin = fopen(argv[nb_opt], "r");
    }

    if (yyparse()) {
        return 1;
    }

    if (help_flag) {
        printf("./bin/tpcc [OPTIONS] < FILE.tpc\n");
        printf("[OPTIONS] : \n");
        printf("-t : affiche l'arbre abstrait sur la sortie standart.\n");
        printf("-s : affiche toutes les tables des symboles sur la sortie standard.\n");
        printf("-h : affiche une description de l’interface utilisateur et termine l’exécution.\n");
        printf("FILE.tpc : le fichier .tpc sur lequel vous voulez tester.\n");
        printf("./test.sh : Est un script bash permettant de lancer tout les tests du dossiers test.\n");
        return 0;
    }

    if (tree_flag) {
        printf("Tree\n");
        /* Affiche tree */
        printTree(abs_tree);
    }

    if (symb_flag) {
        printf("Symbol\n");
        /* Affiche symbol table */
        printTables(abs_tree);
    }

    deleteTree(abs_tree);
    return 0;
}
