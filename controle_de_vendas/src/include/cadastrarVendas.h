#ifndef CADASTRARVENDAS_H
#define CADASTRARVENDAS_H

#include "main.h"

void cadastrarVendas(Cliente clientes[], int *contador, int tamanho, float *faturamentoBruto, int *contagemVendas)
{
    FILE *arquivoDat = fopen("loja_roupa.dat", "ab+");
    if (arquivoDat == NULL)
    {
        printf("\nErro: Arquivo loja_roupa.dat não foi possivel ser criado!");
        exit(1);
    }

    int i;
    size_t j;
    char continuarProduto;
    char continuarCliente;

    printf("\n------------- Inserir Clientes -------------");
    for (i = *contador; i < tamanho; i++)
    {
        float valor = 0;
        clientes[i].quantidadeTotal = 0;

        printf("\nNúmero da venda: %d\n", *contagemVendas + 1);

        (*contagemVendas)++;

        printf("\nNome do cliente: ");
        fgets(clientes[i].nome, sizeof(clientes[i].nome) / sizeof(clientes[i].nome[0]), stdin);

        int codigo;
        do
        {
            printf("Código do cliente: ");
            scanf("%d", &codigo);
            limparBuffer();
            if (codigoExiste(clientes, i, codigo))
            {
                printf("Este código já existe. Por favor, insira um código diferente.\n");
            }
        } while (codigoExiste(clientes, i, codigo));
        clientes[i].codigo = codigo;

        printf("Data da compra [ DD/MM/AAAA ]: ");
        scanf("%d/%d/%d", &clientes[i].data.dia, &clientes[i].data.mes, &clientes[i].data.ano);
        sprintf(clientes[i].data.stringData, "%d/%d/%d", clientes[i].data.dia, clientes[i].data.mes, clientes[i].data.ano);
        limparBuffer();

        for (j = 0; j < sizeof(clientes[i].produtos) / sizeof(clientes[i].produtos[0]); j++)
        {
            printf("Nome do produto: ");
            fgets(clientes[i].produtos[j].nome, sizeof(clientes[i].produtos[j].nome) / sizeof(clientes[i].produtos[j].nome[0]), stdin);

            printf("Marca do produto: ");
            fgets(clientes[i].produtos[j].marca, sizeof(clientes[i].produtos[j].marca) / sizeof(clientes[i].produtos[j].marca[0]), stdin);

            printf("Código do produto: ");
            scanf("%d", &clientes[i].produtos[j].codigo);
            limparBuffer();

            printf("Quantidade do produto: ");
            scanf("%d", &clientes[i].produtos[j].quantidade);
            limparBuffer();

            printf("Valor Unitário do produto: R$");
            scanf("%f", &clientes[i].produtos[j].valorUnitario);
            limparBuffer();

            if (clientes[i].produtos[j].quantidade >= 3)
            {
                printf("Parabéns! Você ganhou 10%% de desconto em cada produto por comprar 3 ou mais produtos!\n");
                clientes[i].produtos[j].valorUnitario *= 0.9;
            }

            valor += clientes[i].produtos[j].valorUnitario * clientes[i].produtos[j].quantidade;
            clientes[i].quantidadeTotal += clientes[i].produtos[j].quantidade;

            printf("\nValor Total: R$%.2f\n", valor);

            printf("\nDeseja adicionar outro produto? [S/N]: ");
            scanf(" %c", &continuarProduto);
            limparBuffer();

            if (continuarProduto == 'n' || continuarProduto == 'N')
                break;
        }
        clientes[i].valorTotal = valor;
        *faturamentoBruto += valor;

        printf("\nDeseja adicionar outro cliente? [S/N]: ");
        scanf(" %c", &continuarCliente);
        printf("\n--------------------------------------------");

        fwrite(&clientes[i], sizeof(Cliente), 1, arquivoDat);

        (*contador)++;

        if (continuarCliente == 'n' || continuarCliente == 'N')
            break;
        limparBuffer();
    }
    atualizarResumo(contador, faturamentoBruto);
    fclose(arquivoDat);
}

#endif