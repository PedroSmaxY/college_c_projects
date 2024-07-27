#include <stdio.h>
#include <stdlib.h>

typedef struct fila
{
    int valor;
    struct fila *prox;
} Fila;

void criarNo(Fila **fila, int valor)
{
    Fila *novo = malloc(sizeof(Fila));
    novo->valor = valor;
    novo->prox = NULL;

    if (*fila == NULL)
        *fila = novo;
    else
    {
        Fila *aux = *fila;
        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

void exibirValoresFila(Fila *fila)
{
    Fila *aux = fila;
    while (aux != NULL)
    {
        printf("%d\n", aux->valor);
        aux = aux->prox;
    }
}

void exibirInvertidoFila(Fila *fila)
{
    Fila *pilha = NULL;
    Fila *aux = fila;

    while (aux != NULL)
    {
        Fila *novo = malloc(sizeof(Fila));
        novo->valor = aux->valor;
        novo->prox = pilha;
        pilha = novo;
        aux = aux->prox;
    }

    while (pilha != NULL)
    {
        printf("%d\n", pilha->valor);
        aux = pilha;
        pilha = pilha->prox;
        free(aux);
    }
}

void definirNosPares(Fila **fila, int tamanho)
{
    int i;
    for (i = 0; i <= tamanho; i++)
    {
        if (i % 2 == 0)
            criarNo(fila, i);
    }
}

void limparFila(Fila *fila)
{
    Fila *temp = NULL;
    while (fila != NULL)
    {
        temp = fila;
        fila = fila->prox;
        free(temp);
    }
}

int main()
{
    Fila *fila = NULL;
    int tamanhoFila = 10;

    definirNosPares(&fila, tamanhoFila);
    exibirValoresFila(fila);
    exibirInvertidoFila(fila);
    limparFila(fila);

    return 0;
}