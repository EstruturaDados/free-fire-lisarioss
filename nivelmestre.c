#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ====================================
// === STRUCT PRINCIPAL DO JOGO =======
// ====================================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ====================================
// === VARIÁVEIS GLOBAIS ==============
// ====================================
int comparacoes = 0;  // contador de comparações
Componente torre[MAX_COMPONENTES];
int total = 0;

// ====================================
// === PROTÓTIPOS DE FUNÇÕES =========
// ====================================
void cadastrarComponentes();
void mostrarComponentes(Componente v[], int n);
void bubbleSortNome(Componente v[], int n);
void insertionSortTipo(Componente v[], int n);
void selectionSortPrioridade(Componente v[], int n);
int buscaBinariaPorNome(Componente v[], int n, char nome[]);
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n);

// ====================================
// === FUNÇÃO PRINCIPAL ===============
// ====================================
int main() {
    int opcao;
    char nomeBusca[30];
    int indice;

    do {
        printf("\n===== TORRE DE FUGA - NIVEL FINAL =====\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar componente-chave (Busca Binaria)\n");
        printf("0. Encerrar missão\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarComponentes();
                break;
            case 2:
                mostrarComponentes(torre, total);
                break;
            case 3:
                medirTempo(bubbleSortNome, torre, total);
                mostrarComponentes(torre, total);
                break;
            case 4:
                medirTempo(insertionSortTipo, torre, total);
                mostrarComponentes(torre, total);
                break;
            case 5:
                medirTempo(selectionSortPrioridade, torre, total);
                mostrarComponentes(torre, total);
                break;
            case 6:
                if (total == 0) {
                    printf("Nenhum componente cadastrado!\n");
                    break;
                }
                printf("Digite o nome do componente-chave: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                indice = buscaBinariaPorNome(torre, total, nomeBusca);
                if (indice != -1)
                    printf("✅ Componente encontrado: %s (%s), prioridade %d\n",
                           torre[indice].nome, torre[indice].tipo, torre[indice].prioridade);
                else
                    printf("❌ Componente nao encontrado!\n");
                printf("Comparacoes realizadas: %d\n", comparacoes);
                break;
            case 0:
                printf("Encerrando o modulo de resgate... Boa sorte, sobrevivente!\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ====================================
// === CADASTRO =======================
// ====================================
void cadastrarComponentes() {
    if (total >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido!\n");
        return;
    }

    Componente novo;
    printf("Nome do componente: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do componente (ex: controle, suporte, propulsao): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Prioridade (1 a 10): ");
    scanf("%d", &novo.prioridade);
    getchar();

    torre[total++] = novo;
    printf("Componente adicionado!\n");
}

// ====================================
// === EXIBIÇÃO =======================
// ====================================
void mostrarComponentes(Componente v[], int n) {
    if (n == 0) {
        printf("Nenhum componente registrado.\n");
        return;
    }
    printf("\n--- COMPONENTES ATUAIS ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ====================================
// === ORDENAÇÕES =====================
// ====================================

// Bubble Sort por NOME
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    printf("Ordenado por NOME (Bubble Sort).\n");
}

// Insertion Sort por TIPO
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
    printf("Ordenado por TIPO (Insertion Sort).\n");
}

// Selection Sort por PRIORIDADE
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
    printf("Ordenado por PRIORIDADE (Selection Sort).\n");
}

// ====================================
// === BUSCA BINÁRIA ==================
// ====================================
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    comparacoes = 0;
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(nome, v[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

// ====================================
// === MEDIÇÃO DE TEMPO ===============
// ====================================
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio, fim;
    inicio = clock();
    algoritmo(v, n);
    fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
}