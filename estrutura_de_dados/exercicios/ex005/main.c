#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int valor;
    struct no *prox;
} No;

typedef struct
{
    No *ini;
    No *fim;
} Fila;

Fila *criarFila()
{
    Fila *fila = malloc(sizeof(Fila));
    fila->ini = fila->fim = NULL;
    return fila;
}

void filaInsere(Fila *fila, int valor)
{
    No *no = malloc(sizeof(No));
    no->valor = valor;
    no->prox = NULL;

    if (fila->fim)
        fila->fim->prox = no;
    else
        fila->ini = no;
    fila->fim = no;
}

float filaRetira(Fila *fila)
{
    No *no = NULL;
    int valor;

    if (fila->ini == NULL)
    {
        printf("\nFila Vazia.\n");
        exit(1);
    }
    no = fila->ini;
    valor = no->valor;
    fila->ini = no->prox;

    if (fila->ini == NULL)
        fila->fim = NULL;
    free(no);
    return valor;
}

int main()
{
    Fila *fila = criarFila();
    return 0;
}