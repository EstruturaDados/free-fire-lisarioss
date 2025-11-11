#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// ==============================
// === STRUCTS PRINCIPAIS ======
// ==============================

// Estrutura de dados básica (usada tanto no vetor quanto na lista)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==============================
// === VARIÁVEIS GLOBAIS =======
// ==============================
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

No* inicioLista = NULL; // ponteiro inicial da lista encadeada
int totalItensLista = 0;

// ==============================
// === FUNÇÕES - VETOR =========
// ==============================

void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void ordenarVetor();
int buscarSequencialVetor(char nome[]);
int buscarBinariaVetor(char nome[]);

// ==============================
// === FUNÇÕES - LISTA =========
// ==============================

void inserirItemLista();
void removerItemLista();
void listarItensLista();
No* buscarSequencialLista(char nome[]);

// ==============================
// === FUNÇÕES AUXILIARES ======
// ==============================
void menuVetor();
void menuLista();

// ==============================
// === FUNÇÃO PRINCIPAL ========
// ==============================
int main() {
    int opcao;
    do {
        printf("\n===== SISTEMA DE MOCHILA - NIVEL 2 =====\n");
        printf("1. Usar MOCHILA com VETOR\n");
        printf("2. Usar MOCHILA com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("Encerrando o sistema... Boa sorte no jogo!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ==============================
// === MENU VETOR ==============
// ==============================
void menuVetor() {
    int opcao;
    do {
        printf("\n--- MOCHILA (VETOR) ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar itens por nome\n");
        printf("5. Buscar item (Sequencial)\n");
        printf("6. Buscar item (Binaria - apos ordenacao)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        char nome[30];
        int pos;

        switch (opcao) {
            case 1:
                inserirItemVetor();
                break;
            case 2:
                removerItemVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4:
                ordenarVetor();
                break;
            case 5:
                printf("Digite o nome para busca sequencial: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                pos = buscarSequencialVetor(nome);
                if (pos != -1)
                    printf("Item encontrado: %s (%s), qtd: %d\n",
                           mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                else
                    printf("Item nao encontrado.\n");
                printf("Comparacoes feitas: %d\n", comparacoesSequencial);
                break;
            case 6:
                printf("Digite o nome para busca binaria: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                pos = buscarBinariaVetor(nome);
                if (pos != -1)
                    printf("Item encontrado: %s (%s), qtd: %d\n",
                           mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                else
                    printf("Item nao encontrado.\n");
                printf("Comparacoes feitas: %d\n", comparacoesBinaria);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// ==============================
// === MENU LISTA ==============
// ==============================
void menuLista() {
    int opcao;
    do {
        printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (Sequencial)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        char nome[30];
        No* encontrado;

        switch (opcao) {
            case 1:
                inserirItemLista();
                break;
            case 2:
                removerItemLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4:
                printf("Digite o nome para busca: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                encontrado = buscarSequencialLista(nome);
                if (encontrado)
                    printf("Item encontrado: %s (%s), qtd: %d\n",
                           encontrado->dados.nome, encontrado->dados.tipo, encontrado->dados.quantidade);
                else
                    printf("Item nao encontrado.\n");
                printf("Comparacoes feitas: %d\n", comparacoesSequencial);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// ==============================
// === IMPLEMENTAÇÃO - VETOR ===
// ==============================

void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochilaVetor[totalItensVetor++] = novo;
    printf("Item inserido com sucesso!\n");
}

void removerItemVetor() {
    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscarSequencialVetor(nome);
    if (pos == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (int i = pos; i < totalItensVetor - 1; i++)
        mochilaVetor[i] = mochilaVetor[i + 1];
    totalItensVetor--;
    printf("Item removido.\n");
}

void listarItensVetor() {
    if (totalItensVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("--- Itens na mochila ---\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d. %s (%s) - %d\n", i + 1,
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void ordenarVetor() {
    Item temp;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome!\n");
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int buscarBinariaVetor(char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = totalItensVetor - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

// ==============================
// === IMPLEMENTAÇÃO - LISTA ===
// ==============================

void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    printf("Nome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicioLista;
    inicioLista = novo;
    totalItensLista++;

    printf("Item inserido com sucesso!\n");
}

void removerItemLista() {
    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado.\n");
        return;
    }

    if (anterior == NULL)
        inicioLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    totalItensLista--;
    printf("Item removido!\n");
}

void listarItensLista() {
    if (inicioLista == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    No* atual = inicioLista;
    int i = 1;
    printf("--- Itens na mochila ---\n");
    while (atual != NULL) {
        printf("%d. %s (%s) - %d\n", i++,
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char nome[]) {
    comparacoesSequencial = 0;
    No* atual = inicioLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}