#include <iostream>

using namespace std;

//implementação de árvores

struct Node{
    int value;
    Node * left;
    Node * right;
    Node * key;
    Node(){

    }

    Node(int value, Node * left, Node * right){
        this->value(value);
        this->left(left);
        this->right(right);
    }

};

struct Tree{
  Node * root;

  Tree(){
    root = nullptr;
  }

  Tree(Tree other){
      root = clone(other.root);
  }

  //clonar
  Node * clone(Node * node){
      if(node == nullptr)
          return nullptr;
     return new Node(clone(node->left), clone(node->right));
  }

  //destrutor
  void erase(Node * node){
      if(node == nullptr)
          return;
      erase(node->right);
      erase(node->left);
      delete node;
  }

private:
  Node * _find(Node * node, int key){
      if(node == nullptr)
          return nullptr;
      if(node->key = key)
          return node;
      auto resposta = _find(node->left, key);
      if(resposta != nullptr)
          return resposta;
      return _find(node->right, key);
  }

public:
  void find(int value){

  }

  int menor(Node * node){
      if(node->left != nullptr && node->right != nullptr)
          return std::min(node->value, std::min(menor(node->left), menor(node->right)));
      if(node->left != nullptr)
          return std::min(node->value, menor(node->left));
      if(node->right != nullptr)
          return std::min(node->value, menor(node->right));
      return node->value;
  }

  int min(Node * node){
      if(node->left != nullptr)
          return 0;
  }

Node * menor_xik(Node * node){
    if(node == nullptr)
        return nullptr;
    auto mleft = menor(node->left);
    auto mright = menor(node->right);
    Node * nmenor = node;
    if(mleft  && (mleft->value < nmenor->value))
        nmenor = mleft;
    if(mright && (mright->value < nmenor->value))
        nmenor = mright;
    return nmenor;
  }

int somar(Node * node){
    if(node == nullptr)
        return 0;
    return node->value + somar(node->left) + somar(node->right);
    }

void mostrar(Node * node){
    if(node == nullptr)
        return;
    cout << node->value << " ";
    mostrar(node->left);
    mostrar(node->right);
}

};


int main(){
    cout << "Hello World!" << endl;
    return 0;
    Tree arvore;
}

