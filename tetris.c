#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // capacidade da fila circular
#define MAX_PILHA 3  // capacidade da pilha

// Struct que representa uma peça
typedef struct {
    char nome;  // tipo da peça ('I', 'O', 'T', 'L')
    int id;     // identificador único
} Peca;

// ---------------------- FILA CIRCULAR ----------------------

typedef struct {
    Peca pecas[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Insere peça no final da fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("⚠️  Fila cheia! Não é possível adicionar mais peças.\n");
        return;
    }
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

// Remove peça da frente da fila
Peca dequeue(Fila *f) {
    Peca p = {'-', -1};
    if (filaVazia(f)) {
        printf("⚠️  Fila vazia! Nenhuma peça disponível.\n");
        return p;
    }
    p = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return p;
}

// Mostra o conteúdo da fila
void mostrarFila(Fila *f) {
    printf("Fila de peças\t");
    for (int i = 0; i < f->total; i++) {
        int idx = (f->inicio + i) % MAX_FILA;
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n");
}

// ---------------------- PILHA ----------------------

typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

// Inicializa a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

// Verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Insere peça no topo da pilha
void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("⚠️  Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    p->pecas[++p->topo] = x;
}

// Remove peça do topo da pilha
Peca pop(Pilha *p) {
    Peca x = {'-', -1};
    if (pilhaVazia(p)) {
        printf("⚠️  Pilha vazia! Nenhuma peça para usar.\n");
        return x;
    }
    return p->pecas[p->topo--];
}

// Mostra o conteúdo da pilha
void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva\t(Topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->pecas[i].nome, p->pecas[i].id);
    }
    printf("\n");
}

// ---------------------- FUNÇÕES GERAIS ----------------------

// Gera peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Exibe o estado atual completo
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n================ ESTADO ATUAL ================\n");
    mostrarFila(f);
    mostrarPilha(p);
    printf("==============================================\n");
}

// Troca peça da frente da fila com o topo da pilha
void trocarTopo(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("⚠️  Não há peças suficientes para realizar a troca.\n");
        return;
    }

    int idxFrente = f->inicio;
    Peca temp = f->pecas[idxFrente];
    f->pecas[idxFrente] = p->pecas[p->topo];
    p->pecas[p->topo] = temp;

    printf("🔁 Troca entre a peça da frente da fila e o topo da pilha realizada!\n");
}

// Troca múltipla: 3 primeiros da fila ↔ 3 peças da pilha
void trocarMultiplas(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("⚠️  É necessário ter pelo menos 3 peças em cada estrutura para realizar a troca múltipla.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idx = (f->inicio + i) % MAX_FILA;
        Peca temp = f->pecas[idx];
        f->pecas[idx] = p->pecas[p->topo - i];
        p->pecas[p->topo - i] = temp;
    }

    printf("🔄 Troca múltipla entre as 3 primeiras peças da fila e as 3 da pilha realizada!\n");
}

// ---------------------- MAIN ----------------------

int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int proximoID = 0;

    // Inicializa fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(proximoID++));
    }

    int opcao;
    do {
        mostrarEstado(&fila, &pilha);

        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Reservar peça (enviar para a pilha)\n");
        printf("3 - Usar peça reservada (remover do topo)\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar as 3 primeiras da fila com as 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("🎮 Jogou a peça [%c %d]\n", jogada.nome, jogada.id);
                    enqueue(&fila, gerarPeca(proximoID++));
                }
                break;
            }

            case 2: { // Reservar peça
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        Peca reservada = dequeue(&fila);
                        push(&pilha, reservada);
                        printf("📦 Peça [%c %d] movida para a pilha de reserva.\n", reservada.nome, reservada.id);
                        enqueue(&fila, gerarPeca(proximoID++));
                    } else {
                        printf("⚠️  Pilha cheia! Libere espaço antes de reservar outra peça.\n");
                    }
                }
                break;
            }

            case 3: { // Usar peça da pilha
                Peca usada = pop(&pilha);
                if (usada.id != -1)
                    printf("🧱 Peça [%c %d] usada da pilha de reserva.\n", usada.nome, usada.id);
                break;
            }

            case 4: // Troca direta
                trocarTopo(&fila, &pilha);
                break;

            case 5: // Troca múltipla
                trocarMultiplas(&fila, &pilha);
                break;

            case 0:
                printf("👋 Encerrando o programa...\n");
                break;

            default:
                printf("⚠️  Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}



