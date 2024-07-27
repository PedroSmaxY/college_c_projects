#include <stdio.h>
#include <stdlib.h>

struct no
{
    int num;
    struct no *prox;
};

typedef struct no No;

int main()
{
    int numero;
    No *lista = NULL;

    No *n0 = malloc(sizeof(No));
    n0->num = 0;
    No *n1 = malloc(sizeof(No));
    n1->num = 2;
    No *n2 = malloc(sizeof(No));
    n2->num = 4;
    No *n3 = malloc(sizeof(No));
    n3->num = 6;
    No *n4 = malloc(sizeof(No));
    n4->num = 8;

    lista = n0;

    n0->prox = n1;
    n1->prox = n2;
    n2->prox = n3;
    n3->prox = n4;
    n4->prox = NULL;

    No *aux = lista;
    printf("Lista:\n");
    while (aux != NULL)
    {
        printf("%d\n", aux->num);
        aux = aux->prox;
    }
    printf("\n");

    printf("Busque um numero: ");
    scanf("%d", &numero);
    getchar();

    aux = lista;
    while (aux != NULL && aux->num != numero)
    {
        aux = aux->prox;
    }
    if (aux != NULL)
    {
        printf("Numero encontrado!\n");
    }
    else
    {
        printf("Numero nao encontrado!\n");
    }

    system("PAUSE");
    return 0;
}