
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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
     BASE = 301,
     GUION_B = 302,
     LONGITUD = 303
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define ENDPROGRAM 259
#define DIM 260
#define AS 261
#define ENDDECLARE 262
#define DECLARE 263
#define START 264
#define ENDWHILE 265
#define BEGINWHILE 266
#define WHILE 267
#define FOR 268
#define TO 269
#define STEP 270
#define NEXT 271
#define IF 272
#define THEN 273
#define ELSE 274
#define ENDIF 275
#define OP_ASIG 276
#define PYC 277
#define CONST_INT 278
#define CONST_BIN 279
#define CONST_HEXA 280
#define CONST_REAL 281
#define CONST_STR 282
#define ID 283
#define ENTERO 284
#define OP_SUMA 285
#define OP_RESTA 286
#define OP_MULT 287
#define OP_DIV 288
#define OP_CONCATENACION 289
#define OP_NOT 290
#define GET 291
#define DISPLAY 292
#define OP_LOG 293
#define OP_COMPARACION 294
#define CORCHETE_A 295
#define CORCHETE_C 296
#define COMA 297
#define TIPO 298
#define PARENTESIS_A 299
#define PARENTESIS_C 300
#define BASE 301
#define GUION_B 302
#define LONGITUD 303




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 208 "Sintactico.y"

	int intval;
	double doubleval;
	char str_val[50];



/* Line 1676 of yacc.c  */
#line 156 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


