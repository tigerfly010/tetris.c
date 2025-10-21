#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5     // tamanho máximo da fila
#define MAX_PILHA 3    // tamanho máximo da pilha de reserva

// ------------------------------
// Struct que representa uma peça
// ------------------------------
typedef struct {
    char nome;  // tipo da peça: I, O, T, L
    int id;     // identificador único
} Peca;

// ------------------------------
// Estrutura da fila circular
// ------------------------------
typedef struct {
    Peca pecas[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// ------------------------------
// Estrutura da pilha de reserva
// ------------------------------
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;  // índice do topo da pilha
} Pilha;

// ------------------------------
// Inicializar a fila
// ------------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// ------------------------------
// Inicializar a pilha
// ------------------------------
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// ------------------------------
// Gerar uma peça aleatória
// ------------------------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// ------------------------------
// Inserir peça na fila (enqueue)
// ------------------------------
void enqueue(Fila *f, Peca p) {
    if (f->total == MAX_FILA) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

// ------------------------------
// Remover peça da fila (dequeue)
// ------------------------------
Peca dequeue(Fila *f) {
    Peca p = {'-', -1};
    if (f->total == 0) {
        printf("Fila vazia! Não há peças para jogar.\n");
        return p;
    }
    p = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return p;
}

// ------------------------------
// Empilhar peça na pilha (push)
// ------------------------------
void push(Pilha *p, Peca novaPeca) {
    if (p->topo == MAX_PILHA - 1) {
        printf("Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    p->pecas[++p->topo] = novaPeca;
}

// ------------------------------
// Remover do topo da pilha (pop)
// ------------------------------
Peca pop(Pilha *p) {
    Peca pecaRemovida = {'-', -1};
    if (p->topo == -1) {
        printf("Pilha vazia! Não há peças reservadas.\n");
        return pecaRemovida;
    }
    pecaRemovida = p->pecas[p->topo--];
    return pecaRemovida;
}

// ------------------------------
// Mostrar a fila
// ------------------------------
void mostrarFila(Fila *f) {
    printf("Fila de peças:\t");
    for (int i = 0; i < f->total; i++) {
        int idx = (f->inicio + i) % MAX_FILA;
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n");
}

// ------------------------------
// Mostrar a pilha
// ------------------------------
void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (p->topo == -1) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pecas[i].nome, p->pecas[i].id);
        }
    }
    printf("\n");
}

// ------------------------------
// Exibir o estado atual
// ------------------------------
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n===== ESTADO ATUAL =====\n");
    mostrarFila(f);
    mostrarPilha(p);
    printf("=========================\n");
}

// ------------------------------
// Programa principal
// ------------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int proximoID = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(proximoID++));
    }

    int opcao;
    do {
        mostrarEstado(&fila, &pilha);
        printf("\nOpções de Ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Reservar peça (mover para pilha)\n");
        printf("3 - Usar peça reservada (pop)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1)
                    printf("Jogou a peça [%c %d]\n", jogada.nome, jogada.id);
                // Sempre gerar nova peça e adicionar à fila
                enqueue(&fila, gerarPeca(proximoID++));
                break;
            }
            case 2: { // Reservar peça
                if (fila.total > 0 && pilha.topo < MAX_PILHA - 1) {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    printf("Reservou a peça [%c %d]\n", reservada.nome, reservada.id);
                    enqueue(&fila, gerarPeca(proximoID++));
                } else {
                    printf("Não foi possível reservar a peça.\n");
                }
                break;
            }
            case 3: { // Usar peça reservada
                Peca usada = pop(&pilha);
                if (usada.id != -1)
                    printf("Usou a peça reservada [%c %d]\n", usada.nome, usada.id);
                break;
            }
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}


