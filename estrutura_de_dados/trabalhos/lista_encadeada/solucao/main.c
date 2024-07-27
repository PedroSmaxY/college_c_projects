#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Estrutura de um nó da fila
typedef struct fila
{
    int valor;
    struct fila *prox;
} Fila;

// Função para adicionar um elemento no início da fila
Fila *enfileirarNoInicio(Fila *fila, int valor)
{
    // Aloca memória para o novo elemento
    Fila *novo = malloc(sizeof(Fila));

    // Configura o novo elemento
    novo->valor = valor;
    novo->prox = NULL;

    // Verifica se a alocação foi bem-sucedida
    if (novo == NULL)
        return NULL;

    // Se a fila estiver vazia, retorna o novo elemento
    if (fila == NULL)
        return novo;

    // Adiciona o novo elemento no início da fila
    novo->prox = fila;
    return novo;
}

// Função para pausar a execução do programa até que o usuário pressione ENTER
void pause()
{
    printf("\n\nPressione ENTER para continuar. . .");
    getchar();
}

Fila *enfileiraNoFim(Fila *fila, int valor)
{
    Fila *novo = malloc(sizeof(Fila)); // Aloca memória para o novo nó

    if (novo == NULL)
        return NULL; // Retorna NULL se a alocação falhou

    novo->valor = valor; // Atribui o valor ao novo nó
    novo->prox = NULL;   // Configura o próximo nó como NULL

    if (fila == NULL)
        return novo; // Retorna o novo nó se a fila estiver vazia

    Fila *aux = fila;
    while (aux->prox != NULL)
        aux = aux->prox; // Percorre até o final da fila

    aux->prox = novo; // Adiciona o novo nó no final da fila

    return fila; // Retorna a fila atualizada
}

// Função para limpar o console
void limparConsole()
{
#ifdef _WIN32
    // Se o sistema for Windows, usa o comando "CLS"
    system("CLS");
#else
    // Se o sistema for baseado em Unix, usa o comando "CLEAR"
    system("CLEAR");
#endif
}

// Função para desenfileirar (remover) um valor da fila
Fila *desenfileira(Fila *fila)
{
    if (fila == NULL)
    {
        printf("Erro: Fila Vazia\n");
        return NULL;
    }

    printf("Valor %d removido da fila\n", fila->valor);

    Fila *temp = fila;
    fila = fila->prox; // O próximo nó se torna o início da fila
    free(temp);        // Libera a memória do nó removido

    return fila;
}

// Função para remover o último elemento de uma fila
Fila *desenfileiraFim(Fila *fila)
{
    // Verifica se a fila está vazia
    if (fila == NULL)
        return NULL;

    // Percorre a fila até o último elemento
    Fila *aux = fila;
    Fila *temp = NULL;
    while (aux->prox != NULL)
    {
        temp = aux;
        aux = aux->prox;
    }

    // Remove o último elemento
    if (temp != NULL)
        temp->prox = NULL;
    else
        fila = NULL;
    free(aux);

    return fila;
}

// Função para remover um elemento de uma posição específica em uma fila
Fila *desenfileiraEspecifico(Fila *fila, int posicao)
{
    // Se a fila estiver vazia, retorna NULL
    if (fila == NULL)
        return NULL;

    // Variáveis auxiliares para percorrer a fila
    int i;
    Fila *aux = fila;
    Fila *temp = NULL;

    // Percorre a fila até a posição desejada
    for (i = 0; i < posicao - 1 && aux->prox != NULL; i++)
    {
        temp = aux;
        aux = aux->prox;
    }

    // Se temp não é NULL, então não estamos removendo o primeiro elemento
    if (temp != NULL)
        temp->prox = aux->prox; // Faz o elemento anterior apontar para o próximo elemento, pulando o elemento atual
    else
        fila = aux->prox; // Se temp é NULL, estamos removendo o primeiro elemento, então fazemos a fila apontar para o segundo elemento

    // Libera a memória do elemento removido
    free(aux);

    // Retorna a fila atualizada
    return fila;
}

// Função para inserir um elemento em uma posição específica em uma fila
Fila *enfileiraEspecifico(Fila *fila, int valor, int posicao)
{
    // Cria um novo nó
    Fila *novo = malloc(sizeof(Fila));
    novo->valor = valor;

    // Se a fila estiver vazia, insere o novo nó
    if (fila == NULL)
    {
        novo->prox = NULL;
        fila = novo;
    }
    // Se a posição for 0, insere o novo nó no início
    else if (posicao == 0)
    {
        novo->prox = fila;
        fila = novo;
    }
    // Caso contrário, percorre a fila até a posição desejada e insere o novo nó
    else
    {
        Fila *anterior = fila;
        int i;
        for (i = 0; i < posicao - 1; i++)
        {
            if (anterior->prox == NULL)
                break;
            anterior = anterior->prox;
        }
        novo->prox = anterior->prox;
        anterior->prox = novo;
    }

    // Retorna a fila atualizada
    return fila;
}

// Função para mostrar os valores da fila
void exibirFila(Fila *fila)
{
    if (fila == NULL)
    {
        printf("Erro: Fila Vazia\n");
        return;
    }
    Fila *aux = fila;
    while (aux != NULL)
    {
        printf("%d\n", aux->valor); // Imprime o valor do nó atual
        aux = aux->prox;            // Vai para o próximo nó
    }
}

// Função para exibir o valor do elemento em uma posição específica na fila
void exibirFilaPosicao(Fila *fila, int posicao)
{
    // Percorre a fila até a posição desejada
    Fila *aux = fila;
    int i;
    for (i = 0; i < posicao - 1 && aux != NULL; i++)
    {
        aux = aux->prox;
    }

    // Se a posição é válida, imprime o valor do elemento
    if (aux != NULL)
        printf("%d\n", aux->valor);
    // Se a posição é inválida, imprime uma mensagem de erro
    else
        printf("Posição inválida\n");
}

// Função para liberar todos os elementos da fila
void liberarElementos(Fila *fila)
{
    // Percorre a fila, liberando a memória de cada elemento
    Fila *aux = fila;
    Fila *temp = NULL;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

int main()
{
    // Configura o idioma para português
    setlocale(LC_ALL, "Portuguese");

    // Declara as variáveis necessárias
    int valor, opcao, posicao;
    Fila *fila = NULL;

    // Loop infinito para o menu de opções
    while (1)
    {
        // Limpa o console e exibe o menu de opções
        limparConsole();
        printf("+-------------------------------------------------+\n");
        printf("MENU DE OPÇÕES\n");
        printf("+-------------------------------------------------+\n");
        printf("[1] Adicionar no início da lista\n");
        printf("[2] Adicionar no final da lista\n");
        printf("[3] Adicionar em um ponto específico da lista\n");
        printf("[4] Listar todos os elementos da lista\n");
        printf("[5] Listar um elemento específico da lista\n");
        printf("[6] Excluir do início da lista\n");
        printf("[7] Excluir do final da lista\n");
        printf("[8] Excluir de um ponto específico da lista\n");
        printf("[9] Liberar os elementos e mostrar a lista vazia\n");
        printf("+-------------------------------------------------+\n");
        printf("[0] Terminar\n");
        printf("+-------------------------------------------------+\n");
        // Lê a opção escolhida pelo usuário
        printf("Digite: ");
        scanf("%d", &opcao);
        getchar();

        // Se a opção for 1, 2 ou 3, lê o valor a ser adicionado
        if (opcao == 1 || opcao == 2 || opcao == 3)
        {
            printf("\nDigite o valor: ");
            scanf("%d", &valor);
            getchar();
        }

        // Se a opção for 3, 5 ou 8, lê a posição
        if (opcao == 3 || opcao == 5 || opcao == 8)
        {
            printf("\nDigite a posição: ");
            scanf("%d", &posicao);
            getchar();
        }

        // Executa a ação correspondente à opção escolhida
        if (opcao != 0)
        {
            switch (opcao)
            {
            case 1:
                fila = enfileirarNoInicio(fila, valor);
                break;
            case 2:
                fila = enfileiraNoFim(fila, valor);
                break;
            case 3:
                fila = enfileiraEspecifico(fila, valor, posicao);
                break;
            case 4:
                exibirFila(fila);
                pause();
                break;
            case 5:
                exibirFilaPosicao(fila, posicao);
                pause();
                break;
            case 6:
                fila = desenfileira(fila);
                break;
            case 7:
                fila = desenfileiraFim(fila);
                break;
            case 8:
                fila = desenfileiraEspecifico(fila, posicao);
                break;
            case 9:
                liberarElementos(fila);
                fila = NULL;
                printf("Todos os elementos foram liberados. A lista está vazia.\n");
                pause();
                break;
            default:
                // Opção inválida
                printf("Opção inválida!\n");
                pause();
                break;
            }
        }
        else
            // Termina o programa
            break;
    }
    printf("Programa encerrado!\n");
    return 0;
}