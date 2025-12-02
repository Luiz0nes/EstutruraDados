#include <stdio.h>
#include <string.h>

/* Definição da estrutura Territorio conforme requisito*/

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {

    // Vetor que guardará exatamente 5 territórios, conforme requisito
    Territorio territorios[5];

    printf("=== Cadastro de Territórios ===\n\n");

    // Laço responsável por pedir ao usuário os dados dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);


        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Linha visual para separar os cadastros
    }

    // Exibição dos dados após todo o cadastro
    printf("\n=== Territorios cadastrados ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("------------------------------\n");
    }

   

    return 0;
}
