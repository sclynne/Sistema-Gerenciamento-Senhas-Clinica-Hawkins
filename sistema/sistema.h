#ifndef SISTEMA_H
#define SISTEMA_H

#include "fila.h"

typedef struct {
    Fila normal;
    Fila preferencial;
    Fila urgente;
    Paciente pacienteAtual;
    int emAtendimento;
    int contadorNormal;
    int contadorPreferencial;
    int contadorUrgente;
} Sistema;

void inicializarSistema(Sistema *sistema);
void cadastrarPaciente(Sistema *sistema);
void consultarProximaSenha(Sistema *sistema);
void chamarProximoPaciente(Sistema *sistema);
void finalizarAtendimento(Sistema *sistema);
void exibirPainel(Sistema *sistema);

#endif
