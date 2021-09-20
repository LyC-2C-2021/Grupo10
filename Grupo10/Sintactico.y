%{
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
#include "biblioteca/constantes.h"

/* Contiene el numero de linea ,recibida del lexico, para informar en caso de error */
extern int yylineno;  

struct node 
*stackCondicion = NULL,
*stackOperador = NULL,
*stackPosicion = NULL,
*stackLongitud = NULL,
*stackExpApil = NULL,
*stackFuncion = NULL;

struct Cola 
colaID,
colaTipo;

// Variable que guarda el dato (int, float o tring) asignado a un id.
char auxAsignacionID[30];		
// Variable para manejar compatibilidad de tipos en asignacion
int flagEsString = 0;
// Variable para manejar compatibilidad de tipos en expresiones
int flagExpresionEsString = 0;

//variables globales
int yystopparser=0;
int contadorLong=0;
FILE  *yyin, *ts;
int flagLong=0;
int cantElementos;
t_symbol *vectorSymbol;


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
int guardarTSBin(char* string);
int guardarTSHexa(char* string);
int guardarTSReal(double num);
int guardarTSString(char* string);
int esString(int pos );
void guardarVariables();
int convertirBinDecim(char* binario);
int guardarTSBin(char* string);
int convertirHexaDecim(char* hexa);
void encolar(char* dato, struct Cola* cola);
void desacolar(struct Cola* cola, char* result);
void mostrarError(int codError, char* parametro);

%}

%union {
	int intval;
	double doubleval;
	char str_val[50];
}

//=====================================================================================================
// Seccion de tokens
//=====================================================================================================
%token PROGRAM ENDPROGRAM DIM AS ENDDECLARE DECLARE START
%token ENDWHILE BEGINWHILE WHILE
%token FOR TO  STEP NEXT 
%token IF THEN ELSE ENDIF 
%token OP_ASIG PYC
%token CONST_INT CONST_BIN CONST_HEXA CONST_REAL CONST_STR
%token ID
%token ENTERO OP_SUMA OP_RESTA OP_MULT OP_DIV OP_CONCATENACION OP_NOT
%token GET DISPLAY
%token OP_LOG OP_COMPARACION
%token CORCHETE_A CORCHETE_C COMA TIPO PARENTESIS_A PARENTESIS_C
%token BASE GUION_B
%token LONGITUD

%%
//=====================================================================================================
// Seccion de definicion de reglas
//=====================================================================================================

programa: 
			START est_declaracion algoritmo 
			| START algoritmo
			;
			
algoritmo: 
			PROGRAM	{ escribirEnPantalla("Bloques", 0);
					} bloque ENDPROGRAM {escribirEnPantalla("Bloques", 1);}	
					{ printf("\n---------------------------\n");}
					{ printf("\n****COMPILACION EXITOSA****\n");}
					{ printf("\n---------------------------\n");} 
			;

bloque:  
		sentencia { printf("\n***REGLA 1 -> Bloque:\n");} 
				  { printf("\t\t\tSentencia\n");}
		|bloque sentencia	{ printf("\n***REGLA 2 -> Bloque:\n");} 
							{ printf("\t\t\t Bloque Sentencia\n");}
		;
	
sentencia:
			decision { printf("\n***REGLA 3 -> Sentencia:\n");} 
					 { printf("\t\t\t Decision\n");} //{escribirLineaEnPantalla("IF");}
			|asignacion { printf("\n***REGLA 4 -> Sentencia:\n");} 
						{ printf("\t\t\t Asignacion\n");}//{ escribirLineaEnPantalla("ASIGNACION"); }
			|while { printf("\n***REGLA 5 -> Sentencia:\n");} 
				   { printf("\t\t\t While\n");}//{escribirLineaEnPantalla("WHILE");}
			|for   { printf("\n***REGLA 6 -> Sentencia:\n");} 
				   { printf("\t\t\t For\n");}//{escribirLineaEnPantalla("FOR");}	   
			|lectura { printf("\n***REGLA 7 -> Sentencia:\n");} 
					 { printf("\t\t\t Lectura\n");}//{escribirLineaEnPantalla("Entrada DISPLAY");}
			|escritura { printf("\n***REGLA 8 -> Sentencia:\n");} 
					   { printf("\t\t\t Escritura\n");}//{ escribirLineaEnPantalla("Salida GET");}
		  |longitud { printf("\n***REGLA 9 -> Sentencia:\n");} 
					  { printf("\t\t\t Longitud\n");}//{ escribirLineaEnPantalla("Funcion LONGITUD");}
			;	

while:
		WHILE PARENTESIS_A condicion PARENTESIS_C  BEGINWHILE bloque ENDWHILE 
		{ printf("\n***REGLA 10 -> While:\n");} 
		{ printf("\t\t\t WHILE (condicion) BEGINWHILE bloque ENDWHILE\n");}
		;
	
decision: 
			IF PARENTESIS_A condicion PARENTESIS_C THEN bloque ENDIF 
			{ printf("\n***REGLA 11 -> Decision:\n");} 
			{ printf("\t\t\t IF (condicion) THEN bloque ENDIF\n");}
			|IF PARENTESIS_A condicion PARENTESIS_C THEN bloque ELSE bloque ENDIF
			{ printf("\n***REGLA 12 -> Decision:\n");} 
			{ printf("\t\t\t IF PARENTESIS_A condicion PARENTESIS_C THEN bloque ELSE bloque ENDIF\n");}
	
	;
	
for: FOR{ printf("\n***REGLA 13 -> C0mienza For:\n");} expresion OP_ASIG expresion TO expresion CORCHETE_A STEP CONST_INT CORCHETE_C NEXT expresion
	{ printf("\n***REGLA 13 -> FIN For:\n");} 
	{ printf("\t\t\t \n");}
	 
condicion:
			expresion_logica { printf("\n***REGLA 14 -> Condicion:\n");} 
							 { printf("\t\t\t expresion_logica\n");}
			|expresion_logica OP_LOG expresion_logica { printf("\n***REGLA 15 -> Condicion:\n");} 
													  { printf("\t\t\t expresion_logica OP_LOG expresion_logica\n");}
			;
	
expresion_logica:
					comparacion { printf("\n***REGLA 16	-> Expresion_logica:\n");} 
								{ printf("\t\t\t comparacion\n");}
					|OP_NOT comparacion { printf("\n***REGLA 17	-> Expresion_logica:\n");} 
										{ printf("\t\t\t OP_NOT comparacion\n");}
					;

comparacion:
				expresion  { flagExpresionEsString = flagEsString;}
				OP_COMPARACION  expresion {
					if ( flagEsString != flagExpresionEsString ) 
					mostrarError(ERROR_EXPRESIONES_INCOMPATIBLES, NULL);
					}
				{ printf("\n***REGLA 18	-> Comparacion:\n");} 
				{ printf("\t\t\t expresion OP_COMPARACION expresion\n");}
				;	
	
asignacion: 
			ID { if (DEBUG) printf("asignacion->ID\n");
					strcpy(auxAsignacionID, $<str_val>1);		// Guardo en una variable auxiliar el indentificador detectado
				}
			OP_ASIG expresion { if (DEBUG) printf("asignacion->OP_ASIG expresion\n");
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
			}
			{	printf("\n***REGLA 19	-> Asignacion:\n");} 
			{	printf("\t\t\t ID OP_ASIG expresion\n");}
			;
	
expresion: 
			termino { 
			  if (DEBUG) printf("expresion->termino\n");
			} 
			{ printf("\n***REGLA 20	-> Expresion:\n");} 
			{ printf("\t\t\t termino\n");}
			|expresion {
				if ( flagEsString  == ES_CADENA ) 
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
			   }
			op_sumres  termino {	
				if ( flagEsString == ES_CADENA ) 
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
				}
			{ printf("\n***REGLA 21	-> Expresion:\n");} 
			{ printf("\t\t\t expresion op_sumres termino\n");}
			;
	
longitud:
			//{ escribirLineaEnPantalla("Inicio Funcion LONGITUD"); }
			{flagLong=1;}
			LONGITUD PARENTESIS_A  CORCHETE_A listaID CORCHETE_C PARENTESIS_C //{printf("La longitud es %d\n",contadorLong);}
			{ escribirLineaEnPantalla("Fin LONGITUD"); }
			{flagLong=0;}
			{contadorLong=0;}
			{printf("\n***REGLA 22 -> Longitud:\n");} 
			{printf("\t\t\t LONGITUD ([listaID])\n");}
		;



op_sumres: 
			OP_SUMA //{escribirLineaEnPantalla("operacion SUMA");} 
			{ printf("\n***REGLA 23 -> Op_sumres:\n");} 
			{ printf("\t\t\t OP_SUMA\n");}
			| OP_RESTA //{escribirLineaEnPantalla("operacion RESTA");} 
			{ printf("\n***REGLA 24 -> Op_sumres:\n");} 
			{ printf("\t\t\t OP_RESTA\n");}
			;
			
termino: 
		factor { if (DEBUG) printf("termino->factor\n");}
			   { printf("\n***REGLA 25 -> Termino:\n");} 
			   { printf("\t\t\t factor\n");}
		|termino {if ( flagEsString == ES_CADENA ) 
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
				 }op_multdiv
		factor {
				if (DEBUG) printf("termino->factor op_multdiv factor\n");
				if ( flagEsString == ES_CADENA ) 
	
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
	
				}
		{ printf("\n***REGLA 26 -> Termino:\n");} 
		{ printf("\t\t\t termino op_multdiv factor\n");}
		;
	

op_multdiv: 
			OP_MULT //{escribirLineaEnPantalla("operacion PRODUCTO");}
			{ printf("\n***REGLA 27 -> op_multdiv:\n");} 
			{ printf("\t\t\t OP_MULT\n");}
			| OP_DIV//{escribirLineaEnPantalla("operacion DIVISION");}
			{ printf("\n***REGLA 28 -> op_multdiv:\n");} 
			{ printf("\t\t\t OP_DIV\n");}
			;
	
lectura:
		DISPLAY ID
		{ printf("\n***REGLA 29 -> Lectura:\n");} 
		{ printf("\t\t\t DISPLAY ID\n");}
		;

escritura:
			GET factor
			{ printf("\n***REGLA 30 -> Escritura:\n");} 
			{ printf("\t\t\t GET factor\n");}
			;	 

factor: 
		ID { 
		  if (DEBUG) 
			printf("factor->ID\n");
		  int pos = buscarEnVector($<str_val>1);
		  if ( pos == -1 ) 
			 mostrarError(ERROR_ID_NO_DECLARADO, $<str_val>1);
		  if ( esString(pos) == ES_CADENA )
			 flagEsString = ES_CADENA;
		  else
			 flagEsString = NO_ES_CADENA;
	      }
		{ printf("\n***REGLA 31 -> Factor:\n");} 
		{ printf("\t\t\t ID\n");}
		|CONST_INT  { if (DEBUG) printf("factor->CONST_INT\n");
							//printf("guardo %d\n",$<intval>1); 
							int pos = guardarTSInt($<intval>1);
							flagEsString = NO_ES_CADENA;
							$<intval>$ = $<intval>1; 
					}
					{ printf("\n***REGLA 32 -> Factor:\n");} 
					{ printf("\t\t\t CONST_INT\n");}

		|CONST_REAL { if (DEBUG) printf("factor->CONST_REAL\n");	
							//printf("guardo %f\n",$<doubleval>1); 
							int pos = guardarTSReal($<doubleval>1); 
							flagEsString = NO_ES_CADENA;
							{ printf("\n***REGLA 33 -> Factor:\n");} 
							{ printf("\t\t\t CONST_REAL\n");}		}
		|CONST_STR { 
						if (DEBUG) 
							printf("factor->CONST_STR\n");
							//printf("guardo cadena %s\n",$<str_val>1);  
							int pos = guardarTSString($<str_val>1); 
					flagEsString = ES_CADENA;
					}
					{ printf("\n***REGLA 34 -> Factor:\n");} 
					{ printf("\t\t\t CONST_STR\n");}
		|longitud {
					if (DEBUG) 
						printf("factor->longitud\n");
						flagEsString = NO_ES_CADENA;
				  }
				 { printf("\n***REGLA 35 -> Factor:\n");} 
				 { printf("\t\t\t longitud\n");}
		|PARENTESIS_A expresion PARENTESIS_C
			{ printf("\n***REGLA 36 -> Factor:\n");} 
			{ printf("\t\t\t PARENTESIS_A expresion PARENTESIS_C\n");}
		;
	
est_declaracion: 
				DECLARE declaraciones ENDDECLARE 	{ printf("\n***REGLA 37 -> est _Declaracion:\n");} 
													{ printf("\t\t\t DECLARE declaraciones ENDDECLARE\n");}
				;

declaraciones:	
				declaracion { guardarVariables();}	
				{ printf("\n***REGLA 38 -> Declaraciones:\n");} 
				{ printf("\t\t\tdeclaracion\n");}
				| declaraciones declaracion { guardarVariables();} 	
				{ printf("\n***REGLA 39 -> Declaraciones:\n");} 
				{ printf("\t\t\tdeclaraciones declaracion\n");}
				;


declaracion:
				DIM CORCHETE_A listaID CORCHETE_C AS CORCHETE_A listaTipo CORCHETE_C {
																		   if ( colaID.cantElem != colaTipo.cantElem) 
																				mostrarError(ERROR_TAM_DISTINTO_LISTAID_LISTATIPO, ""); 
																				escribirLineaEnPantalla("Declaraciones");
																			}
																			{ printf("\n***REGLA 40 -> Declaracion:\n");} 
																			{ printf("\t\t\tDIM[listaID] AS [listaTipo]\n");}
				;

listaTipo:
			TIPO { encolar($<str_val>1, &colaTipo); } 
			{ printf("\n***REGLA 41 -> ListaTipo:\n");} 
			{ printf("\t\t\tTipo\n");}
			|listaTipo COMA TIPO { encolar($<str_val>3, &colaTipo); } 
			{ printf("\n***REGLA 42 -> ListaTipo:\n");} 
			{ printf("\t\t\tlistaTipo COMA TIPO\n");}
			;

listaID:
			ID {  if (flagLong==1)
					contadorLong++;
					if (DEBUG) 
						printf("listaID->ID\n");
					encolar($<str_val>1, &colaID);
			}
			{ printf("\n***REGLA 43 -> ListaId:\n");} 
			{ printf("\t\t\tID\n");}
			| listaID COMA ID { if (flagLong==1)
									contadorLong++;
									if (DEBUG) 
										printf("listaID->listaID COMA ID\n");
									encolar($<str_val>3, &colaID); 
			}
			{ printf("\n***REGLA 44 -> ListaId:\n");} 
			{ printf("\t\t\tlistaId COMA ID\n");}
			;	

	
%%
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
		char linea[100];
		generarLinea(symbol, linea);
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
	for (i = 0; i < cantElementos; ++i){ //recorro el vector
		if(strcmp(vectorSymbol[i].nombreVar, nombre) == 0) //si el nombre coincide
			return i; //ya estaba en la tabla
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
	return guardarEnVector(aux, 0);
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

//guarda un INT en TS
int guardarTSHexa(char* string){

	int valor = convertirHexaDecim(string);
	char buffer[11];
	//itoa(valor, buffer, 16);
	sprintf(buffer, "%d", valor);
	t_symbol aux= getSymbol(string, "CONST_HEXA", string,buffer, "");
	int result = guardarEnVector(aux, 0);
	return result;
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
