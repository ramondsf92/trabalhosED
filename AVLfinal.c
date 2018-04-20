#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*=============================================================================================
Universidade Federal Fluminense
Curso de Ciencia da Computacao
Estrutura de dados - Arvore Binaria de Busca
Professor: Dalessandro
Alunos: Claudio Rodrigues Nunes
        Ramon dos Santos Ferreira
13/04/2018
=============================================================================================*/

typedef struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}Arvore;

int CalcularAltura(Arvore *a);
Arvore *RemoverElemento(Arvore *a,int x);
Arvore *InserirElemento(Arvore *a,int x);

Arvore* LerArvore(Arvore *a,FILE *arq) // Opção 1
{
    int num;
    char ch;

    fscanf(arq,"%c",&ch);
    fscanf(arq,"%d",&num);

    if(num==-1)
        a=NULL;
    else
    {
        a=(Arvore*)malloc(sizeof(Arvore));
        a->info=num;
        a->esq=LerArvore(a->esq,arq);
        a->dir=LerArvore(a->dir,arq);
    }
    fscanf(arq,"%c",&ch);
    return a;
}

int VerificarOrdenada(Arvore *a,int min,int max) // Complemento da opção 1
{
    if(a==NULL)
        return 1;
    else if((a->info < min) || (a->info > max))
    {
        printf("Entrou segundo if");
        return 0;
    }
    return VerificarOrdenada(a->esq,min,a->info) && VerificarOrdenada(a->dir,a->info,max);
}

int VerificarBalanceada(Arvore *a)
{
    if(a==NULL)
        return 1;
    else
    {
        int he=CalcularAltura(a->esq);
        int hd=CalcularAltura(a->dir);
        if((he-hd>1) || (hd-he>1))
            return 0;
        else
            return VerificarBalanceada(a->esq) && VerificarBalanceada(a->dir);
    }
}

Arvore* BalancearArvore(Arvore *a)
{
    if(a!=NULL)
    {
        int he,hd;

        a->esq=BalancearArvore(a->esq);
        a->dir=BalancearArvore(a->dir);

        he=CalcularAltura(a->esq);
        hd=CalcularAltura(a->dir);

        if(hd-he>1)
        {
            int x;
            Arvore *aux=a->dir;
            while(aux->esq!=NULL)
                aux=aux->esq;
            x=a->info;
            a->info=aux->info;
            a->dir=RemoverElemento(a->dir,aux->info);
            a->esq=InserirElemento(a->esq,x);
            a=BalancearArvore(a);
        }
        else if(he-hd>1)
        {
            int x;
            Arvore *aux=a->esq;
            while(aux->dir!=NULL)
                aux=aux->dir;
            x=a->info;
            a->info=aux->info;
            a->esq=RemoverElemento(a->esq,aux->info);
            a->dir=InserirElemento(a->dir,x);
            a=BalancearArvore(a);
        }
    }
    return a;
}

Arvore* InserirElemento(Arvore *a,int x) // Opção 2
{
    if(a==NULL)
    {
        a=(Arvore*)malloc(sizeof(Arvore));
        a->info=x;
        a->esq=NULL;
        a->dir=NULL;
    }
    else if(a->info > x)
        a->esq=InserirElemento(a->esq,x);
    else
        a->dir=InserirElemento(a->dir,x);

    return a;
}

Arvore* RemoverElemento(Arvore *a,int x) // Opção 3
{
    if(a!=NULL){
        if(a->info==x){
            if(a->esq==NULL && a->dir==NULL){
                free(a);
                return NULL;
            }
            else if(a->esq==NULL || a->dir==NULL){
                Arvore *aux;
                if(a->esq==NULL)
                    aux=a->dir;
                else
                    aux=a->esq;
                free(a);
                return aux;
            }
            else{
                Arvore *m=a->esq;
                while(m->dir!=NULL)
                {
                    m=m->dir;
                }
                a->info=m->info;
                a->esq=RemoverElemento(a->esq,m->info);
                return a;
            }
        }
        else if(x<a->info)
            a->esq=RemoverElemento(a->esq,x);
        else a->dir=RemoverElemento(a->dir,x);
    }
    return a;
}

void ImprimirArvore(Arvore* a,int op) // Opção 4
{
    if(op==1)
    {
        if(a!=NULL)
        {
            ImprimirArvore(a->esq,op);
            printf("%d ",a->info);
            ImprimirArvore(a->dir,op);
        }
    }
    else if(op==2)
    {
        if(a==NULL)
            printf("(-1)");
        else
        {
            printf("(");
            printf("%d",a->info);
            ImprimirArvore(a->esq,op);
            ImprimirArvore(a->dir,op);
            printf(")");
        }
    }
    else
        printf("Opcao invalida!");
}

int CalcularAltura(Arvore *a) // Opção 5
{
    if(a==NULL)
        return 0;
    else
    {
        int he=CalcularAltura(a->esq);
        int hd=CalcularAltura(a->dir);
        if(he<hd)
            return hd+1;
        else
            return he+1;
    }
}

void ImprimirEntreXY(Arvore *a,int x,int y) // Opção 6
{
    if(a!=NULL)
    {
        if(a->info > x)
            ImprimirEntreXY(a->esq,x,y);
        if(a->info >= x && a->info <= y)
            printf("%d ",a->info);
        if(a->info < y)
            ImprimirEntreXY(a->dir,x,y);
    }

}

void ImprimirMaouMe(Arvore *a,int x,int y)
{
    if(a!=NULL)
    {
        ImprimirMaouMe(a->esq,x,y);
        if(a->info < x || a->info > y)
            printf("%d ",a->info);
        ImprimirMaouMe(a->dir,x,y);
    }
}

Arvore* DestruirArvore(Arvore* a) // Opção 8
{
    if(a!=NULL)
    {
        a->esq=DestruirArvore(a->esq);
        a->dir=DestruirArvore(a->dir);
        free(a);
    }
    return NULL;
}

int main()
{
    Arvore *a;
    int num,x,y,op,op2;
    char arquivo[20],opbal;
    FILE *arq;

    do{
        printf("Selecione uma opcao");
        printf("\n\n1 - Ler uma arvore a partir de um arquivo e verificar se ela e ordenada e balanceada");
        printf("\n2 - Inserir um elemento na arvore.");
        printf("\n3 - Remover um elemento na arvore.");
        printf("\n4 - Imprimir arvore.");
        printf("\n5 - Altura da arvore.");
        printf("\n6 - Imprimir elementos entre x e y.");
        printf("\n7 - Imprimir elementos menores que x ou maiores que y.");
        printf("\n8 - Sair destruindo a arvore.");
        printf("\n\n Informe a opcao escolhida: ");

        scanf("%d",&op);
        fflush(stdin);

    switch(op)
{
      case 1:
            printf("\nDigite o nome do arquivo que devera ser lido: ");
            gets(arquivo);
            fflush(stdin);
            arq=fopen(arquivo,"r");
            a=LerArvore(a,arq);
            printf("\nA arvore esta ordenada? ");
            if(VerificarOrdenada(a,-894351,894561))
                printf("Sim.");
            else
                printf("Nao.");
            printf("\nA Arvore esta balanceada? ");
            if(VerificarBalanceada(a))
                printf("Sim.");
            else
            {
                printf("Nao.");
                printf("\nDeseja balancear a arvore? S/N ");
                scanf("%c",&opbal);
                fflush(stdin);
                if(opbal=='S' || opbal=='s')
                {
                    a=BalancearArvore(a);
                    printf("Arvore balanceada com sucesso.");
                }
            }
            break;
      case 2:
            printf("Digite o numero a ser inserido na arvore: ");
            scanf("%d",&num);
            fflush(stdin);
            a=InserirElemento(a,num);
            if(!VerificarBalanceada(a))
            {
                printf("A arvore esta desbalaceada. Deseja balancea-la? S/N ");
                scanf("%c",&opbal);
                fflush(stdin);
                if(opbal=='S' || opbal=='s')
                {
                    a=BalancearArvore(a);
                    printf("Arvore balanceada com sucesso.");
                }
            }
            break;
      case 3:
            printf("\nDigite um valor para remover da arvore: ");
            scanf("%d",&num);
            fflush(stdin);
            a=RemoverElemento(a,num);
            if(!VerificarBalanceada(a))
            {
                printf("A arvore esta desbalaceada. Deseja balancea-la? S/N ");
                scanf("%c",&opbal);
                fflush(stdin);
                if(opbal=='S' || opbal=='s')
                {
                    a=BalancearArvore(a);
                    printf("Arvore balanceada com sucesso.\n ");
                }
            }
            break;
      case 4:
            printf("\nDigite a forma de impressao: ");
            printf("\n1 - Em Ordem.");
            printf("\n2 - Notacao textual.");
            scanf("%d",&op2);
            fflush(stdin);
            ImprimirArvore(a,op2);
            break;
      case 5:
            printf("\nA arvore tem altura %d.\n",CalcularAltura(a));
            break;
      case 6:
            printf("Insira os dois numeros do intervalo: ");
            scanf("%d %d",&x,&y);
            fflush(stdin);
            ImprimirEntreXY(a,x,y);
            break;
      case 7:
            printf("Digite os dois numeros: ");
            scanf("%d %d",&x,&y);
            fflush(stdin);
            ImprimirMaouMe(a,x,y);
            break;
      case 8:
          a=DestruirArvore(a);
          exit(1);
          break;
      default:
            printf("\nOpcao invalida.");
            system("PAUSE");
            break;
        }
        getchar();
        system("cls");
    } while (1);

    return 0;
}
