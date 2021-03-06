/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
#include "symbolTable.h"
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


#line 173 "parser.tab.c" /* yacc.c:339  */

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
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 112 "parser.y" /* yacc.c:355  */

	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;

#line 257 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 272 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   166,   166,   167,   170,   174,   180,   184,   190,   197,
     202,   208,   215,   221,   226,   230,   236,   241,   246,   251,
     257,   261,   267,   272,   277,   282,   287,   292,   297,   301,
     307,   311,   317,   322,   330,   335,   342,   346,   352,   356,
     360,   364,   369,   373,   378,   383,   388,   393,   398,   403,
     409,   414,   420,   424,   430,   434,   438,   444,   448,   456,
     460,   465,   470,   475,   480,   485,   490,   494,   499,   506,
     511,   516,   520,   526,   532,   538,   544,   548,   555,   559,
     566,   570,   576,   580,   584,   588,   592,   596,   603,   608,
     613,   617,   623,   627,   633,   637,   643,   647,   653,   657,
     663,   667,   672,   677,   682,   689,   696,   701,   708,   715,
     719,   724,   731,   735,   743,   747
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "global_decl_list", "global_decl", "function_decl", "function_head",
  "opt_param_list", "param_list", "param", "dim_fn", "expr_null", "block",
  "decl_list", "decl", "type_decl", "var_decl", "type", "id_list",
  "dim_decl", "cexpr", "mcexpr", "cfactor", "init_id_list", "init_id",
  "stmt_list", "stmt", "assign_expr_list", "nonempty_assign_expr_list",
  "test", "assign_expr", "relop_expr", "relop_term", "relop_factor",
  "rel_op", "relop_expr_list", "nonempty_relop_expr_list", "expr",
  "add_op", "term", "mul_op", "factor", "var_ref", "dim_list", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF -153

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-153)))

#define YYTABLE_NINF -12

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     122,    22,    25,  -153,  -153,   172,    75,   122,  -153,  -153,
      36,   122,  -153,  -153,  -153,    77,    88,   152,  -153,  -153,
      82,    82,  -153,  -153,   168,  -153,  -153,    91,   156,    83,
      10,    61,    95,  -153,    68,   158,   160,   105,   106,   110,
    -153,   127,  -153,     6,  -153,    23,    65,    83,   148,   130,
    -153,   131,   162,  -153,  -153,  -153,    10,    86,   170,  -153,
      10,    70,  -153,    61,   153,  -153,  -153,   176,   138,   168,
     176,    83,    83,   177,    97,  -153,    83,  -153,   154,  -153,
      83,  -153,    24,    83,    83,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,    83,    83,  -153,  -153,    83,     0,    10,
      10,  -153,    10,    10,   116,    68,    83,   178,     9,  -153,
     178,   135,   148,   179,   173,    83,    83,    62,    83,    63,
    -153,   130,  -153,   174,   162,  -153,  -153,   170,   170,  -153,
    -153,  -153,    61,   180,   174,    83,    45,   181,   182,   183,
       9,  -153,    55,   175,     9,    95,    26,  -153,   200,  -153,
    -153,    83,   142,   184,  -153,   185,  -153,  -153,   144,    83,
      87,    87,    87,   186,  -153,    28,  -153,    26,   155,  -153,
      83,   148,  -153,  -153,  -153,  -153,   187,    92,   189,  -153,
     148,   190,   188,   191,  -153,  -153,  -153,    47,   192,    83,
      26,    26,    83,    87,  -153,  -153,   148,   207,  -153,   193,
    -153,    26,    87,  -153,   195,    26,  -153
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    36,    37,     0,     0,     2,     5,     7,
       0,     0,    29,    30,    31,     0,    54,     0,    52,    10,
       0,     0,     1,     4,    13,     6,    28,    54,     0,     0,
       0,    55,     0,    35,    38,     0,     0,     0,     0,    12,
      15,     0,    34,   112,   103,     0,     0,     0,    56,    76,
      78,    80,    93,    97,   109,    50,     0,     0,    46,    49,
       0,    54,    53,    41,     0,    33,    32,    17,     0,     0,
      16,     0,    89,   113,   112,   105,     0,   111,   112,   104,
       0,   110,     0,     0,     0,    82,    85,    86,    87,    83,
      84,    94,    95,     0,     0,    98,    99,     0,     0,     0,
       0,    42,     0,     0,     0,    39,    23,    19,    27,    14,
      18,     0,    91,     0,    88,     0,    89,     0,    89,     0,
     100,    77,    79,    81,    92,    96,    51,    44,    45,    47,
      48,    43,    40,     0,    22,     0,   112,     0,     0,     0,
      27,    66,     0,     0,    26,     0,    25,    58,     0,   115,
     106,     0,     0,     0,   102,     0,   101,    20,     0,    89,
       0,     0,    70,     0,    67,     0,     8,    24,   112,    57,
       0,    90,   114,   108,   107,    21,     0,   112,     0,    73,
      75,     0,     0,    69,    72,    59,    68,     0,     0,     0,
       0,     0,    89,     0,    62,    65,    74,    63,    60,     0,
      71,     0,    70,    64,     0,     0,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,  -153,   214,   212,  -153,  -153,  -153,   159,   161,
    -153,    89,   -95,    -7,  -153,  -153,    -2,   209,   -27,   120,
     100,    99,   -10,   201,    90,  -135,    30,  -153,    74,  -152,
     -29,   157,   163,  -153,  -110,  -153,   -62,  -153,   143,  -153,
     139,   -44,  -153
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    38,    39,    40,   107,
     133,   143,    11,    12,    13,    14,    15,    35,    31,    57,
      58,    59,    17,    18,   146,   147,   182,   183,   178,   179,
     112,    49,    50,    93,   113,   114,    51,    94,    52,    97,
      53,    54,    73
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    77,    81,    21,    26,    28,   153,    63,   155,   111,
     184,   169,   136,   144,    55,     3,     4,   137,    82,   138,
     139,     5,    41,    99,   100,    16,    74,    75,    19,   168,
     126,   123,   169,    71,   137,    72,   138,   139,    83,    56,
     140,   200,    83,   141,   134,   144,   142,   117,    61,   176,
     184,   119,    76,   152,   120,   197,   198,   140,    43,    44,
     141,    83,   186,   142,   148,    24,   203,    41,    78,    79,
     206,    45,    71,   158,   159,    22,    83,    83,   132,    46,
      27,   194,   199,    29,    47,    34,    43,    44,    60,   164,
     177,    44,   154,   156,    80,    30,   148,    30,    61,    45,
     148,    29,   148,    45,    29,   189,   145,    46,    67,    99,
     100,    46,    47,   165,   101,    30,    47,   -11,    30,    71,
      -9,    72,   171,   148,    71,     1,   116,     2,     3,     4,
      70,   180,   180,   180,     5,    28,    68,    26,   145,    99,
     100,   187,   145,    69,   131,    84,   148,   148,    85,    86,
      87,    88,    89,    90,    91,    92,   105,   148,    91,    92,
     196,   148,    83,   149,   180,    91,    92,    91,    92,   108,
     172,    37,   175,   180,     3,     4,    98,    20,     3,     4,
     104,    71,    71,   118,   159,    32,    33,    95,    96,    32,
      42,    64,    65,    64,    66,   102,   103,    91,    92,   127,
     128,   129,   130,   106,   115,   135,   151,   166,   157,   150,
     160,   161,   162,   170,   173,   174,   201,   188,   185,   190,
     191,    23,   192,    25,   193,   205,   195,   202,   109,   163,
      36,   110,   204,    62,   167,   181,   125,   124,     0,     0,
     121,     0,     0,     0,     0,     0,     0,   122
};

static const yytype_int16 yycheck[] =
{
      29,    45,    46,     5,    11,    15,   116,    34,   118,    71,
     162,   146,     3,   108,     4,     6,     7,     8,    47,    10,
      11,    12,    24,    23,    24,     3,     3,     4,     3,     3,
      30,    93,   167,    27,     8,    29,    10,    11,    14,    29,
      31,   193,    14,    34,   106,   140,    37,    76,     3,   159,
     202,    80,    29,   115,    30,   190,   191,    31,     3,     4,
      34,    14,    34,    37,   108,    29,   201,    69,     3,     4,
     205,    16,    27,   135,    29,     0,    14,    14,   105,    24,
       3,    34,   192,    13,    29,     3,     3,     4,    27,    34,
       3,     4,    30,    30,    29,    27,   140,    27,     3,    16,
     144,    13,   146,    16,    13,    13,   108,    24,     3,    23,
      24,    24,    29,   142,    28,    27,    29,    29,    27,    27,
      29,    29,   151,   167,    27,     3,    29,     5,     6,     7,
       3,   160,   161,   162,    12,   145,    30,   144,   140,    23,
      24,   170,   144,    33,    28,    15,   190,   191,    17,    18,
      19,    20,    21,    22,    23,    24,     3,   201,    23,    24,
     189,   205,    14,    28,   193,    23,    24,    23,    24,    31,
      28,     3,    28,   202,     6,     7,    56,     5,     6,     7,
      60,    27,    27,    29,    29,    33,    34,    25,    26,    33,
      34,    33,    34,    33,    34,    25,    26,    23,    24,    99,
     100,   102,   103,    27,    27,    27,    33,    32,    28,    30,
      29,    29,    29,    13,    30,    30,     9,    30,    32,    30,
      30,     7,    34,    11,    33,    30,    34,    34,    69,   140,
      21,    70,   202,    32,   144,   161,    97,    94,    -1,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    84
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      43,    50,    51,    52,    53,    54,     3,    60,    61,     3,
       5,    54,     0,    41,    29,    42,    51,     3,    60,    13,
      27,    56,    33,    34,     3,    55,    55,     3,    44,    45,
      46,    54,    34,     3,     4,    16,    24,    29,    68,    69,
      70,    74,    76,    78,    79,     4,    29,    57,    58,    59,
      27,     3,    61,    56,    33,    34,    34,     3,    30,    33,
       3,    27,    29,    80,     3,     4,    29,    79,     3,     4,
      29,    79,    68,    14,    15,    17,    18,    19,    20,    21,
      22,    23,    24,    71,    75,    25,    26,    77,    57,    23,
      24,    28,    25,    26,    57,     3,    27,    47,    31,    46,
      47,    74,    68,    72,    73,    27,    29,    68,    29,    68,
      30,    69,    70,    74,    76,    78,    30,    58,    58,    59,
      59,    28,    56,    48,    74,    27,     3,     8,    10,    11,
      31,    34,    37,    49,    50,    54,    62,    63,    79,    28,
      30,    33,    74,    72,    30,    72,    30,    28,    74,    29,
      29,    29,    29,    49,    34,    68,    32,    62,     3,    63,
      13,    68,    28,    30,    30,    28,    72,     3,    66,    67,
      68,    66,    64,    65,    67,    32,    34,    68,    30,    13,
      30,    30,    34,    33,    34,    34,    68,    63,    63,    72,
      67,     9,    34,    63,    64,    30,    63
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    43,
      43,    43,    44,    44,    45,    45,    46,    46,    46,    46,
      47,    47,    48,    48,    49,    49,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      55,    55,    56,    56,    57,    57,    57,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    61,    62,    62,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    64,
      64,    65,    65,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    71,    71,    71,    71,    71,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    79,    79,    80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     7,     2,
       2,     2,     1,     0,     3,     1,     2,     2,     3,     3,
       3,     4,     1,     0,     2,     1,     1,     0,     2,     1,
       1,     1,     4,     4,     3,     3,     1,     1,     1,     3,
       4,     2,     3,     4,     3,     3,     1,     3,     3,     1,
       1,     3,     1,     3,     1,     2,     3,     2,     1,     3,
       5,     9,     4,     5,     7,     5,     1,     2,     3,     1,
       0,     3,     1,     1,     3,     1,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     4,     4,     1,     2,     2,     4,     5,     5,     1,
       2,     2,     1,     2,     4,     3
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
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[0].node)); prog=(yyval.node);}
#line 1505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);}
#line 1511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 171 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                    }
#line 1519 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 175 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 181 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), (yyvsp[0].node));
                }
#line 1535 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 185 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 191 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[-6].node);
                        makeChild((yyval.node), (yyvsp[-4].node));
                        makeChild((yyval.node), (yyvsp[-1].node));
                    }
#line 1553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 198 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 1562 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 203 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                        makeFamily((yyval.node), 2, voidNode, makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 1572 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 209 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* idNode = makeIDNode((yyvsp[-1].lexeme), NORMAL_ID);
                        makeFamily((yyval.node), 2, idNode, makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 1582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 216 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(PARAM_LIST_NODE);
                        makeChild((yyval.node), (yyvsp[0].node));
                    }
#line 1591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 221 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(PARAM_LIST_NODE);
                    }
#line 1599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 227 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 231 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 237 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1624 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 242 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-1].lexeme), NORMAL_ID), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 247 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 252 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 258 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 262 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1667 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 268 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 272 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(NUL_NODE);
                }
#line 1683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 278 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 283 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 288 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 292 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                    }
#line 1718 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 298 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 302 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1734 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 308 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1742 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 312 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1750 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 318 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1759 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 323 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                    makeFamily((yyval.node), 2, voidNode, (yyvsp[-1].node));
                }
#line 1769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 331 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 336 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 1787 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 343 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);
                }
#line 1795 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 347 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 353 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1811 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 357 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-2].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1819 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 361 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 365 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 1835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 370 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 374 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 379 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 384 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 389 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 394 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 399 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 404 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1903 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 410 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1 = (yyvsp[0].const1);
                }
#line 1912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 415 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 421 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 425 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1936 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 431 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 435 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 1952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 439 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-2].lexeme), WITH_INIT_ID), (yyvsp[0].node));
                }
#line 1960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 445 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1968 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 449 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 457 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1984 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 461 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(WHILE_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1993 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 466 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(FOR_STMT);
                    makeFamily((yyval.node), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 471 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(ASSIGN_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2011 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 476 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-2].node), (yyvsp[0].node), Allocate(NUL_NODE));
                }
#line 2020 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 481 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2029 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 486 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-4].lexeme), NORMAL_ID), (yyvsp[-2].node));
                }
#line 2038 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 491 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(NUL_NODE);
                }
#line 2046 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 495 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), Allocate(NUL_NODE));
                }
#line 2055 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 500 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 507 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), (yyvsp[0].node));
                     }
#line 2072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 511 "parser.y" /* yacc.c:1646  */
    {
                         (yyval.node) = Allocate(NUL_NODE);
                     }
#line 2080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 517 "parser.y" /* yacc.c:1646  */
    {
                                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                    }
#line 2088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 521 "parser.y" /* yacc.c:1646  */
    {
                                        (yyval.node) = (yyvsp[0].node);
                                    }
#line 2096 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 527 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2104 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 533 "parser.y" /* yacc.c:1646  */
    {
                        //TODO: for simpler implementation, use ASSIGN_STMT for now
                        (yyval.node) = makeStmtNode(ASSIGN_STMT);
                        makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[0].node));
                    }
#line 2114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 539 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 545 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 549 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2139 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 556 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2147 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 560 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_AND);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2156 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 567 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2164 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 571 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2172 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 577 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2180 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 581 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2188 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 585 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 589 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2204 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 593 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2212 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 597 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2220 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 604 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), (yyvsp[0].node));
                    }
#line 2228 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 608 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
#line 2236 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 614 "parser.y" /* yacc.c:1646  */
    {
                                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                }
#line 2244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 618 "parser.y" /* yacc.c:1646  */
    {
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 624 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2260 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 628 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2268 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 634 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2276 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 638 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2284 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 644 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 648 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2300 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 654 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 658 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2316 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 664 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 668 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2333 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 673 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 678 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 683 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = (yyvsp[0].const1);
                    makeChild((yyval.node), constNode);
                }
#line 2362 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 690 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = (yyvsp[0].const1);
                    makeChild((yyval.node), constNode);
                }
#line 2373 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 697 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 2382 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 702 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                    makeChild((yyval.node), functionCallNode);
                }
#line 2393 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 709 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                    makeChild((yyval.node), functionCallNode);
                }
#line 2404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 716 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2412 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 720 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2421 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 725 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 732 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 736 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node),(yyvsp[0].node));
                }
#line 2447 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 744 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2455 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 748 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2463 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2467 "parser.tab.c" /* yacc.c:1646  */
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
#line 754 "parser.y" /* yacc.c:1906  */


#include "lex.yy.c"
#include <string.h>
#include <stdarg.h>
#include "codeGenerate.h"
    FILE* outputFile;
    int ifCount;
    int whileCount;
    int constCount;
	int forCount;
	int shortCutCount;
	int AROffset;
	int regStat[15] = {0};

    //label number should be maintained on a stack.

#define writeV8(s, b...)			\
  {						\
    fprintf(outputFile, s, ##b);		\
  }

void gen_prologue(char* name, int paramCount)
{
	int paramOffset = -8 * paramCount;
    writeV8("\t.text\n");
    writeV8("_start_%s:\n", name);
    writeV8("\tstr x30, [sp, #%d]\n", paramOffset);
    writeV8("\tstr x29, [sp, #%d]\n", paramOffset-8);
    writeV8("\tadd x29, sp, #%d\n", paramOffset-8);
    writeV8("\tadd sp, sp, #%d\n", paramOffset-16);
    writeV8("\tldr x30, =_frameSize_%s\n", name);
    writeV8("\tldr x30, [x30, #0]\n");
    writeV8("\tsub sp, sp, w30\n");
	writeV8("\tstr x9, [sp, #8]\n");
	writeV8("\tstr x10, [sp, #16]\n");
	writeV8("\tstr x11, [sp, #24]\n");
	writeV8("\tstr x12, [sp, #32]\n");
	writeV8("\tstr x13, [sp, #40]\n");
	writeV8("\tstr x14, [sp, #48]\n");
	writeV8("\tstr x15, [sp, #56]\n");
	writeV8("\tstr x16, [sp, #64]\n");
	writeV8("\tstr x17, [sp, #68]\n");
	writeV8("\tstr x18, [sp, #72]\n");
	writeV8("\tstr x19, [sp, #76]\n");
	writeV8("\tstr x20, [sp, #80]\n");
	writeV8("\tstr x21, [sp, #84]\n");
	writeV8("\tstr x22, [sp, #88]\n");
	writeV8("\tstr x23, [sp, #92]\n\n");
}

void gen_epilogue(char* name, int paramCount)
{
	int paramOffset = 8 * paramCount;
	writeV8("\n_end_%s:\n", name);
	writeV8("\tldr x9, [sp, #8]\n");
	writeV8("\tldr x10, [sp, #16]\n");
	writeV8("\tldr x11, [sp, #24]\n");
	writeV8("\tldr x12, [sp, #32]\n");
	writeV8("\tldr x13, [sp, #40]\n");
	writeV8("\tldr x14, [sp, #48]\n");
	writeV8("\tldr x15, [sp, #56]\n");
	writeV8("\tldr x16, [sp, #64]\n");
	writeV8("\tldr x17, [sp, #68]\n");
	writeV8("\tldr x18, [sp, #72]\n");
	writeV8("\tldr x19, [sp, #76]\n");
	writeV8("\tldr x20, [sp, #80]\n");
	writeV8("\tldr x21, [sp, #84]\n");
	writeV8("\tldr x22, [sp, #88]\n");
	writeV8("\tldr x23, [sp, #92]\n");
	writeV8("\tldr x30, [x29, #8]\n");
	writeV8("\tmov sp, x29\n");
	writeV8("\tadd sp, sp, #%d\n", paramOffset + 8);
	writeV8("\tldr x29, [x29, #0]\n");
	writeV8("\tRET x30\n");
	writeV8("\t.data\n");
}

void gen_frameSizeLabel(char* name, int size)
{
	writeV8("_frameSize_%s:\n", name);
	writeV8("\t.word %d\n", size);
}

void codeGenConvertFromIntToFloat(Reg* reg){
  Reg newReg;
  newReg.c = 's';
  newReg.no = getFreeReg(FLOAT_TYPE);
  writeV8("SCVTF %c%d, %c%d\n#convert int to float\n", newReg.c, newReg.no, reg->c, reg->no)//scvtf s, w
  freeReg(reg->no);
  reg->no = newReg.no;
  reg->c = newReg.c;
}

Reg doMath(AST_NODE* node)
{
	Reg reg;
	if(node->nodeType == CONST_VALUE_NODE)
	{
		int regNo;
		switch(node->semantic_value.const1->const_type)
		{
			case INTEGERC:
				writeV8("\t.data\n");
				writeV8("_CONSTANT_%d:\n", constCount);
				writeV8("\t.word %d\n", node->semantic_value.const1->const_u.intval);
				writeV8("\t.align 3\n");
				writeV8("\t.text\n");
				regNo = getFreeReg(INT_TYPE);
				writeV8("\tldr w%d, _CONSTANT_%d\n", regNo, constCount);
				constCount++;
				reg.c = 'w';
				break;
			case FLOATC:
				writeV8("\t.data\n");
				writeV8("_CONSTANT_%d:\n", constCount);
				writeV8("\t.float %f\n", node->semantic_value.const1->const_u.fval);
				writeV8("\t.align 3\n");
				writeV8("\t.text\n");
				regNo = getFreeReg(FLOAT_TYPE);
				writeV8("\tldr s%d, _CONSTANT_%d\n", regNo, constCount);
				constCount++;
				reg.c = 's';
				break;
		}
		reg.no = regNo;
		return reg;
	}
	else if(node->nodeType == IDENTIFIER_NODE)
	{
		int regNo;
		char* name = node->semantic_value.identifierSemanticValue.identifierName;
		DATA_TYPE type;

		SymbolTableEntry* entry = node->semantic_value.identifierSemanticValue.symbolTableEntry;
		if(node->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
		{
			int arrayElemRegNo = ldrArrayElem(node);
			type = entry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
			
			if(type == INT_TYPE)
			{
				regNo = getFreeReg(INT_TYPE);
				writeV8("\tldr w%d, [x%d, #0]\n", regNo, arrayElemRegNo);
				reg.c = 'w';
			}
			else if(type == FLOAT_TYPE)
			{
				regNo = getFreeReg(FLOAT_TYPE);
				writeV8("\tldr s%d, [x%d, #0]\n", regNo, arrayElemRegNo);
				reg.c = 's';
			}		
			freeReg(arrayElemRegNo);
			reg.no = regNo;
			return reg;
		}
		else if(node->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
		{
			type = entry->attribute->attr.typeDescriptor->properties.dataType;
			if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
			{
				if(entry->nestingLevel == 0)
				{
					char* label = entry->address.label;
					int labelReg = getFreeReg(INT_TYPE);
					writeV8("\tldr x%d, =%s\n", labelReg, label)
					if(type == INT_TYPE)
					{
						regNo = getFreeReg(INT_TYPE);
						writeV8("\tldr w%d, [x%d, #0]\n", regNo, labelReg);
						reg.c = 'w';
					}
					else if(type == FLOAT_TYPE)
					{
						regNo = getFreeReg(FLOAT_TYPE);
						writeV8("\tldr s%d, [x%d, #0]\n", regNo, labelReg);
						reg.c = 's';
					}
					freeReg(labelReg);
				}
				else
				{
					int FpOffset = entry->address.FpOffset;
//					printf("id %s FpOffset = %d\n", name, FpOffset);
					if(type == INT_TYPE)
					{
						regNo = getFreeReg(INT_TYPE);
						writeV8("\tldr w%d, [x29, #%d]\n", regNo, FpOffset);
						reg.c = 'w';
					}
					else if(type == FLOAT_TYPE)
					{
						regNo = getFreeReg(FLOAT_TYPE);
						writeV8("\tldr s%d, [x29, #%d]\n", regNo, FpOffset);
						reg.c = 's';
					}
				}
				reg.no = regNo;
			}
			else //if(entry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
			{	
				reg.no = getFreeReg(INT_TYPE);
				if(entry->nestingLevel == 0)
				{
					char* label = entry->address.label;
					writeV8("\tldr x%d, =%s\n", reg.no, label);
				}
				else
				{
					writeV8("\tadd x%d, x29, #%d\n", reg.no, entry->address.FpOffset);
				}
				reg.c = 'x';
			}
			return reg;
		}
	}
	else if(node->nodeType == EXPR_NODE)
	{
		if(node->semantic_value.exprSemanticValue.kind == BINARY_OPERATION)
		{
			if(node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_AND ||
			   node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_OR)
			{
				Reg resultReg;
				resultReg.c = 'w';
				resultReg.no = getFreeReg(INT_TYPE);
				Reg LHSReg = doMath(node->child);
				if(LHSReg.c == 'w')
				{
					writeV8("\tcmp %c%d, 0\n", LHSReg.c, LHSReg.no);
				} 
				else 
				{
					writeV8("\tfcmp %c%d, 0\n", LHSReg.c, LHSReg.no);
				}
				writeV8("\tcset w%d, ne\n", resultReg.no);
				freeReg(LHSReg.no);
				if(node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_AND)
				{
					writeV8("\tcmp w%d, 0\n", resultReg.no);
					writeV8("\tbeq shortCut%d\n", shortCutCount);
					Reg RHSReg = doMath(node->child->rightSibling);
					if(RHSReg.c == 'w')
					{
						writeV8("\tcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					} 
					else 
					{
						writeV8("\tfcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					}
					writeV8("\tcset w%d, ne\n", resultReg.no);
					freeReg(RHSReg.no);
				}
				else if(node->semantic_value.exprSemanticValue.op.binaryOp == BINARY_OP_OR)
				{
					writeV8("\tcmp w%d, 0\n", resultReg.no);
					writeV8("\tbne shortCut%d\n", shortCutCount);
					Reg RHSReg = doMath(node->child->rightSibling);
					if(RHSReg.c == 'w')
					{
						writeV8("\tcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					} 
					else 
					{
						writeV8("\tfcmp %c%d, 0\n", RHSReg.c, RHSReg.no);
					}
					writeV8("cset w%d, eq\n", resultReg.no);
					freeReg(RHSReg.no);
				}
				writeV8("shortCut%d:\n", shortCutCount++);
				return resultReg;
			}
			else
			{
				Reg LHSReg = doMath(node->child);
				Reg RHSReg = doMath(node->child->rightSibling);
				
				//handle implicit type conversion
				if(LHSReg.c == 'w' && RHSReg.c == 's')
					codeGenConvertFromIntToFloat(&LHSReg);
				else if(LHSReg.c == 's' && RHSReg.c == 'w')
					codeGenConvertFromIntToFloat(&RHSReg);
				
				switch(node->semantic_value.exprSemanticValue.op.binaryOp)
				{
					case BINARY_OP_ADD:
						if(LHSReg.c == 'w')
						{
							writeV8("\tadd %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfadd %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}	
						break;
					case BINARY_OP_SUB:
						if(LHSReg.c == 'w')
						{
							writeV8("\tsub %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfsub %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						break;
					case BINARY_OP_MUL:
						if(LHSReg.c == 'w')
						{
							writeV8("\tmul %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfmul %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						break;
					case BINARY_OP_DIV:
						if(LHSReg.c == 'w')
						{
							writeV8("\tsdiv %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						else
						{
							writeV8("\tfdiv %c%d, %c%d, %c%d\n", LHSReg.c, LHSReg.no, LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
						}
						break;
					case BINARY_OP_EQ:	// ==	
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, eq\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, eq\n", LHSReg.no);
						}
						break;
					case BINARY_OP_GE:	// >=
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, ge\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, ge\n", LHSReg.no);
						}
						break;
					case BINARY_OP_LE:	// <=
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, le\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, le\n", LHSReg.no);
						}
						break;
					case BINARY_OP_NE:	// !=
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, ne\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, ne\n", LHSReg.no);
						}
						break;
					case BINARY_OP_GT:	// >
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, gt\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, gt\n", LHSReg.no);
						}
						break;
					case BINARY_OP_LT:	// <
						if(LHSReg.c == 'w')
						{
							writeV8("\tcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							writeV8("\tcset %c%d, lt\n", LHSReg.c, LHSReg.no);
						}
						else
						{
							writeV8("\tfcmp %c%d, %c%d\n", LHSReg.c, LHSReg.no, RHSReg.c, RHSReg.no);
							freeReg(LHSReg.no);
							LHSReg.no = getFreeReg(INT_TYPE);
							LHSReg.c = 'w';
							writeV8("\tcset w%d, lt\n", LHSReg.no);
						}
						break;
					default:
						break;
				}
				freeReg(RHSReg.no);
				return LHSReg;
			}
		}
		else if(node->semantic_value.exprSemanticValue.kind == UNARY_OPERATION)
		{
			AST_NODE* valueNode = node->child;
			reg = doMath(valueNode);
			if(node->semantic_value.exprSemanticValue.op.unaryOp == UNARY_OP_NEGATIVE)
			{
				if(reg.c == 'w')
				{
					writeV8("\tneg %c%d, %c%d\n", reg.c, reg.no, reg.c, reg.no);
				}
				else
				{
					writeV8("\tfneg %c%d, %c%d\n", reg.c, reg.no, reg.c, reg.no);
				}
			}
			else if(node->semantic_value.exprSemanticValue.op.unaryOp == UNARY_OP_LOGICAL_NEGATION)
			{
				if(reg.c == 'w')
				{
					writeV8("\tcmp %c%d, #0\n", reg.c, reg.no);
					writeV8("\tcset w%d, eq\n", reg.no);
				}
				else
				{
					Reg resultReg;
					resultReg.no = getFreeReg(INT_TYPE);
					resultReg.c = 'w';
					writeV8("\tfcmp %c%d, #0.0\n", reg.c, reg.no);
					writeV8("\tcset w%d, eq\n", resultReg.no);
					freeReg(reg.no);
					return resultReg;
				}	
			}
			return reg;
		}
	}
	else if(node->nodeType == STMT_NODE && node->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
	{
		doFuncCallStmt(node);
		AST_NODE* funcNameNode = node->child;
		SymbolTableEntry* entry = funcNameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
		DATA_TYPE type = entry->attribute->attr.functionSignature->returnType;
		int retReg;
		if(type == INT_TYPE)
		{
			retReg = getFreeReg(INT_TYPE);
			writeV8("\tmov w%d, w0\n", retReg);
			reg.c = 'w';
		}
		else if(type == FLOAT_TYPE)
		{
			retReg = getFreeReg(FLOAT_TYPE);
			writeV8("\tfmov s%d, s0\n", retReg);
			reg.c = 's';
		}
		reg.no = retReg;
		return reg;
	}
}

int getFreeReg(DATA_TYPE type)
{
	int i;
	if(type == INT_TYPE)
	{
		i = 0;
		while(regStat[i] && i<7)
			i++;
		if(i == 7)
			return -1;
	}
	else
	{
		i = 7;
		while(regStat[i] && i<15)
			i++;
		if(i == 15)
			return -1;
	}
	regStat[i] = 1;
	return i+9;
}

void freeReg(int no, ...)
{
	regStat[no-9] = 0;
	
	va_list ap;
	int arg;
	
	va_start(ap, no);
	while(!(arg = va_arg(ap, int)))
	{
		printf("arg = %d\n", arg);
		regStat[arg-9] = 0;
	}
	va_end(ap);
}

int ldrArrayElem(AST_NODE* arrayIDNode)
{
	SymbolTableEntry* entry = arrayIDNode->semantic_value.identifierSemanticValue.symbolTableEntry;
	
	int dimension = entry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension;
	int* sizeInEachDimension = entry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension;
	
	int ctn;
	AST_NODE* indexNode = arrayIDNode->child;
	int offsetRegNo = getFreeReg(INT_TYPE);
	writeV8("\tmov w%d, #0\n", offsetRegNo);
	for(ctn=0; ctn < dimension; ctn++)
	{
		Reg indexReg = doMath(indexNode);
		int i = ctn+1;
		while(i < dimension)
		{
			int dimensionSizeRegNo = getFreeReg(INT_TYPE);
			writeV8("\tmov w%d, #%d\n", dimensionSizeRegNo, sizeInEachDimension[i++]);
			writeV8("\tmul w%d, w%d, w%d\n", indexReg.no, indexReg.no, dimensionSizeRegNo);
			freeReg(dimensionSizeRegNo);
		}
		writeV8("\tadd w%d, w%d, w%d\n", offsetRegNo, offsetRegNo, indexReg.no);
		freeReg(indexReg.no);
		indexNode = indexNode->rightSibling;
	}
	writeV8("\tlsl w%d, w%d, #2\n", offsetRegNo, offsetRegNo);
	
	int addressRegNo = getFreeReg(INT_TYPE);
	if(entry->nestingLevel == 0)
	{
		char* label = entry->address.label;
		writeV8("\tldr x%d, =%s\n", addressRegNo, label);
		writeV8("\tadd x%d, x%d, x%d\n", addressRegNo, addressRegNo, offsetRegNo);
	}
	else
	{
		if(entry->address.FpOffset > 0)
		{
			writeV8("\tldr x%d, [x29, #%d]\n", addressRegNo, entry->address.FpOffset);
		}
		else
		{
			writeV8("\tadd x%d, x29, #%d\n", addressRegNo, entry->address.FpOffset);
		}
		writeV8("\tsub x%d, x%d, x%d\n", addressRegNo, addressRegNo, offsetRegNo);
	}
	freeReg(offsetRegNo);
	return addressRegNo;
}

void doAssignStmt(AST_NODE* assignStatNode)
{
	AST_NODE* LHS = assignStatNode->child;
	AST_NODE* RHS = LHS->rightSibling;
	Reg RHSReg = doMath(RHS);
	
	SymbolTableEntry* LHSEntry = LHS->semantic_value.identifierSemanticValue.symbolTableEntry;
	DATA_TYPE type;
	if(LHS->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
	{
		type = LHSEntry->attribute->attr.typeDescriptor->properties.dataType;
	}
	if(LHS->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
	{
		type = LHSEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
	}
	if((type == FLOAT_TYPE) && (RHSReg.c == 'w'))	//type conversion
	{
		codeGenConvertFromIntToFloat(&RHSReg);
	}
	
	if(LHS->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
	{

		if(LHSEntry->nestingLevel == 0)
		{
			char* label = LHSEntry->address.label;
			int labelRegNo = getFreeReg(INT_TYPE);
			writeV8("\tldr x%d, =%s\n", labelRegNo, label);
			writeV8("\tstr %c%d, [x%d, #0]\n", RHSReg.c, RHSReg.no, labelRegNo);
			freeReg(labelRegNo);
		}
		else
		{
			writeV8("\tstr %c%d, [x29, #%d]\n", RHSReg.c, RHSReg.no, LHSEntry->address.FpOffset);		
//			constCount++;
		}
	}
	else if(LHS->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
	{
		int arrayElemRegNo = ldrArrayElem(LHS);
		
		writeV8("\tstr %c%d, [x%d, #0]\n", RHSReg.c, RHSReg.no, arrayElemRegNo);
		freeReg(arrayElemRegNo);	
	}

	freeReg(RHSReg.no);
}

void writeString(char* strName, char* strValue)
{
	//data part
	writeV8("\t.data\n");

	char* newStrValue = (char*)malloc(sizeof(strValue)*2);
	int count = 0;
	int newcount = 0;
	int length = 0;
	while(strValue[count] != '\0')
	{
    /*if(strValue[count] == '\n'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = 'n';
    } else if(strValue[count] == '\t'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = 't';
    } else if(strValue[count] == '\\'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = '\\';
    } else if(strValue[count] == '\r'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = 'r';
    } else if(strValue[count] == '\0'){
      newStrValue[newcount++] = '\\';
      newStrValue[newcount++] = '0';
      } else {*/
		newStrValue[newcount++] = strValue[count];
		count++;
	}
	newStrValue[newcount] = '\0';
	fprintf(stderr, "original strvalue = [%s], after = [%s]\n", strValue, newStrValue);

	writeV8("%s: .ascii %s\n", strName, newStrValue);

	int alignNum = 4-((strlen(newStrValue)+2)%4);
	if(alignNum == 4)
		alignNum = 0;
	writeV8("\t.align %d\n", alignNum);//align is 4 times
    
	//test part
	writeV8("\t.text\n");
	writeV8("\tldr x0, =%s\n", strName);//"_CONSTANT_0" or what?
	//mov x0, x9 //TODO: check is needed or not
	writeV8("\tbl _write_str\n");
}

void writeInt(Reg reg)//reg will read the value from local stack and write
{
	//if directly give a reg to write, it's value will be deleted(?) after called write()
	writeV8("\tmov w0, %c%d\n", reg.c, reg.no);
	writeV8("\tbl _write_int\n");
}

void writeFloat(Reg reg)
{
	writeV8("\tfmov s0, %c%d\n", reg.c, reg.no);
	writeV8("\tbl _write_float\n");
}

void readInt()//will read value into reg and write into local stack
{
	int i = getFreeReg(INT_TYPE);
	writeV8("\tbl _read_int\n");
	writeV8("\tmov w%d, w0\n", i);
	//writeV8("str w%d, [x29, #-4]\n", i);
}

void readFloat()
{
	int i = getFreeReg(FLOAT_TYPE);
	writeV8("\tbl _read_float\n");
	writeV8("\tfmov s%d, s0\n", i);
	//writeV8("str s%d, [x29, #-8]\n", i);
}

void doFuncCallStmt(AST_NODE* funcCallStmtNode)
{
	AST_NODE* funcNameNode = funcCallStmtNode->child;
	char* funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;

	AST_NODE* parameterListNode = funcNameNode->rightSibling;
	AST_NODE* paramNode = parameterListNode->child;
	if(strcmp(funcName, "fread") == 0)
	{//TODO: 1. how to assign(he use w0 as return val) 2. send parameter
		readFloat();
	} 
	else if(strcmp(funcName, "read") == 0)
	{
		readInt();
	} 
	else if(strcmp(funcName, "write") == 0)
	{
		Reg reg;
		char strName[20];
		switch(paramNode->dataType)
		{
			case INT_TYPE:
				reg = doMath(paramNode);
				writeInt(reg);
				freeReg(reg.no);
				break;
			case FLOAT_TYPE:
				reg = doMath(paramNode);
				writeFloat(reg);
				freeReg(reg.no);
				break;
			case CONST_STRING_TYPE:
				sprintf(strName, "_CONSTANT_%d", constCount++);//TODO: check data declare twice
				writeString(strName, paramNode->semantic_value.const1->const_u.sc);
				break;
		}
	} 
	else
	{
		SymbolTableEntry* funcEntry = funcNameNode->semantic_value.identifierSemanticValue.symbolTableEntry; 
		int paramCount = funcEntry->attribute->attr.functionSignature->parametersCount;
		while(paramCount > 0)
		{
			Reg paramReg = doMath(paramNode);
			writeV8("\tstr %c%d, [sp, #%d]\n", paramReg.c, paramReg.no, (paramCount-1)*(-8));
			paramNode = paramNode -> rightSibling;
			paramCount--;
		}
		writeV8("\tbl _start_%s\n", funcName);
	}
}

void doRetStmt(AST_NODE* stmtNode, char* funcName)
{
	AST_NODE* retValNode = stmtNode->child;
	Reg retReg = doMath(retValNode);
	writeV8("\tmov %c0, %c%d\n", retReg.c, retReg.c, retReg.no);
	writeV8("\tb _end_%s\n", funcName);
	freeReg(retReg.no);
}

void doStmtLst(AST_NODE* stmtLstNode, char* funcName)
{
	AST_NODE* stmtNode = stmtLstNode->child;
	while(stmtNode)
	{
		switch(stmtNode->semantic_value.stmtSemanticValue.kind)
		{
			case ASSIGN_STMT:
				doAssignStmt(stmtNode);
				break;
			case FUNCTION_CALL_STMT:
				doFuncCallStmt(stmtNode);
				break;
			case RETURN_STMT:
				doRetStmt(stmtNode, funcName);
				break;
			case WHILE_STMT:
				doWhileStmt(stmtNode, funcName);
				break;
			case FOR_STMT:
	 			doForStmt(stmtNode, funcName);
				break;
			case IF_STMT:
				doIfStmt(stmtNode, funcName);
				break;
		}
		stmtNode = stmtNode->rightSibling;
	}
}

inline void genLabel(char* name)
{
	writeV8("%s:\n", name);
}

inline void genGoto(char* name)
{
	writeV8("b %s\n", name);
}

inline void genBranch(Reg reg, char* tname, char* fname)
{
	if(reg.c == 'w')
	{
		writeV8("\tcmp %c%d, 0\n", reg.c, reg.no);
	} 
	else
	{
		writeV8("\tfcmp %c%d, 0\n", reg.c, reg.no);
	}
	freeReg(reg.no);
	writeV8("\tbeq %s\n", fname);
	writeV8("\tb %s\n", tname);
}

void doForStmt(AST_NODE* stmtNode, char* funcName)
{
	forCount++;
	char testName[15];
	sprintf(testName, "ForTest%d", forCount);
	char incName[15];
	sprintf(incName, "ForInc%d", forCount);
	char bodyName[15];
	sprintf(bodyName, "ForBody%d", forCount);
	char exitName[15];
	sprintf(exitName, "ForExit%d", forCount);

	AST_NODE* initNode = stmtNode->child;
	AST_NODE* testNode = initNode->rightSibling;
	AST_NODE* incNode = testNode->rightSibling;
	AST_NODE* bodyNode = incNode->rightSibling;
	//init
	writeV8("# forinit\n");
	doStmtLst(initNode, funcName);
	//test
	writeV8("# fortest\n");
	genLabel(testName);
	Reg reg = doMath(testNode->child);  //generate xxx
	genBranch(reg, bodyName, exitName);

	//inc
	writeV8("# forinc\n");
	genLabel(incName);
	doStmtLst(incNode, funcName);
	genGoto(testName);
	//body
	writeV8("# forbody\n");
	genLabel(bodyName);
	doBlock(bodyNode, funcName);
	genGoto(incName);
	//exit
	genLabel(exitName);
}

void doWhileStmt(AST_NODE* stmtNode, char* funcName)
{
	whileCount++;
	char testName[15];
	sprintf(testName, "WhileTest%d", whileCount);
	char exitName[15];
	sprintf(exitName, "WhileExit%d", whileCount);

	writeV8("%s:\n", testName);
	Reg reg = doMath(stmtNode->child);  //generate xxx
	//I wish to get result register 
	if(reg.c == 'w')
	{
		writeV8("\tcmp %c%d, 0\n", reg.c, reg.no);
  	}
	else
	{
    	writeV8("\tfcmp %c%d, 0\n", reg.c, reg.no);
  	}
	freeReg(reg.no);

	writeV8("\tbeq %s\n", exitName);
	doBlock(stmtNode->child->rightSibling, funcName);  //generate yyy
	writeV8("\tb %s\n", testName);
	writeV8("%s:\n", exitName);
}

void doIfStmt(AST_NODE* ifStmtNode, char* funcName)
{
	ifCount++;
	int elsePartCount = 0;
	char exitLabel[14];
	sprintf(exitLabel, "IfStmt%d_exit", ifCount);
		
	while(ifStmtNode->nodeType == STMT_NODE)
	{
		char beforeStartLabel[14] = {'\0'};
		char startLabel[14] = {'\0'};
		char elseIfLabel[14] = {'\0'};
		sprintf(beforeStartLabel, "IfStmt%d_%d", ifCount, elsePartCount++);
		sprintf(elseIfLabel, "IfStmt%d_%d", ifCount, elsePartCount);

		writeV8("%s:\n", beforeStartLabel);
		Reg conditionReg = doMath(ifStmtNode->child);
		writeV8("\tcmp %c%d, 0\n", conditionReg.c, conditionReg.no);
		writeV8("\tbeq %s\n", elseIfLabel);
		doBlock(ifStmtNode->child->rightSibling, funcName);
		writeV8("\tb %s\n", exitLabel);  

		ifStmtNode = ifStmtNode->child->rightSibling->rightSibling;
	}

	writeV8("IfStmt%d_%d:\n", ifCount, elsePartCount);
	if(ifStmtNode->nodeType == BLOCK_NODE)
	{
		doBlock(ifStmtNode, funcName);
	}
	writeV8("%s:\n", exitLabel);
}

void doBlock(AST_NODE* blockNode, char* funcName)
{
	AST_NODE* content = blockNode->child;
	while(content)
    {
		switch(content->nodeType)
		{
			case STMT_LIST_NODE:
				doStmtLst(content, funcName);
				break;
			case VARIABLE_DECL_LIST_NODE:
				doVarDeclLst(content, 1);
				break;
		}
		content = content->rightSibling;
    }
}

void doDeclFunc(AST_NODE* declNode)
{
	AST_NODE* funcNameNode = declNode->child->rightSibling;
	AST_NODE* paramLstNode = funcNameNode->rightSibling;
	AST_NODE* blockNode = paramLstNode->rightSibling;
	AST_NODE* content = blockNode->child;
	
	char* funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;	
	int frameSize = 92;
	AROffset = 0;
	
	AST_NODE* paramNode = paramLstNode->child;
	int paramCount = 0;
	while(paramNode)
	{
		AST_NODE* paramIDNode = paramNode->child->rightSibling;
		paramIDNode->semantic_value.identifierSemanticValue.symbolTableEntry->address.FpOffset = (paramCount+2) * 8;
		paramNode = paramNode->rightSibling;
		paramCount++;
	}
	
	gen_prologue(funcName, paramCount);

	while(content)
	{
		switch(content->nodeType)
		{
			case STMT_LIST_NODE:
				doStmtLst(content, funcName);
				break;
			case VARIABLE_DECL_LIST_NODE:
				doVarDeclLst(content, 1);
				break;
		}
		content = content->rightSibling;
	}

	gen_epilogue(funcName, paramCount);
	gen_frameSizeLabel(funcName, frameSize-AROffset);
	AROffset = 0;
}

void doVarDeclLst(AST_NODE* varDeclNode, int lv)
{
	varDeclNode = varDeclNode->child;
	while(varDeclNode)
	{
		AST_NODE* typeNode = varDeclNode->child;
		AST_NODE* nameNode = typeNode->rightSibling;
		while(nameNode)
		{
			char* name = nameNode->semantic_value.identifierSemanticValue.identifierName;
//			printf("Decl id %s\n", name);
			SymbolTableEntry* entry = nameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
			if(nameNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID || 
			   nameNode->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID)
			{
				if(lv == 0) //global var decl
				{
					char* label = (char*)malloc(sizeof(char)*(4+strlen(name)));
					sprintf(label, "_g_%s", name);
					label[strlen(name)+3] = '\0';
	
					writeV8("\t.data\n");
					writeV8("%s:\n", label);
					if(typeNode->dataType == INT_TYPE)
					{
						if(nameNode->child)
						{
							writeV8("\t.word %d\n", nameNode->child->semantic_value.const1->const_u.intval);
						}
						else
						{
							writeV8("\t.word 0\n");
						}
					}
					else if(typeNode->dataType == FLOAT_TYPE)
					{
						if(nameNode->child)
						{
							writeV8("\t.float %f\n", nameNode->child->semantic_value.const1->const_u.fval);
						}
						else
						{
							writeV8("\t.float 0\n");
						}
					}
					writeV8("\t.align 3\n");
					writeV8("\t.text\n");
					entry->address.label = label;
				}
				else
				{
					AROffset -= 4;
					entry->address.FpOffset = AROffset;
					if(nameNode->child)
					{
						Reg valReg = doMath(nameNode->child);
					
						if((typeNode->dataType == FLOAT_TYPE) && (valReg.c == 'w'))
						{
							codeGenConvertFromIntToFloat(&valReg);
						}	
						writeV8("\tstr %c%d, [x29, #%d]\n", valReg.c, valReg.no, AROffset);
						freeReg(valReg.no);
					}
				}
			}

			else if(nameNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
			{
				AST_NODE* arraySizeNode = nameNode->child;
				int arraySize = arraySizeNode->semantic_value.const1->const_u.intval;
				SymbolTableEntry* entry = nameNode->semantic_value.identifierSemanticValue.symbolTableEntry;
				if(lv == 0)
				{
					char* label = (char*)malloc(sizeof(char)*(4+strlen(name)));
					sprintf(label, "_g_%s", name);
					label[strlen(name)+3] = '\0';
	
					writeV8("\t.data\n");
					writeV8("%s:\n", label);
					writeV8("\t.place %d\n", arraySize);
					writeV8("\t.text\n");
					entry->address.label = label;
				}
				else
				{
					entry->address.FpOffset = AROffset-4;
					AROffset -= 4*arraySize;
				}
			}
//			printf("AROffset = %d, entry->address.FpOffset = %d\n", AROffset, entry->address.FpOffset);
			nameNode = nameNode->rightSibling;
		}
		varDeclNode = varDeclNode->rightSibling;
	}
}

void doDeclLst(AST_NODE* declNode)
{
	switch(declNode->semantic_value.declSemanticValue.kind)
	{
		case FUNCTION_DECL:
			doDeclFunc(declNode);
			break;
	}
}

void printCode(AST_NODE *root)
{
//frame information: temporarily added
    outputFile = fopen("output.s", "w");
    ifCount = 0;
    whileCount = 0;
    constCount = 0;
	forCount = 0;
	shortCutCount = 0;

	AST_NODE* child = root->child;
	while(child)
	{
		if(child->nodeType == VARIABLE_DECL_LIST_NODE)
		{
			doVarDeclLst(child, 0);
		}
		else if(child->nodeType == DECLARATION_NODE);
		{
			doDeclLst(child);
		}
		child = child->rightSibling;
	}
}

main (argc, argv)
int argc;
char *argv[];
{
	yyin = fopen(argv[1],"r");
	yyparse();
	printGV(prog, NULL);

	initializeSymbolTable();

	semanticAnalysis(prog);	

	symbolTableEnd();

	printCode(prog);
     
	if (!g_anyErrorOccur) {
		printf("Parsing completed. No errors found.\n");
	}
} /* main */



int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }
