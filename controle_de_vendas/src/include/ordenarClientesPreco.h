#ifndef ORDENARCLIENTESPRECO_H
#define ORDENARCLIENTESPRECO_H

#include "main.h"


void ordenarClientesPorPreco(Cliente *clientes, int n)
{
    int i, j;
    Cliente temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (clientes[j].valorTotal < clientes[j + 1].valorTotal)
            {
                temp = clientes[j];
                clientes[j] = clientes[j + 1];
                clientes[j + 1] = temp;
            }
        }
    }
}

#endif