#include "../include/main.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int contador = 0;
    int contagemVendas = 0;
    int escolha;
    size_t i, j;
    float faturamentoBruto = 0;
    Cliente clientes[100];

    for (i = 0; i < sizeof(clientes) / sizeof(clientes[0]); i++)
    {
        clientes[i].codigo = 0;
        clientes[i].nome[0] = '\0';
        clientes[i].quantidadeTotal = 0;
        clientes[i].valorTotal = 0;
        for (j = 0; j < sizeof(clientes[0].produtos) / sizeof(clientes[0].produtos[0]); j++)
        {
            clientes[i].produtos[j].codigo = 0;
            clientes[i].produtos[j].marca[0] = '\0';
            clientes[i].produtos[j].nome[0] = '\0';
            clientes[i].produtos[j].quantidade = 0;
            clientes[i].produtos[j].valorUnitario = 0;
        }
    }

    while (1)
    {
        limparConsole();
        printf("\n=================================");
        printf("\n-------- Loja de Roupas ---------");
        printf("\n=================================");
        printf("\n1 - Cadastrar Venda");
        printf("\n2 - Relatório de Vendas");
        printf("\n3 - Procurar cliente por data");
        printf("\n4 - Remover cliente por código");
        printf("\n5 - Limpar arquivos");
        printf("\n0 - Sair");
        printf("\n=================================");
        printf("\nDigite: ");
        scanf("%d", &escolha);
        limparBuffer();

        FILE *arquivoDat;

        if (escolha != 0)
        {
            switch (escolha)
            {
            case 1:
                limparConsole();
                cadastrarVendas(clientes, &contador, sizeof(clientes) / sizeof(clientes[0]), &faturamentoBruto, &contagemVendas);
                break;
            case 2:
                limparConsole();
                arquivoDat = fopen("loja_roupa.dat", "rb");
                if (arquivoDat != NULL)
                {
                    fclose(arquivoDat);
                    relatorioVendas(&contador, faturamentoBruto);
                }
                else
                {
                    printf("\nO arquivo loja_roupa.dat ainda não foi criado. Por favor, realize uma venda primeiro.\n");
                    printf("\nPressione ENTER para continuar. . .\n");
                    getchar();
                }
                break;
            case 3:
                limparConsole();
                arquivoDat = fopen("loja_roupa.dat", "rb");
                if (arquivoDat != NULL)
                {
                    fclose(arquivoDat);
                    procurarClientePorData();
                }
                else
                {
                    printf("\nO arquivo loja_roupa.dat ainda não foi criado. Por favor, realize uma venda primeiro.\n");
                    printf("\nPressione ENTER para continuar. . .\n");
                    getchar();
                }
                limparConsole();
                break;
            case 4:
                limparConsole();
                int codigoCliente;
                printf("\nDigite o código do cliente que deseja remover: ");
                scanf("%d", &codigoCliente);
                limparBuffer();
                removerClientePorCodigo(codigoCliente);
                break;
            case 5:
                limparConsole();
                resetarArquivos();
                break;
            default:
                printf("\nDigite um valor válido!!!");
                continue;
            }
        }
        else
        {
            break;
        }
    }

    return 0;
}