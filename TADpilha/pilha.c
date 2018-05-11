#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "lista.h"

//
// PILHA.C
//

struct pilha
{
    Lista l;
};

Pilha criarPilha()
{
    Pilha p = (Pilha)malloc(sizeof(Pilha));
    p->l = criarLista();
    return p;
}

void empilhar(Pilha p, int x)
{
    p->l = inserirElemento(p->l, x);
}

void desempilhar(Pilha p)
{
    p->l = removerElemento(p->l);
}

void imprimirPilha(Pilha p)
{
    imprimirLista(p->l);
}

int pilhaVazia(Pilha p)
{
    return listaVazia(p->l);
}

Pilha destruirPilha(Pilha p)
{
    p->l = destruirLista(p->l);
    return NULL;
}
