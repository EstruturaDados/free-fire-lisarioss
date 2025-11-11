#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor global que representa a mochila
Item mochila[MAX_ITENS];
int totalItens = 0; // Quantidade atual de itens na mochila

// --- Prototipagem das funções ---
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
int buscarIndicePorNome(char nome[]);

// Função principal (menu interativo)
int main() {
    int opcao;

    do {
        printf("\n===== MOCHILA DE LOOT - NIVEL INICIAL =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema... Boa sorte na sobrevivencia!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Função para inserir novo item ---
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remove o \n do final

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("Item adicionado com sucesso!\n");
    listarItens();
}

// --- Função para remover item ---
void removerItem() {
    char nome[30];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int indice = buscarIndicePorNome(nome);
    if (indice == -1) {
        printf("Item nao encontrado na mochila.\n");
        return;
    }

    // Desloca os itens seguintes uma posição para trás
    for (int i = indice; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    printf("Item removido com sucesso!\n");
    listarItens();
}

// --- Função para listar todos os itens ---
void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("-------------------------\n");
}

// --- Função para buscar item por nome ---
void buscarItem() {
    char nome[30];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int indice = buscarIndicePorNome(nome);
    if (indice == -1) {
        printf("Item nao encontrado.\n");
    } else {
        printf("Item encontrado!\n");
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
    }
}

// --- Função auxiliar: retorna o índice do item com determinado nome ---
int buscarIndicePorNome(char nome[]) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i; // Retorna o índice do item encontrado
        }
    }
    return -1; // Retorna -1 se não encontrar
}