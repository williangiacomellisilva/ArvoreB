#include <stdio.h>
#include "btree.h" // Inclui o arquivo de cabeçalho

int main() {
    Node *root = createNode();

    int keys[] = {3, 7, 11, 18, 22, 31, 42, 50, 62, 78};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    // Teste de inserção
    printf("Árvore B após inserções:\n");
    // Implemente a função de impressão da árvore B para visualizar a estrutura

    int key_to_delete = 22;
    root = deleteKey(root, key_to_delete);

    // Teste de remoção
    printf("Árvore B após a remoção de %d:\n", key_to_delete);
    // Implemente a função de impressão da árvore B novamente

    return 0;
}