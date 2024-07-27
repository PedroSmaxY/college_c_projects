#ifndef REMOVERCLIENTECODIGO_H
#define REMOVERCLIENTECODIGO_H

#include "main.h"

void removerClientePorCodigo(int codigoCliente)
{
    FILE *arquivoDat = fopen("loja_roupa.dat", "rb");
    if (arquivoDat == NULL)
    {
        printf("\nErro: Arquivo loja_roupa.dat não foi possivel ser aberto!");
        exit(1);
    }

    FILE *arquivoTemp = fopen("temp.dat", "wb");
    if (arquivoTemp == NULL)
    {
        printf("\nErro: Arquivo temp.dat não foi possivel ser criado!");
        exit(1);
    }

    Cliente cliente;
    Cliente clienteRemovido;
    int clienteFoiRemovido = 0;
    while (fread(&cliente, sizeof(Cliente), 1, arquivoDat) == 1)
    {
        if (cliente.codigo != codigoCliente)
        {
            fwrite(&cliente, sizeof(Cliente), 1, arquivoTemp);
        }
        else
        {
            clienteRemovido = cliente;
            clienteFoiRemovido = 1;
        }
    }

    fclose(arquivoDat);
    fclose(arquivoTemp);

    remove("loja_roupa.dat");
    rename("temp.dat", "loja_roupa.dat");

    if (clienteFoiRemovido)
    {
        FILE *arquivoResumo = fopen("resumo.dat", "rb+");
        if (arquivoResumo == NULL)
        {
            printf("\nErro: Arquivo resumo.dat não foi possivel ser aberto!");
            exit(1);
        }

        Resumo resumo;
        if (fread(&resumo, sizeof(Resumo), 1, arquivoResumo) != 1)
        {
            printf("\nErro: Não foi possível ler o resumo!");
            exit(1);
        }

        resumo.faturamentoBruto -= clienteRemovido.valorTotal;
        resumo.totalClientesDiarios--;

        fseek(arquivoResumo, 0, SEEK_SET);
        if (fwrite(&resumo, sizeof(Resumo), 1, arquivoResumo) != 1)
        {
            printf("\nErro: Não foi possível atualizar o resumo!");
            exit(1);
        }

        printf("Cliente com código %d foi removido com sucesso.\n", codigoCliente);
        fclose(arquivoResumo);
    }
    else
    {
        printf("Cliente com código %d não foi encontrado.\n", codigoCliente);
    }
    printf("\nPressione ENTER para continuar. . .");
    getchar();
}

#endif