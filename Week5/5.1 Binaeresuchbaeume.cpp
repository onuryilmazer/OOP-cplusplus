#include <iostream>

struct Node {  
    std::string data;
    Node * left;
    Node * right;
};

Node* createNewNode(const std::string &data) {
    Node * newNode = new Node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

void insert(Node * &root, const std::string &data) {
    if(root == nullptr) {
        root = createNewNode(data);
    }
    else if (data == root->data) {
        return;
    }
    else if (data < root->data) {
        insert(root->left, data);
    }
    else {
        insert(root->right, data);
    }
}

Node* search(Node * &root, const std::string &data) { //extra.
    if(root == nullptr || root->data == data) {
        return root;
    }
    else if (data < root->data) {
        return search(root->left, data);
    }
    else {
        return search(root->right, data);
    }
}

void list(Node * &root) {
    if (root == nullptr) {
        return;
    }
    else {
        list(root->left);
        std::cout << root->data << "\n";
        list(root->right);
    }
}

void deleteTree(Node * &root) {
    if (root==nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void populateTree(Node * &root) {
    while (true) {
        std::cout << "Enter a new element or a dot to stop: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == ".") {
            return;
        }
        else {
            insert(root, input);
        }
    }
}

int main() {
    Node * rootNodePtr = nullptr;
    populateTree(rootNodePtr);
    list(rootNodePtr);
    deleteTree(rootNodePtr);
}