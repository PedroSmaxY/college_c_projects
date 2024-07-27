#ifndef ATUALIZARRESUMO_H
#define ATUALIZARRESUMO_H

#include "main.h"

void atualizarResumo(int *contador, float *faturamentoBruto)
{
    FILE *arquivoDat = fopen("resumo.dat", "rb+");
    if (arquivoDat == NULL)
    {
        arquivoDat = fopen("resumo.dat", "wb");
        if (arquivoDat == NULL)
        {
            printf("\nErro: Arquivo resumo.dat não foi possivel ser criado!");
            exit(1);
        }
    }

    Resumo resumo;

    if (fread(&resumo, sizeof(Resumo), 1, arquivoDat) == 1)
    {
        resumo.totalClientesDiarios += *contador;
        resumo.faturamentoBruto += *faturamentoBruto;
    }
    else
    {
        resumo.totalClientesDiarios = *contador;
        resumo.faturamentoBruto = *faturamentoBruto;
    }

    fseek(arquivoDat, 0, SEEK_SET);

    fwrite(&resumo, sizeof(Resumo), 1, arquivoDat);

    fclose(arquivoDat);

    *contador = 0;
    *faturamentoBruto = 0.0;
}

#endif