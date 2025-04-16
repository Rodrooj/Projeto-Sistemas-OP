//
// Created by Rodrigo on 16/04/2025.
//

#ifndef ITEM_H
#define ITEM_H

#include <windows.h>

typedef struct {
    char nome_prod[100];
    char codigo_prod[100];
    int qtd_estoque;
    float preco;
} Produto;

void criarProduto(HWND hwnd, Produto *produtos[], int *nprodutos);
void imprimirProduto(HWND hwnd, Produto *produtos[], int nprodutos);
void excluirProduto(HWND hwnd, Produto *produtos[], int *nprodutos, int indice);
void modificarProduto(HWND hwnd, Produto *produtos[], int nprodutos, int indice);
void liberarMemoriaProdutos(Produto *produtos[], int nprodutos);

#endif
