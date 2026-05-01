#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

// Define a estrutura Territorio com nome, cor do exército e quantidade de tropas.
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Função para cadastrar os territórios a partir de um vetor alocado dinamicamente.
void inicializarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nTerritorio %d de %d:\n", i + 1, total);
        printf("Nome: ");
        scanf("%29s", mapa[i].nome);
        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);
        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir todos os territórios cadastrados de forma clara.
void exibirTerritorios(const Territorio* mapa, int total) {
    printf("\n--- Territorios Registrados ---\n");
    for (int i = 0; i < total; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do exercito: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios usando valores aleatórios.
void atacar(Territorio* atacante, Territorio* defensor) {
    int valorAtaque = rand() % 6 + 1;
    int valorDefesa = rand() % 6 + 1;

    printf("\nAtaque de '%s' (%s) contra '%s' (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Valor do atacante: %d\n", valorAtaque);
    printf("Valor do defensor: %d\n", valorDefesa);

    if (valorAtaque > valorDefesa) {
        printf("Resultado: atacante vence!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas == 0) {
            defensor->tropas = 1;
        }
        printf("O territorio '%s' agora pertence a %s com %d tropas.\n", defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("Resultado: defensor resiste!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) {
            atacante->tropas = 0;
        }
        printf("O atacante '%s' perde 1 tropa e fica com %d tropas.\n", atacante->nome, atacante->tropas);
    }
}

// Função de liberação de memória alocada dinamicamente para o mapa de territórios.
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// Função para escolher um território com validação de índice.
int escolherTerritorio(int total, const char* prompt) {
    int escolha = -1;
    while (escolha < 1 || escolha > total) {
        printf("%s (1 a %d): ", prompt, total);
        scanf("%d", &escolha);
        if (escolha < 1 || escolha > total) {
            printf("Escolha invalida. Tente novamente.\n");
        }
    }
    return escolha - 1;
}

int main(void) {
    srand((unsigned int)time(NULL));

    int totalTerritorios;
    printf("Bem-vindo ao WAR Estruturado!\n");
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);

    if (totalTerritorios <= 0) {
        printf("Numero de territorios invalido. Finalizando o programa.\n");
        return 1;
    }

    Territorio* mapa = calloc(totalTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    inicializarTerritorios(mapa, totalTerritorios);
    exibirTerritorios(mapa, totalTerritorios);

    int continuar = 1;
    while (continuar) {
        printf("--- Fase de Ataque ---\n");
        int indiceAtacante = escolherTerritorio(totalTerritorios, "Escolha o territorio atacante");
        int indiceDefensor = escolherTerritorio(totalTerritorios, "Escolha o territorio defensor");

        if (indiceAtacante == indiceDefensor) {
            printf("O atacante e o defensor devem ser territorios diferentes. Tente novamente.\n");
            continue;
        }

        if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
            printf("Nao e permitido atacar um territorio da mesma cor do exercito. Tente novamente.\n\n");
            continue;
        }

        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        exibirTerritorios(mapa, totalTerritorios);

        printf("Deseja realizar outro ataque? (1 = sim, 0 = nao): ");
        scanf("%d", &continuar);
    }

    liberarMemoria(mapa);
    printf("Memoria liberada. Programa finalizado.\n");
    return 0;
}
