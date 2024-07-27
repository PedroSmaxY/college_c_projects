#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct
{
    char placa[8];
} Carro;

typedef struct
{
    Carro carros[5]; // Array para armazenar os carros
    int topo;        // Índice do topo da pilha
} Pilha;

void inicializaPilha(Pilha *p)
{
    p->topo = -1; // Define o topo como -1, indicando que a pilha está vazia
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1; // Retorna verdadeiro se o topo for -1
}

int pilhaCheia(Pilha *p)
{
    return p->topo == 5 - 1; // Retorna verdadeiro se o topo for igual ao máximo índice (4)
}

int empilha(Pilha *p, Carro carro)
{
    if (pilhaCheia(p)) // Verifica se a pilha está cheia
        return 0;      // Retorna 0 se a pilha estiver cheia

    p->carros[++(p->topo)] = carro; // Incrementa o topo e adiciona o carro na nova posição
    return 1;                       // Retorna 1 indicando sucesso
}

int desempilha(Pilha *p, Carro *carro)
{
    if (pilhaVazia(p)) // Verifica se a pilha está vazia
        return 0;      // Retorna 0 se a pilha estiver vazia

    *carro = p->carros[(p->topo)--]; // Remove o carro do topo e decrementa o topo
    return 1;                        // Retorna 1 indicando sucesso
}

int buscaCarro(Pilha *p, char placa[], int *pos)
{
    int i;

    for (i = 0; i <= p->topo; i++)
    {
        if (strcmp(p->carros[i].placa, placa) == 0)
        {             // Compara a placa
            *pos = i; // Define a posição encontrada
            return 1; // Retorna 1 indicando sucesso
        }
    }
    return 0; // Retorna 0 se o carro não for encontrado
}

void processaEntrada(Pilha *p, char placa[])
{
    Carro carro;
    strcpy(carro.placa, placa); // Copia a placa para o carro

    if (empilha(p, carro))                                     // Tenta empilhar o carro
        printf("Carro %s entrou no estacionamento.\n", placa); // Mensagem de sucesso
    else
        printf("Estacionamento cheio. Carro %s não entrou.\n", placa); // Mensagem de falha
}

void processaSaida(Pilha *p, char placa[])
{
    int i, pos, manobras = 0;
    Pilha aux; // Pilha auxiliar para manobrar os carros
    inicializaPilha(&aux);
    Carro carro;

    if (buscaCarro(p, placa, &pos))
    { // Verifica se o carro está no estacionamento
        for (i = p->topo; i >= pos; i--)
        {
            desempilha(p, &carro);
            if (strcmp(carro.placa, placa) != 0)
            {
                empilha(&aux, carro); // Empilha na pilha auxiliar se não for o carro desejado
                manobras++;
            }
        }

        printf("Carro %s saiu do estacionamento. Manobras: %d\n", placa, manobras); // Mensagem de saída

        while (!pilhaVazia(&aux))
        {
            desempilha(&aux, &carro);
            empilha(p, carro); // Recoloca os carros da pilha auxiliar de volta na pilha principal
        }
    }
    else
        printf("Carro %s não está no estacionamento.\n", placa); // Mensagem de carro não encontrado
}

int main()
{
    size_t i;
    Pilha estacionamento;
    inicializaPilha(&estacionamento);

    setlocale(LC_ALL, "Portuguese");

    // Array de linhas de entrada predefinidas
    char operacoes[][10] = {"E ABC1234", "E DEF5678", "E GHI9012", "E JKL3456", "E MNO7890", "E PQR2345", "S DEF5678", "E PAF9878", "S JKL3456", "S ABC1234"};

    for (i = 0; i < sizeof(operacoes) / sizeof(operacoes[0]); i++)
    {
        char operacao;
        char placa[8];
        sscanf(operacoes[i], "%c %7s", &operacao, placa); // Lê a operação e a placa da linha

        if (operacao == 'E')
            processaEntrada(&estacionamento, placa); // Processa entrada
        else if (operacao == 'S')
            processaSaida(&estacionamento, placa); // Processa saída
    }

    printf("\n\nPressione ENTER para encerrar. . .");
    getchar();
    return 0;
}
