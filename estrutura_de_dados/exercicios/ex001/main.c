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
    No *lista = NULL;

    No *no0 = malloc(sizeof(No));
    no0->num = 0;
    No *no1 = malloc(sizeof(No));
    no1->num = 2;
    No *no2 = malloc(sizeof(No));
    no2->num = 4;
    No *no3 = malloc(sizeof(No));
    no3->num = 6;
    No *no4 = malloc(sizeof(No));
    no4->num = 8;

    lista = no0;

    no0->prox = no1;
    no1->prox = no2;
    no2->prox = no3;
    no3->prox = no4;
    no4->prox = NULL;

    No *aux = lista;
    printf("Lista original:\n");
    while (aux != NULL)
    {
        printf("%d\n", aux->num);
        aux = aux->prox;
    }
    printf("\n");

    // Removendo o Ultimo da Lista
    no3->prox = NULL;
    free(no4);

    // Removendo o Primeiro da Lista
    lista = no0->prox;
    free(no0);

    // Removendo o no Meio da Lista
    no1->prox = no3;
    free(no2);

    aux = lista;
    printf("Lista Alterada:\n");
    while (aux != NULL)
    {
        printf("%d\n", aux->num);
        aux = aux->prox;
    }

    No *tmp = NULL;
    aux = lista;

    // Liberando Memória
    while (aux != NULL)
    {
        tmp = aux;
        aux = aux->prox;
        free(tmp);
    }

    return 0;
}