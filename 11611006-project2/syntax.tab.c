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
#line 1 "syntax.y" /* yacc.c:339  */

	#include "tree.h"
	#define YYSTYPE struct treeNode*
	#include "list.h"
	
    #ifndef LEX
	#define LEX
	#include "lex.yy.c"
	#endif
	
	int childNum;
	int error_flag = 0;
	int struct_flag = 0;
	int arraySize_flag = 0;
	char errmsg[100];
	
	// temporary store child node
	struct treeNode* childNodeList[10];
	
	// temporarily store a list of variable
	struct FieldList* tmpList;
	
	// global
	struct FieldList* globalVariableList;
	struct FieldList* globalStructList;
	
	// funcList is already global
	struct FieldList* funcList;
	
	// store all variable in {  }
	// store all variable that can be used
	struct FieldList* allTmpVarList;
	struct FieldList* structList;
	
	//
	struct FieldList* stDefVarList;
	struct FieldList* stUseVarList;
	
	struct FieldList* retList;
	struct FieldList* funcArgs;
	
	struct FieldList* curFunc;
	Type baseType;
	Type funcRetType;
	
	void yyerror(char*);
	
	FieldList* validDecDefVar(char *name);
	FieldList* validUseVar(char *name);
	
	FieldList* varExist(char *name);
	
	// return 0 if variable add successfully
	// return 1 means error
	int addVar(FieldList*, struct treeNode*, int);
	int addFuncStruct(FieldList* head, struct treeNode* node, Type *type, int lineno);
	
	Type isValidAssign(struct treeNode *a, struct treeNode *b, int lineno);
	Type isValidOperation(struct treeNode *a, struct treeNode *b, char *operation, int lineno);
	Type getExpType(struct treeNode* node, int lineno);
	Type parseSpecifier(struct treeNode* node);

#line 129 "syntax.tab.c" /* yacc.c:339  */

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
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    TYPE = 258,
    ID = 259,
    CHAR = 260,
    FLOAT = 261,
    INT = 262,
    STRUCT = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    FOR = 267,
    RETURN = 268,
    DOT = 269,
    SEMI = 270,
    COMMA = 271,
    ASSIGN = 272,
    LT = 273,
    LE = 274,
    GT = 275,
    GE = 276,
    NE = 277,
    EQ = 278,
    PLUS = 279,
    MINUS = 280,
    MUL = 281,
    DIV = 282,
    AND = 283,
    OR = 284,
    NOT = 285,
    LP = 286,
    RP = 287,
    LB = 288,
    RB = 289,
    LC = 290,
    RC = 291,
    CS = 292,
    CE = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 233 "syntax.tab.c" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   432

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

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
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    71,    71,    76,    77,    79,    84,    85,    99,   101,
     105,   110,   128,   132,   141,   154,   155,   157,   164,   170,
     172,   173,   175,   180,   184,   185,   187,   188,   190,   191,
     194,   195,   198,   208,   209,   210,   212,   214,   215,   217,
     220,   229,   232,   234,   235,   237,   241,   253,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   315,   327,   328,   329,   336,   337,
     338,   339,   341,   343,   344,   346,   347,   349,   359
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "ID", "CHAR", "FLOAT", "INT",
  "STRUCT", "IF", "ELSE", "WHILE", "FOR", "RETURN", "DOT", "SEMI", "COMMA",
  "ASSIGN", "LT", "LE", "GT", "GE", "NE", "EQ", "PLUS", "MINUS", "MUL",
  "DIV", "AND", "OR", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "CS",
  "CE", "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList",
  "Specifier", "StructSpecifier", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "DefStmtList", "StmtList", "Stmt", "DefList",
  "Def", "DecList", "Dec", "Exp", "ExpList", "ExpListEx", "Args", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -77

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      52,   -83,    15,    43,   -83,    52,    59,   -83,    18,   -83,
     -83,    38,   -83,    10,    -9,    35,    52,    41,   -83,   -83,
      68,    69,    52,   -83,    68,    39,    52,   -83,   -83,    68,
      48,    65,   -83,   -83,    49,    90,    34,    11,    66,   -83,
     -83,    53,   -83,    52,   -83,   -83,    57,   -83,   -83,   -83,
      58,    73,    74,   255,   255,   255,   255,   -83,    51,    90,
     291,   255,   -83,   -83,    68,   -83,   187,   255,   255,   227,
     157,   -83,   399,   308,   -83,   -83,    90,   -83,    80,   -83,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   399,   -83,   -83,   328,     9,   345,
     362,   239,   382,   -83,    75,   -83,   -83,   -83,    52,   -83,
     399,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   270,   255,   -83,   -83,   138,   138,    85,
     255,   239,    71,   105,   -83,   -83,    98,   -83,   195,   -83,
     104,   -83,   -83,   138,    81,   195,   -83,   138,    91,   -83,
     138,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    11,     0,     0,     2,     4,     0,    12,    14,     1,
       3,    15,     6,     0,     9,     0,    40,     0,     8,     5,
       0,     0,    40,     7,     0,     0,    40,    19,    18,     0,
       0,    21,    15,    10,     0,     0,    45,     0,    43,    13,
      39,    22,    17,     0,    16,    72,    67,    70,    69,    68,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,    42,    41,     0,    20,     0,     0,     0,     0,
       0,    61,    62,     0,    24,    23,     0,    28,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    44,    64,    78,     0,     0,
       0,     0,    73,    75,     0,    36,    32,    60,    27,    66,
      47,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    48,    49,     0,     0,    71,    63,     0,     0,     0,
       0,     0,     0,     0,    65,    77,    33,    35,     0,    74,
       0,    25,    26,     0,     0,     0,    34,     0,     0,    37,
       0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -83,   -83,   117,   -83,   107,     4,   -83,    -6,   -83,    86,
     -83,   109,   -83,   -54,   -82,    40,   -52,    64,   -83,   -53,
       1,   -81,     8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    13,    24,     7,    14,    15,    30,
      31,    57,   132,    58,    59,    25,    26,    37,    38,    60,
     103,   104,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    71,    72,    73,     6,    77,    76,    20,    94,     6,
     125,    18,    62,    97,    99,   100,   102,   101,    36,     8,
     129,    29,   108,    41,    21,    19,    63,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   126,    27,     9,     1,   136,   137,    29,   102,     2,
     140,    61,    74,    16,     1,     1,   133,   144,    36,     2,
       2,   146,    35,    11,   148,   149,    40,    21,   151,    17,
      22,    97,    32,    28,    12,    39,    34,   102,   102,   142,
      42,    43,    64,    44,   109,   102,    21,    75,    66,    67,
     131,    45,   102,   -29,    46,    47,    48,    49,   -29,    50,
     138,    51,    52,    53,    68,    69,    45,   141,   143,    46,
      47,    48,    49,   147,    50,    54,    51,    52,    53,   145,
      55,    56,    10,   150,    23,    22,   -29,    33,    95,    65,
      54,   139,   135,     0,     0,    55,    56,     0,     0,    45,
      22,   -29,    46,    47,    48,    49,     0,    50,     0,    51,
      52,    53,     0,     0,     0,     0,     0,     0,   105,     0,
       0,     0,     0,    54,     0,     0,     0,     0,    55,    56,
       0,    78,   106,    22,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,     0,    45,     0,
      93,    46,    47,    48,    49,     0,    45,     0,     0,    46,
      47,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,     0,     0,     0,     0,    55,    56,    96,
      54,     0,     0,     0,     0,    55,    56,   -76,    45,     0,
       1,    46,    47,    48,    49,     2,     0,     0,     0,     0,
      45,     0,   -76,    46,    47,    48,    49,     0,     0,     0,
       0,     0,    54,     0,   -76,     0,    45,    55,    56,    46,
      47,    48,    49,     0,    54,     0,     0,     0,     0,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,    78,    55,    56,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,    93,   134,    78,    79,     0,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,     0,    78,     0,    93,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,     0,     0,
     107,    93,    78,     0,   124,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,     0,    78,
       0,    93,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,    78,   127,    93,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     0,     0,   128,    93,    78,     0,   130,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     0,    78,     0,    93,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,     0,
       0,     0,    93
};

static const yytype_int16 yycheck[] =
{
      53,    54,    55,    56,     0,    59,    58,    16,    61,     5,
       1,     1,     1,    66,    67,    68,    69,    69,    24,     4,
     101,    17,    76,    29,    33,    15,    15,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    32,     1,     0,     3,   127,   128,    43,   101,     8,
     131,    17,     1,    35,     3,     3,   108,   138,    64,     8,
       8,   143,    22,     4,   145,   147,    26,    33,   150,    31,
      35,   124,     4,    32,    15,    36,     7,   130,   131,   133,
      32,    16,    16,    34,     4,   138,    33,    36,    31,    31,
      15,     1,   145,     3,     4,     5,     6,     7,     8,     9,
      15,    11,    12,    13,    31,    31,     1,    36,    10,     4,
       5,     6,     7,    32,     9,    25,    11,    12,    13,    15,
      30,    31,     5,    32,    15,    35,    36,    20,    64,    43,
      25,   130,   124,    -1,    -1,    30,    31,    -1,    -1,     1,
      35,    36,     4,     5,     6,     7,    -1,     9,    -1,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    30,    31,
      -1,    14,    15,    35,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,     1,    -1,
      33,     4,     5,     6,     7,    -1,     1,    -1,    -1,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    30,    31,    32,
      25,    -1,    -1,    -1,    -1,    30,    31,    32,     1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
       1,    -1,    15,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    15,    -1,     1,    30,    31,     4,
       5,     6,     7,    -1,    25,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    14,    30,    31,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    33,    34,    14,    15,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    14,    -1,    33,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    14,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    14,
      -1,    33,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    14,    32,    33,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    14,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    14,    -1,    33,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,    40,    41,    42,    44,    45,     4,     0,
      41,     4,    15,    43,    46,    47,    35,    31,     1,    15,
      16,    33,    35,    50,    44,    54,    55,     1,    32,    44,
      48,    49,     4,    43,     7,    54,    46,    56,    57,    36,
      54,    46,    32,    16,    34,     1,     4,     5,     6,     7,
       9,    11,    12,    13,    25,    30,    31,    50,    52,    53,
      58,    17,     1,    15,    16,    48,    31,    31,    31,    31,
      58,    58,    58,    58,     1,    36,    55,    52,    14,    15,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    33,    58,    56,    32,    58,    61,    58,
      58,    55,    58,    59,    60,     1,    15,    32,    52,     4,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    16,     1,    32,    32,    32,    60,
      16,    15,    51,    55,    34,    61,    53,    53,    15,    59,
      60,    36,    52,    10,    60,    15,    53,    32,    60,    53,
      32,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    46,    47,    47,    47,
      48,    48,    49,    50,    50,    50,    51,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    59,    60,    60,    61,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     1,
       3,     1,     1,     5,     2,     1,     4,     4,     3,     3,
       3,     1,     2,     4,     4,     7,     2,     0,     2,     0,
       2,     1,     3,     5,     7,     5,     3,     8,     9,     2,
       0,     3,     3,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       1,     4,     1,     1,     3,     1,     0,     3,     1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 71 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Program", (yyloc).first_line); 
		//if (!error_flag) treePrint($$); 
	}
#line 1565 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 76 "syntax.y" /* yacc.c:1646  */
    { childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExtDefList", (yyloc).first_line); }
#line 1571 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 77 "syntax.y" /* yacc.c:1646  */
    { (yyval)=createEmpty(); }
#line 1577 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 79 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExtDef", (yyloc).first_line); 
		list_link(globalVariableList, tmpList);
		//list_link(globalStructList, structList);
	}
#line 1587 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 84 "syntax.y" /* yacc.c:1646  */
    { childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExtDef", (yyloc).first_line); }
#line 1593 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 85 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExtDef", (yyloc).first_line); 
		funcRetType = parseSpecifier((yyvsp[-2]));
		memcpy(list_getLast(funcList)->type, &funcRetType, sizeof(Type));
		FieldList* ret = retList->next;
		// delete member after checking
		while (ret != NULL){
			if (!isSameType(ret->type, &funcRetType)){
				printf("Error type 8 at Line %d: Function’s return value type mismatches the declared type\n", ret->lineno);
			}
			ret = ret->next;
		}
		list_clear(retList);
	}
#line 1612 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 99 "syntax.y" /* yacc.c:1646  */
    { printf("Error type B at Line %d: Specifier ExtDecList error\n", (yyloc).first_line); error_flag = 1; }
#line 1618 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 101 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExtDecList", (yyloc).first_line);
		addVar(tmpList, (yyvsp[0]), (yyloc).first_line);
	}
#line 1627 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 105 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExtDecList", (yyloc).first_line); 
		addVar(tmpList, (yyvsp[-2]), (yyloc).first_line);
	}
#line 1636 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 110 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Specifier", (yyloc).first_line); 
		baseType.category = PRIMITIVE;
		// "TYPE :"
		strcpy(baseType.name, (yyvsp[0])->value+6);
		switch (baseType.name[0]){
			case 'i':
				baseType.primitive = INT;
				break;
			case 'f':
				baseType.primitive = FLOAT;
				break;
			case 'c':
				baseType.primitive = CHAR;
				break;
		}
		//printf("INT %d FLOAT %d CHAR %d: %d %s\n", INT, FLOAT, CHAR, baseType.primitive, baseType.name);
	}
#line 1659 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 128 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Specifier", (yyloc).first_line); 
	}
#line 1667 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 132 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 5; childNodeList[0]=(yyvsp[-4]); childNodeList[1]=(yyvsp[-3]); childNodeList[2]=(yyvsp[-2]); childNodeList[3]=(yyvsp[-1]); childNodeList[4]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "StructSpecifier", (yyloc).first_line); 
		struct_flag = 1;
		baseType.category = STRUCTURE;
		baseType.structure = (FieldList*)malloc(sizeof(FieldList));
		list_link(baseType.structure, list_getLast(allTmpVarList)->vars);
		list_deleteLast(allTmpVarList);
		addFuncStruct(structList, (yyvsp[-3]), &baseType, (yylsp[-3]).first_line);
	}
#line 1681 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 141 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "StructSpecifier", (yyloc).first_line); 
		FieldList *structType;
		//"ID: "
		if ((structType = list_findByName(structList, (yyvsp[0])->value+4)) != NULL){
			baseType = *(structType->type);
		}
		else{
			error_flag = 1;
			printf("Struct '%s' is used without define.\n", (yyvsp[0])->value+4);
		}
	}
#line 1698 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 154 "syntax.y" /* yacc.c:1646  */
    { childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "VarDec", (yyloc).first_line); }
#line 1704 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 155 "syntax.y" /* yacc.c:1646  */
    { childNum = 4; childNodeList[0]=(yyvsp[-3]); childNodeList[1]=(yyvsp[-2]); childNodeList[2]=(yyvsp[-1]); childNodeList[3]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "VarDec", (yyloc).first_line); }
#line 1710 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 157 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 4; childNodeList[0]=(yyvsp[-3]); childNodeList[1]=(yyvsp[-2]); childNodeList[2]=(yyvsp[-1]); childNodeList[3]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "FunDec", (yyloc).first_line); 
		addFuncStruct(funcList, (yyvsp[-3]), &funcRetType, (yylsp[-3]).first_line);
		curFunc = list_getLast(funcList);
		curFunc->args = (FieldList*)malloc(sizeof(FieldList));
		list_link(curFunc->args, tmpList);
	}
#line 1722 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 164 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "FunDec", (yyloc).first_line); 
		addFuncStruct(funcList, (yyvsp[-2]), &funcRetType, (yylsp[-2]).first_line);
		curFunc = list_getLast(funcList);
		curFunc->args = NULL;
	}
#line 1733 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 170 "syntax.y" /* yacc.c:1646  */
    { printf("Error type B at Line %d: Missing \")\"\n", (yyloc).first_line); error_flag = 1; }
#line 1739 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 172 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "VarList", (yyloc).first_line); }
#line 1745 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 173 "syntax.y" /* yacc.c:1646  */
    { childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "VarList", (yyloc).first_line); }
#line 1751 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 175 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ParamDec", (yyloc).first_line); 
		addVar(tmpList, (yyvsp[0]), (yyloc).first_line);
	}
#line 1760 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 180 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 4; childNodeList[0]=(yyvsp[-3]); childNodeList[1]=(yyvsp[-2]); childNodeList[2]=(yyvsp[-1]); childNodeList[3]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "CompSt", (yyloc).first_line); 
		list_deleteLast(allTmpVarList);
	}
#line 1769 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 184 "syntax.y" /* yacc.c:1646  */
    { printf("Error type B at Line %d: Missing \"}\"\n", (yyloc).first_line); error_flag = 1; }
#line 1775 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 185 "syntax.y" /* yacc.c:1646  */
    { printf("Error type B at Line %d: Definition must at head.\n", (yylsp[-3]).first_line); error_flag = 1; }
#line 1781 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 190 "syntax.y" /* yacc.c:1646  */
    { childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "StmtList", (yyloc).first_line); }
#line 1787 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 191 "syntax.y" /* yacc.c:1646  */
    { (yyval)=createEmpty(); }
#line 1793 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 194 "syntax.y" /* yacc.c:1646  */
    { childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); }
#line 1799 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 195 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); 
	}
#line 1807 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 198 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); 
		Type type = getExpType((yyvsp[-1]), (yylsp[-1]).first_line);
		FieldList *ret = (FieldList*)malloc(sizeof(FieldList));
		ret->lineno = (yylsp[-1]).first_line;
		ret->next = NULL;
		ret->type = (Type*)malloc(sizeof(Type));
		memcpy(ret->type, &type, sizeof(Type));
		list_pushBack(retList, ret);
	}
#line 1822 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 208 "syntax.y" /* yacc.c:1646  */
    { childNum = 5; childNodeList[0]=(yyvsp[-4]); childNodeList[1]=(yyvsp[-3]); childNodeList[2]=(yyvsp[-2]); childNodeList[3]=(yyvsp[-1]); childNodeList[4]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); }
#line 1828 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 209 "syntax.y" /* yacc.c:1646  */
    { childNum = 7; childNodeList[0]=(yyvsp[-6]); childNodeList[1]=(yyvsp[-5]); childNodeList[2]=(yyvsp[-4]); childNodeList[3]=(yyvsp[-3]); childNodeList[4]=(yyvsp[-2]); childNodeList[5]=(yyvsp[-1]); childNodeList[6]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); }
#line 1834 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 210 "syntax.y" /* yacc.c:1646  */
    { childNum = 5; childNodeList[0]=(yyvsp[-4]); childNodeList[1]=(yyvsp[-3]); childNodeList[2]=(yyvsp[-2]); childNodeList[3]=(yyvsp[-1]); childNodeList[4]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); }
#line 1840 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 212 "syntax.y" /* yacc.c:1646  */
    { printf("Error type B at Line %d: Missing \";\"\n", (yyloc).first_line); error_flag = 1; }
#line 1846 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 214 "syntax.y" /* yacc.c:1646  */
    { childNum = 8; childNodeList[0]=(yyvsp[-7]); childNodeList[1]=(yyvsp[-6]); childNodeList[2]=(yyvsp[-5]); childNodeList[3]=(yyvsp[-4]); childNodeList[4]=(yyvsp[-3]); childNodeList[5]=(yyvsp[-2]); childNodeList[6]=(yyvsp[-1]); childNodeList[7]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); }
#line 1852 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 215 "syntax.y" /* yacc.c:1646  */
    { childNum = 9; childNodeList[0]=(yyvsp[-8]); childNodeList[1]=(yyvsp[-7]); childNodeList[2]=(yyvsp[-6]); childNodeList[3]=(yyvsp[-5]); childNodeList[4]=(yyvsp[-4]); childNodeList[5]=(yyvsp[-3]); childNodeList[6]=(yyvsp[-2]); childNodeList[7]=(yyvsp[-1]); childNodeList[8]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Stmt", (yyloc).first_line); }
#line 1858 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 217 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "DefList", (yyloc).first_line); 
	}
#line 1866 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 220 "syntax.y" /* yacc.c:1646  */
    { 
		(yyval)=createEmpty(); 
		FieldList* varDefList = (FieldList*)malloc(sizeof(FieldList));
		varDefList->next = NULL;
		varDefList->vars = (FieldList*)malloc(sizeof(FieldList));
		list_link(varDefList->vars, tmpList);
		list_pushBack(allTmpVarList, varDefList);
	}
#line 1879 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 229 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Def", (yyloc).first_line); 
	}
#line 1887 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 232 "syntax.y" /* yacc.c:1646  */
    { printf("Error type B at Line %d: Missing \";\"\n", (yyloc).first_line); error_flag = 1; }
#line 1893 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 234 "syntax.y" /* yacc.c:1646  */
    { childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "DecList", (yyloc).first_line); }
#line 1899 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 235 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "DecList", (yyloc).first_line); }
#line 1905 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 237 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Dec", (yyloc).first_line); 
		addVar(tmpList, (yyvsp[0]), (yyloc).first_line);
	}
#line 1914 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 241 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Dec", (yyloc).first_line); 
		if (addVar(tmpList, (yyvsp[-2]), (yyloc).first_line) == 0){
			Type tmp = getExpType((yyvsp[0]), (yylsp[-1]).first_line);
			if (!isSameType(&tmp, list_getLast(tmpList)->type)){
				error_flag = 1;
				printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", (yylsp[-1]).first_line);
			}
		}
	}
#line 1929 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 253 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); 
		Type type = isValidAssign((yyvsp[-2]), (yyvsp[0]), (yylsp[-1]).first_line);
		if (type.category == DIFFERENT) {
			error_flag = 1;
			printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", (yylsp[-1]).first_line);
		}
		if ((yyvsp[-2])->childNum == 1) {
			char str[5]; memset(str, 0, sizeof(str));
			memcpy(str, (yyvsp[-2])->child[0]->value, sizeof(char)*4);
			if (!strcmp(str, "INT:") || !strcmp(str, "CHAR") || !strcmp(str, "FLOA")){
				error_flag = 1;
				printf("Error type 6 at Line %d: rvalue on the left side of assignment operator\n", (yylsp[-2]).first_line);
			}
		}
	}
#line 1950 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 269 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1956 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 270 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1962 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 271 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1968 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 272 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1974 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 273 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1980 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 274 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1986 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 275 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1992 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 276 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 1998 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 277 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2004 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 278 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2010 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 279 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2016 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 280 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2022 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 281 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2028 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 282 "syntax.y" /* yacc.c:1646  */
    { childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2034 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 283 "syntax.y" /* yacc.c:1646  */
    { childNum = 2; childNodeList[0]=(yyvsp[-1]); childNodeList[1]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2040 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 284 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 4; childNodeList[0]=(yyvsp[-3]); childNodeList[1]=(yyvsp[-2]); childNodeList[2]=(yyvsp[-1]); childNodeList[3]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); 
		//printf("Size = %d %s\n", list_size(funcList), $1->value+4);
		FieldList* func;
		if ((func = list_findByName(funcList, (yyvsp[-3])->value+4)) == NULL) { // "ID: "
			error_flag = 1;
			if (validUseVar((yyvsp[-3])->value+4)){
				printf("Error type 11 at Line %d: Applying function invocation operator '()' on non-function names '%s'\n", (yylsp[-3]).first_line, (yyvsp[-3])->value+4);
			}
			else{
				printf("Error type 2 at Line %d: Function '%s' is invoked without definition\n", (yylsp[-3]).first_line, (yyvsp[-3])->value+4);
			}
		}
		else{
			FieldList *cur1 = func->args->next, *cur2 = funcArgs->next;
			int ok = 1;
			//printf("Size %d %d\n", list_size(func->args), list_size(funcArgs));
			while (cur1 != NULL && cur2 != NULL){
				if (!isSameType(cur1->type, cur1->type)){
					ok = 0;
					break;
				}
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			if (!ok || (cur1 == NULL && cur2 != NULL) || (cur1 != NULL && cur2 == NULL)){
				printf("Error type 9 at Line %d: Function’s arguments mismatch the declared parameters\n", (yylsp[-1]).first_line);
			}
		}
		list_clear(funcArgs);
	}
#line 2076 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 315 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); 
		if (list_findByName(funcList, (yyvsp[-2])->value+4) == NULL) { // "ID: "
			error_flag = 1;
			if (validUseVar((yyvsp[-2])->value+4)){
				printf("Error type 11 at Line %d: Applying function invocation operator '()' on non-function names '%s'\n", (yylsp[-2]).first_line, (yyvsp[-2])->value+4);
			}
			else{
				printf("Error type 2 at Line %d: Function '%s' is invoked without definition\n", (yylsp[-2]).first_line, (yyvsp[-2])->value+4);
			}
		}
	}
#line 2093 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 327 "syntax.y" /* yacc.c:1646  */
    { childNum = 4; childNodeList[0]=(yyvsp[-3]); childNodeList[1]=(yyvsp[-2]); childNodeList[2]=(yyvsp[-1]); childNodeList[3]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2099 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 328 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2105 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 329 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); 
		if (validUseVar((yyvsp[0])->value+4) == NULL) { //"ID: "
			error_flag = 1;
			printf("Error type 1 at Line %d: Variable '%s' is not defined\n", (yyloc).first_line, (yyvsp[0])->value+4);
		}
	}
#line 2117 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 336 "syntax.y" /* yacc.c:1646  */
    { childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2123 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 337 "syntax.y" /* yacc.c:1646  */
    { childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2129 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 338 "syntax.y" /* yacc.c:1646  */
    { childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Exp", (yyloc).first_line); }
#line 2135 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 339 "syntax.y" /* yacc.c:1646  */
    { printf("Error type B at Line %d: Missing \")\"\n", (yyloc).first_line); error_flag = 1; }
#line 2141 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 341 "syntax.y" /* yacc.c:1646  */
    { /*printf("error\n"); yyerrok;*/ error_flag = 1; }
#line 2147 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 343 "syntax.y" /* yacc.c:1646  */
    { childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExpList", (yyloc).first_line); }
#line 2153 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 344 "syntax.y" /* yacc.c:1646  */
    { childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "ExpList", (yyloc).first_line); }
#line 2159 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 346 "syntax.y" /* yacc.c:1646  */
    { (yyval)=(yyvsp[0]); }
#line 2165 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 347 "syntax.y" /* yacc.c:1646  */
    { (yyval) = createEmpty(); }
#line 2171 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 349 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 3; childNodeList[0]=(yyvsp[-2]); childNodeList[1]=(yyvsp[-1]); childNodeList[2]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Args", (yyloc).first_line); 
		FieldList* arg = (FieldList*)malloc(sizeof(FieldList));
		arg->next = NULL;
		arg->type = (Type*)malloc(sizeof(Type));
		Type type = getExpType((yyvsp[-2]), (yylsp[-2]).first_line);
		memcpy(arg->type, &type, sizeof(type));
		//printf("type %s", TypeToString(arg->type));
		list_pushBack(funcArgs, arg);
	}
#line 2186 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 359 "syntax.y" /* yacc.c:1646  */
    { 
		childNum = 1; childNodeList[0]=(yyvsp[0]); (yyval)=createNode(childNum, childNodeList, "Args", (yyloc).first_line); 
		FieldList* arg = (FieldList*)malloc(sizeof(FieldList));
		arg->next = NULL;
		arg->type = (Type*)malloc(sizeof(Type));
		Type type = getExpType((yyvsp[0]), (yylsp[0]).first_line);
		memcpy(arg->type, &type, sizeof(type));
		//printf("type %d %d %s\n", type.category, type.primitive, TypeToString(&type));
		list_pushBack(funcArgs, arg);
	}
#line 2201 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2205 "syntax.tab.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 370 "syntax.y" /* yacc.c:1906  */


void yyerror(char* s){
	//printf("%s\n", s);
}

char* TypeToString(Type *type){
	char* res;
	switch (type->category){
		case PRIMITIVE:
			//res = (char*)malloc(sizeof(char)*256);
			if (type->primitive == INT) return "INT";
			if (type->primitive == CHAR) return "CHAR";
			if (type->primitive == FLOAT) return "FLOAT";
			//sprintf(res, "%s", type->name);
			//return res;
			break;
		case ARRAY:
			res = ArrayToString(type->array);
			return res;
			break;
		case STRUCTURE:
			printf("FieldList in Struct: %d\n", list_size(type->structure));
			FieldListToString(type->structure);
			return "struct";
			break;
	}
	return res;
}

char* ArrayToString(Array *array){
	char *res = (char*)malloc(sizeof(char)*256);
	sprintf(res, "array baseTypeName=%s size=%d", array->base->name, array->size);
	return res;
}

char *FieldListToString(FieldList* head){
	FieldList* cur = head->next;
	while (cur != NULL){
		printf("Name:%s Type:%s\n", cur->name, TypeToString(cur->type));
		cur = cur->next;
	}
}

FieldList* validDecDefVar(char *name){
	// Just check current field
	FieldList* var;
	var = list_findByName(list_getLast(allTmpVarList)->vars, name);
	if (var != NULL) return var;
	var = list_findByName(tmpList, name);
	if (var != NULL) return var;
	/*
	var = list_getLast(funcList);
	if (var != NULL){
		return list_findByName(var->args, name);
	}
	else 
		return NULL;
	*/
	return NULL;
}

FieldList* validUseVar(char *name){
	// check all fields
	FieldList* var;
	
	FieldList* cur = allTmpVarList->next;
	while (cur != NULL){
		var = list_findByName(cur->vars, name);
		if (var != NULL) return var;
		cur = cur->next;
	}
	var = list_findByName(tmpList, name);
	if (var != NULL) return var;
	var = list_getLast(funcList);
	if (var != NULL){
		return list_findByName(var->args, name);
	}
	else 
		return NULL;
	return NULL;
}

FieldList* varExist(char *name){
	FieldList* var;
	var = list_findByName(list_getLast(allTmpVarList)->vars, name);
	if (var != NULL) return var;
	var = list_findByName(tmpList, name);
	if (var != NULL) return var;
	var = list_getLast(funcList);
	if (var != NULL){
		return list_findByName(var->args, name);
	}
	else 
		return NULL;
	return NULL;
}

int addVar(FieldList* head, struct treeNode* node, int lineno){
	// "ID: "
	if (validDecDefVar(node->child[0]->value+4) != NULL)
	{
		error_flag = 1;
		printf("Error type 3 at Line %d: Variable '%s' is redefined\n", lineno, node->child[0]->value+4);
		return 1;
	}
	if (node->childNum == 1){ // just variable, not array
		FieldList* newItem = (FieldList*)malloc(sizeof(FieldList));
		newItem->type = (Type*)malloc(sizeof(Type));
		memcpy(newItem->type, &baseType, sizeof(Type));
		strcpy(newItem->name, node->child[0]->value+4);
		newItem->next = NULL;
		list_pushBack(head, newItem);
	}
	if (node->childNum == 4){ // array
		FieldList* newItem = (FieldList*)malloc(sizeof(FieldList));
		
		Array *array = (Array*)malloc(sizeof(Array));
		array->base = (Type*)malloc(sizeof(Type));
		memcpy(array->base, &baseType, sizeof(Type));
		array->size = strToInt(node->child[2]->value+5); // "INT: "
		
		newItem->type = (Type*)malloc(sizeof(Type));
		newItem->type->category = ARRAY;
		newItem->type->array = array;
		// just support 1 dimension array
		strcpy(newItem->name, node->child[0]->child[0]->value+4);
		newItem->next = NULL;
		list_pushBack(head, newItem);
	}
	return 0;
}

int addFuncStruct(FieldList* head, struct treeNode* node, Type *type, int lineno){
	// "ID: "
	if (list_findByName(head, node->value+4) != NULL){
		error_flag = 1;
		if (!strcmp(head->name, "func"))
			printf("Error type 4 at Line %d: Function '%s' is redefined\n", lineno, node->value+4);
		if (!strcmp(head->name, "struct"))
			printf("Error type 15 at Line %d: Redefine the same structure type\n", lineno, node->value+4);
		return 1;
	}
	
	FieldList* newItem = (FieldList*)malloc(sizeof(FieldList));
	newItem->type = (Type*)malloc(sizeof(Type));
	memcpy(newItem->type, type, sizeof(Type));
	strcpy(newItem->name, node->value+4);
	newItem->next = NULL;
	list_pushBack(head, newItem);
	
	//printf("BaseType INT %d FLOAT %d CHAR %d: %d %d %s\n", INT, FLOAT, CHAR, baseType.category, baseType.primitive, baseType.name);
	//printf("NewItem  INT %d FLOAT %d CHAR %d: %d %d %s\n", INT, FLOAT, CHAR, newItem->type->category, newItem->type->primitive, newItem->type->name);

	return 0;
}

Type isValidAssign(struct treeNode *a, struct treeNode *b, int lineno){
	Type type_a, type_b;
	type_a = getExpType(a, lineno);
	type_b = getExpType(b, lineno);
	Type type;
	if (isSameType(&type_a, &type_b)){
		return type_a;
	}
	else {
		type.category = DIFFERENT;
		return type;
	}
}

Type isValidOperation(struct treeNode *a, struct treeNode *b, char* operation, int lineno){
	Type type_a, type_b;
	type_a = getExpType(a, lineno);
	type_b = getExpType(b, lineno);
	if (type_a.category == IGNORE) return type_a;
	if (type_b.category == IGNORE) return type_b;
	//printf("a %d %d b %d %d\n", type_a.category, type_a.primitive, type_b.category, type_b.primitive);
	Type type;
	if (type_a.category == PRIMITIVE && (type_a.primitive == INT || type_a.primitive == FLOAT) && isSameType(&type_a, &type_b)){
		return type_a;
	}
	else {
		error_flag = 1;
		printf("Error type 7 at Line %d: Invalid operation '%s' on non-number variables\n", lineno, operation);
		type.category = DIFFERENT;
		return type;
	}
}

Type getExpType(struct treeNode* node, int lineno){
	Type type;
	switch (node->childNum){
		case 1: // ID INT CHAR FLOAT
			//printf("node value = %s\n", node->child[0]->value);
			switch (node->child[0]->value[0]){
				case 'I': // INT or ID
					if (node->child[0]->value[1] == 'D'){ // ID
						FieldList* var;
						if ((var = validUseVar(node->child[0]->value+4)) != NULL){ //"ID: "
							return *(var->type);
						}
						else{ // not find this variable, just ignore it
							//printf("Ignore it!\n");
							//printf("node value = %s\n", node->value);
							type.category = IGNORE;
							return type;
						}
					}
					else { // INT
						type.category = PRIMITIVE;
						type.primitive = INT;
						return type;
					}
					break;
				case 'C': // CHAR
					type.category = PRIMITIVE;
					type.primitive = CHAR;
					return type;
					break;
				case 'F': // FLOAT
					type.category = PRIMITIVE;
					type.primitive = FLOAT;
					return type;
					break;
			}
			break;
		case 2: // only 'MINUS Exp' or 'NOT Exp'
			return getExpType(node->child[1], lineno);
			break;
		case 3:
			// LP Exp RP
			if (!strcmp(node->child[0]->value, "LP") && !strcmp(node->child[2]->value, "RP")){
				return getExpType(node->child[1], lineno);
			}
			// ID LP RP
			if (!strcmp(node->child[1]->value, "LP") && !strcmp(node->child[2]->value, "RP")){
				FieldList *func = list_findByName(funcList, node->child[0]->value+4); // "ID: "
				char *res = TypeToString(func->type);
				//printf("function return type: %s\n", res);
				return *(func->type);
			}
			if (!strcmp(node->child[1]->value, "ASSIGN")){ // for ASSIGN operation, just ensure two Exp has same type
				return isValidAssign(node->child[0], node->child[2], lineno);
			}
			else{
				// Exp DOT ID
				//printf("Operation: %s\n", node->child[1]->value);
				if (!strcmp("DOT", node->child[1]->value)){
					type = getExpType(node->child[0], lineno);
					if (type.category != STRUCTURE){
						error_flag = 1;
						printf("Error type 13 at Line %d: Accessing member of non-structure variable\n", lineno);
						type.category = IGNORE;
						return type;
					}
					else{
						//printf("StructList: %d %d %d\n", type.category, type.structure, list_size(type.structure));
						//FieldListToString(type.structure);
						FieldList* var = list_findByName(type.structure, node->child[2]->value+4);
						if (var == NULL){
							error_flag = 1;
							printf("Error type 14 at Line %d: Accessing an undefined structure member '%s'\n", lineno, node->child[2]->value+4);
							type.category = IGNORE;
							return type;
						}
						else {
							return *(var->type);
						}
					}
				}
				else{
					return isValidOperation(node->child[0], node->child[2], node->child[1]->value, lineno);
				}
			}
			break;
		case 4: 
			// ID LP Args RP
			if (!strcmp(node->child[1]->value, "LP") && !strcmp(node->child[3]->value, "RP")){
				FieldList *func = list_findByName(funcList, node->child[0]->value+4); // "ID: "
				if (func != NULL) return *(func->type);
				else{
					type.category = IGNORE;
					return type;
				}
			}
			//Exp LB Exp RB
			if (!strcmp(node->child[1]->value, "LB") && !strcmp(node->child[3]->value, "RB")){
				type = getExpType(node->child[2], lineno);
				//printf("Type category: %d primitive %d INT %d BOOL %d childNum %d\n", 
				//	type.category, type.primitive, INT, (type.category == PRIMITIVE && type.primitive == INT), node->child[2]->childNum);
				if (!(type.category == PRIMITIVE && type.primitive == INT)){
					error_flag = 1;
					printf("Error type 12 at Line %d: Array indexing with non-integer type expression\n", lineno);
					type.category = IGNORE;
					return type;
				}
				type = getExpType(node->child[0], lineno);
				if (type.category != ARRAY){
					error_flag = 1;
					printf("Error type 10 at Line %d: Applying indexing operator '[]' on non-array type variabless\n", lineno);
					type.category = IGNORE;
					return type;
				}
				type = *(type.array->base);
				return type;
			}
			break;
	}
}

Type parseSpecifier(struct treeNode* node){
	Type type;
	node = node->child[0];
	if (strcmp(node->value, "TYPE")){
		type.category = PRIMITIVE;
		// "TYPE :"
		strcpy(type.name, node->value+6);
		switch (type.name[0]){
			case 'i':
				type.primitive = INT;
				break;
			case 'f':
				type.primitive = FLOAT;
				break;
			case 'c':
				type.primitive = CHAR;
				break;
		}
	}
	return type;
}

void parseCompSt(struct treeNode* node){
	// CompSt -> LC DefList StmtList RC
	// DefList -> Def DefList
	// Def -> Specifier DecList SEMI
	struct treeNode* DefList = node->child[1];
	
}

int main(){
	globalVariableList = list_init();
	globalStructList = list_init();
	
	tmpList = list_init();
	allTmpVarList = list_init();
	
	funcList = list_init(); memcpy(funcList->name, "func", 4);
	
	retList = list_init();
	funcArgs = list_init();
	
	structList = list_init(); memcpy(structList->name, "struct", 6);
	
	stDefVarList = list_init();
	stUseVarList = list_init();
	
    yyparse();
	//#define DEBUG
	#ifdef DEBUG
	printf("Variable List\n");
	//FieldListToString();
	printf("Function List\n");
	FieldListToString(funcList);
	printf("Struct List\n");
	FieldListToString(structList);
	#endif
}
