#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct arvoregeral
{
    int info;
    struct arvoregeral *filho;
    struct arvoregeral *irmao;
}Arvoregeral;

void menu();

Arvoregeral *LerArvore(Arvoregeral *a,FILE *arq) // Op��o 1
{
    int num;
    char ch;

    fscanf(arq,"%c",&ch);
    fscanf(arq,"%d",&num);

    if(num==-1)
        a=NULL;
    else
    {
        a=(Arvoregeral*)malloc(sizeof(Arvoregeral));
        a->info=num;
        a->filho=LerArvore(a->filho,arq);
        a->irmao=LerArvore(a->irmao,arq);
    }
    fscanf(arq,"%c",&ch);
    return a;
}

void ImprimirNotacao(Arvoregeral *a)
{
     if(a==NULL)
            printf("(-1)");
        else
        {
            printf("(");
            printf("%d",a->info);
            ImprimirNotacao(a->filho);
            ImprimirNotacao(a->irmao);
            printf(")");
        }
}

void ImprimirLargura(Arvoregeral *a, int nivel, int cont)
{
    if(a!=NULL)
    {
        if(cont==nivel)
        {
            printf("%d ",a->info);
            ImprimirLargura(a->irmao,nivel,cont);
        }
        else
        {
            ImprimirLargura(a,nivel,cont+1);
        }
    ImprimirLargura(a->filho,nivel+1,cont);
    }
}

void ImprimirArvore(Arvoregeral* a,int op) // Op��o 2
{
    if(op==2)
        ImprimirNotacao(a);
    else if(op==1)
        ImprimirLargura(a,1,1);
    else
        printf("Opcao invalida!");
}

int CalcularAltura(Arvoregeral *a) // Opcao 3
{
    if(a==NULL)
        return 0;
    else
    {
        int hf=CalcularAltura(a->filho)+1;
        int hi=CalcularAltura(a->irmao);
        if(hf>hi)
            return hf;
        else
            return hi;
    }
}

int ContarFolhas(Arvoregeral *a) // Opcao 4
{
    if(a==NULL)
        return 0;
    else
        if(a->filho==NULL)
            return 1 + ContarFolhas(a->filho) + ContarFolhas(a->irmao);
        else
            return ContarFolhas(a->filho) + ContarFolhas(a->irmao);
}

void ImprimirInternos(Arvoregeral *a)
{
    if(a!=NULL)
    {
        if(a->filho!=NULL)
            printf("%d ",a->info);
        ImprimirInternos(a->filho);
        ImprimirInternos(a->irmao);
    }
}

int ImprimirNivelNo(Arvoregeral *a,int x,int cont)
{
    if(a==NULL)
        return 0;
    else
    {
        if(x==a->info)
            return cont;
        else if(ImprimirNivelNo(a->irmao,x,cont)!=0)
            return ImprimirNivelNo(a->irmao,x,cont);
        else if(ImprimirNivelNo(a->filho,x,cont+1)!=0)
            return ImprimirNivelNo(a->filho,x,cont+1);
        else
            return 0;
    }
}

int ExisteElemento(Arvoregeral* a,int x)
{
    if(a==NULL)
    {
        return 0;
    }
    else if(a->info==x)
    {
        return 1;
    }

    return ExisteElemento(a->irmao,x) || ExisteElemento(a->filho,x);
}

Arvoregeral* AchouY(Arvoregeral* a,int x, int y)
{
    if(a==NULL)
    {
        a=(Arvoregeral*)malloc(sizeof(Arvoregeral));
        a->info=x;
        a->filho=NULL;
        a->irmao=NULL;
    }
    else
    {
        a->irmao=AchouY(a->irmao,x,y);
    }
    return a;
}

Arvoregeral* InserirXdeY(Arvoregeral* a,int x,int y) // Op��o 2
{
    if(a!=NULL)
    {
        if(a->info==y)
        {
            a->filho=AchouY(a->filho,x,y);
        }
        else
        {
            a->irmao=InserirXdeY(a->irmao,x,y);
            a->filho=InserirXdeY(a->filho,x,y);
        }
    }
    return a;
}

Arvoregeral* DestruirArvore(Arvoregeral* a)
{
    if(a!=NULL)
    {
        a->filho=DestruirArvore(a->filho);
        a->irmao=DestruirArvore(a->irmao);
        free(a);
    }
    return NULL;
}

int main()
{
    setlocale(LC_ALL,"Portuguese");

    Arvoregeral *a=NULL;
    int op,x,y;
    char arquivo[20];
    FILE *arq;
    do
    {
    printf("Selecione uma op��o");
    printf("\n\n1 - Ler uma �rvore a partir de um arquivo");
    printf("\n2 - Imprimir �rvore.");
    printf("\n3 - Calcular altura da �rvore.");
    printf("\n4 - Contar n�mero de folhas.");
    printf("\n5 - Contar n�mero de n�s internos.");
    printf("\n6 - Imprimir n�vel do n�.");
    printf("\n7 - Inserir o n� x como filho do n� y.");
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
            if(a!=NULL)
                printf("\n�rvore lida com sucesso.");
            else
                printf("\n�rvore n�o pode ser lida.");
            break;
      case 2:
            printf("\nDigite a forma de impressao: ");
            printf("\n1 - Em largura.");
            printf("\n2 - Notacao textual.");
            scanf("%d",&op);
            fflush(stdin);
            ImprimirArvore(a,op);
            break;
      case 3:
            printf("\nA arvore tem altura %d.\n",CalcularAltura(a));
            break;
      case 4:
            printf("\nA arvore tem %d folhas.\n",ContarFolhas(a));
            break;
      case 5:
            printf("\nN�s internos: ");
            ImprimirInternos(a);
            break;
      case 6:
            printf("Insira o n� que se deseja saber o n�vel: ");
            scanf("%d",&x);
            fflush(stdin);
            printf("O n� %d est� no nivel %d",x,ImprimirNivelNo(a,x,1));
            break;
      case 7:
            printf("Digite o n� x e depois o n� y: ");
            scanf("%d %d",&x,&y);
            fflush(stdin);
            if(!ExisteElemento(a,y))
                printf("\nElemento n existe.");
            else
            {
                a=InserirXdeY(a,x,y);
                printf("\nElemento inserido com sucesso.");
            }
            break;
      case 8:
            a=DestruirArvore(a);
            exit(1);
            break;
      default:
            printf("\nOpcao invalida.");
            break;
        }
        getchar();
        system("cls");
    }
    while(1);
    return 0;
}
