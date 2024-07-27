#include <stdio.h>
#include <stdlib.h>

struct no
{
    int num;
    struct no *prox;
};

typedef struct no No;

No *criaNo(int valor)
{
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro: memoria insuficiente.\n");
        exit(0);
    }
    novo->num = valor;
    novo->prox = NULL;
    return novo;
}

void insereApos(No **lista, int numero)
{
    No *aux = *lista;
    No *tmp = NULL;
    while (aux != NULL)
    {
        tmp = aux;
        aux = aux->prox;
    }

    No *novo = malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro: memoria insuficiente.\n");
        exit(0);
    }

    novo->num = numero;
    novo->prox = NULL;

    if (tmp != NULL)
    {
        tmp->prox = novo;
    }
    else
    {
        *lista = novo;
    }
}

void removeApos(No **lista)
{
    if (*lista == NULL)
    {
        printf("Erro: lista vazia.\n");
        return;
    }

    No *aux = *lista;
    No *tmp = aux;

    while (aux->prox != NULL)
    {
        tmp = aux;
        aux = aux->prox;
    }

    if (tmp != NULL)
    {
        tmp->prox = NULL;
    }
    else
    {
        *lista = NULL;
    }
    free(aux);
}

void mostrarLista(No *lista)
{
    if (lista == NULL)
    {
        printf("Lista Vazia\n");
        return;
    }
    printf("Conteudo da lista:\n");
    while (lista != NULL)
    {
        printf("%d\n", lista->num);
        lista = lista->prox;
    }
}

int main()
{
    No *lista = criaNo(1);
    insereApos(&lista, 2);
    insereApos(&lista, 3);
    mostrarLista(lista);

    removeApos(&lista);
    mostrarLista(lista);

    system("PAUSE");
    return 0;
}