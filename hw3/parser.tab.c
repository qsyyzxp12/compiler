/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 4 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
int linenumber = 1;
AST_NODE *prog;

extern int g_anyErrorOccur;

static inline AST_NODE* makeSibling(AST_NODE *a, AST_NODE *b)
{ 
    while (a->rightSibling) {
        a = a->rightSibling;
    }
    if (b == NULL) {
        return a;
    }
    b = b->leftmostSibling;
    a->rightSibling = b;
    
    b->leftmostSibling = a->leftmostSibling;
    b->parent = a->parent;
    while (b->rightSibling) {
        b = b->rightSibling;
        b->leftmostSibling = a->leftmostSibling;
        b->parent = a->parent;
    }
    return b;
}

static inline AST_NODE* makeChild(AST_NODE *parent, AST_NODE *child)
{
    if (child == NULL) {
        return parent;
    }
    if (parent->child) {
        makeSibling(parent->child, child);
    } else {
        child = child->leftmostSibling;
        parent->child = child;
        while (child) {
            child->parent = parent;
            child = child->rightSibling;
        }
    }
    return parent;
}

static AST_NODE* makeFamily(AST_NODE *parent, int childrenCount, ...)
{
    va_list childrenList;
    va_start(childrenList, childrenCount);
    AST_NODE* child = va_arg(childrenList, AST_NODE*);
    makeChild(parent, child);
    AST_NODE* tmp = child;
    int index = 1;
    for (index = 1; index < childrenCount; ++index) {
        child = va_arg(childrenList, AST_NODE*);
        tmp = makeSibling(tmp, child);
    }
    va_end(childrenList);
    return parent;
}

static inline AST_NODE* makeIDNode(char *lexeme, IDENTIFIER_KIND idKind)
{
    AST_NODE* identifier = Allocate(IDENTIFIER_NODE);
    identifier->semantic_value.identifierSemanticValue.identifierName = lexeme;
    identifier->semantic_value.identifierSemanticValue.kind = idKind;
    identifier->semantic_value.identifierSemanticValue.symbolTableEntry = NULL;
    return identifier;                        
}

static inline AST_NODE* makeStmtNode(STMT_KIND stmtKind)
{
    AST_NODE* stmtNode = Allocate(STMT_NODE);
    stmtNode->semantic_value.stmtSemanticValue.kind = stmtKind;
    return stmtNode;                        
}

static inline AST_NODE* makeDeclNode(DECL_KIND declKind)
{
    AST_NODE* declNode = Allocate(DECLARATION_NODE);
    declNode->semantic_value.declSemanticValue.kind = declKind;
    return declNode;                        
}

static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)
{
    AST_NODE* exprNode = Allocate(EXPR_NODE);
    exprNode->semantic_value.exprSemanticValue.isConstEval = 0;
    exprNode->semantic_value.exprSemanticValue.kind = exprKind;
    if (exprKind == BINARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.binaryOp = operationEnumValue;
    } else if (exprKind == UNARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.unaryOp = operationEnumValue;
    } else {
        printf("Error in static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)\n");
    }
    return exprNode;                        
}



/* Line 268 of yacc.c  */
#line 178 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     CONST = 259,
     VOID = 260,
     INT = 261,
     FLOAT = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     FOR = 266,
     TYPEDEF = 267,
     OP_ASSIGN = 268,
     OP_OR = 269,
     OP_AND = 270,
     OP_NOT = 271,
     OP_EQ = 272,
     OP_NE = 273,
     OP_GT = 274,
     OP_LT = 275,
     OP_GE = 276,
     OP_LE = 277,
     OP_PLUS = 278,
     OP_MINUS = 279,
     OP_TIMES = 280,
     OP_DIVIDE = 281,
     MK_LB = 282,
     MK_RB = 283,
     MK_LPAREN = 284,
     MK_RPAREN = 285,
     MK_LBRACE = 286,
     MK_RBRACE = 287,
     MK_COMMA = 288,
     MK_SEMICOLON = 289,
     MK_DOT = 290,
     ERROR = 291,
     RETURN = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 112 "parser.y"

	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;



/* Line 293 of yacc.c  */
#line 259 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 271 "parser.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   213

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNRULES -- Number of states.  */
#define YYNSTATES  185

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    14,    16,    25,
      34,    42,    50,    54,    56,    59,    63,    67,    72,    74,
      75,    78,    80,    82,    83,    86,    88,    90,    92,    97,
     102,   106,   110,   112,   114,   116,   120,   125,   128,   132,
     136,   140,   142,   146,   150,   152,   154,   158,   160,   164,
     166,   169,   173,   176,   178,   182,   192,   197,   199,   202,
     206,   208,   209,   213,   215,   219,   221,   223,   227,   229,
     233,   235,   239,   241,   243,   245,   247,   249,   251,   253,
     254,   258,   260,   264,   266,   268,   270,   274,   276,   278,
     280,   284,   289,   291,   294,   299,   305,   307,   310,   312,
     315,   320
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    -1,    40,    41,    -1,    41,
      -1,    48,    42,    -1,    42,    -1,    52,     3,    29,    43,
      30,    31,    47,    32,    -1,     5,     3,    29,    43,    30,
      31,    47,    32,    -1,    52,     3,    29,    30,    31,    47,
      32,    -1,     5,     3,    29,    30,    31,    47,    32,    -1,
      43,    33,    44,    -1,    44,    -1,    52,     3,    -1,    52,
       3,    45,    -1,    27,    46,    28,    -1,    45,    27,    71,
      28,    -1,    71,    -1,    -1,    48,    60,    -1,    60,    -1,
      48,    -1,    -1,    48,    49,    -1,    49,    -1,    50,    -1,
      51,    -1,    12,    52,    53,    34,    -1,    12,     5,    53,
      34,    -1,    52,    58,    34,    -1,     3,    53,    34,    -1,
       6,    -1,     7,    -1,     3,    -1,    53,    33,     3,    -1,
      53,    33,     3,    54,    -1,     3,    54,    -1,    27,    55,
      28,    -1,    55,    23,    56,    -1,    55,    24,    56,    -1,
      56,    -1,    56,    25,    57,    -1,    56,    26,    57,    -1,
      57,    -1,     4,    -1,    29,    55,    30,    -1,    59,    -1,
      58,    33,    59,    -1,     3,    -1,     3,    54,    -1,     3,
      13,    65,    -1,    60,    61,    -1,    61,    -1,    31,    47,
      32,    -1,    11,    29,    62,    34,    69,    34,    62,    30,
      61,    -1,    76,    13,    65,    34,    -1,    34,    -1,    37,
      34,    -1,    37,    65,    34,    -1,    63,    -1,    -1,    63,
      33,    64,    -1,    64,    -1,     3,    13,    65,    -1,    65,
      -1,    66,    -1,    65,    14,    66,    -1,    67,    -1,    66,
      15,    67,    -1,    71,    -1,    71,    68,    71,    -1,    17,
      -1,    21,    -1,    22,    -1,    18,    -1,    19,    -1,    20,
      -1,    70,    -1,    -1,    70,    33,    65,    -1,    65,    -1,
      71,    72,    73,    -1,    73,    -1,    23,    -1,    24,    -1,
      73,    74,    75,    -1,    75,    -1,    25,    -1,    26,    -1,
      29,    65,    30,    -1,    16,    29,    65,    30,    -1,     4,
      -1,    16,     4,    -1,     3,    29,    69,    30,    -1,    16,
       3,    29,    69,    30,    -1,    76,    -1,    16,    76,    -1,
       3,    -1,     3,    77,    -1,    77,    27,    71,    28,    -1,
      27,    71,    28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   166,   166,   167,   170,   174,   180,   184,   190,   197,
     201,   207,   213,   217,   223,   228,   233,   237,   243,   248,
     253,   257,   262,   267,   272,   276,   282,   286,   292,   296,
     302,   306,   312,   316,   322,   326,   330,   334,   339,   347,
     352,   356,   361,   365,   369,   375,   379,   385,   389,   395,
     399,   403,   409,   413,   421,   426,   430,   437,   441,   445,
     451,   456,   461,   465,   477,   481,   487,   491,   498,   502,
     508,   512,   518,   522,   526,   530,   534,   538,   545,   550,
     555,   559,   565,   569,   575,   579,   585,   589,   595,   599,
     605,   610,   614,   620,   624,   629,   633,   638,   644,   648,
     655,   659
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONST", "VOID", "INT", "FLOAT",
  "IF", "ELSE", "WHILE", "FOR", "TYPEDEF", "OP_ASSIGN", "OP_OR", "OP_AND",
  "OP_NOT", "OP_EQ", "OP_NE", "OP_GT", "OP_LT", "OP_GE", "OP_LE",
  "OP_PLUS", "OP_MINUS", "OP_TIMES", "OP_DIVIDE", "MK_LB", "MK_RB",
  "MK_LPAREN", "MK_RPAREN", "MK_LBRACE", "MK_RBRACE", "MK_COMMA",
  "MK_SEMICOLON", "MK_DOT", "ERROR", "RETURN", "$accept", "program",
  "global_decl_list", "global_decl", "function_decl", "param_list",
  "param", "dim_fn", "expr_null", "block", "decl_list", "decl",
  "type_decl", "var_decl", "type", "id_list", "dim_decl", "cexpr",
  "mcexpr", "cfactor", "init_id_list", "init_id", "stmt_list", "stmt",
  "assign_expr_list", "nonempty_assign_expr_list", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "var_ref", "dim_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    54,    55,
      55,    55,    56,    56,    56,    57,    57,    58,    58,    59,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     3,     1,     1,     1,     3,     4,     2,     3,     3,
       3,     1,     3,     3,     1,     1,     3,     1,     3,     1,
       2,     3,     2,     1,     3,     9,     4,     1,     2,     3,
       1,     0,     3,     1,     3,     1,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     4,     1,     2,     4,     5,     1,     2,     1,     2,
       4,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    32,    33,     0,     0,     2,     5,     7,
       0,    25,    26,    27,     0,    34,     0,     0,     0,     0,
       1,     4,     6,    24,    49,     0,    47,     0,    37,     0,
      31,     0,     0,     0,     0,     0,    50,     0,    30,    45,
       0,     0,    41,    44,    35,     0,     0,    13,     0,    29,
      28,    98,    92,     0,     0,    51,    66,    68,    70,    83,
      87,    96,     0,     0,    49,    48,     0,     0,     0,    38,
       0,     0,    36,    23,     0,     0,    14,     0,    79,    99,
      98,    93,     0,    97,     0,     0,     0,    72,    75,    76,
      77,    73,    74,    84,    85,     0,     0,    88,    89,     0,
      23,     0,    46,    39,    40,    42,    43,    98,     0,    23,
      57,     0,     0,    22,     0,    21,    53,     0,    23,    12,
      19,    15,     0,    81,     0,    78,     0,    79,     0,    90,
      67,    69,    71,    82,    86,     0,    23,    61,     0,    58,
       0,    11,    20,    98,    52,     0,     0,     0,    18,     0,
     101,    94,     0,     0,     0,    91,    10,     0,    98,     0,
      60,    63,    65,    54,    59,     0,     9,    16,     0,    80,
     100,    95,     8,     0,    79,     0,    56,    17,    64,     0,
      62,    61,     0,     0,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    46,    47,   121,   147,   112,
     113,    11,    12,    13,   114,    16,    36,    41,    42,    43,
      25,    26,   115,   116,   159,   160,   161,   123,    56,    57,
      95,   124,   125,    58,    96,    59,    99,    60,    61,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -123
static const yytype_int16 yypact[] =
{
     109,    44,    52,  -123,  -123,   146,    26,   109,  -123,  -123,
     109,  -123,  -123,  -123,    80,    93,   -22,    64,    44,    44,
    -123,  -123,  -123,  -123,    67,   103,  -123,    17,  -123,   104,
    -123,    21,   121,   123,    70,    23,  -123,   169,  -123,  -123,
      17,   107,   133,  -123,    93,   118,    24,  -123,   170,  -123,
    -123,    90,  -123,    15,    70,    96,   159,  -123,   105,   135,
    -123,  -123,   144,    57,    71,  -123,    -7,    17,    17,  -123,
      17,    17,  -123,    29,   145,   156,   150,    70,    70,   151,
     113,  -123,    70,  -123,    75,    70,    70,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,  -123,    70,    70,  -123,  -123,    70,
      29,   149,  -123,   133,   133,  -123,  -123,     6,   152,    29,
    -123,    66,   147,    29,   169,    34,  -123,   171,    29,  -123,
      70,   155,   110,    96,   153,   154,    70,    70,    83,  -123,
     159,  -123,   141,   135,  -123,   157,    29,    72,   158,  -123,
      25,  -123,    34,   161,  -123,    70,   160,   163,   141,    70,
    -123,  -123,    70,   120,   164,  -123,  -123,   165,    79,   162,
     166,  -123,    96,  -123,  -123,    47,  -123,  -123,   122,    96,
    -123,  -123,  -123,    70,    70,    72,  -123,  -123,    96,   167,
    -123,    72,   168,    34,  -123
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,  -123,   178,   176,   172,   125,  -123,  -123,   -94,
     102,    -9,  -123,  -123,     3,   148,    -1,   173,   101,   100,
    -123,   174,    82,  -111,    12,  -123,    27,   -34,   119,   117,
    -123,  -122,  -123,   -70,  -123,   112,  -123,   106,   -51,  -123
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,    23,    83,    14,   144,   154,   135,   122,    19,    15,
      14,    29,    30,    14,    28,   138,    67,    68,    80,    81,
      84,    39,   117,   102,   146,   132,    20,     3,     4,     3,
       4,   144,   107,    77,    48,     3,     4,   143,    48,    85,
     108,     5,   157,    72,    82,   108,    40,    15,   128,   117,
     148,    45,   179,    62,    74,    17,   153,    75,   117,   164,
     109,    85,   117,   110,   117,   109,   111,   117,   110,    51,
      52,   111,   184,    51,    52,   158,    52,   140,    48,   168,
      34,   176,    53,    24,    34,   117,    53,   101,    53,    85,
      75,   117,   173,    31,    27,    54,    35,    85,    27,    54,
     139,    54,    10,   162,    23,   129,    77,    44,    78,    10,
      85,   165,     1,   155,     2,     3,     4,    77,   169,    78,
      27,     5,    87,    88,    89,    90,    91,    92,    93,    94,
      67,    68,   117,    93,    94,    69,    37,    38,   150,   178,
      77,   162,   127,    93,    94,    93,    94,   162,   170,    73,
     177,    18,     3,     4,    29,    49,    29,    50,    70,    71,
      97,    98,     3,     4,    93,    94,    32,    33,   103,   104,
     105,   106,    64,    76,    86,   100,   118,   120,   126,   141,
     136,   137,   149,   151,   145,    21,    22,   152,    77,   156,
     163,   167,   166,   182,   171,   142,   174,   172,   183,   175,
     119,   181,   180,   131,   130,   134,     0,    63,   133,     0,
       0,    65,     0,    66
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-123))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      34,    10,    53,     0,   115,   127,   100,    77,     5,     3,
       7,    33,    34,    10,    15,   109,    23,    24,     3,     4,
      54,     4,    73,    30,   118,    95,     0,     6,     7,     6,
       7,   142,     3,    27,    31,     6,     7,     3,    35,    14,
      11,    12,   136,    44,    29,    11,    29,     3,    82,   100,
     120,    30,   174,    30,    30,     3,   126,    33,   109,    34,
      31,    14,   113,    34,   115,    31,    37,   118,    34,     3,
       4,    37,   183,     3,     4,     3,     4,   111,    75,   149,
      13,    34,    16,     3,    13,   136,    16,    30,    16,    14,
      33,   142,    13,    29,    27,    29,    29,    14,    27,    29,
      34,    29,     0,   137,   113,    30,    27,     3,    29,     7,
      14,   145,     3,    30,     5,     6,     7,    27,   152,    29,
      27,    12,    17,    18,    19,    20,    21,    22,    23,    24,
      23,    24,   183,    23,    24,    28,    33,    34,    28,   173,
      27,   175,    29,    23,    24,    23,    24,   181,    28,    31,
      28,     5,     6,     7,    33,    34,    33,    34,    25,    26,
      25,    26,     6,     7,    23,    24,    18,    19,    67,    68,
      70,    71,     3,     3,    15,    31,    31,    27,    27,    32,
      31,    29,    27,    30,    13,     7,    10,    33,    27,    32,
      32,    28,    32,   181,    30,   113,    34,    32,    30,    33,
      75,    34,   175,    86,    85,    99,    -1,    35,    96,    -1,
      -1,    37,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      48,    49,    50,    51,    52,     3,    53,     3,     5,    52,
       0,    41,    42,    49,     3,    58,    59,    27,    54,    33,
      34,    29,    53,    53,    13,    29,    54,    33,    34,     4,
      29,    55,    56,    57,     3,    30,    43,    44,    52,    34,
      34,     3,     4,    16,    29,    65,    66,    67,    71,    73,
      75,    76,    30,    43,     3,    59,    55,    23,    24,    28,
      25,    26,    54,    31,    30,    33,     3,    27,    29,    77,
       3,     4,    29,    76,    65,    14,    15,    17,    18,    19,
      20,    21,    22,    23,    24,    68,    72,    25,    26,    74,
      31,    30,    30,    56,    56,    57,    57,     3,    11,    31,
      34,    37,    47,    48,    52,    60,    61,    76,    31,    44,
      27,    45,    71,    65,    69,    70,    27,    29,    65,    30,
      66,    67,    71,    73,    75,    47,    31,    29,    47,    34,
      65,    32,    60,     3,    61,    13,    47,    46,    71,    27,
      28,    30,    33,    71,    69,    30,    32,    47,     3,    62,
      63,    64,    65,    32,    34,    65,    32,    28,    71,    65,
      28,    30,    32,    13,    34,    33,    34,    28,    65,    69,
      64,    34,    62,    30,    61
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 166 "parser.y"
    { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[(1) - (1)].node)); prog=(yyval.node);}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 167 "parser.y"
    { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 171 "parser.y"
    {
                        (yyval.node) = makeSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                    }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 175 "parser.y"
    {
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 181 "parser.y"
    {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (2)].node)), (yyvsp[(2) - (2)].node));
                }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 185 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 191 "parser.y"
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[(4) - (8)].node));
                        makeFamily((yyval.node), 4, (yyvsp[(1) - (8)].node), makeIDNode((yyvsp[(2) - (8)].lexeme), NORMAL_ID), parameterList, (yyvsp[(7) - (8)].node));
                    }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 198 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 202 "parser.y"
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[(1) - (7)].node), makeIDNode((yyvsp[(2) - (7)].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[(6) - (7)].node));
                    }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 208 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 214 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 218 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 224 "parser.y"
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (2)].node), makeIDNode((yyvsp[(2) - (2)].lexeme), NORMAL_ID));
                }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 229 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 234 "parser.y"
    {
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 238 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 244 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 248 "parser.y"
    {
                    (yyval.node) = Allocate(NUL_NODE); 
                }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 254 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 258 "parser.y"
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[(1) - (1)].node)));
                    }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 263 "parser.y"
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (1)].node)));
                    }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 267 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 273 "parser.y"
    {
                        /*TODO*/
                }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 277 "parser.y"
    {
                        /*TODO*/
                }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 283 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 287 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 293 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 297 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 303 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 307 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 313 "parser.y"
    {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 317 "parser.y"
    {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 323 "parser.y"
    {
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 327 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 331 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 335 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 340 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 348 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 353 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 357 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 362 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 366 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 370 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 376 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 380 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 386 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 390 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 396 "parser.y"
    {
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 400 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 404 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 410 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 414 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 422 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 427 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 431 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 438 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 442 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 446 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 452 "parser.y"
    {
                        /*TODO*/
                     }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 456 "parser.y"
    {
                         (yyval.node) = Allocate(NUL_NODE); 
                     }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 462 "parser.y"
    {
                                        /*TODO*/
                                    }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 466 "parser.y"
    {
                                        /*TODO*/
                                    }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 478 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 482 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 488 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 492 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 499 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 503 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 509 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 513 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 519 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 523 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 527 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 531 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 535 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 539 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 546 "parser.y"
    {
                        /*TODO*/
                    }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 550 "parser.y"
    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 556 "parser.y"
    {
                                    /*TODO*/
                                }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 560 "parser.y"
    {
                                    /*TODO*/
                                }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 566 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 570 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 576 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 580 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 586 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 590 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 596 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 600 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 606 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 611 "parser.y"
    {   
                    /*TODO*/
                }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 615 "parser.y"
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[(1) - (1)].const1);
                }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 621 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 625 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 630 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 634 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 639 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 645 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 649 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 656 "parser.y"
    {
                    /*TODO*/
                }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 660 "parser.y"
    {
                    /*TODO*/
                }
    break;



/* Line 1806 of yacc.c  */
#line 2580 "parser.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 666 "parser.y"


#include "lex.yy.c"
main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
	 printf("%s\n", "Parsing completed. No errors found.");
	 printGV(prog, NULL);
  } /* main */


int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }

