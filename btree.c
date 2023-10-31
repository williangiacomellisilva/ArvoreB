#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3 // Ajuste T de acordo com a ordem da árvore B

typedef struct Node {
    int n; // Número de chaves no nó
    int keys[2*T-1]; // Chaves armazenadas no nó
    struct Node *child[2*T]; // Ponteiros para filhos
    bool leaf; // Indica se o nó é uma folha
} Node;

Node *createNode() {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->n = 0;
    newNode->leaf = true;
    return newNode;
}

void splitChild(Node *x, int i) {
    Node *y = x->child[i];
    Node *z = createNode();

    // Mova as chaves de y para z
    for (int j = 0; j < T - 1; j++) {
        z->keys[j] = y->keys[j + T];
    }
    z->n = T - 1;

    // Se y não for folha, mova os filhos de y para z
    if (!y->leaf) {
        for (int j = 0; j < T; j++) {
            z->child[j] = y->child[j + T];
        }
    }

    // Reduza o número de chaves em y
    y->n = T - 1;

    // Abra espaço para um novo filho em x
    for (int j = x->n; j > i; j--) {
        x->child[j + 1] = x->child[j];
    }
    
    // Conecte o novo filho z em x
    x->child[i + 1] = z;

    // Mova uma chave de y para x
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[i] = y->keys[T - 1];
    x->n++;
}

void insertNonFull(Node *x, int key) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->n++;
    } else {
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }
        i++;
        if (x->child[i]->n == 2*T - 1) {
            splitChild(x, i);
            if (key > x->keys[i]) {
                i++;
            }
        }
        insertNonFull(x->child[i], key);
    }
}

Node *insert(Node *root, int key) {
    if (root->n == 2*T - 1) {
        Node *newRoot = createNode();
        newRoot->child[0] = root;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

int findKeyInNode(Node *x, int key) {
    int idx = 0;
    while (idx < x->n && key > x->keys[idx]) {
        idx++;
    }
    return idx;
}

void borrowFromPrev(Node *x, int idx) {
    Node *child = x->child[idx];
    Node *sibling = x->child[idx - 1];

    for (int i = child->n - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--) {
            child->child[i + 1] = child->child[i];
        }
    }

    child->keys[0] = x->keys[idx - 1];

    x->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n++;
    sibling->n--;
}

void deleteKey(Node *x, int key) {
    int idx = findKeyInNode(x, key);

    if (idx < x->n && x->keys[idx] == key) {
        if (x->leaf) {
            for (int i = idx; i < x->n - 1; i++) {
                x->keys[i] = x->keys[i + 1];
            }
            x->n--;
        } else {
            // Implemente o código para a remoção em um nó não folha aqui
        }
    } else {
        if (x->leaf) {
            return;
        }
        Node *child = x->child[idx];
        if (child->n < T) {
            // Implemente o código para resolver o caso 2a aqui
        }
        deleteKey(child, key);
    }
}