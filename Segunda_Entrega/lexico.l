%{
//=====================================================================================================
// 									ANALIZADOR LEXICO
//=====================================================================================================

//=====================================================================================================	
// Seccion definiciones
//=====================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <assert.h>
#include "y.tab.h"

#define C_INT -108
#define C_REAL -109
#define C_STR -110
#define ERROR_ID_PALABRA_RESERVADA -114

#define LIM_REAL 2147483647
#define LIM_INT 32768
#define LIM_STR 32			// Incluye las comillas de inicio y fin de cadena


//prototipos
int verificarTamanio(int opc);
void verificarDeclaracionVariable();

//Variables globales
int esDeclaracion= 0;
int esDeclaracionVariable=0;

//=====================================================================================================	
// Seccion de conjuntos, expresiones regulares y reglas
//=====================================================================================================

%}


%option noyywrap  
%option yylineno 

DIGITO								[0-9]
LETRA								[a-zA-Z]
C_REAL_PUNTO_AL_FINAL				{DIGITO}+"."
C_REAL_PUNTO_EN_INICIO_Y_MEDIO		{DIGITO}*"."{DIGITO}+
COMENTARIOS             \*\/({LETRA}|{DIGITO}|.|[OP_COMPARACION]|[OP_SUMA]|[OP_RESTA]|[OP_MULT]|[OP_DIV]|[OP_ASIG]|[OP_LOG]|[PARENTESIS_A]|[PARENTESIS_C]|[CORCHETE_A]|[CORCHETE_C]|[OP_SUMA]|[COMA]|[GUION_B]\n)+\/\*
CONST_STR               \"[^"\n]+\"
CONST_REAL              ({C_REAL_PUNTO_EN_INICIO_Y_MEDIO}|{C_REAL_PUNTO_AL_FINAL})
CONST_INT               {DIGITO}+
TIPO					("real"|"integer"|"string")
ID						{LETRA}({LETRA}|{DIGITO}|_){0,20}
OP_COMPARACION          ["<"|"=="|">"|"<="|">="|"><"]
OP_SUMA                	["+"]
OP_RESTA                ["-"]
OP_MULT					["*"]
OP_DIV					["/"]
OP_ASIG   				["="]
OP_LOG                  ["and"|"or"]
OP_NOT					["not"]
OP_CONCATENACION		["++"]
CORCHETE_A              ["["]
CORCHETE_C              ["]"]
PARENTESIS_A            ["("]
PARENTESIS_C            [")"]
COMA 					[","]
GUION_B					["_"]

%%
"START"			{ verificarDeclaracionVariable(); return START;}
"PROGRAM"		{ verificarDeclaracionVariable(); return PROGRAM;}
"ENDPROGRAM"	{ verificarDeclaracionVariable(); return ENDPROGRAM;}
"DECLARE"		{ verificarDeclaracionVariable(); esDeclaracion = 1; return DECLARE;}
"ENDDECLARE"	{ verificarDeclaracionVariable(); esDeclaracion = 0; return ENDDECLARE;}
"DIM"			{ verificarDeclaracionVariable(); 
			      if ( esDeclaracion == 1 ) 
			      	 esDeclaracionVariable= 1; 		// Activo validacion de nombre de identificador

			      	 return DIM;
			     }
"AS"			{ verificarDeclaracionVariable(); strcpy(yylval.str_val, yytext); return AS;}
"IF"			{ verificarDeclaracionVariable(); return IF;}
"THEN"			{ verificarDeclaracionVariable(); return THEN;}
"ELSE"			{ verificarDeclaracionVariable(); return ELSE;}
"ENDIF"			{ verificarDeclaracionVariable(); return ENDIF;}
"WHILE"			{ verificarDeclaracionVariable(); return WHILE;}
"BEGINWHILE" 	{ verificarDeclaracionVariable(); return BEGINWHILE;}
"ENDWHILE"		{ verificarDeclaracionVariable(); return ENDWHILE;}
"FOR"			{ verificarDeclaracionVariable(); return FOR;}
"TO"			{ verificarDeclaracionVariable(); return TO;}
"STEP"			{ verificarDeclaracionVariable(); return STEP;}
"NEXT"			{ verificarDeclaracionVariable(); return NEXT;}

"GET"			{ verificarDeclaracionVariable(); return GET;}
"DISPLAY"			{ verificarDeclaracionVariable(); return DISPLAY;}
"LONGITUD"		{ verificarDeclaracionVariable(); return LONGITUD;}
","				{ return COMA;}
";"				{ return PYC;}
"="			{ strcpy(yylval.str_val, yytext); return OP_ASIG;}
"+"				{ strcpy(yylval.str_val, yytext); return OP_SUMA;}
"-"				{ strcpy(yylval.str_val, yytext); return OP_RESTA;}
"*"				{ strcpy(yylval.str_val, yytext); return OP_MULT;}
"/"				{ strcpy(yylval.str_val, yytext); return OP_DIV;}
"++"			{ strcpy(yylval.str_val, yytext); return OP_CONCATENACION;}
"("				{ return PARENTESIS_A;}
")"				{ return PARENTESIS_C;}
">"				{ strcpy(yylval.str_val, yytext); return OP_COMPARACION;}
">="			{ strcpy(yylval.str_val, yytext); return OP_COMPARACION;}
"<"				{ strcpy(yylval.str_val, yytext); return OP_COMPARACION;}
"<="			{ strcpy(yylval.str_val, yytext); return OP_COMPARACION;}
"<>"			{ strcpy(yylval.str_val, yytext); return OP_COMPARACION;}
"=="			{ strcpy(yylval.str_val, yytext); return OP_COMPARACION;}
"AND"			{ verificarDeclaracionVariable(); strcpy(yylval.str_val, yytext); return OP_LOG;}
"OR"			{ verificarDeclaracionVariable(); strcpy(yylval.str_val, yytext); return OP_LOG;}
"NOT"			{ verificarDeclaracionVariable(); strcpy(yylval.str_val, yytext); return OP_NOT;}
"["				{ return CORCHETE_A;}
"]"				{ 
				  if ( esDeclaracion == 1 )  
				  	 esDeclaracionVariable = 0;   // Desactivo validacion de nombre de identificador

				  return CORCHETE_C;
				}
"_"				{ return GUION_B;}

{TIPO} {
	// Valido que un tipo de dato no haya sido usado como identificador
	verificarDeclaracionVariable();

	strcpy(yylval.str_val, yytext);
	return TIPO;
}

{ID} {
	strcpy(yylval.str_val, yytext);
	return ID;
}

{CONST_INT} {
 	if(verificarTamanio(C_INT) == 0) 
	 	mostrarError(C_INT, yytext);
		
 	yylval.intval = atoi(yytext);
	return CONST_INT;
}

{CONST_STR} {
 	if(verificarTamanio(C_STR) == 0) 
	 	mostrarError(C_STR, yytext);

	strcpy(yylval.str_val, yytext); 
	return CONST_STR;					 
}

{CONST_REAL} {
 	if(verificarTamanio(C_REAL) == 0) 
	 	mostrarError(C_REAL, yytext);

	yylval.doubleval = atof(yytext);
	return CONST_REAL;
}



{COMENTARIOS} {
	// printf("[COMENTARIO]: %s\n", yytext); 
}

"\t"		
"\n"  

%%

//=====================================================================================================	
// Seccion de codigo
//=====================================================================================================

int verificarTamanio(int opc){
	switch(opc){
		case C_INT:
			if(atoi(yytext) >= -LIM_INT && atoi(yytext) <= LIM_INT-1)
				return 1;
			return 0;
			break;
		case C_STR:
			if(strlen(yytext) <= LIM_STR) 
				return 1;
			return 0;
			break;
		case C_REAL:
			if(atof(yytext) >= -LIM_REAL && atof(yytext) <= LIM_REAL-1)
				return 1;
			return 0;
			break;
	}
	return 0;
}

// Verifica que el nombre de id utilizado en la seccion de declaracion no sea una palabra reservada.
void verificarDeclaracionVariable() {
	if(esDeclaracionVariable == 1 )
		mostrarError(ERROR_ID_PALABRA_RESERVADA, yytext);
}
