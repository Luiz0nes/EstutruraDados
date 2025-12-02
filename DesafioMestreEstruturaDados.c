#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =============================================================
    Struct Território
    Cada território tem um nome, uma cor (quem o controla)
    e a quantidade de tropas.
============================================================= */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


/* =============================================================
    Função: atribuirMissao
    Objetivo:
        - Sorteia uma das missões pré-definidas
        - Copia a missão para o destino usando strcpy
        - A missão do jogador é armazenada dinamicamente

    Parâmetros:
        destino      → área de memória mallocada para missão
        missoes[]    → vetor de strings pré-definidas
        totalMissoes → quantidade de missões desse vetor
============================================================= */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes; // Escolhe uma missão aleatória
    strcpy(destino, missoes[sorteio]);
}


/* =============================================================
    Função: exibirMissao
    Objetivo:
        - Mostrar ao jogador qual é sua missão.
    Observação:
        - É chamada apenas uma vez no início.
============================================================= */
void exibirMissao(char* missao) {
    printf("\n=== SUA MISSAO ===\n");
    printf("%s\n", missao);
    printf("===================\n");
}


/* =============================================================
    Função: verificarMissao
    Objetivo:
        - Verifica se o jogador cumpriu sua missão.
    Observação:
        - Aqui, implementamos uma lógica simples.
        - Você pode expandir depois com missão por cor, etc.

    Exemplo de regra simples:
        - Se o jogador controlar 3 territórios, ganha.
============================================================= */
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Exemplo simples: "Conquistar 3 territorios"
    if (strstr(missao, "3 territorios") != NULL) {
        char corJogador[10];

        // A cor do jogador é a cor do primeiro território encontrado
        // (ficaria mais robusto se houvesse struct Jogador)
        strcpy(corJogador, mapa[0].cor);

        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                cont++;
        }
        if (cont >= 3) return 1;
    }

    // Outras missões podem ser adicionadas aqui

    return 0; // missão não cumprida ainda
}


/* =============================================================
    Função: atacar
    Objetivo:
        - Simula uma batalha usando dados (rand de 1 a 6)
        - Modifica territórios via ponteiros
============================================================= */
void atacar(Territorio* atacante, Territorio* defensor) {

    printf("\n\n=== BATALHA EM ANDAMENTO ===\n");

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("%s (%s) rolou %d\n", atacante->nome, atacante->cor, dadoA);
    printf("%s (%s) rolou %d\n", defensor->nome, defensor->cor, dadoD);

    if (dadoA > dadoD) {
        printf("O atacante venceu!\n");

        defensor->tropas /= 2;  // perde metade das tropas

        // defensor agora vira a cor do atacante (território conquistado)
        strcpy(defensor->cor, atacante->cor);

        printf("Território %s foi conquistado!\n", defensor->nome);
    }
    else {
        printf("O defensor resistiu!\n");

        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("Atacante perde 1 tropa.\n");
        }
    }
}


/* =============================================================
    Função: exibirMapa
    Objetivo:
        - Mostrar todos os territórios
============================================================= */
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor : %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}


/* =============================================================
    Função: liberarMemoria
    Objetivo:
        - Liberar todo espaço alocado dinamicamente no programa
============================================================= */
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}


/* =============================================================
    PROGRAMA PRINCIPAL
============================================================= */
int main() {

    srand(time(NULL)); // aleatoriedade realista

    int qtd;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));

    if (!mapa) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro de cada território
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    /* ---------------------------
        MISSÕES PRE-DEFINIDAS
    ---------------------------- */
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar a cor vermelha",
        "Dominar 2 territorios seguidos",
        "Acumular 20 tropas",
        "Vencer 3 batalhas"
    };
    int totalMissoes = 5;

    /* ---------------------------
        MISSÃO DO JOGADOR
    ---------------------------- */
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    exibirMissao(missaoJogador);

    int a, d;

    while (1) {
        printf("\n\n=== NOVO TURNO ===\n");
        exibirMapa(mapa, qtd);

        // Verificação silenciosa da missão
        if (verificarMissao(missaoJogador, mapa, qtd)) {
            printf("\n\n*** PARABENS! MISSAO CUMPRIDA! ***\n");
            printf("Voce venceu o jogo!\n");
            break;
        }

        printf("\nEscolha o território atacante (0 para sair): ");
        scanf("%d", &a);
        if (a == 0) break;

        printf("Escolha o território defensor: ");
        scanf("%d", &d);

        a--; d--;

        // Validação rápida
        if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
            printf("Você não pode atacar um território da mesma cor!\n");
            continue;
        }

        atacar(&mapa[a], &mapa[d]);
    }

    liberarMemoria(mapa, missaoJogador);

    printf("\nPrograma encerrado. Memoria liberada.\n");
    return 0;
}