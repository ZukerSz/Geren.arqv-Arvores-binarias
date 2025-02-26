//alunos: Iuker de Souza Santos, Gabriel Bauer

#include <iostream>
#include <cstdlib>

struct Node {
    int id;
    Node* left;
    Node* right;
};

Node* criarNovoNo(int id) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->id = id;
    novoNo->left = nullptr;
    novoNo->right = nullptr;
    return novoNo;
}

void inserir(Node** root, int id) {
    if (*root == nullptr) {
        *root = criarNovoNo(id); 
    } else if (id < (*root)->id) {
        inserir(&((*root)->left), id); 
    } else if (id > (*root)->id) {
        inserir(&((*root)->right), id);  
    }
}

void buscar(Node* root, int id, bool* encontrado) {
    if (root == nullptr) {
        *encontrado = false;  
    } else if (root->id == id) {
        *encontrado = true;  
    } else if (id < root->id) {
        buscar(root->left, id, encontrado); 
    } else {
        buscar(root->right, id, encontrado);  
    }
}

//encontra o menor valor de um nó
Node* menorValorNo(Node* node) {
    Node* atual = node;
    while (atual && atual->left != nullptr) {
        atual = atual->left;  
    }
    return atual;
}

void remover(Node** root, int id) {
    if (*root == nullptr) {
        return;
    }

    if (id < (*root)->id) {
        remover(&((*root)->left), id);  
    } else if (id > (*root)->id) {
        remover(&((*root)->right), id);  
    } else {
        if ((*root)->left == nullptr) {
            Node* temp = (*root)->right;
            free(*root);  
            *root = temp;
        } else if ((*root)->right == nullptr) {
            Node* temp = (*root)->left;
            free(*root);  
            *root = temp;
        } else {
            // 
            Node* temp = menorValorNo((*root)->right);
            (*root)->id = temp->id;
            remover(&((*root)->right), temp->id);
        }
    }
}

void menu() {
    Node* root = nullptr;
    int opcao, id;
    bool encontrado;

    do {
        printf("\n                         Lóguitéchi!                            \n");
        printf("\n--------Sistema de Gerenciamento de Arquivos Lóguitéchi!--------\n\n");
        printf("Escolha uma opcao:\n");
        printf("1. Inserir arquivo\n");
        printf("2. Buscar arquivo\n");
        printf("3. Remover arquivo\n");
        printf("4. Sair\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Para inserir, digite o identificador do arquivo: ");
                scanf("%d", &id);
                inserir(&root, id);
                printf("Arquivo inserido com sucesso!\n");
                break;

            case 2:
                printf("Para buscar, digite o identificador do arquivo: ");
                scanf("%d", &id);
                buscar(root, id, &encontrado);
                if (encontrado) {
                    printf("Arquivo encontrado!\n");
                } else {
                    printf("Arquivo nao encontrado!\n");
                }
                break;

            case 3:
                printf("Para remover, digite o identificador do arquivo: ");
                scanf("%d", &id);
                remover(&root, id);
                printf("Arquivo removido com sucesso!\n");
                break;

            case 4:
                printf("Saindo do sistema.\n");
                break;

            default:
                printf("Opcao invalida. Favor Digitar apenas algum dos números citados.\n");
        }
    } while (opcao != 4);
}

int main() {
    menu();
    return 0;
}
