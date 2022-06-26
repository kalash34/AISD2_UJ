#include <iostream>
using namespace std;

class BST {
    int data;
    BST *left, *right;

public:
    BST();

    BST(int val);

    BST* Insert(BST* r, int val);
    BST* minValueNode(BST* node);
    BST* deleteNode(BST* r, int val);

    void Inorder(BST* r);
};


BST ::BST() : data(0), left(NULL), right(NULL)
{

}

BST ::BST(int value)
{
    data = value;
    left = right = NULL;
}


BST* BST ::Insert(BST* root, int value)
{
    if (root==NULL) {
        return new BST(value);
    }

    if (value > root->data) {
        root->right = Insert(root->right, value);
    }
    else {
        root->left = Insert(root->left, value);
    }

    return root;
}

BST* BST::minValueNode(BST* node){
  BST* current = node;
  while(current->left != NULL){
    current = current->left;
  }
  return current;
}

BST* BST::deleteNode(BST* root, int value){
  if(root==NULL){
    return root;
  }
  if(value < root->data){
    root->left = deleteNode(root->left, value);
  }
  else if(value > root->data){
    root->right = deleteNode(root->right, value);
  }
  else{
    // Jedno Dziecko Albo Brak Dzieci
    if(root->left == NULL){
      BST* temp = root->right;
      return temp;
    }
    else if(root->right == NULL){
      BST* temp = root->left;
      return temp;
    }
    // Obydwa Dzieci

    //Szukamy Potomka ktory wstawimy na miejsce wezla do usuniecia
    BST* temp = minValueNode(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }
  return root;
}



void BST ::Inorder(BST* root)
{
    if (root==NULL) {
        return;
    }
    Inorder(root->left);
    cout << root->data << endl;
    Inorder(root->right);
}

int main()
{
    BST b, *root = NULL;
    root = b.Insert(root, 50);
    b.Insert(root, 30);
    b.Insert(root, 20);
    b.Insert(root, 40);
    b.Insert(root, 70);
    b.Insert(root, 60);
    b.Insert(root, 80);

    b.Inorder(root);

    cout<<"Po usunieciu wezla 60: "<<endl;
    b.deleteNode(root, 60);

    b.Inorder(root);
    return 0;
}
