#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <utility>
#include <queue>

using namespace std;
#define ll long long

//   A
//  / \
// B   C

template <typename T> struct BinaryTree;
template <typename T> struct Node
{
  T value = T();
  Node<T> *left{nullptr}, *right{nullptr}, *parent{nullptr};

  BinaryTree<T>* tree{nullptr};  //everyone has a ptr to the tree

  Node(T value) : value(value) {}

  Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right)
  {
    this->left->tree = this->right->tree = tree;
    this->left->parent = this->right->parent = this;
  }

  void set_tree(BinaryTree<T>* t)
  {
    tree = t;
    if (left) left->set_tree(t);
    if (right) right->set_tree(t);
  }

  ~Node()
  {
    if (left) delete left;
    if (right) delete right;
  }
};

template <typename T> struct BinaryTree
{
  Node<T>* root{nullptr};


  BinaryTree(Node<T> * root) : root(root), pre_order(*this)
  {
    root->set_tree(this);
  }

  ~BinaryTree() { if (root) delete root; }

  //iterator
  template <typename U> struct PreOrderIterator
  {
    Node<U>* current;

    PreOrderIterator(Node<U> *current) : current(current) {}

    bool operator != (const PreOrderIterator<U>& other)
    {
      return current != other.current;
    }

    PreOrderIterator<U>& operator++()
    {
      if(current->right)
      {
        current = current->right;
        while(current->left)
          current = current->left;
      }
      else
      {
        Node<T>* p = current->parent;
        while(p && current == p->right)
        {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    Node<U>& operator* () { return *current; }
  };
  

  //Ok, we want tomake the PreOrderIterator the default iterator for the binary tree. How?
  //this is how?
  typedef PreOrderIterator<T> iterator;
  iterator begin()
  {
    Node<T>* n = root;
    if(n)
      while(n->left)
        n = n->left;
    return iterator{ n };
  }
  iterator end()
  {
    return iterator{nullptr};
  }


  //another way?!
  class PreOrderTraversal
  {
    BinaryTree& tree;
  public:
    PreOrderTraversal(BinaryTree &tree) : tree(tree) {}
    iterator begin() { return tree.begin(); }
    iterator end() { return tree.end(); }
  } pre_order;
};

int main(){
  //building a family tree example
  BinaryTree<string> family {
    new Node<string>{
      "me",
      new Node<string>{ "mother",
                        new Node<string>{"mother's mother"},
                        new Node<string>{"mother's father"}
      },
      new Node<string>{ "father" }
    }
  };

  //style 1
  for (auto it=family.begin(); it != family.end(); ++it){
    cout << (*it).value << "\n";
  }
  //now we get to use the cool loop
  for (auto &&it : family)
    cout << it.value << "\n";

  //style 3
  for (const auto &it : family.pre_order)
    cout << it.value << "\n";
}
