#include <iostream>
#include <stack>
#include <cctype>
#include <cstring>

using namespace std;

struct node {
    char data;
    struct node* left;
    struct node* right;
};

struct node* createNode(char data) {
    struct node* newNode = new node;
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct node* constructExpressionTree(char prefixExp[]) {
    int i;
    struct node* tempStack[100];
    int top = -1; 
    for (i = strlen(prefixExp) - 1; i >= 0; i--) {

        if (isdigit(prefixExp[i])) {
            struct node* newNode = createNode(prefixExp[i]);
            tempStack[++top] = newNode;
        }
    
        else if (prefixExp[i] == '+' || prefixExp[i] == '-' || prefixExp[i] == '*' || prefixExp[i] == '/') {
            struct node* newNode = createNode(prefixExp[i]);
            newNode->left = tempStack[top--];
            newNode->right = tempStack[top--];
            tempStack[++top] = newNode;
        }
    }
    
    return tempStack[top--];
}

void preOrder(struct node* root){
    if(root!=NULL){
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct node* root){
    if(root!=NULL){
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

void inorder(struct node* root){
    if(root!= NULL){
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void iterativePreorder(struct node* root) {
    stack<node*> st;
    st.push(root);
    while (!st.empty()) {
        struct node* temp = st.top();
        st.pop();
        cout << temp->data << " ";
        if (temp->right != NULL) {
            st.push(temp->right);
        }
        if (temp->left != NULL) {
            st.push(temp->left);
        }
    }
}

void iterativeInorder(struct node* root) {
    stack<node*> st;
    struct node* current = root;
    while (current != NULL || !st.empty()) {
        while (current != NULL) {
            st.push(current);
            current = current->left;
        }
        current = st.top();
        st.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void iterativePostorder(struct node* root) {
    stack<node*> st1;
    stack<node*> st2;
    st1.push(root);
    while (!st1.empty()) {
        struct node* temp = st1.top();
        st1.pop();
        st2.push(temp);
        if (temp->left != NULL) {
            st1.push(temp->left);
        }
        if (temp->right != NULL) {
            st1.push(temp->right);
        }
    }
    while (!st2.empty()) {
        struct node* temp = st2.top();
        st2.pop();
        cout << temp->data << " ";
    }
}
int main() {
    char prefixExp[100];
    cout << "Enter the prefix expression: ";
    cin >> prefixExp;
    struct node* root = constructExpressionTree(prefixExp);
    cout << "Recursive Preorder expression is: ";
    preOrder(root);
    cout<<"\nRecursive Inorder expression is: ";
    inorder(root);
    cout<<"\nRecursive Postorder expression is: ";
    postOrder(root);
    cout<<"\nIterative Preorder expression is: ";
    iterativePreorder(root);
    cout<<"\nIterative Inorder expression is: ";
    iterativeInorder(root);
    cout<<"\nIterative Postorder expression is: ";
    iterativePostorder(root);
    return 0;
}