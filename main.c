#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"

static int lerOpcao(void) {
    char entrada[50];
    char *fim;
    long opcao;

    while (1) {
        printf("Escolha uma opcao: ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        opcao = strtol(entrada, &fim, 10);

        if (fim == entrada || (*fim != '\n' && *fim != '\0')) {
            printf("Digite uma opcao valida.\n");
            continue;
        }

        if (opcao < 0 || opcao > 5) {
            printf("Escolha uma opcao entre 0 e 5.\n");
            continue;
        }

        return (int)opcao;
    }
}

static void exibirMenu(void) {
    printf("\n========== SISTEMA DA CLINICA ==========\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Consultar proxima senha\n");
    printf("3 - Chamar proximo paciente\n");
    printf("4 - Finalizar atendimento\n");
    printf("5 - Exibir painel\n");
    printf("0 - Sair\n");
    printf("========================================\n");
}

int main(void) {
    Sistema sistema;
    int opcao;

    inicializarSistema(&sistema);

    do {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                cadastrarPaciente(&sistema);
                break;
            case 2:
                consultarProximaSenha(&sistema);
                break;
            case 3:
                chamarProximoPaciente(&sistema);
                break;
            case 4:
                finalizarAtendimento(&sistema);
                break;
            case 5:
                exibirPainel(&sistema);
                break;
            case 0:
                printf("\nSistema encerrado.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
