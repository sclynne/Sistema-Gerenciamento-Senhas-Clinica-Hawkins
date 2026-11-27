#include "fila.h"

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

int filaCheia(Fila *fila) {
    return fila->quantidade == MAX_PACIENTES;
}

int inserirFila(Fila *fila, Paciente paciente) {
    if (filaCheia(fila)) {
        return 0;
    }

    fila->pacientes[fila->fim] = paciente;
    fila->fim = (fila->fim + 1) % MAX_PACIENTES;
    fila->quantidade++;

    return 1;
}

int removerFila(Fila *fila, Paciente *paciente) {
    if (filaVazia(fila)) {
        return 0;
    }

    *paciente = fila->pacientes[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_PACIENTES;
    fila->quantidade--;

    return 1;
}

Paciente consultarInicioFila(Fila *fila) {
    return fila->pacientes[fila->inicio];
}
