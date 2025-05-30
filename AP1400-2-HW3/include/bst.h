#ifndef BST_H
#define BST_H

class Node
{
  friend std::ostream& operator<<(std::ostream& os, Node& node);
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

// Comparison operators (int vs Node) - declared as free functions
class BST
{
    friend std::ostream& operator<<(std::ostream& os, const BST& bst);
public:
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST& operator++();
    BST operator++(int);

    BST();//default constructor
    BST(const BST& bst);//copy constructor
    BST(BST&& bst);//move constructor
    BST& operator=(const BST& bst);//copy assignment operator
    BST& operator=(BST&& bst);//move assignment operator
    ~BST();

private:
    Node* root;
};

std::ostream& operator<<(std::ostream& os, const BST& bst);
std::ostream& operator<<(std::ostream& os, Node& node);

bool operator>(int val, const Node& node);
bool operator>=(int val, const Node& node);
bool operator<(int val, const Node& node);
bool operator<=(int val, const Node& node);
bool operator==(int val, const Node& node);
bool operator!=(int val, const Node& node);
#endif //BST_H
