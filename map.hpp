#pragma once
// clang-format off
#include "opt_ref.hpp"
#include "pair.hpp"
#include "queue.hpp"

template <class T, class P> class Node 
{
public:
  pair<T, P> p;
  Node *right;
  Node *left;

  Node() : right(nullptr), left(nullptr) {}

  Node &operator=(P value) 
  {
    this->p.second = value;
    return *this;
  }
};

template <class T, class P> class Map 
{
  Node<T, P> *root;

private:
  size_t element_count;

  void find_best_place(Node<T, P> *&node, const pair<T, P> &left_pair);

  void print_element(Node<T, P> *&node);

  Node<T, P> *create_new_node(const pair<T, P> &left_pair);

  void delete_node(Node<T, P> *&node);

  opt_ref<Node<T, P>> bfsearch(const T &key);

  opt_ref<Node<T, P>> dfsearch(const T &key);

  opt_ref<Node<T, P>> check_if_exists(Node<T, P> *&node, const T &key);

public:
  Map();

  void insert(const pair<T, P> &p);

  void print_map();

  size_t size() { return element_count; }

  bool empty() { return (element_count == 0) ? true : false; }

  Node<T, P> &operator[](T key);

  ~Map();
};

template <class T, class P>
Map<T, P>::Map() : root(nullptr), element_count(0) {}

template <class T, class P>
Node<T, P> *Map<T, P>::create_new_node(const pair<T, P> &left_pair) 
{
  Node<T, P> *new_node = new Node<T, P>();
  new_node->p = left_pair;
  new_node->left = new_node->right = nullptr;
  return new_node;
}

template <class T, class P> void Map<T, P>::insert(const pair<T, P> &p) 
{
  if (!bfsearch(p.first).has_value()) 
  {
    find_best_place(this->root, p);
  }
}

template <class T, class P>
void Map<T, P>::find_best_place(Node<T, P> *&node,
                                const pair<T, P> &left_pair) 
{
  if (node == nullptr) 
  {
    node = create_new_node(left_pair);
    ++element_count;
  } 
  else if (left_pair.first < node->p.first) 
  {
    find_best_place(node->left, left_pair);
  } 
  else 
  {
    find_best_place(node->right, left_pair);
  }
}

template <class T, class P> void Map<T, P>::print_element(Node<T, P> *&node) 
{
  if (node == nullptr) 
  {
    return;
  }
  std::cout << "[" << node->p.first << "] = " << node->p.second << "\n";
  print_element(node->left);
  print_element(node->right);
}

template <class T, class P> void Map<T, P>::print_map() 
{
  print_element(this->root);
}

template <class T, class P> Map<T, P>::~Map<T, P>() 
{ 
  delete_node(this->root); 
}

template <class T, class P> void Map<T, P>::delete_node(Node<T, P> *&node) 
{
  if (node == nullptr) 
  {
    return;
  }
  if (node->right == nullptr && node->left == nullptr) 
  {
    return delete node;
  }
  if (node->left != nullptr) 
  {
    delete_node(node->left);
  }
  if (node->right != nullptr) 
  {
    delete_node(node->right);
  }
  node = nullptr;
}

template <class T, class P>
opt_ref<Node<T, P>> Map<T, P>::bfsearch(const T &key) 
{
  if (this->root == nullptr) 
  {
    return {};
  }
  Queue<Node<T, P> *> que(element_count);
  que.push(this->root);
  while (que.empty() == false) 
  {
    Node<T, P> *node = que.front();
    if (node->p.first == key) 
    {
      return *node;
    }
    que.pop();
    if (node->left != nullptr) 
    {
      que.push(node->left);
    }
    if (node->right != nullptr) 
    {
      que.push(node->right);
    }
  }
  return {};
}

template <class T, class P>
opt_ref<Node<T, P>> Map<T, P>::check_if_exists(Node<T, P> *&node,
                                               const T &key) 
{
  if (node == nullptr) 
  {
    return {};
  } 
  else if (node->p.first == key) 
  {
    return *node;
  }
  if (node->p.first > key && node->left != nullptr) 
  {
    return check_if_exists(node->left, key);
  }
  else if (node->p.first < key && node->right != nullptr) 
  {
    return check_if_exists(node->right, key);
  } 
  else 
  {
    return {};
  }
}

template <class T, class P>
opt_ref<Node<T, P>> Map<T, P>::dfsearch(const T &key) 
{
  opt_ref<Node<T, P>> result = check_if_exists(this->root, key);
  return result;
}

template <class T, class P> Node<T, P> &Map<T, P>::operator[](T key) 
{
  opt_ref<Node<T, P>> result = dfsearch(key);
  if (result.has_value()) 
  {
    return result.get();
  } 
  else 
  {
    P value{};
    pair<T, P> p = pair<T, P>::make_pair(key, value);
    find_best_place(this->root, p);
    opt_ref<Node<T, P>> result = dfsearch(key);
    return result.get();
  }
}
