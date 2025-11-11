#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20

/**************************************************************
 *                     NIVEL NOVATO
 *         Inventário inicial com vetor de structs
 **************************************************************/

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("⚠️  Mochila cheia! Capacidade máxima atingida.\n");
        return;
    }
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", mochila[*total].nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", mochila[*total].tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    (*total)++;
    printf("✅ Item adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *total) {
    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("🗑️  Item removido com sucesso!\n");
            return;
        }
    }
    printf("❌ Item não encontrado.\n");
}

void listarItens(Item mochila[], int total) {
    printf("\n=== Itens da Mochila ===\n");
    for (int i = 0; i < total; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    if (total == 0)
        printf("Mochila vazia!\n");
}

void buscarItem(Item mochila[], int total) {
    char nome[30];
    int comparacoes = 0;
    printf("Digite o nome do item a buscar: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < total; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("🔎 Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparações: %d\n", comparacoes);
            return;
        }
    }
    printf("❌ Item não encontrado. Comparações: %d\n", comparacoes);
}

void nivelNovato() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n=== NIVEL NOVATO ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(mochila, &total); break;
            case 2: removerItem(mochila, &total); break;
            case 3: listarItens(mochila, total); break;
            case 4: buscarItem(mochila, total); break;
            case 0: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

/**************************************************************
 *                     NIVEL AVENTUREIRO
 *     Comparação entre vetor e lista encadeada
 **************************************************************/

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

No* inserirLista(No *inicio) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) return inicio;
    printf("Digite o nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Digite o tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = inicio;
    printf("✅ Item inserido na lista!\n");
    return novo;
}

No* removerLista(No *inicio) {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No *atual = inicio, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) inicio = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("🗑️  Item removido!\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado.\n");
    return inicio;
}

void listarLista(No *inicio) {
    No *p = inicio;
    printf("\n=== Itens da Lista ===\n");
    while (p != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               p->dados.nome, p->dados.tipo, p->dados.quantidade);
        p = p->proximo;
    }
}

void buscarLista(No *inicio) {
    char nome[30];
    int comparacoes = 0;
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);
    No *p = inicio;
    while (p != NULL) {
        comparacoes++;
        if (strcmp(p->dados.nome, nome) == 0) {
            printf("🔎 Encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   p->dados.nome, p->dados.tipo, p->dados.quantidade);
            printf("Comparações: %d\n", comparacoes);
            return;
        }
        p = p->proximo;
    }
    printf("❌ Item não encontrado. Comparações: %d\n", comparacoes);
}

void nivelAventureiro() {
    No *lista = NULL;
    Item vetor[MAX_ITENS];
    int total = 0, opcao, modo;

    printf("\n=== NIVEL AVENTUREIRO ===\n");
    printf("Escolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n");
    scanf("%d", &modo);

    do {
        printf("\n1 - Inserir item\n2 - Remover item\n3 - Listar\n4 - Buscar\n0 - Voltar\nEscolha: ");
        scanf("%d", &opcao);
        if (modo == 1) {
            switch (opcao) {
                case 1: inserirItem(vetor, &total); break;
                case 2: removerItem(vetor, &total); break;
                case 3: listarItens(vetor, total); break;
                case 4: buscarItem(vetor, total); break;
            }
        } else {
            switch (opcao) {
                case 1: lista = inserirLista(lista); break;
                case 2: lista = removerLista(lista); break;
                case 3: listarLista(lista); break;
                case 4: buscarLista(lista); break;
            }
        }
    } while (opcao != 0);
}

/**************************************************************
 *                     NIVEL MESTRE
 *         Ordenação e Busca Binária com Análise
 **************************************************************/

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

void bubbleSortNome(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
}

void insertionSortTipo(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, key.tipo) > 0) {
            (*comparacoes)++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

void selectionSortPrioridade(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        Componente temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

int buscaBinariaPorNome(Componente v[], int n, char nome[], int *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, v[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n=== Componentes ===\n");
    for (int i = 0; i < n; i++)
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
}

void nivelMestre() {
    Componente v[MAX_COMPONENTES];
    int total = 0, opcao, comparacoes = 0;
    char nomeBusca[30];
    clock_t inicio, fim;
    double tempo;

    do {
        printf("\n=== NIVEL MESTRE ===\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Ordenar por nome (Bubble Sort)\n");
        printf("3 - Ordenar por tipo (Insertion Sort)\n");
        printf("4 - Ordenar por prioridade (Selection Sort)\n");
        printf("5 - Buscar componente-chave (binária)\n");
        printf("6 - Listar componentes\n");
        printf("0 - Voltar\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (total >= MAX_COMPONENTES) {
                    printf("Limite máximo atingido!\n");
                    break;
                }
                printf("Nome: ");
                scanf(" %[^\n]", v[total].nome);
                printf("Tipo: ");
                scanf(" %[^\n]", v[total].tipo);
                printf("Prioridade (1-10): ");
                scanf("%d", &v[total].prioridade);
                total++;
                printf("✅ Componente adicionado!\n");
                break;

            case 2:
                inicio = clock();
                bubbleSortNome(v, total, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("Ordenado por nome (Bubble Sort)\nComparações: %d | Tempo: %.4fs\n", comparacoes, tempo);
                break;

            case 3:
                inicio = clock();
                insertionSortTipo(v, total, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("Ordenado por tipo (Insertion Sort)\nComparações: %d | Tempo: %.4fs\n", comparacoes, tempo);
                break;

            case 4:
                inicio = clock();
                selectionSortPrioridade(v, total, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("Ordenado por prioridade (Selection Sort)\nComparações: %d | Tempo: %.4fs\n", comparacoes, tempo);
                break;

            case 5:
                printf("Digite o nome do componente-chave: ");
                scanf(" %[^\n]", nomeBusca);
                int idx = buscaBinariaPorNome(v, total, nomeBusca, &comparacoes);
                if (idx != -1)
                    printf("🔑 Componente encontrado: %s | Tipo: %s | Prioridade: %d\nComparações: %d\n",
                           v[idx].nome, v[idx].tipo, v[idx].prioridade, comparacoes);
                else
                    printf("❌ Componente não encontrado. Comparações: %d\n", comparacoes);
                break;

            case 6:
                mostrarComponentes(v, total);
                break;
        }
    } while (opcao != 0);
}

/**************************************************************
 *                     MENU PRINCIPAL
 **************************************************************/

int main() {
    int opcao;
    do {
        printf("\n=== SISTEMA DE SOBREVIVÊNCIA ===\n");
        printf("1 - Nível Novato\n");
        printf("2 - Nível Aventureiro\n");
        printf("3 - Nível Mestre\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: nivelNovato(); break;
            case 2: nivelAventureiro(); break;
            case 3: nivelMestre(); break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}