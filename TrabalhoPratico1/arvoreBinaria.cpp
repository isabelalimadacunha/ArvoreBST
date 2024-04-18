#include <iostream>
#include <fstream> 
#include <cstdlib>

using namespace std;

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int valor) {
    Node* novo = new Node;
    novo->data = valor;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

//Insere um nodo na árvore

Node* insert(Node *root, int data){
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


//Busca um valor na árvore
Node* search(int key, Node* root) {
    if (root == NULL || root->data == key){
        return root;
    }
        

    if (key < root -> data){
        return search(key, root->left);
    }
        

    return search(key, root->right);
}

// Encontra o nodo de menor valor
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

//Remove um nodo da árvore
Node* removeNode(Node* root, int key) {
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

// Caminhamento pré-ordem
void preOrder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Caminhamento em ordem
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// Caminhamento pós-ordem
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

// Gera um arquivo DOT para a visualização da árvore em Graphviz (caminhamento pré-ordem)
void generateDotFile(Node* root, ofstream& arqSaida, const char* color) {
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




int main(){

    int i;
    int array[15] =
    { 36, 84, 15, 6, 10, 99, 79, 4, 88, 80, 30,
    39, 100, 27, 33};
    Node *root = NULL;

    //Inserção dos nodos na árvore

    for(i=0; i < 15; i++) {
        root = insert(root, array[i]);
    }

   //Impressão dos caminhos pré-ordem, em-ordem e pós-ordem
    cout << "Caminhamento pre-ordem: ";
	preOrder(root);
	cout << "\n--------------------------\n";

    cout << "Caminhamento em-ordem: ";
	inOrder(root);
	cout << "\n--------------------------\n";

    cout << "Caminhamento pos-ordem: ";
	postOrder(root);
	cout << "\n--------------------------\n";

    //Árvore com caminhamento pré-ordem
    ofstream dotFileOriginal("arvoreOriginal.dot");

    if (dotFileOriginal.is_open()) {
        cout << "Arquivo arvoreOriginal aberto com sucesso!\n";
        dotFileOriginal << "digraph ArvoreBinaria {" << endl;
        dotFileOriginal << "node [color=\"#9370DB\", style=filled];\n";
        generateDotFile(root, dotFileOriginal, "#9370DB");
        dotFileOriginal << "}" << endl; 
        dotFileOriginal.close(); 
        system("dot -Tsvg arvoreOriginal.dot -o arvoreOriginal.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }



    // Árvore com inserção de 2 novos valores na árvore pré-ordem
    root = insert(root, 2);
    root = insert(root, 50);
    root = insert(root, 90);

    ofstream insertionDotFile1("arvoreInsercao1.dot");

    if (insertionDotFile1.is_open()) {
        cout << "Arquivo arvoreInsercao1 aberto com sucesso!\n";
        insertionDotFile1 << "digraph BST {\n";
        insertionDotFile1 << "node [color=\"#90EE90\", style=filled];\n";
        generateDotFile(root, insertionDotFile1, "#90EE90");
        insertionDotFile1 << "}\n";
        insertionDotFile1.close();
        system("dot -Tsvg arvoreInsercao1.dot -o arvoreInsercao1.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com remoção de dois valor na árvore pré-ordem
    root = removeNode(root, 84);    
    root = removeNode(root, 100);

    ofstream removalDotFile1("arvoreRemocao1.dot");

    if (removalDotFile1.is_open()) {
        cout << "Arquivo arvoreRemocao1 aberto com sucesso!\n";
        removalDotFile1 << "digraph BST {\n";
        removalDotFile1 << "node [color=\"#ADD8E6\", style=filled];\n";
        generateDotFile(root, removalDotFile1, "#ADD8E6");
        removalDotFile1 << "}\n";
        removalDotFile1.close();
        system("dot -Tsvg arvoreRemocao1.dot -o arvoreRemocao1.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com inserção de 2 novos valores na árvore pré-ordem
    root = insert(root, 96);
    root = insert(root, 38);
    root = insert(root, 119);
    root = insert(root, 29);
    root = insert(root, 82);

    ofstream insertionDotFile2("arvoreInsercao2.dot");

    if (insertionDotFile2.is_open()) {
        cout << "Arquivo arvoreInsercao2 aberto com sucesso!\n";
        insertionDotFile2 << "digraph BST {\n";
        insertionDotFile2 << "node [color=\"#90EE90\", style=filled];\n";
        generateDotFile(root, insertionDotFile2, "#90EE90");
        insertionDotFile2 << "}\n";
        insertionDotFile2.close();
        system("dot -Tsvg arvoreInsercao2.dot -o arvoreInsercao2.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com remoção de três valor na árvore pré-ordem
    root = removeNode(root, 10);
    root = removeNode(root, 15);
    root = removeNode(root, 88);

    ofstream removalDotFile2("arvoreRemocao2.dot");

    if (removalDotFile2.is_open()) {
        cout << "Arquivo arvoreRemocao2 aberto com sucesso!\n";
        removalDotFile2 << "digraph BST {\n";
        removalDotFile2 << "node [color=\"#ADD8E6\", style=filled];\n";
        generateDotFile(root, removalDotFile2, "#ADD8E6");
        removalDotFile2 << "}\n";
        removalDotFile2.close();
        system("dot -Tsvg arvoreRemocao2.dot -o arvoreRemocao2.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Árvore com inserção de cinco novos valores na árvore pré-ordem
    root = insert(root, 19);
    root = insert(root, 13);
    root = insert(root, 20);
    root = insert(root, 130);
    root = insert(root, 104);

    ofstream insertionDotFile3("arvoreInsercao3.dot");

    if (insertionDotFile3.is_open()) {
        cout << "Arquivo arvoreInsercao3 aberto com sucesso!\n";
        insertionDotFile3 << "digraph BST {\n";
        insertionDotFile3 << "node [color=\"#90EE90\", style=filled];\n";
        generateDotFile(root, insertionDotFile3, "#90EE90");
        insertionDotFile3 << "}\n";
        insertionDotFile3.close();
        system("dot -Tsvg arvoreInsercao3.dot -o arvoreInsercao3.svg");
    } else {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }
    return 0;
}