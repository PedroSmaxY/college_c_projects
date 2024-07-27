#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definição da estrutura do nó da árvore
typedef struct no
{
    char palavra[16];              // Palavra armazenada no nó
    int cont;                      // Contador para a frequência da palavra
    struct no *esquerda, *direita; // Ponteiros para os nós filhos
} No;

// Função para criar um novo nó
No *novoNo(char *palavra)
{
    No *no = malloc(sizeof(No));  // Aloca memória para o novo nó
    strcpy(no->palavra, palavra); // Copia a palavra para o nó
    no->cont = 1;                 // Inicializa o contador como 1
    no->esquerda = NULL;          // Inicializa o ponteiro para o filho esquerdo como NULL
    no->direita = NULL;           // Inicializa o ponteiro para o filho direito como NULL
    return no;                    // Retorna o novo nó criado
}

// Função para inserir uma palavra na árvore
No *inserir(No *no, char *palavra)
{
    if (no == NULL) // Se a árvore estiver vazia, cria um novo nó com a palavra
        return novoNo(palavra);

    int comp = strcmp(palavra, no->palavra); // Compara a palavra com a palavra do nó atual

    if (comp < 0) // Se a palavra for menor, insere à esquerda
        no->esquerda = inserir(no->esquerda, palavra);
    else if (comp > 0) // Se a palavra for maior, insere à direita
        no->direita = inserir(no->direita, palavra);
    else // Se a palavra for igual, incrementa o contador
        no->cont++;

    return no; // Retorna o nó atualizado
}

// Função para imprimir as palavras em ordem alfabética
void printEmOrdem(No *no)
{
    if (no != NULL)
    {
        printEmOrdem(no->esquerda);                 // Imprime as palavras da subárvore esquerda
        printf("%s (%d)\n", no->palavra, no->cont); // Imprime a palavra e sua frequência
        printEmOrdem(no->direita);                  // Imprime as palavras da subárvore direita
    }
}

// Função para processar um array de palavras e construir a árvore
void processaPalavras(char *palavras[])
{
    int i;
    No *root = NULL; // Raiz da árvore inicializada como NULL

    for (i = 0; palavras[i] != NULL; i++)
    {
        root = inserir(root, palavras[i]); // Insere cada palavra na árvore
    }
    printEmOrdem(root); // Imprime as palavras em ordem alfabética
}

void minusculo(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] != '\0')
    {
        s2[i] = tolower(s1[i]);
        i++;
    }
    s2[i] = '\0'; // caractere que indica o fim da string
}

int main()
{
    No *root = NULL; // Raiz da árvore inicializada como NULL
    char palavra[16];
    char pminusculo[16];
    int escolha;

    while (1) // Loop infinito para o menu
    {
        printf("\n+---------------------------------------+");
        printf("\n|        Arvore Binaria de Busca        |");
        printf("\n+---------------------------------------+");
        printf("\n|1 - Iniciar | 2 - Listar | 3 - Encerrar|");
        printf("\n+---------------------------------------+\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha); // Lê a escolha do usuário
        getchar();

        switch (escolha)
        {
        case 1:
            system("clear");
            printf("\nDigite palavras (ou '0' para voltar ao menu):\n");
            while (1)
            {
                scanf("%15s", palavra); // Limita a leitura a 15 caracteres para evitar overflow

                if (strcmp(palavra, "0") == 0) // Se a palavra for "0", volta ao menu
                    break;

                minusculo(palavra, pminusculo);   // Converte a palavra para minúsculas
                root = inserir(root, pminusculo); // Insere a palavra convertida na árvore
            }
            system("clear");
            break;

        case 2:
            system("clear");
            if (root == NULL)
                printf("\nA lista esta vazia.\n");
            else
                printEmOrdem(root); // Imprime as palavras em ordem alfabética
            printf("\nAperte ENTER para voltar ao menu.\n");
            getchar();
            system("clear");
            break;

        case 3:
            printf("\nEncerrando o programa...\n");
            exit(0); // Encerra o programa
            break;

        default:
            printf("\nOpcao invalida. Aperte ENTER.\n");
            getchar();
            system("clear");
            break;
        }
    }
    return 0;
}