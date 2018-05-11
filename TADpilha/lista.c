#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//
// LISTA.C
//

struct lista
{
    int info;
    struct lista* prox;
};

Lista criarLista()
{
    Lista l;
    l = NULL;
    return l;
}

Lista inserirElemento(Lista l, int x)
{
    if(l == NULL)
    {
        l = (Lista)malloc(sizeof(Lista));
        l->info = x;
        l->prox = NULL;
    }
    else
        l->prox = inserirElemento(l->prox, x);
    return l;
}

Lista removerElemento(Lista l)
{
    if(l->prox == NULL)
        l = NULL;
    else
        l->prox = removerElemento(l->prox);
    return l;
}

void imprimirLista(Lista l)
{
    if(l != NULL)
    {
        printf("%d ", l->info);
        imprimirLista(l->prox);
    }
}

int listaVazia(Lista l)
{
    return l == NULL;
}

Lista destruirLista(Lista l)
{
    if(l != NULL)
    {
        l->prox = destruirLista(l->prox);
        free(l);
    }
    return NULL;
}
