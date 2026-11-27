#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "paciente.h"

static int lerInteiro(const char *mensagem, int minimo, int maximo) {
    char entrada[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        valor = strtol(entrada, &fim, 10);

        if (fim == entrada || (*fim != '\n' && *fim != '\0')) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            continue;
        }

        if (valor < minimo || valor > maximo) {
            printf("Digite um valor entre %d e %d.\n", minimo, maximo);
            continue;
        }

        return (int)valor;
    }
}

static int lerSimNao(const char *mensagem) {
    printf("%s\n", mensagem);
    printf("1 - Sim\n");
    printf("0 - Nao\n");
    return lerInteiro("Opcao: ", 0, 1);
}

static void lerNome(char nome[]) {
    while (1) {
        printf("Nome do paciente: ");

        if (fgets(nome, TAM_NOME, stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        nome[strcspn(nome, "\n")] = '\0';

        if (strlen(nome) > 0) {
            return;
        }

        printf("O nome nao pode ficar vazio.\n");
    }
}

static char lerGenero(void) {
    char entrada[20];
    char genero;

    while (1) {
        printf("Genero (M - Masculino, F - Feminino, O - Outro/nao informado): ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        genero = (char)toupper((unsigned char)entrada[0]);

        if ((genero == 'M' || genero == 'F' || genero == 'O') &&
            (entrada[1] == '\n' || entrada[1] == '\0')) {
            return genero;
        }

        printf("Opcao invalida. Digite M, F ou O.\n");
    }
}

void cadastrarDadosPaciente(Paciente *paciente) {
    printf("\n========== CADASTRO DE PACIENTE ==========\n");

    lerNome(paciente->nome);
    paciente->genero = lerGenero();
    paciente->idade = lerInteiro("Idade: ", 0, 120);

    paciente->gestante = 0;
    if (paciente->genero == 'F') {
        paciente->gestante = lerSimNao("A paciente esta gestante?");
    }

    paciente->lactante = lerSimNao("O paciente e lactante?");
    paciente->necessidadeEspecial = lerSimNao("Possui necessidade especial?");
    paciente->obesidade = lerSimNao("Possui condicao de obesidade?");
}

int classificarPaciente(Paciente paciente) {
    /* 3 = urgente, 2 = preferencial, 1 = normal */

    if (paciente.idade > 80) {
        return 3;
    }

    if (paciente.gestante ||
        paciente.lactante ||
        paciente.necessidadeEspecial ||
        paciente.obesidade ||
        (paciente.genero == 'F' && paciente.idade >= 60) ||
        (paciente.genero == 'M' && paciente.idade >= 65)) {
        return 2;
    }

    return 1;
}
