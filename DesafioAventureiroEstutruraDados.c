#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Estrutura Territorio:
    Guarda os dados essenciais de cada território do jogo.
    Campos:
        - nome  : nome do território (ex: "Alasca")
        - cor   : cor do exército que controla o território (ex: "Vermelho")
        - tropas: quantidade de tropas posicionadas nele
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


/* ---------------------------------------------------------
   Função: cadastrarTerritorios
   Objetivo: preencher os dados dos territórios usando ponteiros.
   Obs: o vetor de territórios foi alocado dinamicamente.
----------------------------------------------------------- */
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome do território: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


/* ---------------------------------------------------------
   Função: exibirTerritorios
   Objetivo: mostrar o estado atual do mapa (quem controla o que).
----------------------------------------------------------- */
void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n=== Estado Atual dos Territórios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome : %s\n", mapa[i].nome);
        printf("Cor  : %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}


/* ---------------------------------------------------------
   Função: atacar
   Objetivo: simular uma batalha entre dois territórios.
   Regras:
     - Cada lado rola 1 dado (1 a 6).
     - Quem tirar maior, vence a batalha.
     - Se atacante vencer → defensor muda de cor e perde metade das tropas.
     - Se defensor vencer → atacante perde 1 tropa (se não morrer).
----------------------------------------------------------- */
void atacar(Territorio* atacante, Territorio* defensor) {

    printf("\n=== BATALHA ===\n");

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("%s (Cor %s) rolou: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("%s (Cor %s) rolou: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");

        // Metade das tropas do defensor é perdida
        defensor->tropas /= 2;

        // O defensor muda de cor para a cor do atacante
        strcpy(defensor->cor, atacante->cor);

        // Pequeno reforço narrativo
        printf("O território %s foi conquistado!\n", defensor->nome);
    }
    else {
        printf("\nO defensor resistiu ao ataque!\n");

        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("O atacante perdeu 1 tropa.\n");
        } else {
            printf("O atacante não tem tropas suficientes para continuar.\n");
        }
    }
}


/* ---------------------------------------------------------
   Função: liberarMemoria
   Objetivo: liberar o vetor alocado dinamicamente.
----------------------------------------------------------- */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}


/* =========================================================
   FUNÇÃO PRINCIPAL
   Onde tudo começa :)
========================================================== */
int main() {
    srand(time(NULL)); // Garante dados aleatórios a cada execução

    int qtd;

    printf("Quantidade de territórios para cadastrar: ");
    scanf("%d", &qtd);

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int escolhaA, escolhaD;

    while (1) {
        exibirTerritorios(mapa, qtd);

        printf("\nEscolha o território atacante (0 para sair): ");
        scanf("%d", &escolhaA);
        if (escolhaA == 0) break;

        printf("Escolha o território defensor: ");
        scanf("%d", &escolhaD);

        // Ajusta índices
        escolhaA--;
        escolhaD--;

        // Validações:
        if (escolhaA < 0 || escolhaA >= qtd || escolhaD < 0 || escolhaD >= qtd) {
            printf("Índice inválido!\n");
            continue;
        }
        if (strcmp(mapa[escolhaA].cor, mapa[escolhaD].cor) == 0) {
            printf("Você não pode atacar um território da mesma cor!\n");
            continue;
        }

        atacar(&mapa[escolhaA], &mapa[escolhaD]);
    }

    liberarMemoria(mapa);

    printf("\nMemória liberada. Programa encerrado.\n");

    return 0;
}
