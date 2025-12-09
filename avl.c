#include <stdio.h>
#include <stdlib.h>
 
// Estrutura de um nó da AVL
typedef struct Node{
    int item;
    struct Node *left;
    struct Node *right;
    int height; // guarda a altura desse nó (importante pro balanceamento)
} Node;

// Retorna o maior entre dois valores
int bigger(int a, int b){
    return (a > b) ? a : b;
}

// Retorna a altura de um nó (ou -1 se for NULL)
int hightNode(Node *root){
    return (root == NULL) ? -1 : root->height;
}

// Fator de balanceamento = (altura da esquerda) - (altura da direita)
// Se o resultado for:
//   > 1  = desbalanceada pra esquerda
//   < -1 = desbalanceada pra direita
int balanceFactor(Node *root){
    if (root == NULL)
        return 0;
    return hightNode(root->left) - hightNode(root->right);
}   

// ---------------- ROTACOES ----------------

// Rotação simples à esquerda
// Quando usar?
// - Quando a árvore está desbalanceada pra direita (fb < -1)
// - E o filho da direita também está “pendendo” pra direita (caso simples)
Node *leftRotate(Node *root){
    Node *y = root->right; // filho da direita vira a nova raiz
    Node *f = y->left;     // subárvore esquerda de y será movida

    // Faz a troca:
    // root sobe para a esquerda de y
    y->left = root;
    root->right = f;

    // Recalcula alturas
    root->height = bigger(hightNode(root->left), hightNode(root->right)) + 1;
    y->height = bigger(hightNode(y->left), hightNode(y->right)) + 1;

    return y; // y vira o novo topo
}

// Rotação simples à direita
// Quando usar?
// - Quando a árvore está desbalanceada pra esquerda (fb > 1)
// - E o filho da esquerda também pende pra esquerda
Node *rightRotate(Node *root){
    Node *y = root->left;
    Node *f = y->right;

    y->right = root;
    root->left = f;

    root->height = bigger(hightNode(root->left), hightNode(root->right)) + 1;
    y->height = bigger(hightNode(y->left), hightNode(y->right)) + 1;

    return y;
}

// Rotação dupla: Direita-Esquerda
// Quando usar?
// - Desbalanceada pra direita (fb < -1)
// - Mas o filho da direita está pendendo pra esquerda
Node *rightlerftRotate(Node *root){
    root->right = rightRotate(root->right); // primeiro arruma o filho
    return leftRotate(root);                // depois faz a rotação simples
}

// Rotação dupla: Esquerda-Direita
// Quando usar?
// - Desbalanceada pra esquerda (fb > 1)
// - Mas o filho da esquerda está pendendo pra direita
Node *leftRightRotate(Node *root){
    root->left = leftRotate(root->left);
    return rightRotate(root);
}

// Função que decide qual rotação aplicar
Node *balance(Node *root){
    int fb = balanceFactor(root);

    // Caso 1 — Desbalanceada pra direita (pendendo demais pra direita)
    // Rotação simples à esquerda
    if(fb < -1 && balanceFactor(root->right) <= 0){
        root = leftRotate(root);
    }
    // Caso 2 — Desbalanceada pra esquerda (pendendo demais pra esquerda)
    // Rotação simples à direita
    else if (fb > 1 && balanceFactor(root->left) >= 0){
        root = rightRotate(root);
    }
    // Caso 3 — Desbalanceada pra direita, mas filho pende pra esquerda
    // Rotação dupla Direita-Esquerda
    else if (fb < -1 && balanceFactor(root->right) > 0){
        root = rightlerftRotate(root);
    }
    // Caso 4 — Desbalanceada pra esquerda, mas filho pende pra direita
    // Rotação dupla Esquerda-Direita
    else if (fb > 1 && balanceFactor(root->left) < 0){
        root = leftRightRotate(root);
    }

    return root;
}

// ---------------- INSERÇÃO ----------------

// Inserindo um item na AVL
Node *insert(Node *root, int item){

    // Inserção normal de árvore binária de busca
    if (root == NULL){
        Node *new = malloc(sizeof(Node));
        if (new == NULL) {
            printf("Erro: Falha na alocacao de memoria.\n");
            return NULL;
        }
        new->item = item;
        new->left = NULL;
        new->right = NULL;
        new->height = 0; // novo nó é sempre folha
        return new;
    }
    else if (item > root->item){
        root->right = insert(root->right, item);
    }
    else if (item < root->item){
        root->left = insert(root->left, item);
    }
    else {
        printf("Item ja existe na arvore.\n");
        return root;
    }

    // Atualiza altura do nó depois da inserção
    root->height = bigger(hightNode(root->left), hightNode(root->right)) + 1;

    // Verifica se desbalanceou e corrige com rotações
    root = balance(root);

    return root;
}

// Impressão pré-ordem
void treeprint(Node *root){   
    if (root != NULL){
        printf("%d \n", root->item);
        treeprint(root->left);
        treeprint(root->right);
    }
}

// Libera memória da árvore inteira
void treefree(Node *root){                 
    if (root != NULL){
        treefree(root->left);
        treefree(root->right);
        free(root);
    }
}

// Busca um item na árvore (padrão BST)
Node *treeSearch(Node *root, int item){
    if (root != NULL){
        if (root->item == item)
            return root;
        else if (item > root->item)
            return treeSearch(root->right, item);
        else
            return treeSearch(root->left, item);   
    }
    return NULL;
}

// Acha o menor elemento (vai sempre descendo à esquerda)
Node *treeMin(Node *root){
    if(root != NULL){
        Node *aux = root;
        while(aux->left != NULL){
            aux = aux->left;
        }
        return aux;
    }
    return NULL;
}

// ---------------- REMOÇÃO ----------------
// Também igual a BST, mas no final rebalanceia
Node *removeNode (Node *root, int item){       
    if (root != NULL){

        if(item > root->item){
            root->right = removeNode(root->right, item);
        }
        else if (item < root->item){
            root->left = removeNode(root->left, item);
        }
        else{ // achou o item

            // Nó sem filhos
            if(root->left == NULL && root->right == NULL){
                free(root);
                return NULL;
            }
            // Só filho da direita
            else if(root->left == NULL){
                Node *aux = root->right;
                free(root);
                return aux;
            }
            // Só filho da esquerda
            else if(root->right == NULL){
                Node *aux = root->left;
                free(root);
                return aux;
            }
            // Dois filhos → pega o menor da direita (sucessor)
            else{
                Node *aux = treeMin(root->right);
                int ItemAux = aux->item;
                root->item = ItemAux;  
                root->right = removeNode(root->right, ItemAux);
                return root;                
            }
        }
    }
    else{
        return NULL;
    }
    
    // Atualiza altura depois da remoção
    root->height = bigger(hightNode(root->left), hightNode(root->right)) + 1;

    // Rebalanceia
    root = balance(root);
    return root;
}

int main(){
    int opcao;
    int item;
    Node *root = NULL;

    do{
        printf("\n==== MENU ARVORE BINARIA ====\n");
        printf("1 - Inserir\n");
        printf("2 - Buscar\n");
        printf("3 - Remover\n");
        printf("4 - Imprimir\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao){

        case 1:
            printf("digite o numero q o senhor deseja inserir: ");
            scanf("%d", &item);
            root = insert(root, item);
            printf("item Inserido!\n");
            break;

        case 2:
            if (root == NULL){
                printf("A Arvore ainda está vazia.\n");
                break;
            }
            printf("Digite o item que deseja buscar: ");
            scanf("%d", &item);
            {
                Node *aux = treeSearch(root, item);

                (aux != NULL) ?
                    printf("Item %d encontrado!\n", item) :
                    printf("Item %d NAO encontrado.\n", item);
            }
            break;

        case 3:
            if (root == NULL){
                printf("A Arvore ainda está vazia.\n");
                break;
            }
            printf("Digite o item que deseja remover: ");
            scanf("%d", &item);
            root = removeNode(root, item);

            printf("Item removido (ou não encontrado).\n");
            break;

        case 4: 
            if (root == NULL) {
                printf("A árvore está vazia!\n");
            } 
            else {
                printf("Árvore (pré-ordem):\n");
                treeprint(root);
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    treefree(root); // libera memória
    return 0;
}
