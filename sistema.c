#include <stdio.h>
#include <string.h>
#include "sistema.h"
#include "paciente.h"
#include "fila.h"

static void gerarSenha(Sistema *sistema, Paciente *paciente, int categoria) {
    if (categoria == 3) {
        sistema->contadorUrgente++;
        sprintf(paciente->senha, "U%03d", sistema->contadorUrgente);
        strcpy(paciente->categoria, "Urgente");
    } else if (categoria == 2) {
        sistema->contadorPreferencial++;
        sprintf(paciente->senha, "P%03d", sistema->contadorPreferencial);
        strcpy(paciente->categoria, "Preferencial");
    } else {
        sistema->contadorNormal++;
        sprintf(paciente->senha, "N%03d", sistema->contadorNormal);
        strcpy(paciente->categoria, "Normal");
    }
}

static int obterProximoPaciente(Sistema *sistema, Paciente *paciente) {
    if (removerFila(&sistema->urgente, paciente)) {
        return 1;
    }

    if (removerFila(&sistema->preferencial, paciente)) {
        return 1;
    }

    if (removerFila(&sistema->normal, paciente)) {
        return 1;
    }

    return 0;
}

static void mostrarFila(Fila *fila, int *total, int limite) {
    int i;
    int posicao;

    for (i = 0; i < fila->quantidade && *total < limite; i++) {
        posicao = (fila->inicio + i) % MAX_PACIENTES;
        printf("%s - %s\n",
               fila->pacientes[posicao].senha,
               fila->pacientes[posicao].nome);
        (*total)++;
    }
}

void inicializarSistema(Sistema *sistema) {
    inicializarFila(&sistema->normal);
    inicializarFila(&sistema->preferencial);
    inicializarFila(&sistema->urgente);

    sistema->emAtendimento = 0;
    sistema->contadorNormal = 0;
    sistema->contadorPreferencial = 0;
    sistema->contadorUrgente = 0;
}

void cadastrarPaciente(Sistema *sistema) {
    Paciente paciente;
    int categoria;
    int sucesso;

    cadastrarDadosPaciente(&paciente);
    categoria = classificarPaciente(paciente);
    gerarSenha(sistema, &paciente, categoria);

    if (categoria == 3) {
        sucesso = inserirFila(&sistema->urgente, paciente);
    } else if (categoria == 2) {
        sucesso = inserirFila(&sistema->preferencial, paciente);
    } else {
        sucesso = inserirFila(&sistema->normal, paciente);
    }

    if (!sucesso) {
        printf("\nFila cheia. Nao foi possivel cadastrar o paciente.\n");
        return;
    }

    printf("\nPaciente cadastrado com sucesso!\n");
    printf("Nome: %s\n", paciente.nome);
    printf("Senha: %s\n", paciente.senha);
    printf("Categoria: %s\n", paciente.categoria);
}

void consultarProximaSenha(Sistema *sistema) {
    Paciente paciente;

    if (sistema->emAtendimento) {
        printf("\nFinalize o atendimento atual antes de consultar a proxima chamada.\n");
        return;
    }

    if (!filaVazia(&sistema->urgente)) {
        paciente = consultarInicioFila(&sistema->urgente);
    } else if (!filaVazia(&sistema->preferencial)) {
        paciente = consultarInicioFila(&sistema->preferencial);
    } else if (!filaVazia(&sistema->normal)) {
        paciente = consultarInicioFila(&sistema->normal);
    } else {
        printf("\nNao existem pacientes aguardando.\n");
        return;
    }

    printf("\nProxima senha: %s\n", paciente.senha);
    printf("Paciente: %s\n", paciente.nome);
    printf("Categoria: %s\n", paciente.categoria);
}

void chamarProximoPaciente(Sistema *sistema) {
    if (sistema->emAtendimento) {
        printf("\nJa existe um paciente em atendimento.\n");
        return;
    }

    if (obterProximoPaciente(sistema, &sistema->pacienteAtual)) {
        sistema->emAtendimento = 1;

        printf("\n========== CHAMADA DE PACIENTE ==========\n");
        printf("Senha: %s\n", sistema->pacienteAtual.senha);
        printf("Nome: %s\n", sistema->pacienteAtual.nome);
        printf("Categoria: %s\n", sistema->pacienteAtual.categoria);
    } else {
        printf("\nNao existem pacientes na fila.\n");
    }
}

void finalizarAtendimento(Sistema *sistema) {
    if (!sistema->emAtendimento) {
        printf("\nNao existe atendimento em andamento.\n");
        return;
    }

    printf("\nAtendimento da senha %s finalizado.\n",
           sistema->pacienteAtual.senha);

    sistema->emAtendimento = 0;
}

void exibirPainel(Sistema *sistema) {
    int total = 0;

    printf("\n=========================================\n");
    printf("             PAINEL DA CLINICA\n");
    printf("=========================================\n");

    if (sistema->emAtendimento) {
        printf("Senha chamada: %s\n", sistema->pacienteAtual.senha);
        printf("Paciente: %s\n", sistema->pacienteAtual.nome);
        printf("Categoria: %s\n", sistema->pacienteAtual.categoria);
    } else {
        printf("Senha atualmente chamada: Nenhuma\n");
    }

    printf("\n----------- PACIENTES EM ESPERA ---------\n");
    printf("Urgentes: %d\n", sistema->urgente.quantidade);
    printf("Preferenciais: %d\n", sistema->preferencial.quantidade);
    printf("Normais: %d\n", sistema->normal.quantidade);

    printf("\nProximas senhas aguardando:\n");
    mostrarFila(&sistema->urgente, &total, 5);
    mostrarFila(&sistema->preferencial, &total, 5);
    mostrarFila(&sistema->normal, &total, 5);

    if (total == 0) {
        printf("Nenhuma senha aguardando.\n");
    }

    printf("=========================================\n");
}
