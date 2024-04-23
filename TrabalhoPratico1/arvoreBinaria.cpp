#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

class BinaryTree {

public:
    BinaryTree();
    Node* getRoot();
    void insert(int data);
    void removeNode(int key);
    Node* search(int key);
    void preOrder(Node* root);
    void inOrder(Node* root);
    void postOrder(Node* root);
    void generateDotFile(Node* root, ofstream& arqSaida, const char* color);

protected:
    Node* root;
    Node* createNode(int valor);
    Node* insert(Node *root, int data);
    Node* removeNode(Node* root, int key);
    Node* search(int key, Node* root);
    Node* minValueNode(Node* root);
};

BinaryTree::BinaryTree() {
    root = NULL;
}

Node* BinaryTree::getRoot() {
    return root;
}
//Método criar nodo
Node* BinaryTree::createNode(int valor) {
    Node* novo = new Node;
    novo->data = valor;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}
// Método inserir nodo
Node* BinaryTree::insert(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else {
        if (data < root->data) {
            root->left = insert(root->left, data);
        } else if (data > root->data) {
            root->right = insert(root->right, data);
        }
    }
    return root;
}

//Método buscar nodo
Node* BinaryTree::search(int key, Node* root) {
    if (root == NULL || root->data == key){
        return root;
    }
    if (key < root->data){
        return search(key, root->left);
    }
    return search(key, root->right);
}

//Método acha o nodo de menor valor
Node* BinaryTree::minValueNode(Node* root) {
    Node* current = root;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

//Método remover nodo
Node* BinaryTree::removeNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = removeNode(root->left, key);
    else if (key > root->data)
        root->right = removeNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
    }
    return root;
}


void BinaryTree::insert(int data) {
    root = insert(root, data);
}

void BinaryTree::removeNode(int key) {
    root = removeNode(root, key);
}

Node* BinaryTree::search(int key) {
    return search(key, root);
}

void BinaryTree::preOrder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void BinaryTree::inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

void BinaryTree::postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

void BinaryTree::generateDotFile(Node* root, ofstream& arqSaida, const char* color) {
    if (root != NULL) {
        arqSaida << root->data << " [color=\"" << color << "\", style=filled];\n";
        if (root->left != NULL) {
            arqSaida << root->data << " -> " << root->left->data << ";\n";
        }
        if (root->right != NULL) {
            arqSaida << root->data << " -> " << root->right->data << ";\n";
        }
        generateDotFile(root->left, arqSaida, color);
        generateDotFile(root->right, arqSaida, color);
    }
}

int main() {

    BinaryTree tree;
    int array[15] = {36, 84, 15, 6, 10, 99, 79, 4, 88, 80, 30, 39, 100, 27, 33};

    // Inserção dos nodos na árvore
    for (int i = 0; i < 15; i++) {
        tree.insert(array[i]);
    }

    // Impressão dos caminhos pré-ordem, em-ordem e pós-ordem
    cout << "Caminhamento pre-ordem: ";
    tree.preOrder(tree.getRoot());
    cout << "\n--------------------------\n";

    cout << "Caminhamento em-ordem: ";
    tree.inOrder(tree.getRoot());
    cout << "\n--------------------------\n";

    cout << "Caminhamento pos-ordem: ";
    tree.postOrder(tree.getRoot());
    cout << "\n--------------------------\n";

    // Geração de arquivos DOT e SVG
    ofstream dotFileOriginal("arvoreOriginal.dot");
    if (dotFileOriginal.is_open()) {
        dotFileOriginal << "digraph ArvoreBinaria {\n";
        dotFileOriginal << "node [color=\"#9370DB\", style=filled];\n";
        tree.generateDotFile(tree.getRoot(), dotFileOriginal, "#9370DB");
        dotFileOriginal << "}\n";
        dotFileOriginal.close();
        system("dot -Tsvg arvoreOriginal.dot -o arvoreOriginal.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }
    // Árvore com inserção de três novos valores na árvore pré-ordem
    tree.insert(2);
    tree.insert(50);
    tree.insert(90);

    ofstream insertionDotFile1("arvoreInsercao1.dot");
    if (insertionDotFile1.is_open()) {
        cout << "Arquivo arvoreInsercao1 aberto com sucesso!\n";
        insertionDotFile1 << "digraph BST {\n";
        insertionDotFile1 << "node [color=\"#90EE90\", style=filled];\n";
        tree.generateDotFile(tree.getRoot(), insertionDotFile1, "#90EE90");
        insertionDotFile1 << "}\n";
        insertionDotFile1.close();
        system("dot -Tsvg arvoreInsercao1.dot -o arvoreInsercao1.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com remoção de dois valor na árvore pré-ordem
    tree.removeNode(84);
    tree.removeNode(100);

    ofstream removalDotFile1("arvoreRemocao1.dot");

    if (removalDotFile1.is_open()) {
        cout << "Arquivo arvoreRemocao1 aberto com sucesso!\n";
        removalDotFile1 << "digraph BST {\n";
        removalDotFile1 << "node [color=\"#ADD8E6\", style=filled];\n";
        tree.generateDotFile(tree.getRoot(), removalDotFile1, "#ADD8E6");
        removalDotFile1 << "}\n";
        removalDotFile1.close();
        system("dot -Tsvg arvoreRemocao1.dot -o arvoreRemocao1.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com inserção de cinco novos valores na árvore pré-ordem
    tree.insert(96);
    tree.insert(38);
    tree.insert(119);
    tree.insert(29);
    tree.insert(82);

    ofstream insertionDotFile2("arvoreInsercao2.dot");

    if (insertionDotFile2.is_open()) {
        cout << "Arquivo arvoreInsercao2 aberto com sucesso!\n";
        insertionDotFile2 << "digraph BST {\n";
        insertionDotFile2 << "node [color=\"#90EE90\", style=filled];\n";
        tree.generateDotFile(tree.getRoot(), insertionDotFile2, "#90EE90");
        insertionDotFile2 << "}\n";
        insertionDotFile2.close();
        system("dot -Tsvg arvoreInsercao2.dot -o arvoreInsercao2.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com remoção de três valor na árvore pré-ordem
    tree.removeNode(10);
    tree.removeNode(15);
    tree.removeNode(88);

    ofstream removalDotFile2("arvoreRemocao2.dot");

    if (removalDotFile2.is_open()) {
        cout << "Arquivo arvoreRemocao2 aberto com sucesso!\n";
        removalDotFile2 << "digraph BST {\n";
        removalDotFile2 << "node [color=\"#ADD8E6\", style=filled];\n";
        tree.generateDotFile(tree.getRoot(), removalDotFile2, "#ADD8E6");
        removalDotFile2 << "}\n";
        removalDotFile2.close();
        system("dot -Tsvg arvoreRemocao2.dot -o arvoreRemocao2.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com inserção de cinco novos valores na árvore pré-ordem
    tree.insert(19);
    tree.insert(13);
    tree.insert(20);
    tree.insert(130);
    tree.insert(104);

    ofstream insertionDotFile3("arvoreInsercao3.dot");

    if (insertionDotFile3.is_open()) {
        cout << "Arquivo arvoreInsercao3 aberto com sucesso!\n";
        insertionDotFile3 << "digraph BST {\n";
        insertionDotFile3 << "node [color=\"#90EE90\", style=filled];\n";
        tree.generateDotFile(tree.getRoot(), insertionDotFile3, "#90EE90");
        insertionDotFile3 << "}\n";
        insertionDotFile3.close();
        system("dot -Tsvg arvoreInsercao3.dot -o arvoreInsercao3.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }
    return 0;
}
