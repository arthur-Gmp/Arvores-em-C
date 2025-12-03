#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int item;
    struct Node *left;
    struct Node *right;
} Node;

Node *insert(Node *root, int item){

    if (root == NULL){
        Node *new = malloc(sizeof(Node));
        new->item = item;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    else{
        if (item > root->item){

            root->right = insert(root->right, item);
        }
        else if (item < root->item){

            root->left = insert(root->left, item);
        }
    }
    return root;
}

void treeprint(Node *root){   

    if (root != NULL){
        printf("%d \n", root->item);
        treeprint(root->left);
        treeprint(root->right);
    }
}
void treefree(Node *root){                 
    if (root != NULL)
    {
        treefree(root->left);
        treefree(root->right);
        free(root);
    }
}
Node *treeSearch(Node *root, int item){
    
    if (root != NULL){
        if (root->item == item){
            return root;
        }
        else{
            if (item > root->item)
                return treeSearch(root->right, item);
            else
                return treeSearch(root->left, item);   
        }
    }
    return NULL;
}

Node *treeMin(Node *root){

    if(root != NULL){
        Node *aux = root;
        while(aux->left != NULL){
            aux = aux -> left;
        }
        return aux;
    }
    return NULL;
}

Node *removeNode (Node *root, int item){       
    if (root != NULL){
        if(item > root->item){  //quando o valor do item for igual desce para o else da linha 86
            root-> right = removeNode(root->right, item);  

        }else if (item < root->item){ //quando o valor do item for igual desce para o else da linha 86
            root->left = removeNode (root->left, item);  

        }
        else{ //achou o elemento
            if(root->left == NULL && root->right == NULL){ //elemento sem filhor
                free(root);
                return NULL;
            }
            else if(root->left == NULL && root->right != NULL){ // elemento com 1 filho
                Node *aux = root->right;
                free(root);
                return aux;
            }
            else if(root->right == NULL && root->left != NULL){  // elemento com 1 filho
                Node *aux = root->left;
                free(root);
                return aux;
            }
            else{ // elemento com 2 filhos

                Node *aux = treeMin (root->right);
                int ItemAux = aux->item;
                root->item = ItemAux;                              
                root->right = removeNode(root->right, ItemAux);     
                return root;                
            }
        }
    }
    else
        return NULL;
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
            printf("Digite o item que deseja buscar: ");
            scanf("%d", &item);
            {
                Node *aux = treeSearch(root, item);       
                if(aux != NULL)                               
                    printf("Item %d encontrado!\n", item);
                else
                    printf("Item %d NAO encontrado.\n", item);
            }
            break;                                         

        case 3:
            printf("Digite o item que deseja remover: ");
            scanf("%d", &item);
            root = removeNode(root, item);
            if (root != NULL)
                printf("Item removido com sucesso");
            else
                printf("Item nao escontrado");

            break;

        case 4: 
            if (root == NULL) {
                printf("A árvore está vazia!\n");
            } 
            else {
                printf("Árvore (pré-ordem):\n");
                treeprint(root);
                printf("\n");
            }
            break;
        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    treefree(root); // fazendo a liberacao (lá ele).

    return 0;
}
