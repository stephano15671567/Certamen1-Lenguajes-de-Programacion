%{
#include "viaje.tab.h"
%}

%%
"definir_tasas"       { return DEFINIR_TASAS; }
"crear_ac"            { return CREAR_AC; }
"conectar_ac"         { return CONECTAR_AC; }
"iniciar_simulacion"  { return INICIAR_SIMULACION; }
"avanzar_pasos"       { return AVANZAR_PASOS; }
"detener_simulacion"  { return DETENER_SIMULACION; }
"seleccionar_modelo"  { return SELECCIONAR_MODELO; }
[0-9]+(\.[0-9]+)?     { yylval.numero = atof(yytext); return NUMERO; }
[ \t\n]               { /* Ignorar espacios, tabulaciones y nuevas líneas */ }
.                     { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
