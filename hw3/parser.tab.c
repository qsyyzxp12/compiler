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
#line 4 "parser.y" /* yacc.c:339  */

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
	while (a->rightSibling)
		a = a->rightSibling;

	if (b == NULL)
		return a;

	b = b->leftmostSibling;
	a->rightSibling = b;

	b->leftmostSibling = a->leftmostSibling;
	b->parent = a->parent;
	while (b->rightSibling)
	{
		b = b->rightSibling;
		b->leftmostSibling = a->leftmostSibling;
		b->parent = a->parent;
	}
	return b;
}

static inline AST_NODE* makeChild(AST_NODE *parent, AST_NODE *child)
{
	if (child == NULL)
		return parent;
    
	if (parent->child)
        	makeSibling(parent->child, child);
	else 
	{
		child = child->leftmostSibling;
		parent->child = child;
		while (child) 
		{
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


#line 175 "parser.tab.c" /* yacc.c:339  */

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

union YYSTYPE
{
#line 115 "parser.y" /* yacc.c:355  */

	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;

#line 259 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 276 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   264

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  212

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
       0,   169,   169,   176,   180,   184,   189,   193,   198,   205,
     209,   215,   220,   224,   229,   234,   239,   243,   249,   254,
     258,   265,   270,   276,   280,   285,   290,   294,   299,   304,
     310,   316,   322,   326,   331,   335,   340,   344,   350,   354,
     360,   365,   370,   375,   380,   385,   390,   395,   400,   404,
     410,   414,   418,   424,   429,   434,   438,   443,   448,   453,
     457,   462,   467,   471,   475,   480,   485,   490,   494,   500,
     504,   509,   519,   524,   529,   533,   539,   543,   549,   553,
     559,   563,   567,   571,   575,   579,   584,   590,   594,   598,
     603,   607,   612,   616,   621,   625,   630,   634,   639,   644,
     648,   654,   661,   666,   670,   675,   680,   684,   689,   693
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
  "global_decl_list", "global_decl", "function_decl", "param_list",
  "param", "dim_fn", "expr_null", "block", "decl_list", "decl",
  "type_decl", "var_decl", "type", "id_list", "dim_decl", "cexpr",
  "mcexpr", "cfactor", "init_id_list", "init_id", "stmt_list", "stmt",
  "else_if_list", "assign_expr_list", "nonempty_assign_expr_list",
  "assign_expr", "relop_expr", "relop_term", "relop_factor", "rel_op",
  "relop_expr_list", "nonempty_relop_expr_list", "expr", "add_op", "term",
  "mul_op", "factor", "var_ref", "dim_list", YY_NULLPTR
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

#define YYPACT_NINF -126

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-126)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     157,    24,    37,  -126,  -126,   192,    59,   157,  -126,  -126,
     157,  -126,  -126,  -126,    83,    64,   104,    74,    24,    24,
    -126,  -126,  -126,  -126,    16,   170,  -126,    12,  -126,   108,
    -126,    31,   172,   174,    49,    95,  -126,   113,  -126,  -126,
      12,   158,   184,  -126,    64,    88,    55,  -126,   126,  -126,
    -126,   -19,  -126,    18,    49,   119,   133,  -126,   153,   186,
    -126,  -126,   127,   117,     5,  -126,   155,    12,    12,    64,
      12,    12,  -126,   120,   130,   207,   138,    49,    49,   188,
     139,  -126,    49,  -126,    82,    49,    49,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,    49,    49,  -126,  -126,    49,
     120,   149,  -126,   184,   184,  -126,  -126,  -126,    22,   164,
     191,   194,   120,  -126,    66,   163,   120,   113,    23,  -126,
     211,   120,  -126,    49,   198,   160,   119,   171,   195,    49,
      49,    92,  -126,   133,  -126,   193,   186,  -126,   197,   120,
      49,    49,    49,    89,   199,  -126,    10,  -126,    23,   173,
    -126,    49,   201,   159,   193,    49,  -126,  -126,    49,   166,
     202,  -126,  -126,   203,   204,   206,   208,   122,    86,   196,
     209,  -126,   119,  -126,  -126,    41,  -126,  -126,   168,   119,
    -126,  -126,  -126,   205,    23,    23,    23,    49,    49,    89,
    -126,  -126,  -126,   228,  -126,  -126,   119,   210,  -126,    73,
    -126,    89,   212,  -126,   213,    49,    23,   215,  -126,    23,
     228,  -126
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    32,    33,     0,     0,     2,     5,     7,
       0,    25,    26,    27,     0,    34,     0,     0,     0,     0,
       1,     4,     6,    24,    50,     0,    48,     0,    37,     0,
      31,     0,     0,     0,     0,     0,    51,     0,    30,    46,
       0,     0,    42,    45,    35,     0,     0,    13,     0,    29,
      28,   106,   100,     0,     0,    52,    74,    76,    78,    91,
      95,   104,     0,     0,    50,    49,     0,     0,     0,    38,
       0,     0,    36,    23,     0,     0,    14,     0,    87,   107,
     106,   101,     0,   105,     0,     0,     0,    80,    83,    84,
      85,    81,    82,    92,    93,     0,     0,    96,    97,     0,
      23,     0,    47,    40,    41,    39,    43,    44,   106,     0,
       0,     0,    23,    62,     0,     0,    22,     0,    21,    54,
       0,    23,    12,    19,    15,     0,    89,     0,    86,     0,
      87,     0,    98,    75,    77,    79,    90,    94,     0,    23,
      87,     0,    87,    69,     0,    63,     0,    11,    20,   106,
      53,     0,     0,     0,    18,     0,   109,   102,     0,     0,
       0,    99,    10,     0,     0,     0,     0,    78,   106,     0,
      68,    71,    73,    55,    64,     0,     9,    16,     0,    88,
     108,   103,     8,     0,     0,     0,     0,     0,    87,     0,
      59,    17,    61,    67,    57,    56,    72,     0,    70,     0,
      60,    69,     0,    66,     0,     0,     0,     0,    58,     0,
      67,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,   233,   236,   214,   175,  -126,  -126,   -93,
     114,    -8,  -126,  -126,     4,   200,    -2,   216,   154,   156,
    -126,   217,   131,  -112,    38,    50,  -126,    63,   -34,   176,
     -85,  -126,  -125,  -126,   -65,  -126,   161,  -126,   165,   -50,
    -126
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    46,    47,   124,   153,   115,
     116,    11,    12,    13,   117,    16,    36,    41,    42,    43,
      25,    26,   118,   119,   200,   169,   170,   171,   126,    56,
      57,    95,   127,   128,    58,    96,    59,    99,    60,    61,
      79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,   134,    23,    83,    14,   160,   150,   138,    77,    19,
      78,    14,   125,    28,    14,   164,    39,   166,    34,   144,
      84,    80,    81,   120,    85,    15,   149,    15,   152,    34,
     135,   109,    27,   110,   111,    48,   150,     3,     4,    48,
      17,    40,    72,    27,   174,    35,   163,    82,   131,    77,
     120,   140,    51,    52,   112,    85,   165,   113,   154,    20,
     114,    45,   120,   197,   159,    53,   120,   105,   120,    51,
      52,   120,   193,   194,   195,   190,   149,   167,    54,    48,
     146,   202,    53,   110,   111,    74,    24,   203,    75,   120,
     178,    27,   168,    52,   208,    54,    85,   210,   120,   187,
     145,     3,     4,    31,   112,    53,    85,   113,    23,   172,
     114,    44,   132,    77,    10,    78,    64,   175,    54,    73,
     207,    10,   161,   108,   179,    62,     3,     4,   109,    76,
     110,   111,     5,    85,   120,   120,   120,    29,    30,    87,
      88,    89,    90,    91,    92,    93,    94,   101,    86,   120,
      75,   112,   186,   196,   113,   172,   120,   114,   100,   120,
       1,   121,     2,     3,     4,   123,    77,   172,   130,     5,
      87,    88,    89,    90,    91,    92,    93,    94,    67,    68,
     139,    67,    68,    93,    94,   102,    69,   177,   156,    93,
      94,    93,    94,   141,   180,   147,   191,    18,     3,     4,
      77,   157,   140,    37,    38,    29,    49,    29,    50,    70,
      71,    97,    98,     3,     4,   129,    93,    94,    32,    33,
     142,   103,   104,   143,   151,   155,   106,   107,   158,   162,
     188,   173,   181,   176,   183,   182,   184,   199,   185,   192,
      21,   205,   189,   206,   201,   209,    22,   148,   211,    63,
     122,   204,   198,     0,    65,     0,    66,   136,     0,     0,
       0,   133,     0,     0,   137
};

static const yytype_int16 yycheck[] =
{
      34,    86,    10,    53,     0,   130,   118,   100,    27,     5,
      29,     7,    77,    15,    10,   140,     4,   142,    13,   112,
      54,     3,     4,    73,    14,     3,     3,     3,   121,    13,
      95,     8,    27,    10,    11,    31,   148,     6,     7,    35,
       3,    29,    44,    27,    34,    29,   139,    29,    82,    27,
     100,    29,     3,     4,    31,    14,   141,    34,   123,     0,
      37,    30,   112,   188,   129,    16,   116,    69,   118,     3,
       4,   121,   184,   185,   186,    34,     3,   142,    29,    75,
     114,     8,    16,    10,    11,    30,     3,   199,    33,   139,
     155,    27,     3,     4,   206,    29,    14,   209,   148,    13,
      34,     6,     7,    29,    31,    16,    14,    34,   116,   143,
      37,     3,    30,    27,     0,    29,     3,   151,    29,    31,
     205,     7,    30,     3,   158,    30,     6,     7,     8,     3,
      10,    11,    12,    14,   184,   185,   186,    33,    34,    17,
      18,    19,    20,    21,    22,    23,    24,    30,    15,   199,
      33,    31,    30,   187,    34,   189,   206,    37,    31,   209,
       3,    31,     5,     6,     7,    27,    27,   201,    29,    12,
      17,    18,    19,    20,    21,    22,    23,    24,    23,    24,
      31,    23,    24,    23,    24,    30,    28,    28,    28,    23,
      24,    23,    24,    29,    28,    32,    28,     5,     6,     7,
      27,    30,    29,    33,    34,    33,    34,    33,    34,    25,
      26,    25,    26,     6,     7,    27,    23,    24,    18,    19,
      29,    67,    68,    29,    13,    27,    70,    71,    33,    32,
      34,    32,    30,    32,    30,    32,    30,     9,    30,    34,
       7,    29,    33,    30,    34,    30,    10,   116,   210,    35,
      75,   201,   189,    -1,    37,    -1,    40,    96,    -1,    -1,
      -1,    85,    -1,    -1,    99
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
      34,     3,     4,    16,    29,    66,    67,    68,    72,    74,
      76,    77,    30,    43,     3,    59,    55,    23,    24,    28,
      25,    26,    54,    31,    30,    33,     3,    27,    29,    78,
       3,     4,    29,    77,    66,    14,    15,    17,    18,    19,
      20,    21,    22,    23,    24,    69,    73,    25,    26,    75,
      31,    30,    30,    56,    56,    54,    57,    57,     3,     8,
      10,    11,    31,    34,    37,    47,    48,    52,    60,    61,
      77,    31,    44,    27,    45,    72,    66,    70,    71,    27,
      29,    66,    30,    67,    68,    72,    74,    76,    47,    31,
      29,    29,    29,    29,    47,    34,    66,    32,    60,     3,
      61,    13,    47,    46,    72,    27,    28,    30,    33,    72,
      70,    30,    32,    47,    70,    68,    70,    72,     3,    63,
      64,    65,    66,    32,    34,    66,    32,    28,    72,    66,
      28,    30,    32,    30,    30,    30,    30,    13,    34,    33,
      34,    28,    34,    61,    61,    61,    66,    70,    65,     9,
      62,    34,     8,    61,    63,    29,    30,    68,    61,    30,
      61,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    54,    54,
      55,    55,    55,    56,    56,    56,    57,    57,    58,    58,
      59,    59,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      72,    72,    73,    73,    74,    74,    75,    75,    76,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     3,     1,     1,     1,     3,     4,     2,     3,     4,
       3,     3,     1,     3,     3,     1,     1,     3,     1,     3,
       1,     2,     3,     2,     1,     3,     5,     5,     9,     4,
       6,     5,     1,     2,     3,     7,     2,     0,     1,     0,
       3,     1,     3,     1,     1,     3,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     3,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     4,
       1,     2,     4,     5,     1,     2,     1,     2,     4,     3
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
#line 170 "parser.y" /* yacc.c:1646  */
    { 	
	 		(yyval.node)=Allocate(PROGRAM_NODE);  
	 		makeChild((yyval.node),(yyvsp[0].node)); 
			prog=(yyval.node);
		}
#line 1517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 176 "parser.y" /* yacc.c:1646  */
    { 
			(yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);
		}
#line 1525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 181 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                    	}
#line 1533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 185 "parser.y" /* yacc.c:1646  */
    {
                        	(yyval.node) = (yyvsp[0].node);
                    	}
#line 1541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 190 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), (yyvsp[0].node));
                }
#line 1549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 194 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 199 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, (yyvsp[-7].node), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
		}
#line 1568 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 206 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
		}
#line 1576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 210 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[-6].node), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
		}
#line 1586 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 216 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
		}
#line 1594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 221 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 225 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1610 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 230 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1619 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 235 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 1627 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 240 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 244 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 250 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 1651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 254 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 1659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 259 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = Allocate(BLOCK_NODE);
			AST_NODE* decl_list = makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node));
			AST_NODE* stmt_list = makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node));
			makeFamily((yyval.node), 2, decl_list, stmt_list);
		}
#line 1670 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 266 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = Allocate(BLOCK_NODE);
			makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
		}
#line 1679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 271 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = Allocate(BLOCK_NODE);
			makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
		}
#line 1688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 276 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);/*?*/
		}
#line 1696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 281 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[-1].node);	/*?*/
			makeSibling((yyval.node), (yyvsp[-1].node));
                }
#line 1705 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 286 "parser.y" /* yacc.c:1646  */
    {			/*?*/
                        (yyval.node) = (yyvsp[0].node);
                }
#line 1713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 291 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
                }
#line 1721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 295 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
                }
#line 1729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 300 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeDeclNode(TYPE_DECL);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 305 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeDeclNode(TYPE_DECL);
			makeFamily((yyval.node), 2, makeIDNode("void", NORMAL_ID), (yyvsp[-1].node));
                }
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 311 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-2].node);
			makeSibling((yyval.node), (yyvsp[-1].node));

                }
#line 1757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 317 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeDeclNode(VARIABLE_DECL);
			makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 1766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 323 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = makeIDNode("int", NORMAL_ID);  
                }
#line 1774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 327 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 332 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 336 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-2].node);
			makeSibling((yyval.node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 341 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 1807 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 345 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
			makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 351 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-1].node);
                }
#line 1824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 355 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-2].node);
			makeSibling((yyval.node), (yyvsp[0].node));
		}
#line 1833 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 361 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 366 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 371 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
                }
#line 1859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 376 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1868 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 381 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 386 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
                }
#line 1885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 391 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = Allocate(CONST_VALUE_NODE);
			(yyval.node)->semantic_value.const1 = (yyvsp[0].const1);
                }
#line 1894 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 396 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-1].node);
                }
#line 1902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 401 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
		}
#line 1910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 405 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-2].node);
			makeSibling((yyval.node), (yyvsp[0].node));
		}
#line 1919 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 411 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1927 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 415 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 1935 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 419 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeIDNode((yyvsp[-2].lexeme), NORMAL_ID);
			makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 425 "parser.y" /* yacc.c:1646  */
    {
                    	(yyval.node) = (yyvsp[-1].node);
			makeSibling((yyval.node), (yyvsp[0].node));
                }
#line 1953 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 430 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = (yyvsp[0].node);
                }
#line 1961 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 435 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = (yyvsp[-1].node);
                }
#line 1969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 439 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeStmtNode(WHILE_STMT);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1978 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 444 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeStmtNode(WHILE_STMT);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 1987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 449 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = makeStmtNode(FOR_STMT);
			makeFamily((yyval.node), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1996 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 454 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 458 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeStmtNode(IF_STMT);
			makeFamily((yyval.node), 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
		}
#line 2013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 463 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
			makeFamily((yyval.node), 2, makeIDNode((yyvsp[-4].lexeme), NORMAL_ID), (yyvsp[-2].node));
		}
#line 2022 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 468 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2030 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 472 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2038 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 476 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2046 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 481 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = makeStmtNode(IF_STMT);
				makeFamily((yyval.node), 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
			}
#line 2055 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 486 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = (yyvsp[0].node);
			}
#line 2063 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 490 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = Allocate(NUL_NODE);
			}
#line 2071 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 495 "parser.y" /* yacc.c:1646  */
    {
                        	(yyval.node) = Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE);
				makeChild((yyval.node), (yyvsp[0].node));
                     	}
#line 2080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 500 "parser.y" /* yacc.c:1646  */
    {
				(yyval.node) = Allocate(NUL_NODE); 
			}
#line 2088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 505 "parser.y" /* yacc.c:1646  */
    {
                                        (yyval.node) = (yyvsp[-2].node);
					makeSibling((yyval.node), (yyvsp[0].node));
				}
#line 2097 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 510 "parser.y" /* yacc.c:1646  */
    {
                                        (yyval.node) = (yyvsp[0].node);
				}
#line 2105 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 520 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeStmtNode(ASSIGN_STMT);
			makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[0].node));
		}
#line 2114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 525 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
		}
#line 2122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 530 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 534 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2139 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 540 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = (yyvsp[0].node);
                }
#line 2147 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 544 "parser.y" /* yacc.c:1646  */
    {
                	(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2156 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 550 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
		}
#line 2164 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 554 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-1].node);
			makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
		}
#line 2173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 560 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2181 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 564 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2189 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 568 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2197 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 572 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2205 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 576 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2213 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 580 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2221 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 585 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE);
			makeChild((yyval.node), (yyvsp[0].node));
		}
#line 2230 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 590 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = Allocate(NUL_NODE);
		}
#line 2238 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 595 "parser.y" /* yacc.c:1646  */
    {
                                    /*TODO*/
                                }
#line 2246 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 599 "parser.y" /* yacc.c:1646  */
    {
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2254 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 604 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2262 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 608 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2270 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 613 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2278 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 617 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2286 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 622 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2294 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 626 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2302 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 631 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2310 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 635 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2318 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 640 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[-1].node); /*?*/
                }
#line 2326 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 645 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeSibling(makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION), (yyvsp[-1].node)); /*?*/
                }
#line 2334 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 649 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = Allocate(CONST_VALUE_NODE);
			(yyval.node)->semantic_value.const1 = (yyvsp[0].const1);
                }
#line 2343 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 655 "parser.y" /* yacc.c:1646  */
    {
			/*?*/
                        AST_NODE* CONST = Allocate(CONST_VALUE_NODE);
			CONST->semantic_value.const1 = (yyvsp[0].const1);
			(yyval.node) = makeSibling(makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION), CONST);
                }
#line 2354 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 662 "parser.y" /* yacc.c:1646  */
    {
			/*TODO*/
                }
#line 2362 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 667 "parser.y" /* yacc.c:1646  */
    {
			/*TODO*/
                }
#line 2370 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 671 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);
                }
#line 2378 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 676 "parser.y" /* yacc.c:1646  */
    {
			/*TODO*/
                }
#line 2386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 681 "parser.y" /* yacc.c:1646  */
    {
			(yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 685 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2402 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 690 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 694 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 2418 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2422 "parser.tab.c" /* yacc.c:1646  */
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
#line 697 "parser.y" /* yacc.c:1906  */


#include "lex.yy.c"
main (argc, argv)
int argc;
char *argv[];
{
	yyin = fopen(argv[1],"r");
	printf("Start parsing\n");
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
