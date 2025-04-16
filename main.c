//
// Created by Rodrigo on 16/04/2025.
//

#include <windows.h>
#include "item.h"

#define ID_BTN_CRIAR    1
#define ID_BTN_EXCLUIR  2
#define ID_BTN_MODIFICAR 3

#define ID_NOME_PROD    100
#define ID_CODIGO       101
#define ID_QTD_ESTOQUE  102
#define ID_PRECO        103
#define ID_INDICE       104
#define ID_SAIDA        200

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MinhaJanela";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, "MinhaJanela", "Minha Aplicacao",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static Produto *produtos[100];
    static int nprodutos = 0;

    switch (uMsg) {
        case WM_CREATE:
            CreateWindowW(L"Button", L"Criar Produto", WS_VISIBLE | WS_CHILD, 10, 10, 150, 30, hwnd, (HMENU)ID_BTN_CRIAR, NULL, NULL);
            CreateWindowW(L"Button", L"Excluir Produto", WS_VISIBLE | WS_CHILD, 10, 50, 150, 30, hwnd, (HMENU)ID_BTN_EXCLUIR, NULL, NULL);
            CreateWindowW(L"Button", L"Modificar Produto", WS_VISIBLE | WS_CHILD, 10, 90, 150, 30, hwnd, (HMENU)ID_BTN_MODIFICAR, NULL, NULL);

            CreateWindowW(L"Static", L"Nome:", WS_VISIBLE | WS_CHILD, 180, 10, 100, 25, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 10, 150, 25, hwnd, (HMENU)ID_NOME_PROD, NULL, NULL);

            CreateWindowW(L"Static", L"Codigo:", WS_VISIBLE | WS_CHILD, 180, 50, 100, 25, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 50, 150, 25, hwnd, (HMENU)ID_CODIGO, NULL, NULL);

            CreateWindowW(L"Static", L"Qtd. estoque:", WS_VISIBLE | WS_CHILD, 180, 90, 100, 25, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 90, 150, 25, hwnd, (HMENU)ID_QTD_ESTOQUE, NULL, NULL);

            CreateWindowW(L"Static", L"Preco:", WS_VISIBLE | WS_CHILD, 180, 130, 100, 25, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 130, 150, 25, hwnd, (HMENU)ID_PRECO, NULL, NULL);

            CreateWindowW(L"Static", L"Indice:", WS_VISIBLE | WS_CHILD, 180, 170, 100, 25, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 170, 150, 25, hwnd, (HMENU)ID_INDICE, NULL, NULL);

            CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_READONLY, 500, 10, 250, 550, hwnd, (HMENU)ID_SAIDA, NULL, NULL);
            break;

        case WM_COMMAND: {
            int id = LOWORD(wParam);
            char buffer[100];
            int indice;

            switch (id) {
                case ID_BTN_CRIAR:
                    criarProduto(hwnd, produtos, &nprodutos);
                    break;
                case ID_BTN_EXCLUIR:
                    GetWindowText(GetDlgItem(hwnd, ID_INDICE), buffer, sizeof(buffer));
                    indice = atoi(buffer) - 1;
                    excluirProduto(hwnd, produtos, &nprodutos, indice);
                    break;
                case ID_BTN_MODIFICAR:
                    GetWindowText(GetDlgItem(hwnd, ID_INDICE), buffer, sizeof(buffer));
                    indice = atoi(buffer) - 1;
                    modificarProduto(hwnd, produtos, nprodutos, indice);
                    break;
            }
            break;
        }
        case WM_DESTROY:
            liberarMemoriaProdutos(produtos, nprodutos);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
