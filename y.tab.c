/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "sintatica.y" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <stack>

#define YYSTYPE atributos
#define oi(N) cout << "oi "<< N << endl

using namespace std;

struct atributos
{
	string label;
	string traducao;
	string tipo;
};

typedef struct SwitchLabelStacks{
	string endLabel;
	string nextLabel;
	string varLabel;
} SwitchLabels;

struct coercao{
	string retornoTipo, conversaoTipo;
};

typedef struct caracteristicas{
	string localVar, tipo;
} caracteristicas;

typedef caracteristicas* caracteristicasPtr;



typedef std::tuple<string, string, string> KeyTriple;

int yylex(void);
void yyerror(string);
string gerarLabel();
string labelUsuario();
string declararVars();
void inserirTabela(string);
void inserirTemporaria(string, string);
struct coercao verificarCoercao(string , string  ,string );
KeyTriple genKey(string , string, string);
struct atributos conversaoImplicita(struct atributos, struct atributos, string);
struct atributos declaracaoVariavel(struct atributos, string);
struct atributos operacaoRelacional(struct atributos, struct atributos, string);
string gerarGotoLabel();
int getN();
vector<string> split(const string&, const string&);
void inicializarTabelaCoercao();
caracteristicasPtr buscarVariavel(string);
caracteristicasPtr buscarVariavelTopo(string);
bool operator<(KeyTriple const & lhs, KeyTriple const & rhs) {
	/*
    if (lhs.a < rhs.a) return true;
    if (rhs.a < lhs.a) return false;
    if (lhs.b < rhs.b) return true;
    if (rhs.b < lhs.b) return false;
    if (lhs.c < rhs.c) return true;
    return false;
	*/
    // Alternatively, if you can use C++11 but don't want a tuple for a key
    return std::tie(get<0>(lhs), get<1>(lhs), get<2>(lhs) ) < std::tie(get<0>(rhs), get<1>(rhs), get<2>(rhs));
}



// -------------------------variaveis ------------------------------------------------

int nTemp = 0;
int nUser = 0;
int nGoto = 0;
int lineCount = 1;

stack <SwitchLabels> gambiarraSwitch ;

vector <unordered_map<string, caracteristicas>> pilhaContexto;

unordered_map<string, caracteristicas> tabela;
std::unordered_map<std::string, string> temporarias;
std::unordered_map<std::string, std::string> revertTable;

std::map<KeyTriple, struct coercao> tabelaCoercao;

// --------------------------------------------LEFTS E TOKENS -------------------------------



#line 162 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_NUM = 258,
    TK_REAL = 259,
    TK_CHAR = 260,
    TK_MAIN = 261,
    TK_ID = 262,
    TK_FIM = 263,
    TK_ERROR = 264,
    TK_TIPO_FLOAT = 265,
    TK_TIPO_INT = 266,
    TK_TIPO_CHAR = 267,
    TK_TIPO_BOOL = 268,
    TK_EQ = 269,
    TK_NOT_EQ = 270,
    TK_BIG_EQ = 271,
    TK_SMALL_EQ = 272,
    TK_AND = 273,
    TK_OR = 274,
    TK_NOT = 275,
    TK_LOGICO = 276,
    TK_PRINT = 277,
    TK_IF = 278,
    TK_WHILE = 279,
    TK_FOR = 280,
    TK_ELSE = 281,
    TK_SWITCH = 282,
    TK_CASE = 283,
    TK_DEFAULT = 284,
    TK_BREAK = 285,
    TK_CONTINUE = 286
  };
#endif
/* Tokens.  */
#define TK_NUM 258
#define TK_REAL 259
#define TK_CHAR 260
#define TK_MAIN 261
#define TK_ID 262
#define TK_FIM 263
#define TK_ERROR 264
#define TK_TIPO_FLOAT 265
#define TK_TIPO_INT 266
#define TK_TIPO_CHAR 267
#define TK_TIPO_BOOL 268
#define TK_EQ 269
#define TK_NOT_EQ 270
#define TK_BIG_EQ 271
#define TK_SMALL_EQ 272
#define TK_AND 273
#define TK_OR 274
#define TK_NOT 275
#define TK_LOGICO 276
#define TK_PRINT 277
#define TK_IF 278
#define TK_WHILE 279
#define TK_FOR 280
#define TK_ELSE 281
#define TK_SWITCH 282
#define TK_CASE 283
#define TK_DEFAULT 284
#define TK_BREAK 285
#define TK_CONTINUE 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 275 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    34,     2,     2,
      39,    40,    37,    35,    45,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    43,
      32,    46,    33,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   133,   140,   147,   148,   151,   152,   153,
     154,   155,   156,   157,   158,   161,   170,   180,   181,   203,
     208,   217,   218,   221,   227,   234,   238,   241,   246,   250,
     271,   275,   288,   292,   296,   303,   307,   311,   315,   319,
     323,   332,   336,   340,   348,   352,   355,   359,   363,   366,
     371,   381,   388,   395,   402,   408,   417,   418,   419,   420
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_NUM", "TK_REAL", "TK_CHAR",
  "TK_MAIN", "TK_ID", "TK_FIM", "TK_ERROR", "TK_TIPO_FLOAT", "TK_TIPO_INT",
  "TK_TIPO_CHAR", "TK_TIPO_BOOL", "TK_EQ", "TK_NOT_EQ", "TK_BIG_EQ",
  "TK_SMALL_EQ", "TK_AND", "TK_OR", "TK_NOT", "TK_LOGICO", "TK_PRINT",
  "TK_IF", "TK_WHILE", "TK_FOR", "TK_ELSE", "TK_SWITCH", "TK_CASE",
  "TK_DEFAULT", "TK_BREAK", "TK_CONTINUE", "'<'", "'>'", "'%'", "'+'",
  "'-'", "'*'", "'/'", "'('", "')'", "'{'", "'}'", "';'", "':'", "','",
  "'='", "$accept", "S", "BLOCO", "BLOCO_AUX", "COMANDOS", "COMANDO",
  "SWITCH", "SWITCH_AUX", "caseRecursao", "IF", "BLOMANDO", "WHILE",
  "FN_ARGS", "FN_ARGS_AUX", "ATRIBUICAO", "DECLARACAO", "E", "TIPO", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    60,    62,    37,    43,    45,    42,    47,    40,
      41,   123,   125,    59,    58,    44,    61
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,    -1,     7,   -22,   -96,    -7,   -96,   -96,   -23,    51,
     -96,   -96,   -96,   -24,    28,    29,    43,    44,    62,   -96,
      14,    18,    20,    31,    92,   -96,    26,    51,   -96,   -96,
     -96,    34,    36,   156,    62,   -96,    35,   -96,   -96,   -96,
     236,    62,    62,    62,    73,   -96,   -96,   -96,   -96,    -6,
      58,   -96,   -96,   -96,   -96,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,   -96,   204,
      62,    60,   100,   168,   195,   -96,    70,   -96,    62,    50,
      50,    50,    50,   229,   236,    50,    50,    71,   -34,   -34,
     -96,   -96,   204,    48,    62,   -96,    51,    51,    79,   -96,
     -96,   100,   -96,   -96,    85,   -96,   -96,    93,   -96,    51,
      62,    94,   -96,   125,    78,    51,    51,    93,    82,   -96,
     -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     4,     2,     0,     6,
      51,    52,    53,    54,     0,     0,     0,     0,     0,    55,
       0,     0,     0,     0,     0,    14,     0,     6,    13,    11,
      12,     0,     0,     0,     0,    32,    30,    33,    34,    54,
      43,    26,     0,     0,     0,    59,    57,    58,    56,     0,
       0,     3,     5,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,    29,
       0,     0,    28,     0,     0,    16,     0,    40,     0,    48,
      49,    46,    47,    41,    42,    44,    45,    39,    35,    36,
      37,    38,    31,     0,     0,    25,     4,     4,     0,    50,
      10,    28,    21,    22,    19,    24,    23,    17,    27,     4,
       0,     0,    20,     0,     0,     4,     4,    17,     0,    18,
      15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,    -4,   -96,    98,    -8,   -96,   -96,     9,   -96,
     -95,   -96,   -96,    27,   -96,   -96,   -18,   -96
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,   102,     8,    26,   103,    28,    76,   111,    29,
     104,    30,    71,    95,    31,    32,    33,    50
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    27,     7,    66,    67,     3,    49,     4,    55,    56,
      57,    58,    59,    60,   112,     1,    69,     5,     9,    27,
     117,   118,    34,    72,    73,    74,    61,    62,    63,    64,
      65,    66,    67,     6,    77,    35,    36,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      37,    38,    92,    41,    10,    11,    12,    42,    13,    43,
      99,    14,    15,    16,    17,    10,    11,    12,    51,    39,
      44,    18,    19,    20,    21,    22,   101,    53,    23,    54,
      75,    70,    18,    19,    63,    64,    65,    66,    67,   106,
      24,   100,   113,   105,    25,    10,    11,    12,    78,    39,
      93,    24,    45,    46,    47,    48,    64,    65,    66,    67,
      98,   109,    18,    19,    55,    56,    57,    58,    59,    60,
     107,   110,   116,   114,   120,    52,   119,     0,   108,     0,
       0,    24,    61,    62,    63,    64,    65,    66,    67,    55,
      56,    57,    58,    59,    60,    94,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,   115,
      55,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,     0,     0,     0,     0,    68,
      61,    62,    63,    64,    65,    66,    67,     0,    96,    55,
      56,    57,    58,    59,    60,     0,     0,     0,    55,    56,
      57,    58,    59,    60,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,     0,    97,    61,    62,    63,    64,
      65,    66,    67,    55,    56,    57,    58,     0,    60,     0,
      55,    56,    57,    58,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    61,    62,
      63,    64,    65,    66,    67
};

static const yytype_int8 yycheck[] =
{
      18,     9,     6,    37,    38,     6,    24,     0,    14,    15,
      16,    17,    18,    19,   109,    11,    34,    39,    41,    27,
     115,   116,    46,    41,    42,    43,    32,    33,    34,    35,
      36,    37,    38,    40,    40,     7,     7,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       7,     7,    70,    39,     3,     4,     5,    39,     7,    39,
      78,    10,    11,    12,    13,     3,     4,     5,    42,     7,
      39,    20,    21,    22,    23,    24,    94,    43,    27,    43,
       7,    46,    20,    21,    34,    35,    36,    37,    38,    97,
      39,    43,   110,    97,    43,     3,     4,     5,    40,     7,
      40,    39,    10,    11,    12,    13,    35,    36,    37,    38,
      40,    26,    20,    21,    14,    15,    16,    17,    18,    19,
      41,    28,    44,    29,    42,    27,   117,    -1,   101,    -1,
      -1,    39,    32,    33,    34,    35,    36,    37,    38,    14,
      15,    16,    17,    18,    19,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    44,
      14,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    19,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      32,    33,    34,    35,    36,    37,    38,    -1,    40,    14,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    -1,    40,    32,    33,    34,    35,
      36,    37,    38,    14,    15,    16,    17,    -1,    19,    -1,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    32,    33,
      34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    48,     6,     0,    39,    40,    49,    50,    41,
       3,     4,     5,     7,    10,    11,    12,    13,    20,    21,
      22,    23,    24,    27,    39,    43,    51,    52,    53,    56,
      58,    61,    62,    63,    46,     7,     7,     7,     7,     7,
      63,    39,    39,    39,    39,    10,    11,    12,    13,    63,
      64,    42,    51,    43,    43,    14,    15,    16,    17,    18,
      19,    32,    33,    34,    35,    36,    37,    38,    43,    63,
      46,    59,    63,    63,    63,     7,    54,    40,    40,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    40,    45,    60,    40,    40,    40,    63,
      43,    63,    49,    52,    57,    49,    52,    41,    60,    26,
      28,    55,    57,    63,    29,    44,    44,    57,    57,    55,
      42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      62,    62,    62,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    64,    64,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     4,     0,     2,     0,     2,     2,     2,
       5,     1,     1,     1,     1,    10,     1,     0,     5,     5,
       7,     1,     1,     5,     5,     2,     0,     3,     0,     3,
       2,     4,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 128 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n\n#define BOOL int\n\nint main(void)\n{\n" << declararVars() << "\n" << (yyvsp[0]).traducao << "\n\treturn 0;\n}" << endl; 
			}
#line 1464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 134 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
				pilhaContexto.pop_back();
			}
#line 1473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 140 "sintatica.y" /* yacc.c:1646  */
    {
				unordered_map<string, caracteristicas> table;
				pilhaContexto.push_back(table);
				
			}
#line 1483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 147 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;}
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 148 "sintatica.y" /* yacc.c:1646  */
    {  (yyval).traducao = "" ;}
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 151 "sintatica.y" /* yacc.c:1646  */
    { (yyval).traducao = (yyvsp[-1]).traducao; }
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 152 "sintatica.y" /* yacc.c:1646  */
    { (yyval).traducao =(yyvsp[-1]).traducao;}
#line 1507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 153 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = "";}
#line 1513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 154 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = (yyvsp[-2]).traducao + "\t" + "std::cout <<" + (yyvsp[-2]).label + "<<std::endl;\n";}
#line 1519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 155 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = (yyvsp[0]).traducao;}
#line 1525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 156 "sintatica.y" /* yacc.c:1646  */
    { (yyval).traducao = (yyvsp[0]).traducao;}
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 157 "sintatica.y" /* yacc.c:1646  */
    { (yyval).traducao = (yyvsp[0]).traducao;}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 162 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-4]).traducao + (yyvsp[-1]).traducao + "\t" + gambiarraSwitch.top().endLabel+ ":\n";
					nGoto -= 1;
					gambiarraSwitch.pop();
			}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 171 "sintatica.y" /* yacc.c:1646  */
    {
				SwitchLabels a;
				a.endLabel = gerarGotoLabel();
				a.nextLabel = gerarGotoLabel();
				a.varLabel = (yyvsp[0]).label;
				gambiarraSwitch.push(a);
				
			}
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 180 "sintatica.y" /* yacc.c:1646  */
    { (yyval).traducao = "";}
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 182 "sintatica.y" /* yacc.c:1646  */
    {
				SwitchLabels topoDaPilha = gambiarraSwitch.top();
				(yyval).traducao = "";
				//cout << "a traducao disso é " + $$.traducao + "fiim" << endl;
				struct atributos auxiliar;
				auxiliar.tipo = tabela[revertTable[topoDaPilha.varLabel]].tipo;
				auxiliar.label = topoDaPilha.varLabel;

				struct atributos temporaria = conversaoImplicita((yyvsp[-3]), auxiliar, "==");
				(yyval).traducao += temporaria.traducao;
				(yyval).traducao += "\t" + temporaria.label + " = !" + temporaria.label + ";\n";
				(yyval).traducao +=  "\tif( "+ temporaria.label + " ) goto " + topoDaPilha.nextLabel + ";\n";
				(yyval).traducao += (yyvsp[-1]).traducao;

				(yyval).traducao += "\tgoto " + topoDaPilha.endLabel+ ";\n\t" + topoDaPilha.nextLabel + ":\n" +(yyvsp[0]).traducao ;
				gambiarraSwitch.top().nextLabel = gerarGotoLabel();
			}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 204 "sintatica.y" /* yacc.c:1646  */
    {
				string endLabel = gerarGotoLabel();
				(yyval).traducao = (yyvsp[-2]).traducao + "\t" + (yyvsp[-2]).label + " = !" + (yyvsp[-2]).label + ";\n" + "\tif( " + (yyvsp[-2]).label + " ) goto " + endLabel + ";\n" + (yyvsp[0]).traducao + "\t" + endLabel + ":\n"; 
			}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 209 "sintatica.y" /* yacc.c:1646  */
    {
				string midLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				(yyval).traducao = (yyvsp[-4]).traducao + "\t" + (yyvsp[-4]).label + " = !" + (yyvsp[-4]).label + ";\n" + "\tif( " + (yyvsp[-4]).label + " ) goto " + midLabel + ";\n" + (yyvsp[-2]).traducao + "\tgoto " + endLabel+ ";\n\t"+ midLabel + ":\n" + (yyvsp[0]).traducao + "\t" +endLabel + ":\n"; 
			}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 222 "sintatica.y" /* yacc.c:1646  */
    {
				string startLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				(yyval).traducao = "\t"+ startLabel + ":\n" +(yyvsp[-2]).traducao + "\t" + (yyvsp[-2]).label + " = !" + (yyvsp[-2]).label + ";\n" + "\tif( " + (yyvsp[-2]).label + " ) \n\t\t goto " + endLabel + ";\n" + (yyvsp[0]).traducao + "\tgoto "+ startLabel + ";\n\t" + endLabel + ":\n"; 
			}
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 228 "sintatica.y" /* yacc.c:1646  */
    {
				string startLabel = gerarGotoLabel();
				string endLabel = gerarGotoLabel();
				(yyval).traducao = "\t"+ startLabel + ":\n" +(yyvsp[-2]).traducao + "\t" + (yyvsp[-2]).label + " = !" + (yyvsp[-2]).label + ";\n" + "\tif( " + (yyvsp[-2]).label + " ) \n\t\t goto " + endLabel + ";\n" + (yyvsp[0]).traducao + "\tgoto "+ startLabel + ";\n\t" + endLabel + ":\n"; 
			}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 235 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao; (yyval).label = (yyvsp[-1]).label + (yyvsp[0]).label;
			}
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 238 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = ""; (yyval).label = "";}
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 242 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				(yyval).label = "<<\" , \"<<" + (yyvsp[-1]).label + (yyvsp[0]).label;
			}
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 246 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = ""; (yyval).label = ""; }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 251 "sintatica.y" /* yacc.c:1646  */
    {

				string var = revertTable[(yyvsp[-2]).label];
				(yyvsp[-2]).tipo = tabela[var].tipo;
				if((yyvsp[-2]).tipo == (yyvsp[0]).tipo){
					(yyval).traducao = (yyvsp[0]).traducao +  "\t" + (yyvsp[-2]).label + " = " + (yyvsp[0]).label + ";\n";
				}
				else{
					struct coercao correcao = verificarCoercao((yyvsp[-2]).tipo, "=", (yyvsp[0]).tipo);
					if(correcao.retornoTipo != "NULL"){
						(yyval).traducao = (yyvsp[0]).traducao +  "\t" + (yyvsp[-2]).label + " = " + "(" + correcao.conversaoTipo + ")" + (yyvsp[0]).label + ";\n";
					}
					else{
						yyerror("a operacao = nao esta definida para " + (yyvsp[-2]).tipo + " e " + (yyvsp[0]).tipo);
					}

				}
			}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 272 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = declaracaoVariavel((yyvsp[0]), "int");
			}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 276 "sintatica.y" /* yacc.c:1646  */
    {
				/*
				string var = revertTable[$2.label];
				if(tabela.find(var) != tabela.end()){
					if(tabela[var].tipo == "Undefined"){
						tabela[var].tipo = "int";
						temporarias[$2.label] = "int";
					}
				}
				*/
			}
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 289 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = declaracaoVariavel((yyvsp[0]), "float");
			}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 293 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = declaracaoVariavel((yyvsp[0]), "char");
			}
#line 1719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 297 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = declaracaoVariavel((yyvsp[0]), "bool");
			}
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 304 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]) , "+");
			}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 308 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]) , "-");
			}
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 312 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]) , "*");
			}
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 316 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]) , "/");
			}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 320 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]) , "%");
			}
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 324 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = (yyvsp[-1]).label;
				(yyval).traducao = (yyvsp[-1]).traducao;
				(yyval).tipo = (yyvsp[-1]).tipo;

			}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 332 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "&&");

			}
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 336 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "||");

			}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 340 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarLabel();
				(yyval).tipo = "bool";
				inserirTemporaria((yyval).label, (yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = !" + (yyvsp[0]).label + ";\n";
			}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 348 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "<");
			}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 352 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), ">");
			}
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 355 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), ">=");
			}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 359 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "<=");
			}
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 363 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "==");
			}
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 366 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "!=");
			}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 371 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarLabel();
				(yyval).tipo = (yyvsp[-2]).traducao;
				inserirTemporaria((yyval).label, (yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = (" + (yyvsp[-2]).traducao + ") " + (yyvsp[0]).label + ";\n";
			}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 382 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarLabel();
				inserirTemporaria((yyval).label, "int");
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).traducao + ";\n";
				(yyval).tipo = "int";
			}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 389 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarLabel();
				inserirTemporaria((yyval).label, "float");
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).traducao + ";\n";
				(yyval).tipo = "float";
			}
#line 1888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 396 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarLabel();
				inserirTemporaria((yyval).label, "char");
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).traducao + ";\n";
				(yyval).tipo = "char";
			}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 402 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = (yyvsp[0]).label;
				(yyval).traducao = "";
				(yyval).tipo = (yyvsp[0]).tipo;
				//cout << "$1.tipo = " << $1.tipo << endl;
			}
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 408 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarLabel();
				inserirTemporaria((yyval).label, "bool");
				(yyval).tipo = "bool";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).traducao + ";\n";

			}
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 417 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = "bool";}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 418 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = "int";}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 419 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = "char";}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 420 "sintatica.y" /* yacc.c:1646  */
    {(yyval).traducao = "float";}
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1950 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 422 "sintatica.y" /* yacc.c:1906  */


#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	yydebug = 1;

	inicializarTabelaCoercao();

	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				

string gerarLabel(){
	return string("TMP") + to_string(nTemp++);
	
}

string gerarGotoLabel(){
	return string("Label") + to_string(nGoto++);
	
}

string labelUsuario(){
	return string("USRVAR") + to_string(nUser++);
	
}

string declararVars(){
	string retorno = "";
	for(auto &x: temporarias){
		if(x.second == "bool")
			x.second = "BOOL";
		retorno = retorno + "\t" + x.second + " " +x.first + ";\n";
	}
	return retorno;
}

void inserirTabela(string a){
	string aux = labelUsuario();
	pilhaContexto.back()[a] ={
		aux,
		"Undefined"
	};
	temporarias[aux] = "Undefined";
	revertTable[aux] = a;
}

void inserirTemporaria(string label, string tipo){
	temporarias[label] = tipo;
}

/*
bool varDeclarada(){
	if(tipos.find(yytext) != tipos.end())
		return true;
	else
		return false;
}*/



struct coercao verificarCoercao(string opUm, string operador ,string opDois){

	KeyTriple chave (opUm, operador, opDois);
	if(tabelaCoercao.find(chave) != tabelaCoercao.end()){
		return tabelaCoercao[chave];
	}


	if( operador != "="){
		get<0>(chave) = opDois;
		get<2>(chave) = opUm;
		if(tabelaCoercao.find(chave) != tabelaCoercao.end())
			return tabelaCoercao[chave];
	}

	struct coercao a = {"NULL","NULL"};
	return a;
}

void inicializarTabelaCoercao(){

	tabelaCoercao[genKey("int" , "+" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "-" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "*" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "/" , "int")] = {"int", "int"};
	tabelaCoercao[genKey("int" , "%", "int")] = {"int", "int"};

	tabelaCoercao[genKey("float", "+", "float")] = {"float", "float"};
	tabelaCoercao[genKey("float", "-", "float")] = {"float", "float"};
	tabelaCoercao[genKey("float", "*", "float")] = {"float", "float"};
	tabelaCoercao[genKey("float", "/", "float")] = {"float", "float"};

	tabelaCoercao[genKey("int", "+", "float")] = {"float", "float"};
	tabelaCoercao[genKey("int", "-", "float")] = {"float", "float"};
	tabelaCoercao[genKey("int", "*", "float")] = {"float", "float"};
	tabelaCoercao[genKey("int", "/", "float")] = {"float", "float"};

	
	



	tabelaCoercao[genKey("int", "=", "float")] = {"int","int"};
	tabelaCoercao[genKey("float", "=", "int")] = {"float","float"};


	tabelaCoercao[genKey("bool" , "&&", "bool")] = {"bool","bool"};
	tabelaCoercao[genKey("bool" , "||", "bool")] = {"bool","bool"};

	//tabelaCoercao[genKey("bool" , "<", "bool")] = "bool";
	tabelaCoercao[genKey("int" , "<", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "<", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "<", "float")] = {"bool","float"};

	tabelaCoercao[genKey("int" , ">", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , ">", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , ">", "float")] = {"bool","float"};

	tabelaCoercao[genKey("int" , ">=", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , ">=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , ">=", "float")] = {"bool","float"};

	tabelaCoercao[genKey("int" , "<=", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "<=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "<=", "float")] = {"bool","float"};


	tabelaCoercao[genKey("int" , "==", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "==", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "==", "float")] = {"bool","float"};
	tabelaCoercao[genKey("char" , "==", "char")] = {"bool","char"};
	tabelaCoercao[genKey("bool" , "==", "bool")] = {"bool","bool"};

	tabelaCoercao[genKey("int" , "!=", "int")] = {"bool","int"};
	tabelaCoercao[genKey("float" , "!=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("int" , "!=", "float")] = {"bool","float"};
	tabelaCoercao[genKey("char" , "!=", "char")] = {"bool","char"};
	tabelaCoercao[genKey("bool" , "!=", "bool")] = {"bool","bool"};





	//tabelaCoercao[] = "float";
}

KeyTriple genKey(string a , string b, string c){
	KeyTriple chave (a , b, c);
	return chave;
}

struct atributos conversaoImplicita(struct atributos $1, struct atributos $3 , string operador){
	struct atributos $$;

	if(revertTable.find($1.label) != revertTable.end() ){
		caracteristicasPtr atr1 = buscarVariavel(revertTable[$1.label]);
		if(atr1)
			$1.tipo = atr1->tipo;
	}

	if(revertTable.find($3.label) != revertTable.end() ){
		caracteristicasPtr atr3 = buscarVariavel(revertTable[$3.label]);
		if(atr3)
			$3.tipo = atr3->tipo;
	}


	struct coercao coercaoToken = verificarCoercao($1.tipo, operador, $3.tipo);

	if(coercaoToken.retornoTipo != "NULL"){

		$$.label = gerarLabel();
		inserirTemporaria($$.label , coercaoToken.retornoTipo);


		$$.tipo = coercaoToken.retornoTipo;
		if($1.tipo == coercaoToken.conversaoTipo && $3.tipo == coercaoToken.conversaoTipo)
			$$.traducao = $1.traducao + $3.traducao  + "\t" + $$.label +" = " + $1.label + " " + operador + " " + $3.label +";\n";

		else{

			string coercaoLabel = gerarLabel();
			inserirTemporaria(coercaoLabel, coercaoToken.conversaoTipo);

			string coercao = "\t"+ coercaoLabel + " = " "("+ coercaoToken.conversaoTipo +") ",resultado;

			if($1.tipo != coercaoToken.conversaoTipo){

				coercao += $1.label;
				resultado = coercaoLabel + " " + operador + " " + $3.label;
			}
			else if($3.tipo != coercaoToken.conversaoTipo){

				coercao += $3.label;
				resultado = $1.label + " " + operador + " " + coercaoLabel;
			}
			coercao += ";\n";
			$$.traducao = $1.traducao + $3.traducao + coercao +"\t" +  $$.label + " = "  + resultado + ";\n";
		}
	}
	else{
		yyerror("a operacao "+ operador + " nao esta definida para " + $1.tipo + " e " + $3.tipo);
	}

	return $$;
}

struct atributos declaracaoVariavel(struct atributos $2, string tipo){
	struct atributos $$;
	$$.traducao = "";
	string var = revertTable[$2.label];

	caracteristicasPtr varCaracteristicas = buscarVariavelTopo(var);
	if(varCaracteristicas != NULL){
		if(varCaracteristicas->tipo == "Undefined"){
			//cout << "declarando "<< var << " como " << tipo << endl;
			varCaracteristicas->tipo = tipo;
			temporarias[$2.label] = tipo;
		}
	}
	else{
		yyerror("A variavel \"" + var  + "\" ja foi declada como "+ tabela[var].tipo + " anteriormente\n");
	}

	return $$;
}

struct atributos operacaoRelacional(struct atributos $1, struct atributos $3, string operador){	
	if(revertTable.find($1.label) != revertTable.end() ){
		caracteristicasPtr atr1 = buscarVariavel(revertTable[$1.label]);
		if(atr1)
			$1.tipo = atr1->tipo;
	}

	if(revertTable.find($3.label) != revertTable.end() ){
		caracteristicasPtr atr3 = buscarVariavel(revertTable[$3.label]);
		if(atr3)
			$3.tipo = atr3->tipo;
	}
	struct coercao aux = verificarCoercao($1.tipo , operador, $3.tipo);
	struct atributos $$;


	$$.label = gerarLabel();
	$$.tipo = "bool";
	inserirTemporaria($$.label , $$.tipo);
	if(aux.retornoTipo != "NULL"){
		$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " " + operador + " " + $3.label + ";\n";
	}
	else{
		yyerror("A operacao " + operador + " não esta definida para os tipos " + $1.tipo + " e " + $3.tipo);
	}

	return $$;
}

/*
struct atributos gerarCodigoRelacional(struct atributos $1, struct atributos $3, string operador){
	
	if(revertTable.find($1.label) != revertTable.end() )
		$1.tipo = tabela[revertTable[$1.label]].tipo;

	if(revertTable.find($3.label) != revertTable.end() )
		$3.tipo = tabela[revertTable[$3.label]].tipo;

	string aux = verificarCoercao($1.tipo , operador, $3.tipo);
	struct atributos $$;


	$$.label = gerarLabel();
	$$.tipo = "bool";
	inserirTemporaria($$.label , $$.tipo);
	if(aux != ""){
		$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " " + operador + " " + $3.label + ";\n";
	}
	else{
		yyerror("A operacao " + operador + " não esta definida para os tipos " + $1.tipo + " e " + $3.tipo);
	}

	return $$;
}*/


vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

caracteristicasPtr buscarVariavel(string var){
	int size = pilhaContexto.size();
	while(size > 0){
		unordered_map<string,caracteristicas> posAtual = pilhaContexto[size - 1];
		if(posAtual.find(var) != posAtual.end()){
			return &(posAtual[var]);
		}
		size -= 1;
	}
	return NULL;

}

caracteristicasPtr buscarVariavelTopo(string var){
	unordered_map<string,caracteristicas> topo = pilhaContexto.back();
	if(topo.find(var) != topo.end()){
		return &(topo[var]);
	}
	return NULL;
}
