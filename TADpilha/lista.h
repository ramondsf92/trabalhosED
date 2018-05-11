//
// LISTA.H
//

typedef struct lista *Lista;

Lista criarLista();

Lista inserirElemento(Lista l,int x);

Lista removerElemento(Lista l);

void imprimirLista(Lista l);

int listaVazia(Lista l);

Lista destruirLista(Lista l);
