#ifndef RESETARARQUIVO_H
#define RESETARARQUIVO_H

#include "main.h"

void resetarArquivos()
{
    char confirmacao;

    printf("Deseja limpar os arquivos? [S/N]: ");
    scanf(" %c", &confirmacao);
    limparBuffer();

    if (confirmacao == 'S' || confirmacao == 's')
    {
        FILE *arquivoDat = fopen("resumo.dat", "wb");
        if (arquivoDat == NULL)
        {
            printf("\nErro: Arquivo resumo.dat não foi possivel ser criado!");
            exit(1);
        }

        Resumo resumoVazio = {0, 0};
        fwrite(&resumoVazio, sizeof(Resumo), 1, arquivoDat);
        fclose(arquivoDat);

        arquivoDat = fopen("loja_roupa.dat", "wb");
        if (arquivoDat == NULL)
        {
            printf("\nErro: Arquivo loja_roupa.dat não foi possivel ser criado!");
            exit(1);
        }
        fclose(arquivoDat);

        printf("\nOs arquivos foram resetados com sucesso!\n");
    }
    else
    {
        printf("\nOperação cancelada pelo usuário.\n");
    }
    printf("\nPressione ENTER para continuar. . .\n");
    getchar();
}

#endif