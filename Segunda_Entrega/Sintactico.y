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
int auxForInicio=0;
int valorForInicio=0;
int valorForFinal=0;
int auxForFinal=0;
int auxForIncremento=1;

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
int guardarTSIntFor(int num);
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
%token FOR TO STEP NEXT 
%token IF THEN ELSE ENDIF
%token OP_ASIG PYC
%token CONST_INT CONST_BIN CONST_HEXA CONST_REAL CONST_STR
%token ID
%token ENTERO OP_SUMA OP_RESTA OP_MULT OP_DIV OP_CONCATENACION OP_NOT
%token GET DISPLAY
%token OP_LOG OP_COMPARACION
%token CORCHETE_A CORCHETE_C COMA TIPO PARENTESIS_A PARENTESIS_C
%token BASE GUION_B
//%token FILTER
//%right MENOS_UNARIO
%token LONGITUD

%%
//=====================================================================================================
// Seccion de definicion de reglas
//=====================================================================================================

programa: 
			START {aumentarNivelParentesis();}est_declaracion algoritmo {escribirArchivoTercetos(); escribirEncabezadoArchivoAssembler();}
			| START {aumentarNivelParentesis();} algoritmo {escribirArchivoTercetos(); escribirEncabezadoArchivoAssembler();}
			;
			
algoritmo: 
	PROGRAM{
		//escribirEnPantalla("Bloques", 0);
	} bloque ENDPROGRAM {
		//escribirEnPantalla("Bloques", 1);
	}
	{ printf        ("\n---------------------------\n");}
					{ printf("\n****COMPILACION EXITOSA****\n");}
					{ printf("\n---------------------------\n");} 
	;

bloque:  
	sentencia 
	|bloque sentencia
	;
	
sentencia:
	  decision  //{escribirLineaEnPantalla("IF");}
	 |asignacion //{ escribirLineaEnPantalla("ASIGNACION"); }
     |while		//{escribirLineaEnPantalla("WHILE");}
	 |for		//{escribirLineaEnPantalla("FOR");}
	 |lectura  //{escribirLineaEnPantalla("Entrada DISPLAY");}
	 |escritura //{ escribirLineaEnPantalla("Salida GET");}
	 ;	

while:
	WHILE {push(STACK_POSICION, indiceTerceto);} 
	PARENTESIS_A condicion PARENTESIS_C  
	BEGINWHILE 
	bloque 
	ENDWHILE{
		setearSalto(indiceTerceto+1); 
		crearTerceto("BI", -1 , pop(STACK_POSICION));
		}
		
	;
	
decision: 
	IF PARENTESIS_A condicion PARENTESIS_C THEN bloque ENDIF {
		setearSalto(indiceTerceto);   
	}
	|IF PARENTESIS_A condicion PARENTESIS_C THEN bloque {
		setearSalto(indiceTerceto+1);
		push(STACK_CONDICION,crearTerceto("BI", -1, -1).numeroTerceto);   
	}  ELSE bloque ENDIF { 
		vectorTercetos[pop(STACK_CONDICION)].t2 = indiceTerceto;   
	}
	;
	
for: FOR inicioFor  TO  finFor CORCHETE_A STEP constanteEntera  CORCHETE_C NEXT expresion 
	
	{
		int v[100];
		int pos[100];
		int j=0, valor;
		//printf("valorForInicio es: %d\n",valorForInicio);
		//printf("valorForFinal es: %d\n",valorForFinal);
		//printf("auxForIncremento es: %d\n",auxForIncremento);
		for(valorForInicio;valorForInicio<valorForFinal;auxForIncremento)
		{
			//printf("guardo %d\n",valorForInicio); 
			//printf("\n for valor  %d:\n",valorForInicio); 
			sprintf(auxAsignacionID, "%d", valorForInicio);				
			//valorForInicio+=auxForIncremento;
			//printf("valorForInicio es: %d\n",valorForInicio);
			//GUARDAR EN LA TABLA DE SIMBOLO
			v[j]=valorForInicio;
			//pos[j]= guardarTSInt(v[j]);
			//printf("v[j]es: %d\n",v[j]);
			char buffer[11];
			itoa(v[j], buffer, 10);
			t_symbol aux= getSymbol(buffer, "CONST_INT", buffer,buffer,"");
			pos[j]=guardarEnVector(aux, 0);
			//printf("posicion: %d\n",pos[j]);
			j++;
			//
			//CREA EL TERCETO
			t_terceto tAux = crearTerceto(auxAsignacionID,-1,-1);
			crearTerceto(":=", expresion_terceto.numeroTerceto,tAux.numeroTerceto);
			valorForInicio+=auxForIncremento;
		}
		}
	

inicioFor:{auxForInicio=-1;}asignacion /*{ printf("\n for valor inicio %d:\n",valorForInicio);}*/{auxForInicio=0;} ;

finFor:{auxForFinal=-1;} expresion/*{ printf("\n for valor final %d:\n",valorForFinal);}*/{auxForFinal=0;};
constanteEntera:CONST_INT  { 
							auxForIncremento=$<intval>1;
					//  printf("valor %d\n",auxForIncremento);
				}
 
for: FOR inicioFor  TO  finFor CORCHETE_A STEP  CORCHETE_C NEXT expresion 
	
	{
		int v[100];
		int pos[100];
		int j=0, valor;
		int auxIncremento;
		auxIncremento=1;
		for(valorForInicio;valorForInicio<valorForFinal;auxIncremento)
		{
			
			sprintf(auxAsignacionID, "%d", valorForInicio);		
			//GUARDAR EN LA TABLA DE SIMBOLO
			v[j]=valorForInicio;
			
			char buffer[11];
			itoa(v[j], buffer, 10);
			t_symbol aux= getSymbol(buffer, "CONST_INT", buffer,buffer,"");
			pos[j]=guardarEnVector(aux, 0);
			j++;
			//
			//CREA EL TERCETO
			t_terceto tAux = crearTerceto(auxAsignacionID,-1,-1);
			crearTerceto(":=", expresion_terceto.numeroTerceto,tAux.numeroTerceto);
			valorForInicio+=auxIncremento;
		}
		}
			
condicion:
	expresion_logica {
		push(STACK_OPERADOR, 0);
		//printf("PASA1\n");
	}
	|expresion_logica OP_LOG {
		if(strcmp($<str_val>2, "AND") == 0) 
		{	push(STACK_OPERADOR, OPERADOR_AND);
		}
		else
		{
			push(STACK_OPERADOR, OPERADOR_OR);
		}
	} expresion_logica 
	;


	
expresion_logica:
	comparacion
	|OP_NOT comparacion {
		negarTerceto(indiceTerceto-1);
	}  
	;

comparacion:
	expresion  {
		flagExpresionEsString = flagEsString; 
		expresion_terceto_aux = expresion_terceto;
	} OP_COMPARACION {
				strcpy(operador_comparacion,$<str_val>3);
			}
		expresion {
		if ( flagEsString != flagExpresionEsString ) 
			mostrarError(ERROR_EXPRESIONES_INCOMPATIBLES, NULL);
			
		t_terceto CMP_terceto = crearTerceto("CMP", expresion_terceto_aux.numeroTerceto, expresion_terceto.numeroTerceto);
		t_terceto condicion_if_terceto = crearTerceto(getValueCondicion(operador_comparacion), CMP_terceto.numeroTerceto,-1);
		push(STACK_CONDICION,condicion_if_terceto.numeroTerceto);
	}
	;	
	
asignacion: 
    ID {
    	if (DEBUG) printf("asignacion->ID\n");

    	strcpy(auxAsignacionID, $<str_val>1);		// Guardo en una variable auxiliar el indentificador detectado
	
		
		
    	}
    OP_ASIG expresion 
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
		 if(auxForInicio!=-1 && auxForFinal!=-1)
				{
		t_terceto tAux = crearTerceto(auxAsignacionID,-1,-1);
		
		crearTerceto(":=", tAux.numeroTerceto, expresion_terceto.numeroTerceto);
}
    	}
	;
	
expresion: 
	termino { 
	
			  //printf("Es termino\n");
			  if (DEBUG) printf("expresion->termino\n");
			  expresion_terceto = termino_terceto;
			  setearTercetoOperacionActual(expresion_terceto.numeroTerceto, -1 , -1);
			 // printf("Es termino %d\n",expresion_terceto.numeroTerceto);
			} 
	|expresion {
				if ( flagEsString  == ES_CADENA ) 
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
			   }
	op_sumres {
	
		
				push_op(STACK_EXPRESION, $<str_val>3);
				} termino {
				if(auxForInicio!=-1 && auxForFinal!=-1)
				{
				if ( flagEsString == ES_CADENA ) 
					mostrarError(ERROR_NUMERO_ESPERADO, NULL);
				char operador[3];
				pop_op(STACK_EXPRESION, operador);
				expresion_terceto = crearTerceto(operador, obtenerTercetoOperacionActual().expresion, obtenerTercetoOperacionActual().termino);
				setearTercetoOperacionActual(expresion_terceto.numeroTerceto, -1 , -1);
				}
				}
				
	;


longitud:
			//{ escribirLineaEnPantalla("Inicio Funcion LONGITUD"); }
			{flagLong=1;}
			LONGITUD PARENTESIS_A  CORCHETE_A listaID CORCHETE_C PARENTESIS_C //{printf("La longitud es %d\n",contadorLong);}
			
			 {	
				//char*str; sprintf(str,"%d", contadorLong);
				//sprintf(auxAsignacionID, "%d", contadorLong);	
				int pos =guardarTSInt(contadorLong); 
				factor_terceto =  crearTerceto(vectorSymbol[pos].nombreVar,-1,-1);
				  setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);
				  }
			
			//{ escribirLineaEnPantalla("Fin LONGITUD"); }
			{flagLong=0;}
			{contadorLong=0;}
			//{printf("\n***REGLA 22 -> Longitud:\n");} 
		//	{printf("\t\t\t LONGITUD ([listaID])\n");}
			
		;


	
	
op_sumres: OP_SUMA {if(auxForInicio!=-1 && auxForFinal!=-1);
					} 

| OP_RESTA {if(auxForInicio!=-1 && auxForFinal!=-1)
				;} 
	;
			
termino: 
	factor  { 
				//printf("Es termino\n");
				if (DEBUG) printf("termino->factor\n");
				termino_terceto = factor_terceto;
				
				setearTercetoOperacionActual(-1, termino_terceto.numeroTerceto, -1);
				//printf("dsp\n");
				
				
			}
			
	|termino {
		if ( flagEsString == ES_CADENA ) 
			mostrarError(ERROR_NUMERO_ESPERADO, NULL);
	}
	op_multdiv {push_op(STACK_FACTOR, $<str_val>3);} 
	factor {

		if (DEBUG) printf("termino->factor op_multdiv factor\n");

		if ( flagEsString == ES_CADENA ) 
			mostrarError(ERROR_NUMERO_ESPERADO, NULL);
		char operador[3];
		pop_op(STACK_FACTOR, operador);
		termino_terceto = crearTerceto(operador, obtenerTercetoOperacionActual().termino, obtenerTercetoOperacionActual().factor);
		setearTercetoOperacionActual(-1, termino_terceto.numeroTerceto, -1);
	}
	
	;
	
op_multdiv: OP_MULT  | OP_DIV;
	;
lectura:
	DISPLAY ID 
	;

escritura:
	GET factor
	;	 


factor:
	ID { 
		  if (DEBUG) printf("factor->ID\n");
		
		  int pos = buscarEnVector($<str_val>1);

		  if ( pos == -1 ) 
			 mostrarError(ERROR_ID_NO_DECLARADO, $<str_val>1);

		  if ( esString(pos) == ES_CADENA )
			 flagEsString = ES_CADENA;
		  else
			 flagEsString = NO_ES_CADENA;
			 
			factor_terceto = crearTerceto($<str_val>1,-1,-1);
			setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);

	   }
	|CONST_INT  { 
					if(auxForInicio==-1)
					{
						valorForInicio+=$<intval>1;
					}
					if(auxForFinal==-1)
					{
						valorForFinal+=$<intval>1;
					}
					if(auxForInicio!=-1 && auxForFinal!=-1)
					{
						if (DEBUG) printf("factor->CONST_INT\n");

				  //printf("guardo %d\n",$<intval>1);
				  int pos = guardarTSInt($<intval>1);				  
				  flagEsString = NO_ES_CADENA;
				
				  factor_terceto =  crearTerceto(vectorSymbol[pos].nombreVar,-1,-1);
				  setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);
					
					}
				  
				}
	
	|CONST_REAL { 
				  if (DEBUG) printf("factor->CONST_REAL\n");	

				 // printf("guardo %f\n",$<doubleval>1); 
				  int pos = guardarTSReal($<doubleval>1); 
				  flagEsString = NO_ES_CADENA;
				  factor_terceto =  crearTerceto(vectorSymbol[pos].nombreVar,-1,-1);
				  setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);
				}
	|CONST_STR { 
				  if (DEBUG) printf("factor->CONST_STR\n");

				  //printf("guardo cadena %s\n",$<str_val>1);  
				  int pos = guardarTSString($<str_val>1); 
				  factor_terceto =  crearTerceto(vectorSymbol[pos].nombreVar,-1,-1); 
				  setearTercetoOperacionActual(-1,-1, factor_terceto.numeroTerceto);
				  flagEsString = ES_CADENA;
				}	
|longitud {
				if (DEBUG) printf("factor->longitud\n");

				//flagEsString = NO_ES_CADENA;
				
				
			}			
	|PARENTESIS_A { 

		aumentarNivelParentesis();
	} expresion  
	PARENTESIS_C {
		if(NO_ES_CADENA) 
			mostrarError(ERROR_PARENTESIS_CONCATENACION, NULL);
		decrementarNivelParentesis();
		factor_terceto = expresion_terceto;
		 
	}
	;
	

est_declaracion: 
				DECLARE declaraciones ENDDECLARE 
				;

declaraciones:	
				declaracion {guardarVariables();}
				| declaraciones declaracion {guardarVariables();}
				;


declaracion:
	DIM CORCHETE_A listaID CORCHETE_C AS CORCHETE_A listaTipo CORCHETE_C {
																		   if ( colaID.cantElem != colaTipo.cantElem) 
																		  	  mostrarError(ERROR_TAM_DISTINTO_LISTAID_LISTATIPO, ""); 

																		   //escribirLineaEnPantalla("Declaraciones");
																		  }
	;

listaTipo:
	TIPO {encolar($<str_val>1, &colaTipo); }
	|listaTipo COMA TIPO { encolar($<str_val>3, &colaTipo); }
	;

listaID:
	ID { 
	if (flagLong==1)contadorLong++;
		if (DEBUG) printf("listaID->ID\n");
		encolar($<str_val>1, &colaID);
		
			if(filterActivado==1)
			{
				//printf("********encolo: %s\n", $<str_val>1);
				cantidadVar++;
				// busco en vector de tercetos
				t_terceto var;
				strcpy(var.operacion,$<str_val>1);
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
				
				////////////////// creo terceto 
		
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
			
		
	}
	| listaID COMA ID { 
	if (flagLong==1)contadorLong++;
		if (DEBUG) printf("listaID->listaID COMA ID\n");
		encolar($<str_val>3, &colaID); 
		
	
			if(filterActivado==1)
			{
				//printf("********encolo: %s\n", $<str_val>1);
				cantidadVar++;
				// busco en vector de tercetos
				t_terceto var;
				strcpy(var.operacion,$<str_val>3);
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

			
		
	}
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