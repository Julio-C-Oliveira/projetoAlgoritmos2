/*
Discentes:
- Luiz Gabriel Santos Moreira - 202304940001
- Júlio Costa Oliveira - 202104940025
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

// Definições para cores dos nós
enum Color {RED, BLACK};

// Estrutura que define um nó da Árvore Rubro-Negra
struct rbNode {
    int dado;       // Valor armazenado no nó
    Color cor;      // Cor do nó (RED ou BLACK)
    rbNode *esq;    // Ponteiro para o nó filho à esquerda
    rbNode *dir;    // Ponteiro para o nó filho à direita
    rbNode *pai;    // Ponteiro para o nó pai
};
typedef rbNode *ptRbNode;

// Função para criar um novo nó
ptRbNode createNode(int valor) {
    ptRbNode novoNo = new rbNode;
    novoNo->dado = valor;
    novoNo->cor = RED;  // Novos nós sempre começam como RED
    novoNo->esq = novoNo->dir = novoNo->pai = NULL;
    return novoNo;
}

// Função para fazer a rotação à esquerda
void leftRotate(ptRbNode &raiz, ptRbNode x) {
    ptRbNode y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL)
        y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

// Função para fazer a rotação à direita
void rightRotate(ptRbNode &raiz, ptRbNode y) {
    ptRbNode x = y->esq;
    y->esq = x->dir;
    if (x->dir != NULL)
        x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai == NULL)
        raiz = x;
    else if (y == y->pai->esq)
        y->pai->esq = x;
    else
        y->pai->dir = x;
    x->dir = y;
    y->pai = x;
}

// Função para balancear a árvore após inserção
void balanceInsert(ptRbNode &raiz, ptRbNode novoNo) {
    while (novoNo != raiz && novoNo->pai->cor == RED) {
        if (novoNo->pai == novoNo->pai->pai->esq) {
            ptRbNode tio = novoNo->pai->pai->dir;
            if (tio != NULL && tio->cor == RED) {
                novoNo->pai->cor = BLACK;
                tio->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->dir) {
                    novoNo = novoNo->pai;
                    leftRotate(raiz, novoNo);
                }
                novoNo->pai->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                rightRotate(raiz, novoNo->pai->pai);
            }
        } else {
            ptRbNode tio = novoNo->pai->pai->esq;
            if (tio != NULL && tio->cor == RED) {
                novoNo->pai->cor = BLACK;
                tio->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->esq) {
                    novoNo = novoNo->pai;
                    rightRotate(raiz, novoNo);
                }
                novoNo->pai->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                leftRotate(raiz, novoNo->pai->pai);
            }
        }
    }
    raiz->cor = BLACK;
}

// Função para inserir um valor na árvore
void insert(ptRbNode &raiz, int valor) {
    ptRbNode novoNo = createNode(valor);
    ptRbNode y = NULL;
    ptRbNode x = raiz;
    while (x != NULL) {
        y = x;
        if (novoNo->dado < x->dado)
            x = x->esq;
        else
            x = x->dir;
    }
    novoNo->pai = y;
    if (y == NULL)
        raiz = novoNo;
    else if (novoNo->dado < y->dado)
        y->esq = novoNo;
    else
        y->dir = novoNo;
    balanceInsert(raiz, novoNo);
}

// Função para pesquisar um valor na árvore
ptRbNode search(ptRbNode raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor)
        return raiz;
    if (valor < raiz->dado)
        return search(raiz->esq, valor);
    return search(raiz->dir, valor);
}

// Função auxiliar para exibir a árvore em ordem
void inOrder(ptRbNode raiz) {
    if (raiz == NULL)
        return;
    inOrder(raiz->esq);
    cout << raiz->dado << " (" << (raiz->cor == RED ? "R" : "B") << ") ";
    inOrder(raiz->dir);
}

// Função para exibir a árvore balanceada
void displayTree(ptRbNode raiz) {
    cout << "\n\nArvore em ordem (valor e cor):\n";
    inOrder(raiz);
    cout << "\n";
}

// Programa principal
int main() {
    ptRbNode raiz = NULL;
    int opcao, valor;

    do {
        cout << "\n1. Inserir elemento";
        cout << "\n2. Pesquisar elemento";
        cout << "\n3. Mostrar arvore";
        cout << "\n4. Sair";
        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Digite o valor a ser inserido: ";
                cin >> valor;
                insert(raiz, valor);
                break;
            case 2:
                cout << "Digite o valor a ser pesquisado: ";
                cin >> valor;
                if (search(raiz, valor) != NULL)
                    cout << "Valor encontrado!\n";
                else
                    cout << "Valor nao encontrado.\n";
                break;
            case 3:
                displayTree(raiz);
                break;
            case 4:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
        }
    } while (opcao != 4);

    return 0;
}
