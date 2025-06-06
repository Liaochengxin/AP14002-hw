#ifndef BST_H
#define BST_H

#include <iostream>     // for std::ostream
#include <queue>        // for std::queue in BFS
#include <vector>       // for std::vector in destructor
#include <string>       // for std::string in output formatting
#include <functional>   // for std::function in BFS
#include <iomanip>      // for std::setw, std::left, etc.



// Comparison operators (int vs Node) - declared as free functions
class BST
{
    friend std::ostream& operator<<(std::ostream& os, const BST& bst);
public:
    class Node;
    Node* get_root() const;
    void bfs(std::function<void(Node*& node)> func);
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST& operator++();
    BST operator++(int);
    Node* copy_node(Node* node);

    BST(std::initializer_list<int> values);//default constructor
    BST(const BST& bst);//copy constructor
    BST(BST&& bst);//move constructor
    BST& operator=(const BST& bst);//copy assignment operator
    BST& operator=(BST&& bst);//move assignment operator
    ~BST();

private:
    Node* root;
};

class BST::Node
{
  friend std::ostream& operator<<(std::ostream& os, const Node& node);
public:
	Node(int value, Node* left, Node* right);
	Node();
	Node(const Node& node);

  //(Node vs Int)
  bool operator>(int val) const;
  bool operator>=(int val) const;
  bool operator==(int val) const;
  bool operator!=(int val) const;
  bool operator<(int val) const;
  bool operator<=(int val) const;


	int value;
	Node* left;
	Node* right;
};

std::ostream& operator<<(std::ostream& os, const BST& bst);
std::ostream& operator<<(std::ostream& os, const BST::Node& node);

bool operator>(int val, const BST::Node& node);
bool operator<(int val, const BST::Node& node);
bool operator>=(int val, const BST::Node& node);
bool operator<=(int val, const BST::Node& node);
bool operator==(int val, const BST::Node& node);
bool operator!=(int val, const BST::Node& node);
#endif //BST_H
