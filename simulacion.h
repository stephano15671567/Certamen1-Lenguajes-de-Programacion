#ifndef SIMULACION_H
#define SIMULACION_H

// Definición del tipo enumerado Modelo
typedef enum {
    SEIR,
    SEIRD,
    SEIVR,
    SEIHFR
} Modelo;

typedef struct {
    int id;
    float S, E, I, R;   // Compartimentos básicos de SEIR
    float D;            // Añadir este para SEIRD
    float V;            // Añadir este para SEIVR
    float H, F;         // Añadir estos para SEIHFR
} AC;

void crear_ac(int id);
void conectar_ac(int ac1, int ac2);
void definir_tasas(float beta, float alpha1, float alpha2, float rho, float mu, float delta, float Lambda, float gamma_rate, float omega, float theta);
void seleccionar_modelo(Modelo modelo); // Nueva función para seleccionar el modelo
void iniciar_simulacion();
void avanzar_pasos(int n);
void detener_simulacion();

#endif

