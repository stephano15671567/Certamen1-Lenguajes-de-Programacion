%{
#include <stdio.h>
#include "simulacion.h"

// Declarar las funciones utilizadas por Bison y Flex
int yylex();
void yyerror(const char *s);
%}

// Declaración del tipo de datos para los tokens
%union {
    int entero;
    float numero;
}

// Definición de los tokens
%token DEFINIR_TASAS CREAR_AC CONECTAR_AC INICIAR_SIMULACION AVANZAR_PASOS DETENER_SIMULACION SELECCIONAR_MODELO
%token <numero> NUMERO

%type <numero> comando

%%

comandos:
    comando
    | comandos comando
    ;

comando:
    DEFINIR_TASAS NUMERO NUMERO NUMERO NUMERO NUMERO NUMERO NUMERO NUMERO NUMERO NUMERO {
        definir_tasas($2, $3, $4, $5, $6, $7, $8, $9, $10, $11);
    }
    | CREAR_AC NUMERO {
        crear_ac($2);
    }
    | CONECTAR_AC NUMERO NUMERO {
        conectar_ac($2, $3);
    }
    | INICIAR_SIMULACION {
        iniciar_simulacion();
    }
    | AVANZAR_PASOS NUMERO {
        avanzar_pasos($2);
    }
    | DETENER_SIMULACION {
        detener_simulacion();
    }
    | SELECCIONAR_MODELO NUMERO {
        seleccionar_modelo($2);
    }
    ;

%%
int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
