#ifndef CODIGOEXISTENTE_H
#define CODIGOEXISTENTE_H

#include "main.h"

int codigoExiste(Cliente clientes[], int contadorArray, int codigo)
{
    int i;
    for (i = 0; i < contadorArray; i++)
    {
        if (clientes[i].codigo == codigo)
        {
            return 1;
        }
    }

    FILE *arquivoDat = fopen("loja_roupa.dat", "rb");
    if (arquivoDat != NULL)
    {
        Cliente cliente;
        while (fread(&cliente, sizeof(Cliente), 1, arquivoDat))
        {
            if (cliente.codigo == codigo)
            {
                fclose(arquivoDat);
                return 1;
            }
        }
        fclose(arquivoDat);
    }

    return 0;
}

#endif