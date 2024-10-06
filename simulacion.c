#include <stdio.h>
#include <stdlib.h>
#include "simulacion.h"

#define NUM_AC 10 // Número máximo de ACs

AC ac_list[NUM_AC]; // Lista de ACs
int num_ac = 0;
Modelo modelo_seleccionado = SEIR; // Variable para almacenar el modelo seleccionado

// Parámetros del modelo
float beta = 0.3, alpha1 = 0.1, alpha2 = 0.1, rho = 0.05, mu = 0.02, delta = 0.01, Lambda = 1.0;
float gamma_rate = 0.1, omega = 0.05, theta = 0.02; // Nuevas tasas para modelos adicionales

void crear_ac(int id) {
    if (num_ac < NUM_AC) {
        ac_list[num_ac].id = id;
        ac_list[num_ac].S = 100;
        ac_list[num_ac].E = 0;
        ac_list[num_ac].I = 1;
        ac_list[num_ac].R = 0;
        ac_list[num_ac].D = 0;
        ac_list[num_ac].V = 0;
        ac_list[num_ac].H = 0;
        ac_list[num_ac].F = 0;
        num_ac++;
        printf("AC creado con ID: %d\n", id);
    } else {
        printf("Número máximo de AC alcanzado\n");
    }
}

void conectar_ac(int ac1, int ac2) {
    if (ac1 >= 0 && ac1 < num_ac && ac2 >= 0 && ac2 < num_ac) {
        printf("Conexión creada entre AC %d y AC %d\n", ac1, ac2);
    } else {
        printf("Error: IDs de AC no válidos\n");
    }
}

void definir_tasas(float b, float a1, float a2, float r, float m, float d, float L, float g, float o, float t) {
    beta = b;
    alpha1 = a1;
    alpha2 = a2;
    rho = r;
    mu = m;
    delta = d;
    Lambda = L;
    gamma_rate = g; 
    omega = o;
    theta = t;
    printf("Tasas definidas: β=%.2f, α1=%.2f, α2=%.2f, ρ=%.2f, μ=%.2f, δ=%.2f, Λ=%.2f, γ=%.2f, ω=%.2f, θ=%.2f\n", beta, alpha1, alpha2, rho, mu, delta, Lambda, gamma_rate, omega, theta);
}

void seleccionar_modelo(Modelo modelo) {
    modelo_seleccionado = modelo;
    switch (modelo) {
        case SEIR:
            printf("Modelo SEIR seleccionado.\n");
            break;
        case SEIRD:
            printf("Modelo SEIRD seleccionado.\n");
            break;
        case SEIVR:
            printf("Modelo SEIVR seleccionado.\n");
            break;
        case SEIHFR:
            printf("Modelo SEIHFR seleccionado.\n");
            break;
    }
}

void avanzar_pasos(int n) {
    for (int paso = 0; paso < n; paso++) {
        for (int i = 0; i < num_ac; i++) {
            float dS = 0, dE = 0, dI = 0, dR = 0, dD = 0, dV = 0, dH = 0, dF = 0;
            float N = ac_list[i].S + ac_list[i].E + ac_list[i].I + ac_list[i].R + ac_list[i].D + ac_list[i].V + ac_list[i].H + ac_list[i].F;
            
            // Modelo SEIR
            if (modelo_seleccionado == SEIR) {
                dS = Lambda + rho * ac_list[i].R - beta * ac_list[i].S * ac_list[i].I / N - mu * ac_list[i].S;
                dE = beta * ac_list[i].S * ac_list[i].I / N - alpha1 * ac_list[i].E - mu * ac_list[i].E;
                dI = alpha1 * ac_list[i].E - alpha2 * ac_list[i].I - mu * ac_list[i].I - delta * ac_list[i].I;
                dR = alpha2 * ac_list[i].I - rho * ac_list[i].R - mu * ac_list[i].R;
            }

            // Modelo SEIRD - incluyendo D (Muertos)
            if (modelo_seleccionado == SEIRD) {
                dS = Lambda + rho * ac_list[i].R - beta * ac_list[i].S * ac_list[i].I / N - mu * ac_list[i].S;
                dE = beta * ac_list[i].S * ac_list[i].I / N - alpha1 * ac_list[i].E - mu * ac_list[i].E;
                dI = alpha1 * ac_list[i].E - alpha2 * ac_list[i].I - mu * ac_list[i].I - delta * ac_list[i].I;
                dR = alpha2 * ac_list[i].I - rho * ac_list[i].R - mu * ac_list[i].R;
                dD = delta * ac_list[i].I; // Muertos por la enfermedad
            }

            // Modelo SEIVR - incluyendo V (Vacunados)
            if (modelo_seleccionado == SEIVR) {
                dS = Lambda + rho * ac_list[i].R - beta * ac_list[i].S * ac_list[i].I / N - mu * ac_list[i].S - omega * ac_list[i].S;
                dE = beta * ac_list[i].S * ac_list[i].I / N - alpha1 * ac_list[i].E - mu * ac_list[i].E;
                dI = alpha1 * ac_list[i].E - alpha2 * ac_list[i].I - mu * ac_list[i].I - delta * ac_list[i].I;
                dR = alpha2 * ac_list[i].I - rho * ac_list[i].R - mu * ac_list[i].R;
                dV = omega * ac_list[i].S; // Tasa de vacunación
            }

            // Modelo SEIHFR - incluyendo H (Hospitalizado) y F (Fallecido)
            if (modelo_seleccionado == SEIHFR) {
                dS = Lambda + rho * ac_list[i].R - beta * ac_list[i].S * ac_list[i].I / N - mu * ac_list[i].S;
                dE = beta * ac_list[i].S * ac_list[i].I / N - alpha1 * ac_list[i].E - mu * ac_list[i].E;
                dI = alpha1 * ac_list[i].E - alpha2 * ac_list[i].I - mu * ac_list[i].I - delta * ac_list[i].I - gamma_rate * ac_list[i].I;
                dR = alpha2 * ac_list[i].I - rho * ac_list[i].R - mu * ac_list[i].R;
                dH = gamma_rate * ac_list[i].I; // Hospitalización
                dF = theta * ac_list[i].H; // Fallecimientos hospitalizados
            }

            // Actualizar valores
            ac_list[i].S += dS;
            ac_list[i].E += dE;
            ac_list[i].I += dI;
            ac_list[i].R += dR;
            ac_list[i].D += dD;
            ac_list[i].V += dV;
            ac_list[i].H += dH;
            ac_list[i].F += dF;

            printf("AC %d - S: %.2f, E: %.2f, I: %.2f, R: %.2f, D: %.2f, V: %.2f, H: %.2f, F: %.2f\n", ac_list[i].id, ac_list[i].S, ac_list[i].E, ac_list[i].I, ac_list[i].R, ac_list[i].D, ac_list[i].V, ac_list[i].H, ac_list[i].F);
        }
    }
}

void iniciar_simulacion() {
    printf("Simulación iniciada\n");
}

void detener_simulacion() {
    printf("Simulación detenida\n");
}
