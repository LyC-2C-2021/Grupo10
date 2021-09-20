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

#define TABLA_SIMBOLO "ts.txt"

#define DEBUG		0					// 1: Activa debug. Imprime las reglas aplicadas	
										// 0: Desactiva debug


typedef struct symbol{
	char nombreVar[35], tipo[20], valor[35], valorDecimal[35], longitud[33];
} t_symbol;

struct node{
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

