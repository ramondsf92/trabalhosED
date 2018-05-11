#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

//
// ALUNO: RAMON DOS SANTOS FERREIRA
//

//
// MAIN.C
//

int main() {
    Pilha p;
    int op, num;
    p = criarPilha();

    do
    {
        printf("Pilha atualizada: \n");
        if(pilhaVazia(p))
            printf("LISTA VAZIA!\n");
        else
        {
            imprimirPilha(p);
            printf("\n");
        }
        printf("\n");
        printf("Digite a opcao desejada: ");
        printf("\n1 - Inserir elemento na pilha. ");
        printf("\n2 - Remover elemento do topo da pilha. ");
        printf("\n3 - Destruir a pilha e sair. ");
        printf("\nOpcao desejada: ");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
                printf("Digite o elemento para inserir na pilha: ");
                scanf("%d", &num);
                empilhar(p, num);
                break;
            case 2:
                if(pilhaVazia(p))
                    printf("A pilha ja esta vazia. Ta doidao?");
                else
                    desempilhar(p);
                break;
            case 3:
                p = destruirPilha(p);
                exit(1);
            default:
                printf("Opcao invalida!");
                break;
        }
        fflush(stdin);
        getchar();
        system("CLS");
    }
    while(1);
    return 0;
}
