#ifndef MAIN_H
#define MAIN_H

typedef struct
{
    int dia;
    int mes;
    int ano;
    char stringData[50];
} Data;

typedef struct
{
    char nome[50];
    char marca[50];
    int codigo;
    int quantidade;
    float valorUnitario;
} Produto;

typedef struct
{
    char nome[50];
    int codigo;
    Data data;
    Produto produtos[50];
    float valorTotal;
    int quantidadeTotal;
} Cliente;

typedef struct
{
    int totalClientesDiarios;
    float faturamentoBruto;
} Resumo;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

#include "limparBuffer.h"
#include "limparConsole.h"
#include "atualizarResumo.h"
#include "codigoExistente.h"
#include "cadastrarVendas.h"
#include "relatorioVendas.h"
#include "ordenarClientesPreco.h"
#include "procurarClienteData.h"
#include "resetarArquivo.h"
#include "removerClienteCodigo.h"

#endif