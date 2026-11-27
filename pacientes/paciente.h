#ifndef PACIENTE_H
#define PACIENTE_H

#define TAM_NOME 80

typedef struct {
    char nome[TAM_NOME];
    char genero;
    int idade;
    int gestante;
    int lactante;
    int necessidadeEspecial;
    int obesidade;
    char senha[10];
    char categoria[20];
} Paciente;

void cadastrarDadosPaciente(Paciente *paciente);
int classificarPaciente(Paciente paciente);

#endif
