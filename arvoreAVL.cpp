#include <iostream>
#include <stdlib.h>
using namespace std;


typedef int tDado;

// Estrutura que define um nó da árvore
struct noArv{
    noArv *esq;    // Ponteiro para o nó filho à esquerda
    noArv *dir;    // Ponteiro para o nó filho à direita
    tDado dado;    // Valor armazenado no nó
    int height;    // Altura do nó (para balanceamento da árvore)
};
typedef noArv * ptNo;


// Função para construir a árvore a partir de entrada do usuário
void buildTree(ptNo &noRaiz)
{
    tDado x;
    cout << "Digite um valor para o nó (use -1 para NULL): ";
    cin >> x;
    
    if (x == -1){  // Caso o valor seja -1, significa que o nó é NULL
        noRaiz = NULL;
        return;
    }
    
    // Aloca um novo nó e define seus valores
    noRaiz = new noArv;
    noRaiz -> dado = x;
    noRaiz -> esq = NULL;
    noRaiz -> dir = NULL;
    noRaiz -> height = 1;
    
    // Chama recursivamente para inserir à esquerda e à direita
    cout << "Ins. à esquerda de " << noRaiz->dado << ". " << endl;
    buildTree(noRaiz->esq);
    cout << "Ins. à direita de " << noRaiz->dado << ". " << endl;
    buildTree(noRaiz->dir);
    return;
}


// Função para calcular a altura de um nó
int getHeight(ptNo noRaiz){
    if (noRaiz == NULL) return 0;  // Se o nó for NULL, a altura é 0
    int left = getHeight(noRaiz -> esq);  // Altura do filho à esquerda
    int right = getHeight(noRaiz -> dir); // Altura do filho à direita
    return 1 + max(left, right);  // Altura do nó é 1 + maior altura entre os filhos
};


// Função que retorna a altura do filho à esquerda do nó
int getHeightL(ptNo noRaiz) {
    return (noRaiz != NULL && noRaiz->esq != NULL) ? noRaiz->esq->height : 0;
}


// Função que retorna a altura do filho à direita do nó
int getHeightR(ptNo noRaiz) {
    return (noRaiz != NULL && noRaiz->dir != NULL) ? noRaiz->dir->height : 0;
}


// Função que atualiza a altura do nó e de seus filhos
void updateHeight(ptNo noRaiz) {
    if (noRaiz == NULL) return;  // Se o nó for NULL, não há necessidade de atualizar
    // Atualiza a altura do nó com base nas alturas dos filhos
    noRaiz->height = 1 + (max(getHeightL(noRaiz), getHeightR(noRaiz)));
    // Atualiza as alturas dos filhos recursivamente
    updateHeight(noRaiz->dir);
    updateHeight(noRaiz->esq);
}


// Função para realizar rotação à esquerda
int leftRotation(ptNo &noRaiz){
    if (getHeightR(noRaiz) - getHeightL(noRaiz) > 1){  // Verifica se a árvore está desequilibrada
        ptNo noAtual = noRaiz -> dir;  // O nó à direita se torna a nova raiz
        noRaiz -> dir = noAtual -> esq;  // O filho à esquerda do nó à direita se torna filho à direita da raiz
        noAtual -> esq = noRaiz;  // A raiz original passa a ser filho à esquerda do novo nó
        
        // Atualiza as alturas dos nós envolvidos na rotação
        noRaiz->height = 1 + max(getHeight(noRaiz->esq), getHeight(noRaiz->dir));
        noAtual->height = 1 + max(getHeight(noAtual->esq), getHeight(noAtual->dir));
        
        noRaiz = noAtual;  // A nova raiz da árvore é o nó à direita
        return 1;  // Indica que houve rotação
    }
    else{
        return 0;  // Não houve rotação
    }
};


// Função para realizar rotação à direita
int rightRotation(ptNo &noRaiz){
    if (getHeightL(noRaiz) - getHeightR(noRaiz) > 1){  // Verifica se a árvore está desequilibrada
        ptNo noAtual = noRaiz-> esq;  // O nó à esquerda se torna a nova raiz
        noRaiz -> esq = noAtual -> dir;  // O filho à direita do nó à esquerda se torna filho à esquerda da raiz
        noAtual -> dir = noRaiz;  // A raiz original passa a ser filho à direita do novo nó
        
        // Atualiza as alturas dos nós envolvidos na rotação
        noRaiz->height = 1 + max(getHeight(noRaiz->esq), getHeight(noRaiz->dir));
        noAtual->height = 1 + max(getHeight(noAtual->esq), getHeight(noAtual->dir));
        
        noRaiz = noAtual;  // A nova raiz da árvore é o nó à esquerda
        return 1;  // Indica que houve rotação
    }
    return 0;  // Não houve rotação
};


// Função para exibir os dados de um nó
void showNode(ptNo noRaiz){
    cout <<"\n" << noRaiz ->dado << endl;
}


// Função que verifica se um valor existe na árvore
ptNo exists(ptNo noRaiz, int x) { 
    if (noRaiz == NULL)
        return NULL;  // Se o nó for NULL, não existe valor
    if (noRaiz->dado == x)
        return noRaiz;  // Retorna o nó se o valor for encontrado
    
    ptNo leftResult = exists(noRaiz->esq, x);  // Busca no filho à esquerda
    if (leftResult != NULL)
        return leftResult;

    return exists(noRaiz->dir, x);  // Busca no filho à direita
}


// Função para adicionar um valor à esquerda do nó com valor 'y'
void addL(ptNo &noRaiz, int x, int y) 
{
    ptNo noAtual = exists(noRaiz, y);  // Encontra o nó com valor 'y'
    if (noAtual == NULL || noAtual -> esq != NULL)  // Se o nó não existir ou já tiver filho à esquerda, retorna
    {
        return;
    }
    ptNo s = new noArv;  // Cria um novo nó
    s -> dado = x;  // Atribui o valor ao novo nó
    noAtual -> esq = s;  // O novo nó é adicionado à esquerda do nó atual
    s -> esq = s -> dir = NULL;  // Os filhos do novo nó são NULL
    updateHeight(noRaiz);  // Atualiza a altura a partir da raiz
}


// Função para adicionar um valor à direita do nó com valor 'y'
void addR(ptNo &noRaiz, int x, int y) {
    ptNo noAtual = exists(noRaiz, y);  // Encontra o nó com valor 'y'
    if (noAtual == NULL || noAtual->dir != NULL) {
        return;  // Se o nó não existir ou já tiver filho à direita, retorna
    }
    ptNo s = new noArv;  // Cria um novo nó
    s->dado = x;  // Atribui o valor ao novo nó
    s->esq = s->dir = NULL;  // Os filhos do novo nó são NULL
    noAtual->dir = s;  // O novo nó é adicionado à direita do nó atual
    updateHeight(noRaiz);  // Atualiza a altura a partir da raiz
}


// Função para exibir a árvore em pré-ordem
void preOrder (ptNo noRaiz){
    if (noRaiz == NULL){
        return;  // Se o nó for NULL, retorna
    }
    
    showNode(noRaiz);  // Exibe o nó
    preOrder(noRaiz->esq);  // Chama recursivamente para o filho à esquerda
    preOrder(noRaiz->dir);  // Chama recursivamente para o filho à direita
}


// Função para exibir a árvore em ordem
void inOrder(ptNo noRaiz){
    if (noRaiz == NULL){
        return;  // Se o nó for NULL, retorna
    }
    inOrder(noRaiz->esq);  // Chama recursivamente para o filho à esquerda
    showNode(noRaiz);  // Exibe o nó
    inOrder(noRaiz->dir);  // Chama recursivamente para o filho à direita
}


// Função para exibir a árvore em pós-ordem
void postOrder(ptNo noRaiz){
    if (noRaiz == NULL){
        return;  // Se o nó for NULL, retorna
    }
    postOrder(noRaiz->esq);  // Chama recursivamente para o filho à esquerda
    postOrder(noRaiz->dir);  // Chama recursivamente para o filho à direita
    showNode(noRaiz);  // Exibe o nó
}
