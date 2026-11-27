#ifndef FILA_H
#define FILA_H

#include "paciente.h"

#define MAX_PACIENTES 1000

typedef struct {
    Paciente pacientes[MAX_PACIENTES];
    int inicio;
    int fim;
    int quantidade;
} Fila;

void inicializarFila(Fila *fila);
int filaVazia(Fila *fila);
int filaCheia(Fila *fila);
int inserirFila(Fila *fila, Paciente paciente);
int removerFila(Fila *fila, Paciente *paciente);
Paciente consultarInicioFila(Fila *fila);

#endif
