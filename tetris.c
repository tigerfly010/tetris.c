#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // tamanho máximo da fila

// Struct que representa uma peça
typedef struct {
    char nome;  // tipo da peça: I, O, T, L
    int id;     // identificador único
} Peca;

// Struct da fila circular
typedef struct {
    Peca pecas[MAX];
    int inicio;
    int fim;
    int total; // total de elementos na fila
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Função para gerar peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Inserir peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (f->total == MAX) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Remover peça da frente da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca p = {'-', -1}; // peça "inválida" caso fila esteja vazia
    if (f->total == 0) {
        printf("Fila vazia! Não há peças para jogar.\n");
        return p;
    }
    p = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return p;
}

// Mostrar a fila de peças
void mostrarFila(Fila *f) {
    printf("\nFila de peças:\n");
    for (int i = 0; i < f->total; i++) {
        int idx = (f->inicio + i) % MAX;
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    int proximoID = 0;

    // Inicializar fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(proximoID++));
    }

    int opcao;
    do {
        mostrarFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1)
                    printf("Jogou a peça [%c %d]\n", jogada.nome, jogada.id);
                break;
            }
            case 2: {
                enqueue(&fila, gerarPeca(proximoID++));
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

