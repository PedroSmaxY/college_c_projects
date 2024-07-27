#ifndef PROCURARCLIENTEDATA_H
#define PROCURARCLIENTEDATA_H

#include "main.h"

void procurarClientePorData()
{
    char dataProcurada[12];
    char dataFormatada[11];
    int dia, mes, ano;
    int i;

    printf("\nDigite a data para a pesquisa");
    printf("\nFormato [ DD/MM/AAAA ]: ");
    fgets(dataProcurada, sizeof(dataProcurada), stdin);
    dataProcurada[strcspn(dataProcurada, "\n")] = '\0';

    if (sscanf(dataProcurada, "%d/%d/%d", &dia, &mes, &ano) != 3)
    {
        printf("\nData inválida. Por favor, insira a data no formato 'DD/MM/AAAA'.\n");
    }
    else
    {
        if (dia < 10 && mes < 10)
            sprintf(dataFormatada, "%d/%d/%d", dia, mes, ano);
        else if (dia < 10)
            sprintf(dataFormatada, "%d/%02d/%d", dia, mes, ano);
        else if (mes < 10)
            sprintf(dataFormatada, "%02d/%d/%d", dia, mes, ano);
        else
            sprintf(dataFormatada, "%02d/%02d/%d", dia, mes, ano);

        FILE *arquivoDat = fopen("loja_roupa.dat", "rb");
        if (arquivoDat == NULL)
        {
            printf("\nErro: Arquivo loja_roupa.dat não foi possível ser aberto!");
            printf("Pressione ENTER para continuar. . .");
            getchar();
            return;
        }

        Cliente cliente;
        Cliente clientesEncontrados[100];
        int n = 0;

        while (fread(&cliente, sizeof(Cliente), 1, arquivoDat) == 1)
        {
            if (strcmp(cliente.data.stringData, dataFormatada) == 0)
            {
                clientesEncontrados[n++] = cliente;
            }
        }

        fclose(arquivoDat);

        ordenarClientesPorPreco(clientesEncontrados, n);

        if (n == 0)
        {
            printf("\nNenhum cliente encontrado com a data: %s\n", dataProcurada);
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                printf("\nCódigo do cliente: %d\n", clientesEncontrados[i].codigo);
                printf("Nome do cliente: %s", clientesEncontrados[i].nome);
                printf("Data da Compra: %s\n", clientesEncontrados[i].data.stringData);
                printf("Gasto total: R$%.2f\n", clientesEncontrados[i].valorTotal);
                printf("Quantidade de produtos comprados: %d\n", clientesEncontrados[i].quantidadeTotal);
                printf("\n--------------------------------------\n");
            }
        }
    }

    printf("Pressione ENTER para continuar. . .");
    getchar();
}

#endif