//
// Created by Rodrigo on 16/04/2025.
//

#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_NOME_PROD    100
#define ID_CODIGO       101
#define ID_QTD_ESTOQUE  102
#define ID_PRECO        103
#define ID_INDICE       104
#define ID_SAIDA        200

void criarProduto(HWND hwnd, Produto *produtos[], int *nprodutos) {
    if (*nprodutos >= 100) {
        MessageBox(hwnd, "Limite máximo de produtos atingido.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }

    Produto *produto = malloc(sizeof(Produto));
    if (!produto) {
        MessageBox(hwnd, "Erro ao alocar memória.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }

    GetWindowText(GetDlgItem(hwnd, ID_NOME_PROD), produto->nome_prod, sizeof(produto->nome_prod));
    GetWindowText(GetDlgItem(hwnd, ID_CODIGO), produto->codigo_prod, sizeof(produto->codigo_prod));

    char buffer[64];
    GetWindowText(GetDlgItem(hwnd, ID_QTD_ESTOQUE), buffer, sizeof(buffer));
    produto->qtd_estoque = atoi(buffer);

    GetWindowText(GetDlgItem(hwnd, ID_PRECO), buffer, sizeof(buffer));
    produto->preco = atof(buffer);

    produtos[*nprodutos] = produto;
    (*nprodutos)++;

    imprimirProduto(hwnd, produtos, *nprodutos);
}

void imprimirProduto(HWND hwnd, Produto *produtos[], int nprodutos) {
    char message[4096] = "", temp[256];
    for (int i = 0; i < nprodutos; ++i) {
        sprintf(temp, "Indice %d:\nProduto: %s\nCodigo do Produto: %s\nQuantidade em estoque: %d\nPreço: %.2f\n\n",
                i + 1, produtos[i]->nome_prod, produtos[i]->codigo_prod, produtos[i]->qtd_estoque, produtos[i]->preco);
        strcat(message, temp);
    }
    SetDlgItemText(hwnd, ID_SAIDA, message);
}

void excluirProduto(HWND hwnd, Produto *produtos[], int *nprodutos, int indice) {
    if (indice < 0 || indice >= *nprodutos) {
        MessageBox(hwnd, "Índice inválido para exclusão.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }

    free(produtos[indice]);
    for (int i = indice; i < *nprodutos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }
    (*nprodutos)--;

    imprimirProduto(hwnd, produtos, *nprodutos);
}

void modificarProduto(HWND hwnd, Produto *produtos[], int nprodutos, int indice) {
    if (indice < 0 || indice >= nprodutos) {
        MessageBox(hwnd, "Índice inválido para modificação.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }

    GetWindowText(GetDlgItem(hwnd, ID_NOME_PROD), produtos[indice]->nome_prod, sizeof(produtos[indice]->nome_prod));
    GetWindowText(GetDlgItem(hwnd, ID_CODIGO), produtos[indice]->codigo_prod, sizeof(produtos[indice]->codigo_prod));

    char buffer[64];
    GetWindowText(GetDlgItem(hwnd, ID_QTD_ESTOQUE), buffer, sizeof(buffer));
    produtos[indice]->qtd_estoque = atoi(buffer);

    GetWindowText(GetDlgItem(hwnd, ID_PRECO), buffer, sizeof(buffer));
    produtos[indice]->preco = atof(buffer);

    imprimirProduto(hwnd, produtos, nprodutos);
}

void liberarMemoriaProdutos(Produto *produtos[], int nprodutos) {
for (int i = 0; i < nprodutos; i++) {
    free(produtos[i]);
    }
}
