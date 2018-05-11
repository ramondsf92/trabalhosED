//
// PILHA.H
//

typedef struct pilha *Pilha;

Pilha criarPilha();

void empilhar(Pilha p, int x);

void imprimirPilha(Pilha p);

void desempilhar(Pilha p);

int pilhaVazia(Pilha p);

Pilha destruirPilha(Pilha p);
