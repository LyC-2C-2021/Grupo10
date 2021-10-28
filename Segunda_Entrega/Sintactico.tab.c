
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Line 189 of yacc.c  */
#line 1 "Sintactico.y"

//=====================================================================================================
// 									ANALIZADOR SINTACTICO
//=====================================================================================================

//=====================================================================================================	
// Seccion de declaraciones
//=====================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "y.tab.h"


/* Contiene el numero de linea ,recibida del lexico, para informar en caso de error */
extern int yylineno;  

//=====================================================================================================
// Declaracio de constantes y tipos de datos
//=====================================================================================================
#define ERROR_GENERICO -100
#define ERROR_ID_NO_DECLARADO -101
#define ERROR_ID_DUPLICADO -102
#define ERROR_TIPO_INCOMPATIBLE -103
#define ERROR_SINTAXIS -104
#define ERROR_STRING_ESPERADO -105
#define ERROR_NUMERO_ESPERADO -106
#define ERROR_EXPRESIONES_INCOMPATIBLES -107
#define ERROR_INT_MUY_GRANDE -108
#define ERROR_FLOAT_MUY_GRANDE -109
#define ERROR_STRING_MUY_LARGO -110
#define ERROR_PARENTESIS_CONCATENACION -111
#define ERROR_TAKE_EXPRESION -112
#define ERROR_STACK_VACIA -113
#define ERROR_ID_PALABRA_RESERVADA -114
#define ERROR_ARCHIVO_INEXISTENTE -115
#define ERROR_MEMORIA -116
#define ERROR_NO_STRING -117
#define ERROR_MUCHOS_MENOS -118
#define ERROR_FALTA_CODIGO -119

#define ERROR_TAM_DISTINTO_LISTAID_LISTATIPO -120	
#define ES_CADENA		1
#define NO_ES_CADENA	0	
#define ERROR_STRING_ESPERADO_EN_ASIGNACION -121
#define ERROR_STRING_ESPERADO_EN_CONCATENACION -122

#define QUEUE_ID 250
#define QUEUE_TIPO 251

#define OPERADOR_AND 301
#define OPERADOR_OR 302

#define TABLA_SIMBOLO "ts.txt"
#define ENCABEZADO "final.txt"
#define MAXTEXTSIZE 50
#define TAM_LINEA_ARCHIVO_TS	200		
#define DEBUG		0					// 1: Activa debug. Imprime las reglas aplicadas	
										// 0: Desactiva debug


typedef struct symbol{
	char nombreVar[35], tipo[20], valor[35], valorDecimal[35], longitud[33];
} t_symbol;

struct node
{
    int data;
    struct node *link;
};

struct nodo{
	char dato[30];
	struct nodo *sig;
};

struct Cola
{
	struct nodo *pri;
	struct nodo *ult;
	int cantElem ;
};

typedef struct terceto{
	char operacion[35];
	int t1, t2;
	int numeroTerceto;
} t_terceto;

//estructura del terceto operacion, tiene los valores de los numeros de tercetos que se estan usando
typedef struct tercetoOperacion{
	int expresion, 
		termino, 
		factor;
} t_operacion;


#define STACK_EXPRESION 208
#define STACK_FACTOR 209
#define STACK_CONDICION 200
#define STACK_OPERADOR 201
#define STACK_POSICION 202
#define STACK_BIFILTER 203
//=====================================================================================================



struct Cola 
colaID,
colaTipo;

// tercetos
//nodo de los tercetos de operaciones
struct nodoOperaciones{
	t_operacion operacion;
	struct nodoOperaciones *link;
} *stackOperaciones = NULL;

struct nodo_operacion{
	char op[2];
	struct nodo_operacion *sig;
}*stackExpresion, *stackFactor;

// Variable que guarda el dato (int, float o tring) asignado a un id.
char auxAsignacionID[30];		
// Variable para manejar compatibilidad de tipos en asignacion
int flagEsString = 0;
// Variable para manejar compatibilidad de tipos en expresiones
int flagExpresionEsString = 0;

//variables globales
int yystopparser=0;
FILE  *yyin, *ts, *intermedia;
int flagLong=0;
int cantElementos;
int contadorLong=0;
t_symbol *vectorSymbol;

t_terceto *vectorTercetos;

int indiceTerceto = 0;
t_terceto 	factor_terceto;
#define TERCETOS "intermedia.txt"
struct Cola colaFilter;
t_terceto *vectorTercetosFilter;
t_terceto expresion_terceto, termino_terceto, expresion_terceto_aux, concatenacion_terceto, factor_terceto_aux;
t_terceto expresion_terceto_filter;
char operador_comparacion[2];
struct node *stackCondicion = NULL, *stackOperador = NULL,*stackPosicion = NULL, * stackBiFilter=NULL;

//prototipos
void escribirLineaEnPantalla(char* linea);
void escribirEnPantalla(char *motivo, int cierre);
t_symbol getSymbol(char * nombreVar, char * tipo, char * valor, char * valorDecimal, char * longitud);
int guardarEnVector(t_symbol symbol, int esDeclaracion);
void escribirArchivo(FILE** archivo,const char* nombre, char* linea);
char* generarLinea(t_symbol symbol, char * linea);
int buscarEnVector(char* nombre);
void openFile(const char* nombre, FILE** archivo);
int guardarTSInt(int num);
//int guardarTSBin(char* string);
//int guardarTSHexa(char* string);
int guardarTSReal(double num);
int guardarTSString(char* string);
int esString(int pos );
void guardarVariables();
//int convertirBinDecim(char* binario);
int guardarTSBin(char* string);
//int convertirHexaDecim(char* hexa);
void encolar(char* dato, struct Cola* cola);
void desacolar(struct Cola* cola, char* result);
void mostrarError(int codError, char* parametro);
//t_terceto crearTercetoFilter(char* operacion,int t1,int t2);
void aumentarNivelParentesis();
t_operacion decrementarNivelParentesis();
t_operacion obtenerTercetoOperacionActual();
void push_op(int destino, char* op);
char* getValueCondicion(char* comparacion);
void setearSalto(int t);
void negarTerceto(int i);
int pop(int destino);
void escribirEncabezadoArchivoAssembler();
void escribirSymbol(t_symbol symbol, FILE *arch);

t_terceto crearTerceto(char*,int,int);
t_terceto* buscarTerceto(t_terceto t);
void escribirTerceto(t_terceto t, FILE *arch);
void escribirArchivoTercetos();
void setearTercetoOperacionActual(int, int, int);
void pop_op(int destino, char* result);
void push(int destino, int i);
int filterActivado = 0;
int indiceTercetoFilter = 0;
int cantFilter=0;
int cantidadVar;
t_terceto filter_terceto;


/* Line 189 of yacc.c  */
#line 274 "Sintactico.tab.c"

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
     PROGRAM = 258,
     ENDPROGRAM = 259,
     DIM = 260,
     AS = 261,
     ENDDECLARE = 262,
     DECLARE = 263,
     START = 264,
     ENDWHILE = 265,
     BEGINWHILE = 266,
     WHILE = 267,
     FOR = 268,
     TO = 269,
     STEP = 270,
     NEXT = 271,
     IF = 272,
     THEN = 273,
     ELSE = 274,
     ENDIF = 275,
     OP_ASIG = 276,
     PYC = 277,
     CONST_INT = 278,
     CONST_BIN = 279,
     CONST_HEXA = 280,
     CONST_REAL = 281,
     CONST_STR = 282,
     ID = 283,
     ENTERO = 284,
     OP_SUMA = 285,
     OP_RESTA = 286,
     OP_MULT = 287,
     OP_DIV = 288,
     OP_CONCATENACION = 289,
     OP_NOT = 290,
     GET = 291,
     DISPLAY = 292,
     OP_LOG = 293,
     OP_COMPARACION = 294,
     CORCHETE_A = 295,
     CORCHETE_C = 296,
     COMA = 297,
     TIPO = 298,
     PARENTESIS_A = 299,
     PARENTESIS_C = 300,
     LONGITUD = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 201 "Sintactico.y"

	int intval;
	double doubleval;
	char str_val[50];



/* Line 214 of yacc.c  */
#line 364 "Sintactico.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 376 "Sintactico.tab.c"

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
# if YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   122

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    14,    15,    16,    17,
      18,    26,    27,    30,    31,    35,    37,    39,    41,    43,
      45,    47,    49,    50,    59,    67,    68,    79,    92,    94,
      95,   100,   102,   105,   106,   107,   113,   114,   119,   121,
     122,   123,   129,   130,   131,   132,   133,   134,   146,   148,
     150,   152,   153,   154,   160,   162,   164,   167,   170,   172,
     174,   176,   178,   179,   184,   188,   190,   193,   202,   204,
     208,   210
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    -1,     9,    49,    91,    51,    -1,    -1,
       9,    50,    51,    -1,    -1,    -1,    -1,    -1,     3,    52,
      56,     4,    53,    54,    55,    -1,    -1,    59,    57,    -1,
      -1,    56,    59,    58,    -1,    62,    -1,    71,    -1,    60,
      -1,    64,    -1,    87,    -1,    88,    -1,    76,    -1,    -1,
      12,    61,    44,    65,    45,    11,    56,    10,    -1,    17,
      44,    65,    45,    18,    56,    20,    -1,    -1,    17,    44,
      65,    45,    18,    56,    63,    19,    56,    20,    -1,    13,
      65,    21,    73,    14,    73,    40,    15,    23,    41,    16,
      65,    -1,    67,    -1,    -1,    67,    38,    66,    67,    -1,
      68,    -1,    35,    68,    -1,    -1,    -1,    73,    69,    39,
      70,    73,    -1,    -1,    28,    72,    21,    73,    -1,    83,
      -1,    -1,    -1,    73,    74,    82,    75,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    46,    44,    40,    95,    41,
      45,    78,    79,    80,    81,    -1,    30,    -1,    31,    -1,
      89,    -1,    -1,    -1,    83,    84,    86,    85,    89,    -1,
      32,    -1,    33,    -1,    37,    28,    -1,    36,    89,    -1,
      28,    -1,    23,    -1,    26,    -1,    27,    -1,    -1,    44,
      90,    73,    45,    -1,     8,    92,     7,    -1,    93,    -1,
      92,    93,    -1,     5,    40,    95,    41,     6,    40,    94,
      41,    -1,    43,    -1,    94,    42,    43,    -1,    28,    -1,
      95,    42,    28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   232,   232,   232,   233,   233,   237,   239,   242,   243,
     237,   248,   248,   250,   250,   255,   256,   257,   258,   259,
     260,   261,   265,   265,   277,   280,   280,   288,   292,   296,
     296,   310,   311,   317,   320,   317,   334,   334,   379,   385,
     389,   385,   405,   407,   408,   409,   410,   405,   418,   418,
     422,   430,   434,   430,   449,   449,   452,   456,   461,   478,
     489,   498,   507,   507,   519,   523,   524,   529,   538,   539,
     543,   603
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ENDPROGRAM", "DIM", "AS",
  "ENDDECLARE", "DECLARE", "START", "ENDWHILE", "BEGINWHILE", "WHILE",
  "FOR", "TO", "STEP", "NEXT", "IF", "THEN", "ELSE", "ENDIF", "OP_ASIG",
  "PYC", "CONST_INT", "CONST_BIN", "CONST_HEXA", "CONST_REAL", "CONST_STR",
  "ID", "ENTERO", "OP_SUMA", "OP_RESTA", "OP_MULT", "OP_DIV",
  "OP_CONCATENACION", "OP_NOT", "GET", "DISPLAY", "OP_LOG",
  "OP_COMPARACION", "CORCHETE_A", "CORCHETE_C", "COMA", "TIPO",
  "PARENTESIS_A", "PARENTESIS_C", "LONGITUD", "$accept", "programa", "$@1",
  "$@2", "algoritmo", "$@3", "$@4", "$@5", "$@6", "bloque", "$@7", "$@8",
  "sentencia", "while", "$@9", "decision", "$@10", "for", "condicion",
  "$@11", "expresion_logica", "comparacion", "$@12", "$@13", "asignacion",
  "$@14", "expresion", "$@15", "$@16", "longitud", "$@17", "$@18", "$@19",
  "$@20", "$@21", "op_sumres", "termino", "$@22", "$@23", "op_multdiv",
  "lectura", "escritura", "factor", "$@24", "est_declaracion",
  "declaraciones", "declaracion", "listaTipo", "listaID", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    49,    48,    50,    48,    52,    53,    54,    55,
      51,    57,    56,    58,    56,    59,    59,    59,    59,    59,
      59,    59,    61,    60,    62,    63,    62,    64,    65,    66,
      65,    67,    67,    69,    70,    68,    72,    71,    73,    74,
      75,    73,    77,    78,    79,    80,    81,    76,    82,    82,
      83,    84,    85,    83,    86,    86,    87,    88,    89,    89,
      89,    89,    90,    89,    91,    92,    92,    93,    94,    94,
      95,    95
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     0,     0,     0,     0,
       7,     0,     2,     0,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     8,     7,     0,    10,    12,     1,     0,
       4,     1,     2,     0,     0,     5,     0,     4,     1,     0,
       0,     5,     0,     0,     0,     0,     0,    11,     1,     1,
       1,     0,     0,     5,     1,     1,     2,     2,     1,     1,
       1,     1,     0,     4,     3,     1,     2,     8,     1,     3,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     0,     0,     1,     0,     0,     6,     5,
       0,     0,    65,     3,    42,     0,    64,    66,    22,     0,
       0,    36,     0,     0,    42,    11,    17,    15,    18,    16,
      21,     0,    19,    20,    70,     0,     0,    59,    60,    61,
      58,     0,    62,     0,    28,    31,    39,    38,    50,     0,
       0,    57,    56,     7,    13,    12,     0,     0,     0,     0,
      32,     0,     0,    29,     0,     0,     0,     0,     0,     8,
      14,     0,     0,    71,     0,    39,    39,     0,    34,    48,
      49,    40,    54,    55,    52,     0,    37,     9,     0,     0,
       0,    63,     0,    30,     0,     0,     0,    42,    10,     0,
      68,     0,    42,    39,    35,    41,    53,    25,     0,    67,
       0,    42,     0,    24,     0,    43,    69,    23,     0,    42,
      44,     0,    42,    45,     0,    26,    46,     0,    47,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     9,    14,    69,    87,    98,    24,
      55,    70,    25,    26,    36,    27,   114,    28,    43,    77,
      44,    45,    64,    94,    29,    50,    46,    65,    95,    30,
      31,   120,   123,   126,   128,    81,    47,    66,    96,    84,
      32,    33,    48,    61,     7,    11,    12,   101,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const yytype_int8 yypact[] =
{
      -6,     7,    15,    10,    19,   -84,    25,    19,   -84,   -84,
      27,    18,   -84,   -84,    44,     5,   -84,   -84,   -84,    20,
      38,   -84,    47,    58,     4,   -84,   -84,   -84,   -84,   -84,
     -84,    42,   -84,   -84,   -84,    -7,    45,   -84,   -84,   -84,
     -84,    47,   -84,    50,    52,   -84,    53,    21,   -84,    20,
      72,   -84,   -84,   -84,   -84,   -84,    51,    88,    68,    20,
     -84,    47,    47,   -84,    60,    28,    30,    55,    47,   -84,
     -84,    57,    61,   -84,    59,    62,    89,    20,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,    84,    35,   -84,     5,    63,
      94,   -84,    47,   -84,    47,    47,    47,    44,   -84,    36,
     -84,    43,    44,    69,    35,    21,   -84,    -8,    65,   -84,
      70,    14,    93,   -84,    92,   -84,   -84,   -84,    91,    44,
     -84,    71,    32,   -84,    99,   -84,   -84,    20,   -84,   -84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   -84,   109,   -84,   -84,   -84,   -84,   -83,
     -84,   -84,   -24,   -84,   -84,   -84,   -84,   -84,   -48,   -84,
      40,    77,   -84,   -84,   -84,   -84,   -55,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,    24,   -84,   -84,   -84,
     -84,   -84,   -20,   -84,   -84,   -84,   110,   -84,    34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -52
static const yytype_int16 yytable[] =
{
      54,    67,    51,     1,    18,    19,    75,    76,    53,    20,
      -4,    74,   113,    86,   107,     5,    18,    19,     6,   111,
      21,    20,     8,    10,   117,    16,    18,    19,    22,    23,
      10,    20,    21,    34,    57,    58,   122,   103,   -42,   104,
      22,    23,    21,    37,    18,    19,    38,    39,    40,    20,
      22,    23,   125,   -51,   -51,    41,    18,    19,    79,    80,
      21,    20,    82,    83,    42,   -39,   -39,    15,    22,    23,
      37,    62,    21,    38,    39,    40,   106,   108,    58,   129,
      22,    23,    49,    54,   109,   110,    52,    54,    56,    59,
      63,    42,   -33,    68,    72,    71,    73,    88,    54,    78,
      85,    89,    97,    92,    90,   102,   100,    91,   118,   112,
     115,   119,   124,   116,   121,   127,    13,    93,    60,   105,
       0,    17,    99
};

static const yytype_int8 yycheck[] =
{
      24,    49,    22,     9,    12,    13,    61,    62,     4,    17,
       3,    59,    20,    68,    97,     0,    12,    13,     8,   102,
      28,    17,     3,     5,    10,     7,    12,    13,    36,    37,
       5,    17,    28,    28,    41,    42,   119,    92,    46,    94,
      36,    37,    28,    23,    12,    13,    26,    27,    28,    17,
      36,    37,    20,    32,    33,    35,    12,    13,    30,    31,
      28,    17,    32,    33,    44,    30,    31,    40,    36,    37,
      23,    21,    28,    26,    27,    28,    96,    41,    42,   127,
      36,    37,    44,   107,    41,    42,    28,   111,    46,    44,
      38,    44,    39,    21,     6,    44,    28,    40,   122,    39,
      45,    40,    18,    14,    45,    11,    43,    45,    15,    40,
      45,    19,    41,    43,    23,    16,     7,    77,    41,    95,
      -1,    11,    88
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    48,    49,    50,     0,     8,    91,     3,    51,
       5,    92,    93,    51,    52,    40,     7,    93,    12,    13,
      17,    28,    36,    37,    56,    59,    60,    62,    64,    71,
      76,    77,    87,    88,    28,    95,    61,    23,    26,    27,
      28,    35,    44,    65,    67,    68,    73,    83,    89,    44,
      72,    89,    28,     4,    59,    57,    46,    41,    42,    44,
      68,    90,    21,    38,    69,    74,    84,    65,    21,    53,
      58,    44,     6,    28,    65,    73,    73,    66,    39,    30,
      31,    82,    32,    33,    86,    45,    73,    54,    40,    40,
      45,    45,    14,    67,    70,    75,    85,    18,    55,    95,
      43,    94,    11,    73,    73,    83,    89,    56,    41,    41,
      42,    56,    40,    20,    63,    45,    43,    10,    15,    19,
      78,    23,    56,    79,    41,    20,    80,    16,    81,    65
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

/* Line 1455 of yacc.c  */
#line 232 "Sintactico.y"
    {aumentarNivelParentesis();;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 232 "Sintactico.y"
    {escribirArchivoTercetos(); escribirEncabezadoArchivoAssembler();;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 233 "Sintactico.y"
    {aumentarNivelParentesis();;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 233 "Sintactico.y"
    {escribirArchivoTercetos(); escribirEncabezadoArchivoAssembler();;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 237 "Sintactico.y"
    {
		escribirEnPantalla("Bloques", 0);
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 239 "Sintactico.y"
    {
		escribirEnPantalla("Bloques", 1);
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 242 "Sintactico.y"
    { printf("\n---------------------------\n");;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 243 "Sintactico.y"
    { printf("\n****COMPILACION EXITOSA****\n");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 244 "Sintactico.y"
    { printf("\n---------------------------\n");;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 248 "Sintactico.y"
    { printf("\n***REGLA 1 -> Bloque:\n");;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 249 "Sintactico.y"
    { printf("\t\t\tSentencia\n");;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 250 "Sintactico.y"
    { printf("\n***REGLA 2 -> Bloque:\n");;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 251 "Sintactico.y"
    { printf("\t\t\t Bloque Sentencia\n");;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 255 "Sintactico.y"
    {escribirLineaEnPantalla("IF");;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 256 "Sintactico.y"
    { escribirLineaEnPantalla("ASIGNACION"); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 257 "Sintactico.y"
    {escribirLineaEnPantalla("WHILE");;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 258 "Sintactico.y"
    {escribirLineaEnPantalla("FOR");;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 259 "Sintactico.y"
    {escribirLineaEnPantalla("Entrada DISPLAY");;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 260 "Sintactico.y"
    { escribirLineaEnPantalla("Salida GET");;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 261 "Sintactico.y"
    {escribirLineaEnPantalla("funcion LONGITUD");;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 265 "Sintactico.y"
    {push(STACK_POSICION, indiceTerceto);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 269 "Sintactico.y"
    {
		setearSalto(indiceTerceto+1); 
		crearTerceto("BI", -1 , pop(STACK_POSICION));
		;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 277 "Sintactico.y"
    {
		setearSalto(indiceTerceto);   
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 280 "Sintactico.y"
    {
		setearSalto(indiceTerceto+1);
		push(STACK_CONDICION,crearTerceto("BI", -1, -1).numeroTerceto);   
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 283 "Sintactico.y"
    { 
		vectorTercetos[pop(STACK_CONDICION)].t2 = indiceTerceto;   
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 292 "Sintactico.y"
    {
		push(STACK_OPERADOR, 0);
		printf("PASA1\n");
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 296 "Sintactico.y"
    {
		if(strcmp((yyvsp[(2) - (2)].str_val), "AND") == 0) 
		{	push(STACK_OPERADOR, OPERADOR_AND);
		}
		else
		{
			push(STACK_OPERADOR, OPERADOR_OR);
		}
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 311 "Sintactico.y"
    {
		negarTerceto(indiceTerceto-1);
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 317 "Sintactico.y"
    {
		flagExpresionEsString = flagEsString; 
		expresion_terceto_aux = expresion_terceto;
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 320 "Sintactico.y"
    {
				strcpy(operador_comparacion,(yyvsp[(3) - (3)].str_val));
			;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 323 "Sintactico.y"
    {
		if ( flagEsString != flagExpresionEsString ) 
			mostrarError(ERROR_EXPRESIONES_INCOMPATIBLES, NULL);
			
		t_terceto CMP_terceto = crearTerceto("CMP", expresion_terceto_aux.numeroTerceto, expresion_terceto.numeroTerceto);
		t_terceto condicion_if_terceto = crearTerceto(getValueCondicion(operador_comparacion), CMP_terceto.numeroTerceto,-1);
		push(STACK_CONDICION,condicion_if_terceto.numeroTerceto);
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 334 "Sintactico.y"
    {
    	if (DEBUG) printf("asignacion->ID\n");

    	strcpy(auxAsignacionID, (yyvsp[(1) - (1)].str_val));		// Guardo en una variable auxiliar el indentificador detectado
		
		
		
    	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 343 "Sintactico.y"
    {
    	if (DEBUG) printf("asignacion->OP_ASIG expresion\n");

    	int pos= buscarEnVector(auxAsignacionID);
		if ( pos == -1 ) {
			mostrarError(ERROR_ID_NO_DECLARADO, auxAsignacionID);
		}

		// Analizo compatibilidad de datos en la asignacion
		if ( esString(pos) == ES_CADENA ) { 
			// El identificador es del tipo 'string'
			// Valido que la expresion que quiero asignar sea del mismo tipo
			if ( flagEsString == NO_ES_CADENA ) 
				mostrarError(ERROR_STRING_ESPERADO_EN_ASIGNACION, NULL); 
			
		}
		else { 
			// El identificador es del tipo 'int' o 'real' 
			// Valido que la expresion que quiero asignar sea del mismo tipo.
			if ( flagEsString == ES_CADENA ) 
				mostrarError(ERROR_NUMERO_ESPERADO, NULL); 
		}


		/*
		char linea[50];
		sprintf(linea, "ASIGNACION DE %s", auxAsignacionID);
		escribirLineaEnPantalla(linea);
		*/
		t_terceto tAux = crearTerceto(auxAsignacionID,-1,-1);
		
		crearTerceto(":=", tAux.numeroTerceto, expresion_terceto.numeroTerceto);
    	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 379 "Sintactico.y"
    { 
			  //printf("Es termino\n");
			  if (DEBUG) printf("expresion->termino\n");
			  expresion_terceto = termino_terceto;
			  setearTercetoOperacionActual(expresion_terceto.numeroTerceto, -1 , -1);
			;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 385 "Sintactico.y"
    {
				if ( flagEsString  == ES_CADENA ) 
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
			   ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 389 "Sintactico.y"
    {
				push_op(STACK_EXPRESION, (yyvsp[(3) - (3)].str_val));
				;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 391 "Sintactico.y"
    {
				if ( flagEsString == ES_CADENA ) 
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
				char operador[3];
				pop_op(STACK_EXPRESION, operador);
				expresion_terceto = crearTerceto(operador, obtenerTercetoOperacionActual().expresion, obtenerTercetoOperacionActual().termino);
				setearTercetoOperacionActual(expresion_terceto.numeroTerceto, -1 , -1);
				;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 405 "Sintactico.y"
    {flagLong=1;;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 407 "Sintactico.y"
    { escribirLineaEnPantalla("Fin LONGITUD"); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 408 "Sintactico.y"
    {flagLong=0;;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 409 "Sintactico.y"
    {contadorLong=0;;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 410 "Sintactico.y"
    {printf("\n***REGLA 22 -> Longitud:\n");;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 411 "Sintactico.y"
    {printf("\t\t\t LONGITUD ([listaID])\n");;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 418 "Sintactico.y"
    {escribirLineaEnPantalla("operacion SUMA");;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 418 "Sintactico.y"
    {escribirLineaEnPantalla("operacion RESTA");;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 422 "Sintactico.y"
    { 
				//printf("Es termino\n");
				if (DEBUG) printf("termino->factor\n");
				termino_terceto = factor_terceto;
				
				setearTercetoOperacionActual(-1, termino_terceto.numeroTerceto, -1);
				//printf("dsp\n");
			;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 430 "Sintactico.y"
    {
		if ( flagEsString == ES_CADENA ) 
			mostrarError(ERROR_NUMERO_ESPERADO, NULL);
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 434 "Sintactico.y"
    {push_op(STACK_FACTOR, (yyvsp[(3) - (3)].str_val));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 435 "Sintactico.y"
    {

		if (DEBUG) printf("termino->factor op_multdiv factor\n");

		if ( flagEsString == ES_CADENA ) 
			mostrarError(ERROR_NUMERO_ESPERADO, NULL);
		char operador[3];
		pop_op(STACK_FACTOR, operador);
		termino_terceto = crearTerceto(operador, obtenerTercetoOperacionActual().termino, obtenerTercetoOperacionActual().factor);
		setearTercetoOperacionActual(-1, termino_terceto.numeroTerceto, -1);
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 449 "Sintactico.y"
    {escribirLineaEnPantalla("operacion PRODUCTO");;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 449 "Sintactico.y"
    {escribirLineaEnPantalla("operacion DIVISION");;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 461 "Sintactico.y"
    { 
		  if (DEBUG) printf("factor->ID\n");
		
		  int pos = buscarEnVector((yyvsp[(1) - (1)].str_val));

		  if ( pos == -1 ) 
			 mostrarError(ERROR_ID_NO_DECLARADO, (yyvsp[(1) - (1)].str_val));

		  if ( esString(pos) == ES_CADENA )
			 flagEsString = ES_CADENA;
		  else
			 flagEsString = NO_ES_CADENA;
			 
			factor_terceto = crearTerceto((yyvsp[(1) - (1)].str_val),-1,-1);
			setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);

	   ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 478 "Sintactico.y"
    { 
				  if (DEBUG) printf("factor->CONST_INT\n");

				  printf("guardo %d\n",(yyvsp[(1) - (1)].intval)); 
				  int pos = guardarTSInt((yyvsp[(1) - (1)].intval));
				  flagEsString = NO_ES_CADENA;
				
				  factor_terceto =  crearTerceto(vectorSymbol[pos].nombreVar,-1,-1);
				  setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);
				;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 489 "Sintactico.y"
    { 
				  if (DEBUG) printf("factor->CONST_REAL\n");	

				  printf("guardo %f\n",(yyvsp[(1) - (1)].doubleval)); 
				  int pos = guardarTSReal((yyvsp[(1) - (1)].doubleval)); 
				  flagEsString = NO_ES_CADENA;
				  factor_terceto =  crearTerceto(vectorSymbol[pos].nombreVar,-1,-1);
				  setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);
				;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 498 "Sintactico.y"
    { 
				  if (DEBUG) printf("factor->CONST_STR\n");

				  printf("guardo cadena %s\n",(yyvsp[(1) - (1)].str_val));  
				  int pos = guardarTSString((yyvsp[(1) - (1)].str_val)); 
				  factor_terceto =  crearTerceto(vectorSymbol[pos].nombreVar,-1,-1); 
				  setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);
				  flagEsString = ES_CADENA;
				;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 507 "Sintactico.y"
    {
		aumentarNivelParentesis();
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 509 "Sintactico.y"
    {
		if(NO_ES_CADENA) 
			mostrarError(ERROR_PARENTESIS_CONCATENACION, NULL);
		decrementarNivelParentesis();
		factor_terceto = expresion_terceto;
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 523 "Sintactico.y"
    {guardarVariables();;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 524 "Sintactico.y"
    {guardarVariables();;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 529 "Sintactico.y"
    {
																		   if ( colaID.cantElem != colaTipo.cantElem) 
																		  	  mostrarError(ERROR_TAM_DISTINTO_LISTAID_LISTATIPO, ""); 

																		   escribirLineaEnPantalla("Declaraciones");
																		  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 538 "Sintactico.y"
    {encolar((yyvsp[(1) - (1)].str_val), &colaTipo); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 539 "Sintactico.y"
    { encolar((yyvsp[(3) - (3)].str_val), &colaTipo); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 543 "Sintactico.y"
    { 
		if (DEBUG) printf("listaID->ID\n");
		encolar((yyvsp[(1) - (1)].str_val), &colaID);
		
			if(filterActivado==1)
			{
				//printf("********encolo: %s\n", $<str_val>1);
				cantidadVar++;
				// busco en vector de tercetos
				t_terceto var;
				strcpy(var.operacion,(yyvsp[(1) - (1)].str_val));
				var.t1=-1;
				var.t2=-1;
				
				
				t_terceto *aux = buscarTerceto(var);
				if(indiceTerceto > 0 && aux != NULL)
				{	var = *aux;
					
				}	
				else{
					var.numeroTerceto = indiceTerceto++;
					vectorTercetos = (t_terceto*) realloc(vectorTercetos, sizeof(t_terceto) * indiceTerceto);
					if(vectorTercetos == NULL)
						mostrarError(ERROR_MEMORIA, "realloc del vectorTercetos en crearTerceto()");
					vectorTercetos[indiceTerceto-1] = var;
				}

				t_terceto CMP_terceto = crearTerceto("CMP", var.numeroTerceto , expresion_terceto.numeroTerceto); //expresion_terceto_filter.numeroTerceto
				t_terceto condicion_if_terceto = crearTerceto(getValueCondicion(operador_comparacion), CMP_terceto.numeroTerceto,-1);
				push(STACK_CONDICION,condicion_if_terceto.numeroTerceto);
				
				////////////////// creo terceto filter
		
				char auxNombre[10];
				sprintf(auxNombre, "filter%d", cantFilter);
				guardarEnVector(getSymbol(auxNombre,"string","","",""), 0); //(char * nombreVar, char * tipo, char * valor, char * valorDecimal, char * longitud);
				factor_terceto = filter_terceto = crearTerceto(auxNombre,-1,-1);

				////////////////////////////////
				// asigno filter:=var
			
				crearTerceto(":=",filter_terceto.numeroTerceto,var.numeroTerceto);
				// terceto de salto incondicional
				t_terceto saltoIncond;
				strcpy(saltoIncond.operacion,"BI");
				saltoIncond.t1=-1;
				saltoIncond.t2=-1;
				saltoIncond.numeroTerceto = indiceTerceto++;
				vectorTercetos = (t_terceto*) realloc(vectorTercetos, sizeof(t_terceto) * indiceTerceto);
					if(vectorTercetos == NULL)
						mostrarError(ERROR_MEMORIA, "realloc del vectorTercetos en crearTerceto()");
					vectorTercetos[indiceTerceto-1] = saltoIncond;
					
				push(STACK_BIFILTER,saltoIncond.numeroTerceto);
				
			}
			
		
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 603 "Sintactico.y"
    { 
		if (DEBUG) printf("listaID->listaID COMA ID\n");
		encolar((yyvsp[(3) - (3)].str_val), &colaID); 
		
	
			if(filterActivado==1)
			{
				//printf("********encolo: %s\n", $<str_val>1);
				cantidadVar++;
				// busco en vector de tercetos
				t_terceto var;
				strcpy(var.operacion,(yyvsp[(3) - (3)].str_val));
				var.t1=-1;
				var.t2=-1;
				int existe=0;
				t_terceto *aux = buscarTerceto(var);
				if(indiceTerceto > 0 && aux != NULL)
				{	var = *aux;
					existe=1;
				}
				else{
					var.numeroTerceto = indiceTerceto++;
					vectorTercetos = (t_terceto*) realloc(vectorTercetos, sizeof(t_terceto) * indiceTerceto);
					if(vectorTercetos == NULL)
						mostrarError(ERROR_MEMORIA, "realloc del vectorTercetos en crearTerceto()");
					vectorTercetos[indiceTerceto-1] = var;
					
					vectorTercetos[pop(STACK_CONDICION)].t2 = var.numeroTerceto;
				//	printf("terceto::: %d*****= %d*********\n",vectorTercetos[num].numeroTerceto,var.numeroTerceto);
				}
				
				t_terceto CMP_terceto = crearTerceto("CMP", var.numeroTerceto , expresion_terceto.numeroTerceto); //expresion_terceto_filter.numeroTerceto
				if(existe==1)
					vectorTercetos[pop(STACK_CONDICION)].t2 = indiceTerceto;
				t_terceto condicion_if_terceto = crearTerceto(getValueCondicion(operador_comparacion), CMP_terceto.numeroTerceto,-1);
				push(STACK_CONDICION,condicion_if_terceto.numeroTerceto);
				
				
				t_terceto filterAux;
				char auxNombre[10];
				sprintf(auxNombre, "filter%d", cantFilter);
				strcpy(filterAux.operacion,auxNombre);
				filterAux.t1=-1;
				filterAux.t2=-1;
				t_terceto* filter_terceto = buscarTerceto(filterAux);
				
				crearTerceto(":=",filter_terceto->numeroTerceto,var.numeroTerceto);
				// terceto de salto incondicional
				t_terceto saltoIncond;
				strcpy(saltoIncond.operacion,"BI");
				saltoIncond.t1=-1;
				saltoIncond.t2=-1;
				saltoIncond.numeroTerceto = indiceTerceto++;
				vectorTercetos = (t_terceto*) realloc(vectorTercetos, sizeof(t_terceto) * indiceTerceto);
					if(vectorTercetos == NULL)
						mostrarError(ERROR_MEMORIA, "realloc del vectorTercetos en crearTerceto()");
					vectorTercetos[indiceTerceto-1] = saltoIncond;
					
				push(STACK_BIFILTER,saltoIncond.numeroTerceto);
			}

			
		
	;}
    break;



/* Line 1455 of yacc.c  */
#line 2430 "Sintactico.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 672 "Sintactico.y"

//=====================================================================================================
// Seccion de codigo
//=====================================================================================================

int main(int argc,char *argv[])
{
  if ((yyin = fopen(argv[1], "rt")) == NULL)
  {
	printf("\nNo se puede abrir el archivo: %s\n", argv[1]);
  }
  else
  {
	openFile(TABLA_SIMBOLO, &ts);
	openFile(TERCETOS, &intermedia);
	yyparse();
  }
  fclose(yyin);
  return 0;
}

//Se llama automaticamente cuando hay un error de sintaxis
int yyerror (void) {
	 printf("Syntax Error. Error cerca de linea nro %d\n", yylineno);
	 system ("Pause");
	 exit (1);
}


//Escribe por pantalla respetando espacios
void escribirLineaEnPantalla(char* linea){
	int i;
//	for(i = 0; i < cantEspacios; i++)
//		printf("\t");
	printf("%s.\n", linea);
}

void escribirEnPantalla(char *motivo, int cierre){
	int i = 0;
	if(cierre == 0){
	/*	for(i = 0; i < cantEspacios; i++)
			printf("\t");
	*/	printf("Apertura de %s.\n", motivo);
	//	cantEspacios++;
		}
	else{
	//	cantEspacios--;
	/*	for(i = 0; i < cantEspacios; i++)
			printf("\t");
		*/printf("Cierre de %s.\n", motivo);
	}
}

//Constructor de Symbol
t_symbol getSymbol(char * nombreVar, char * tipo, char * valor, char * valorDecimal, char * longitud){
	t_symbol result;
	if (strlen(valor) == 0) {
		sprintf(result.nombreVar, "%s", nombreVar);
	}	
	else {
		sprintf(result.nombreVar, "_%s", nombreVar);
	}	
	strcpy(result.valor, valor);
	strcpy(result.valorDecimal, valorDecimal);
	strcpy(result.tipo, tipo);	
	strcpy(result.longitud, longitud);
	
	return result;
}

//Genera una linea para escribir en la TS
char* generarLinea(t_symbol symbol, char * linea){
	if (strlen(symbol.valor) == 0) {
		sprintf(linea, "%-35s|%-10s|%-35c|%-35c|0", symbol.nombreVar,symbol.tipo,'-','-');
	}	
	else {
		sprintf(linea, "%-35s|%-10s|%-35s|%-35s|%s", symbol.nombreVar,symbol.tipo,symbol.valor,symbol.valorDecimal,symbol.longitud);
	}
}

//Guarda un Symbol en el vector
int guardarEnVector(t_symbol symbol, int esDeclaracion){
	int pos = buscarEnVector(symbol.nombreVar);
	
	if(esDeclaracion == 1){
		if(pos >= 0)
			mostrarError(ERROR_ID_DUPLICADO, symbol.nombreVar);
	}
	if(pos == -1){
		pos = cantElementos++;	
		
		vectorSymbol = (t_symbol*) realloc(vectorSymbol, cantElementos * sizeof(t_symbol));
		
		if(vectorSymbol == NULL)
			mostrarError(ERROR_MEMORIA, "realloc del vectorSymbol en guardarEnVector()");	
	
		vectorSymbol[pos] = symbol;		
		
		char linea[TAM_LINEA_ARCHIVO_TS];
		//printf("pos_cant_elementos: %d\n",pos);
		generarLinea(symbol, linea);
		//printf("pos_cant_elementos: %d\n",pos);
		escribirArchivo(&ts, TABLA_SIMBOLO, linea);
		
	}
	
	return pos;
}

//Escribe una linea en el archivo
void escribirArchivo(FILE** archivo,const char* nombre, char* linea){
	FILE *arch = fopen(nombre, "a+");
	fprintf(arch, "%s\n", linea);
	fclose(arch);
}

//Busca un ID en la TS
int buscarEnVector(char* nombre){
	int i;
	for ( i = 0; i < cantElementos; i++ ) { //recorro el vector
		if ( strcmp(vectorSymbol[i].nombreVar, nombre ) == 0 ) { //si el nombre coincide
			return i; //ya estaba en la tabla
		}
	}
	
	return -1;
}

//Abre el archivo de ts la primera vez
void openFile(const char* nombre, FILE** archivo){
		*archivo = fopen(nombre, "w+");	//pisa el archivo y crea uno nuevo
		if(strcmp(nombre, TABLA_SIMBOLO) == 0){
			fprintf(ts, "%-35s|%-10s|%-35s|%-35s|%s\n","NOMBRE","TIPO","VALOR","VALOR DECIMAL","LONGITUD"); //genera el encabezado
			cantElementos = 0; //inicializa cantidad de elementos del vector
		}
		fclose(*archivo);
}

//guarda un INT en TS
int guardarTSInt(int num){
	char buffer[11];
	itoa(yylval.intval, buffer, 10);
	t_symbol aux= getSymbol(buffer, "CONST_INT", buffer,buffer,"");
	int poss=guardarEnVector(aux, 0);
	//printf("posicion: %d\n",poss);
	return poss;
}


int convertirBinDecim(char* binario){

	int decimal=0;
	int i;
	int tam;
	tam = strlen(binario);
	tam -=3; // _potencia
	int potencia=1;
	int de;
	
	for(i=tam;i>0;i--){
		
		de =  (int) (binario[i] - 48);
		decimal += de * potencia;
		potencia *=2;
	}
	
	return decimal;
}

//guarda un INT en TS
int guardarTSBin(char* string){
	int valor = convertirBinDecim(string);
	char buffer[11];
	//itoa(valor, buffer, 16);
	sprintf(buffer, "%d", valor);
	t_symbol aux= getSymbol(string, "CONST_BIN", string,buffer, "");
	int result = guardarEnVector(aux, 0);
	return result;
}

int convertirHexaDecim(char* hexa){

	int decimal=0;
	int i;
	int tam;
	tam = strlen(hexa);
	tam -=4; // _potencia
	int potencia=1;
	int de;
	
	for(i=tam;i>0;i--){
	
	
		switch(hexa[i])
		{
			case 'A':
					decimal += 10*potencia;
					break;
			case 'B':
					decimal += 11*potencia;
					break;
			case 'C':
					decimal += 12*potencia;
					break;
			case 'D':
					decimal += 13*potencia;
					break;
			case 'E':
					decimal += 14*potencia;
					break;
			case 'F':
					decimal += 15*potencia;
					break;
			default:
					de =  (int) (hexa[i] - 48);
					decimal += (de*potencia);
		
		}
		
		potencia *=16;
	}
	
	return decimal;
}


//guarda un Float en TS
int guardarTSReal(double num){
	char buffer[11];
	sprintf(buffer, "%f", yylval.doubleval);
	t_symbol aux= getSymbol(buffer, "CONST_REAL", buffer,buffer, "");
	return guardarEnVector(aux, 0);
}

//guarda un string en TS
int guardarTSString(char* string){
    char bufferLongitud[33];
	int longitudCad;
	
	longitudCad = strlen(string);
	if ( longitudCad >= 3 ) {
		//Resto las doble comillas de inicio y final de cadena
		sprintf(bufferLongitud, "%d", longitudCad - 2);
	}

	t_symbol aux= getSymbol(string, "CONST_STR", string,"", bufferLongitud);
	int result = guardarEnVector(aux, 0);
	return result;
}

//Verifica si un ID esta declarado como string
int esString(int pos ){
	if(strcmp(vectorSymbol[pos].tipo, "string") == 0) //si el nombre coincide y el tipo es string
		return 1;
	return 0;
}


void guardarVariables(){
	t_symbol symbol;
	char nombreID[30];
	char tipo[30];
	while(colaID.pri != NULL && colaTipo.pri != NULL){
		desacolar(&colaID, nombreID);
		desacolar(&colaTipo, tipo);
        symbol= getSymbol(nombreID,tipo,"","","");
		guardarEnVector(symbol, 1);
	}
	while(colaID.pri != NULL)
		desacolar(&colaID, nombreID);
	while(colaTipo.pri != NULL)
		desacolar(&colaTipo, tipo);
}

void encolar ( char* dato, struct Cola* cola ) {
	struct nodo *aux = (struct nodo*) malloc(sizeof(struct nodo));
	if(aux == NULL)
		mostrarError(ERROR_MEMORIA, "malloc de nodo aux en encolar()");
	strcpy(aux->dato,dato);
	aux->sig = NULL;

	if ( cola->pri == NULL )
		cola->pri = aux;		
	else
		cola->ult->sig = aux;
	cola->ult = aux;

	cola->cantElem++;
}

void desacolar ( struct Cola* cola, char* result ) {
	struct nodo *aux;

	if ( cola->pri == NULL ) {
		result = NULL;
	}	
	else
	{
		aux = cola->pri;
		strcpy(result, aux->dato);
		cola->pri = aux->sig;
		if(cola->pri == NULL)
			cola->ult = NULL;

		cola->cantElem--;
	}
	free(aux);
}




//Muestra el mensaje error segun el codigo y el parametro
void mostrarError(int codError, char* parametro){
	printf("\n\nERROR CERCA DE LA LINEA %d. ", yylineno);
	switch(codError){
	case ERROR_ID_NO_DECLARADO:
		printf("No se declaro la variable \"%s\".\n", parametro);
		break;
	case ERROR_ID_DUPLICADO:
		printf("Se ha declarado dos veces la variable \"%s\".\n", parametro);
		break;
	case ERROR_TIPO_INCOMPATIBLE:
		printf("La variable \"%s\" no tiene el tipo correcto para esa operacion.\n", parametro);
		break;
	case ERROR_NO_STRING:
		printf("El operador unario menos, no puede ser usado con Strings.\n");
		break;
	case ERROR_SINTAXIS:
		printf("Error de sintaxis no reconocido.\n");
		break;
	case ERROR_STRING_ESPERADO:
		printf("La variable o constante \"%s\" debe ser string para completar la operacion.\n", parametro);
		break;
	case ERROR_NUMERO_ESPERADO:
		//printf("La variable o constante \"%s\" debe ser int o float para completar la operacion.\n", parametro);
		printf("Tipos de datos incompatibles. Se esperaban valores numericos. No se puede llevar a cabo la operacion. \n"); 	
		break;
	case ERROR_EXPRESIONES_INCOMPATIBLES:
		printf("No es posible comparar una expresion String con una expresion algebraica.\n");
		break;
	case ERROR_INT_MUY_GRANDE:
		printf("La constante entera %s es demasiado grande. Los limites son -32768 y 32767.\n", parametro);
		break;
	case ERROR_FLOAT_MUY_GRANDE:
		printf("La constante real %s es demasiado grande. Los limites son -2147483647 y 2147483646.\n", parametro);
		break;
	case ERROR_STRING_MUY_LARGO:
		printf("La constante string %s es demasiado larga. El limite son 30 caracteres.\n", parametro);
		break;
	case ERROR_PARENTESIS_CONCATENACION:
		printf("Los parentesis solo pueden encerrar expresiones algebraicas.\n");
		break;
	case ERROR_STACK_VACIA:
		printf("Error de compilador inesperado. La pila %s se encontraba vacia.\n", parametro);
	break;
	case ERROR_ID_PALABRA_RESERVADA:
		printf("Se ha declarado la variable \"%s\", la cual es una palabra reservada.\n", parametro);
		break;
	case ERROR_ARCHIVO_INEXISTENTE:
		printf("No se puede abrir el archivo: %s\n", parametro);
		break;
	case ERROR_MEMORIA:
		printf("Error de memoria. No se pudo realizar el %s.\n", parametro);
		break;
	case ERROR_MUCHOS_MENOS:
		printf("Los factores solo pueden tener un menos delante.\n");
		break;
	case ERROR_FALTA_CODIGO:
		printf("Debe haber al menos una sentencia de codigo entre program y endprogram.\n");
		break;
	case ERROR_TAM_DISTINTO_LISTAID_LISTATIPO:
		printf("En la declaracion debe coincidir cantidad de elementos de las listas de id y tipo.\n"); 	
		break;
	case ERROR_STRING_ESPERADO_EN_ASIGNACION:
		printf("Tipos de datos incompatibles. No se puede llevar a cabo la operacion de asignacion. \n"); 	
		break;
	case ERROR_STRING_ESPERADO_EN_CONCATENACION:
		printf("Tipos de datos incompatibles. No se puede llevar a cabo la operacion de concatenacion. \n"); 	
		break;

	case ERROR_GENERICO:
	default:
		printf("No se ha podido identificar el error.\n");
		break;
	}
	//system("Pause");
	exit(codError);
}

//Crea el terceto con los indices de los tercetos. Si no existen tiene -1
t_terceto crearTercetoFilter(char* operacion,int t1,int t2){
	t_terceto result;
	t_terceto *tmp;
	strcpy(result.operacion, operacion);
	result.t1 = t1;
	result.t2 = t2;
/*	t_terceto *aux = buscarTerceto(result);
	if(indiceTercetoFilter > 0 && aux != NULL)
		result = *aux;
	else{
	*/	result.numeroTerceto = indiceTercetoFilter++;
		vectorTercetosFilter = (t_terceto*) realloc(vectorTercetosFilter, sizeof(t_terceto) * indiceTercetoFilter);
		if(vectorTercetosFilter == NULL)
			mostrarError(ERROR_MEMORIA, "realloc del vectorTercetosFilter en crearTerceto()");
		vectorTercetosFilter[indiceTercetoFilter-1] = result;
	//}
	return result;
}


//Crea el terceto con los indices de los tercetos. Si no existen tiene -1
t_terceto crearTerceto(char* operacion,int t1,int t2){
	t_terceto result;
	t_terceto *tmp;
	strcpy(result.operacion, operacion);
	result.t1 = t1;
	result.t2 = t2;
	t_terceto *aux = buscarTerceto(result);
	if(indiceTerceto > 0 && aux != NULL)
		result = *aux;
	else{
		result.numeroTerceto = indiceTerceto++;
		vectorTercetos = (t_terceto*) realloc(vectorTercetos, sizeof(t_terceto) * indiceTerceto);
		if(vectorTercetos == NULL)
			mostrarError(ERROR_MEMORIA, "realloc del vectorTercetos en crearTerceto()");
		vectorTercetos[indiceTerceto-1] = result;
	}
	return result;
}


//Busca un terceto en el vector de tercetos
t_terceto* buscarTerceto(t_terceto t){
	int i;
	for (i = 0; i < indiceTerceto; ++i) 
		if(strcmp(vectorTercetos[i].operacion, t.operacion) == 0 && vectorTercetos[i].t1 == -1 && vectorTercetos[i].t2 == -1){
			return &(vectorTercetos[i]); 
			}
	return NULL;
}


//Escribe un terceto en el archivo
void escribirTerceto(t_terceto t, FILE *arch){	
	if(strcmp(t.operacion, "BI")==0) //salto no condicional
		fprintf(arch, "[%d] (%s, [%d], -)\n", t.numeroTerceto, t.operacion, t.t2);
	else if(t.t1 == -1 && t.t2 == -1) //terceto de asignacion de memoria
		fprintf(arch, "[%d] (%s, _, _)\n", t.numeroTerceto, t.operacion);
	else if(t.t2 == -1) //terceto en el caso cuando se escriben los cmp 
		fprintf(arch, "[%d] (%s, [%d], _)\n", t.numeroTerceto, t.operacion, t.t1);
	else //terceto completo sin problemas
		fprintf(arch, "[%d] (%s, [%d], [%d])\n", t.numeroTerceto, t.operacion, t.t1, t.t2);	
}


//Escribe todos los Tercetos
void escribirArchivoTercetos(){
	int i;
	FILE* arch = fopen(TERCETOS, "w+");
	for(i = 0; i < indiceTerceto; i++)
		escribirTerceto(vectorTercetos[i], arch);		
	t_terceto t = crearTerceto("fin",-1,-1);
	escribirTerceto(t, arch);
	fclose(arch);
}


//crea un nuevo nivel de parentesis para operar, es similar al pu_sh de la pila, pero que no se le pasa parametros
void aumentarNivelParentesis(){
	struct nodoOperaciones *temp;
	temp = (struct nodoOperaciones*)malloc(sizeof(struct nodoOperaciones));
	if(temp == NULL)
		mostrarError(ERROR_MEMORIA, "malloc de temp en aumentarNivelParentesis()");
	temp->operacion.expresion = -1;
	temp->operacion.termino = -1;
	temp->operacion.factor = -1;
	temp->link = stackOperaciones;
	stackOperaciones = temp;
}

//decrementa el nivel de parentesis, es similar al POP de la pila
t_operacion decrementarNivelParentesis(){
	t_operacion result;
    struct nodoOperaciones *temp;
	if (stackOperaciones == NULL)
		mostrarError(ERROR_STACK_VACIA, "stackOperaciones");
	else{
		temp = stackOperaciones;
		stackOperaciones = stackOperaciones->link;
	}
	result = temp->operacion;
	//setearTercetoOperacionActual(result.expresion, result.termino, result.factor);
	setearTercetoOperacionActual(-1,-1, expresion_terceto.numeroTerceto);
    free(temp);
	return result;
}

//permite modificar los valores de los valores de terceto de operacion del nivel de parentesis actual
void setearTercetoOperacionActual(int expresion, int termino, int factor){
	if(expresion >= 0)
		stackOperaciones->operacion.expresion= expresion;
	if(termino >= 0)
		stackOperaciones->operacion.termino= termino;
	if(factor >= 0)
		stackOperaciones->operacion.factor= factor;
}


void push_op(int destino, char* op){
	struct nodo_operacion *temp;
    temp = (struct nodo_operacion*)malloc(sizeof(struct nodo_operacion));
    if(temp == NULL)
		mostrarError(ERROR_MEMORIA, "malloc de temp en push_op())");
    strcpy(temp->op, op);
    switch(destino){
    	case STACK_EXPRESION:
	    	temp->sig = stackExpresion;
	    	stackExpresion = temp;	
    	break;
    	case STACK_FACTOR:
    		temp->sig = stackFactor;
	    	stackFactor = temp;	
    	break;
    }
}

void pop_op(int destino, char* result){
    struct nodo_operacion *temp;
    switch(destino){
    	case STACK_EXPRESION:
	    	if (stackExpresion == NULL)
				mostrarError(ERROR_STACK_VACIA, "stackExpresion");
		    else
		    {
		        temp = stackExpresion;
		        stackExpresion = stackExpresion->sig;
		    }	
    	break;
    	case STACK_FACTOR:
	    	if (stackFactor == NULL)
				mostrarError(ERROR_STACK_VACIA, "stackFactor");
		    else
		    {
		        temp = stackFactor;
		        stackFactor = stackFactor->sig;
		    }	
    	break;
    }
	strcpy(result,temp->op);
    free(temp);
}

//te devuelve el terceto de operacion actual 
t_operacion obtenerTercetoOperacionActual(){
	return stackOperaciones->operacion;
}


//Obtiene el Assembler para el comparador correspondiente
char* getValueCondicion(char* comparacion){
	if(strcmp(comparacion, ">=") == 0)
		return "BLT";
	if(strcmp(comparacion, ">") == 0)
		return "BLE";
	if(strcmp(comparacion, "<=") == 0)
		return "BGT";
	if(strcmp(comparacion, "<") == 0)
		return "BGE";
	if(strcmp(comparacion, "<>") == 0)
		return "BEQ";
	if(strcmp(comparacion, "==") == 0)
		return "BNE";
	return NULL;
}


// to insert elements in stack
void push(int destino, int i)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    if(temp == NULL)
		mostrarError(ERROR_MEMORIA, "malloc de temp en push())");
    temp->data = i;
    switch(destino){
    	case STACK_CONDICION:
	    	temp->link = stackCondicion;
	    	stackCondicion = temp;	
    	break;
    	case STACK_OPERADOR:
	    	temp->link = stackOperador;
	    	stackOperador = temp;
    	break;
		case STACK_POSICION:
	    	temp->link = stackPosicion;
	    	stackPosicion = temp;
		break;
		case STACK_BIFILTER:
	    	temp->link = stackBiFilter;
	    	stackBiFilter = temp;
		break;
	
    }
}



// to delete elements from stack
int pop(int destino )
{
	int result;
    struct node *temp;
    switch(destino){
    	case STACK_CONDICION:
	    	if (stackCondicion == NULL)
				mostrarError(ERROR_STACK_VACIA, "stackCondicion");
		    else
		    {
		        temp = stackCondicion;
		        stackCondicion = stackCondicion->link;
		    }	
    	break;
    	case STACK_OPERADOR:
	    	if (stackOperador == NULL)
		        mostrarError(ERROR_STACK_VACIA, "stackOperador");
		    else
		    {
		        temp = stackOperador;
		        stackOperador = stackOperador->link;
		    }
	    	break;
		case STACK_BIFILTER:
	    	if (stackBiFilter == NULL)
				mostrarError(ERROR_STACK_VACIA, "stackBiFilter");
		    else
		    {
		        temp = stackBiFilter;
		        stackBiFilter = stackBiFilter->link;
		    }	
    	break;
    	case STACK_POSICION:
	    	if (stackPosicion == NULL)
				mostrarError(ERROR_STACK_VACIA, "stackPosicion");
		    else
		    {
		        temp = stackPosicion;
		        stackPosicion = stackPosicion->link;
		    }
	    	break;
    }
    result = temp->data;
    free(temp);
	return result;
}

//Niega la la condicion de un terceto
void negarTerceto(int i){
	if(strcmp(vectorTercetos[i].operacion, "BLT") == 0)
		strcpy(vectorTercetos[i].operacion, "BGE");
	else if(strcmp(vectorTercetos[i].operacion, "BGE") == 0)
		strcpy(vectorTercetos[i].operacion, "BLT");
	else if(strcmp(vectorTercetos[i].operacion, "BGT") == 0)
		strcpy(vectorTercetos[i].operacion, "BLE");
	else if(strcmp(vectorTercetos[i].operacion, "BLE") == 0)
		strcpy(vectorTercetos[i].operacion, "BGT");
	else if(strcmp(vectorTercetos[i].operacion, "BEQ") == 0)
		strcpy(vectorTercetos[i].operacion, "BNE");
	else if(strcmp(vectorTercetos[i].operacion, "BNE") == 0)
		strcpy(vectorTercetos[i].operacion, "BEQ");
}


//Setea el salto para las instrucciones if
void setearSalto(int t){
	int aux, aux2;
	int opLogico = pop(STACK_OPERADOR);
	switch(opLogico){
		case 0: //sin operador logico
			vectorTercetos[pop(STACK_CONDICION)].t2 = t;
		break;
		case OPERADOR_AND: //and
			vectorTercetos[pop(STACK_CONDICION)].t2 = t;
			vectorTercetos[pop(STACK_CONDICION)].t2 = t;
		break;
		case OPERADOR_OR: //or
			aux = pop(STACK_CONDICION);
			aux2 = pop(STACK_CONDICION);
			vectorTercetos[aux].t2 = t;
			vectorTercetos[aux2].t2 = aux-aux2; //vectorTercetos[aux2].t2 = aux+1;
			//negarTerceto(aux2);//
		break;
	}
}


//Escribe el encabezado Assembler
void escribirEncabezadoArchivoAssembler(){
	int i;
	FILE* arch = fopen(ENCABEZADO, "w+");
	fprintf(arch, ".MODEL LARGE\n.386\n.STACK 200h\n.DATA\nMAXTEXTSIZE equ %d\n", MAXTEXTSIZE);
	for(i = 0; i < cantElementos; i++) 
		escribirSymbol(vectorSymbol[i], arch);		
	fclose(arch);
}
//Escribe los simbolos de la tabla de simbolos
void escribirSymbol(t_symbol symbol, FILE *arch){
	if(strcmp(symbol.tipo, "string") == 0 || strcmp(symbol.tipo, "CONST_STR") == 0){
		if(strlen(symbol.valor) == 0)
			fprintf(arch, "%s db MAXTEXTSIZE dup(?), '$'\n", symbol.nombreVar);
		else
			fprintf(arch, "%s db %s, '$',%d dup(?),\n", symbol.nombreVar, symbol.valor, MAXTEXTSIZE-strlen(symbol.valor));
	}
	else{
		if(strlen(symbol.valor) == 0)
			fprintf(arch, "%s dd ?\n", symbol.nombreVar);
		else
			fprintf(arch, "%s dd %s\n", symbol.nombreVar, symbol.valor);
	}
}
