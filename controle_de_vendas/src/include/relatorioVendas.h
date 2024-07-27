#ifndef RELATORIOVENDAS_H
#define RELATORIOVENDAS_H

#include "main.h"

void relatorioVendas()
{
    int i = 0;
    int j, k, p;
    Cliente clientes[100];
    Produto produtosMaisVendidos[100];
    Produto produtosMenosVendidos[100];
    int quantidadeProdutosMaisVendidos = 0;
    int quantidadeProdutosMenosVendidos = 0;
    int quantidadeMaisVendida = 0;
    int quantidadeMenosVendida = INT_MAX;

    FILE *arquivoDat = fopen("loja_roupa.dat", "rb");
    if (arquivoDat != NULL)
    {
        Cliente cliente;
        while (fread(&cliente, sizeof(Cliente), 1, arquivoDat))
        {
            clientes[i++] = cliente;
            for (p = 0; p < cliente.quantidadeTotal; p++)
            {
                if (cliente.produtos[p].quantidade > quantidadeMaisVendida)
                {
                    quantidadeMaisVendida = cliente.produtos[p].quantidade;
                    quantidadeProdutosMaisVendidos = 0;
                }
                if (cliente.produtos[p].quantidade == quantidadeMaisVendida)
                {
                    strcpy(produtosMaisVendidos[quantidadeProdutosMaisVendidos].nome, cliente.produtos[p].nome);
                    strcpy(produtosMaisVendidos[quantidadeProdutosMaisVendidos].marca, cliente.produtos[p].marca);
                    produtosMaisVendidos[quantidadeProdutosMaisVendidos].quantidade = cliente.produtos[p].quantidade;
                    quantidadeProdutosMaisVendidos++;
                }
                if (cliente.produtos[p].quantidade < quantidadeMenosVendida && cliente.produtos[p].quantidade > 0)
                {
                    quantidadeMenosVendida = cliente.produtos[p].quantidade;
                    quantidadeProdutosMenosVendidos = 0;
                }
                if (cliente.produtos[p].quantidade == quantidadeMenosVendida)
                {
                    strcpy(produtosMenosVendidos[quantidadeProdutosMenosVendidos].nome, cliente.produtos[p].nome);
                    strcpy(produtosMenosVendidos[quantidadeProdutosMenosVendidos].marca, cliente.produtos[p].marca);
                    produtosMenosVendidos[quantidadeProdutosMenosVendidos].quantidade = cliente.produtos[p].quantidade;
                    quantidadeProdutosMenosVendidos++;
                }
            }
        }
        fclose(arquivoDat);
    }

    for (j = 0; j < i; j++)
    {
        for (k = 0; k < i - j - 1; k++)
        {
            if (clientes[k].valorTotal < clientes[k + 1].valorTotal)
            {
                Cliente temp = clientes[k];
                clientes[k] = clientes[k + 1];
                clientes[k + 1] = temp;
            }
        }
    }

    printf("\n-------------- CLIENTES --------------");

    for (j = 0; j < i; j++)
    {
        printf("\nCódigo do cliente: %d", clientes[j].codigo);
        printf("\nNome do cliente: %s", clientes[j].nome);
        printf("Data da Compra: %s", clientes[j].data.stringData);
        printf("\nGasto total: R$%.2f", clientes[j].valorTotal);
        printf("\nQuantidade de produtos comprados: %d", clientes[j].quantidadeTotal);
        printf("\n--------------------------------------");
    }

    FILE *arquivoResumo = fopen("resumo.dat", "rb");
    if (arquivoResumo == NULL)
    {
        printf("\nErro: Arquivo resumo.dat não foi possivel ser aberto!");
        exit(1);
    }

    Resumo resumo;
    fread(&resumo, sizeof(Resumo), 1, arquivoResumo);

    printf("\nTotal de clientes cadastrados: %d", resumo.totalClientesDiarios);
    printf("\nFaturamento Bruto da Loja: R$%.2f\n", resumo.faturamentoBruto);
    printf("\n--------------------------------------");
    printf("\nProdutos mais vendidos:");
    for (j = 0; j < quantidadeProdutosMaisVendidos; j++)
    {
        printf("\nProduto: %s", produtosMaisVendidos[j].nome);
        printf("Marca: %s", produtosMaisVendidos[j].marca);
        printf("Unidades vendidas: %d\n", produtosMaisVendidos[j].quantidade);
    }

    printf("\nProdutos menos vendidos:");
    for (j = 0; j < quantidadeProdutosMenosVendidos; j++)
    {
        printf("\nProduto: %s", produtosMenosVendidos[j].nome);
        printf("Marca: %s", produtosMenosVendidos[j].marca);
        printf("Unidades vendidas: %d\n", produtosMenosVendidos[j].quantidade);
    }

    printf("\n--------------------------------------");

    printf("\nPressione ENTER para continuar. . .");
    getchar();
}

#endif