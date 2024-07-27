#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct no
{
    int i;
    struct no *prox;
};

typedef struct no No;

int main()
{
    No *lista = NULL;

    No *no1 = malloc(sizeof(No));
    no1->i = 1;
    no1->prox = NULL;

    lista = no1;

    No *no2 = malloc(sizeof(No));
    no2->i = 2;
    no2->prox = NULL;
    no1->prox = no2;

    No *no3 = malloc(sizeof(No));
    no3->i = 3;
    no3->prox = NULL;
    no2->prox = no3;

    No *aux = NULL;
    aux = lista;

    system("CLS");

    while (aux != NULL)
    {
        printf("%d\n", aux->i);
        aux = aux->prox;
    }
    printf("\n");

    No *no0 = malloc(sizeof(No));
    no0->i = 0;
    no0->prox = no1;

    lista = no0;

    aux = lista;
    while (aux != NULL)
    {
        printf("%d\n", aux->i);
        aux = aux->prox;
    }
    printf("\n");

    No *novo = malloc(sizeof(No));
    novo->i = 15;
    novo->prox = no2;
    no1->prox = novo;

    aux = lista;
    while (aux != NULL)
    {
        printf("%d\n", aux->i);
        aux = aux->prox;
    }
    printf("\n");

    // Busca
    // int valor;
    // printf("Digite um valor para encontra-lo: ");
    // scanf("%d", &valor);

    // aux = lista;

    // while (aux != NULL && aux->i != valor)
    // {
    //     aux = aux->prox;
    // }

    // if (aux != NULL)
    // {
    //     printf("Valor Encontrado!\n");
    // }
    // else
    // {
    //     printf("Valor Nao Encontrado!\n");
    // }

    // Apagando Novo

    no1->prox = no2;
    free(novo);

    aux = lista;
    while (aux != NULL)
    {
        printf("%d\n", aux->i);
        aux = aux->prox;
    }

    // Apagando a memoria alocada

    aux = lista;
    No *temp = NULL;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    system("PAUSE");
    return 0;
}