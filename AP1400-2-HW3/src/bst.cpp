#include "bst.h"

/**
 * Node class constructors and operator implementations
 */

// Constructor: Creates a node with specified value and child pointers
BST::Node::Node(int value, BST::Node* left, BST::Node* right) : value(value), left(left), right(right){
}

// Default constructor: Creates a node with value 0 and null pointers
BST::Node::Node() : value(0), left(nullptr), right(nullptr){
}

// Copy constructor: Creates a node by copying another node's data
BST::Node::Node(const BST::Node& node) : value(node.value), left(node.left), right(node.right){
}

/**
 * Node comparison operators with integers
 * These operators allow comparing Node values with integers
 */
//(Node vs int)
bool BST::Node::operator>(int val) const {return value > val; }
bool BST::Node::operator>=(int val) const {return value >= val;}
bool BST::Node::operator==(int val) const {return value == val;}
bool BST::Node::operator!=(int val) const {return value != val;}
bool BST::Node::operator<(int val) const {return value < val;}
bool BST::Node::operator<=(int val) const {return value <= val;}

// Stream output operator for Node class
// Formats the node information for output including memory address and node values
std::ostream& operator<<(std::ostream& os, const BST::Node& node) { 
  os << std::hex                    // 切换到十六进制输出模式
     << &node                       // 输出节点的地址（不是输出流的地址）
     << std::dec                    // 切换回十进制输出模式
     << "\t=> value:" << node.value // 输出节点值
     << "\tleft:" 
     << std::left                   
     << std::setw(20)              
     << std::hex                    
     << node.left                   // 输出左子节点地址
     << "\tright:" << node.right    // 输出右子节点地址
     << std::dec;                   
  return os; 
}

/**
 * Integer comparison operators with Node
 * These operators allow comparing integers with Node values
 */
bool operator>=(int val, const BST::Node& node) {return val >= node.value;}
bool operator==(int val, const BST::Node& node) {return val == node.value;}
bool operator!=(int val, const BST::Node& node) {return val != node.value;}
bool operator<=(int val, const BST::Node& node) {return val <= node.value;}
bool operator<(int val, const BST::Node& node) {return val < node.value;}
bool operator>(int val, const BST::Node& node) {return val > node.value; }

// Returns the root node of the BST
BST::Node* BST::get_root() const {return root;}

/**
 * Performs a breadth-first traversal of the BST
 * @param func Function to be applied to each node during traversal
 */
void BST::bfs(std::function<void(BST::Node*& node)> func){
  if (!root){
    return;
  }
  std::queue<BST::Node*> q;
  q.push(root);

  if (!q.empty()){
    BST::Node*& current = q.front();
    q.pop();

    func(current);

    if (current->left) { q.push(current->left); }
    if (current->right) { q.push(current->right); }
  }
}

/**
 * Calculates the number of nodes in the BST
 * @return The total number of nodes in the tree
 */
size_t BST::length() const{
  size_t num_node = 0;
  if (!root){
    return 0;
  }
  std::queue<BST::Node*> q;
  q.push(root);

  if (!q.empty()){
    BST::Node*& current = q.front();
    q.pop();
    num_node++;

    if (current->left) { q.push(current->left); }
    if (current->right) { q.push(current->right); }
  }
  return num_node;
}

/**
 * Adds a new node with the given value to the BST
 * @param value The value to be added
 * @return true if the value was successfully added, false if it already exists
 */
bool BST::add_node(int value){
  if (!root) { 
    root = new BST::Node(value, nullptr, nullptr);  
    return true; } 

  BST::Node* current = root;
  while(true){
    if (value == current->value){
      return false;
    }
    else if (value < current->value){
      if (!current->left){
        current->left = new BST::Node(value, nullptr, nullptr);
        return true;
      }
      current = current->left;
    }
    else {
      if (!current->right){
        current->right = new BST::Node(value, nullptr, nullptr);
        return true;
      }
      current = current->right;
    }
  }
}

/**
 * Finds a node with the specified value in the BST
 * @param value The value to search for
 * @return Pointer to the node pointer containing the value, or nullptr if not found
 */
BST::Node** BST::find_node(int value){
  BST::Node** current = &root;

  while ((*current) != nullptr){
    if (value == (*current)->value){
      return current;
    }
    else if (value < (*current)->value){
      current = &(*current)->left;
    }
    else{
      current = &(*current)->right;
    }
  }
  return nullptr;
}

/**
 * Finds the parent node of a node with the specified value
 * @param value The value whose parent node is to be found
 * @return Pointer to the parent node pointer, or nullptr if not found or if root
 */
BST::Node** BST::find_parent(int value){
  BST::Node** parent = nullptr;
  BST::Node** current = &root;

  while ( (*current) != nullptr ){
    if ( value == (*current)->value){
      return parent;
    }
    else if (value < (*current)->value){
      parent = current;
      current = &((*current)->left); 
    }
    else{
      parent = current;
      current = &((*current)->right);
    } 
  }
  return nullptr;
}

/**
 * Finds the successor node of a node with the specified value
 * @param value The value whose successor is to be found
 * @return Pointer to the successor node pointer, or nullptr if not found
 */
BST::Node** BST::find_successor(int value){
    // First find the node with the given value
  BST::Node** current = find_node(value);
    if ((*current) == nullptr) {
        return nullptr;  // Node with given value not found
    }
    current = &(*current)->right;
    while ((*current)->left != nullptr){
      current = &(*current)->left;
    }
    return current;
}

bool BST::delete_node(int value){
  BST::Node** node_to_delete = find_node(value);
  if (!node_to_delete|| !*node_to_delete) return false;

  BST::Node* target = *node_to_delete;

  if (!target->left && !target->right){
    delete target;
    *node_to_delete = nullptr;
    return true;
  }
  else if (target->left && !target->right){
    *node_to_delete = target->left;
    delete target;
    return true;
  }
  else if (!target->left && target->right){
    *node_to_delete = target->right;
    delete target;
    return true;
  }
  else{
    BST::Node** successor = find_successor(value);
    target->value = (*successor)->value; 
    return delete_node((*successor)->value);
  }
}

std::ostream& operator<<(std::ostream& os, const BST& bst){
  //std::string(count, char), "" is a string
  std::cout << std::string(82, '*') << std::endl;
  std::queue<BST::Node*> q;
  q.push(bst.get_root());
  while (!q.empty()){
    BST::Node* current = q.front();
    q.pop();
    os << *current << std::endl;
    if (current->left) q.push(current->left);
    if (current->right) q.push(current->right);
  }
  std::cout << "binary search tree size:" << bst.length() << std::endl;
  std::cout << std::string(82, '*') << std::endl;
  return os;
}

//++BST
BST& BST::operator++(){
  auto increment = [](BST::Node*& node){
    node->value++;
  };
  bfs(increment);
  return *this;
}

//BST++
BST BST::operator++(int){
  BST temp = *this;
  ++(*this);
  return temp;
}

BST::Node* BST::copy_node(BST::Node* node){
  if (!node) return nullptr;
  BST::Node* new_node = new BST::Node(node->value, copy_node(node->left), copy_node(node->right));
  return new_node;
}

BST::BST(std::initializer_list<int> values){
  for (int value: values){
    add_node(value);
  }
}

BST::BST(const BST& bst){
  root = copy_node(bst.root);
}

BST::BST(BST&& bst){
  root = bst.root;
  bst.root = nullptr;
}

BST& BST::operator=(const BST& bst){
  if (this == &bst) return *this;
  root = copy_node(bst.root);
  return *this;
}

BST& BST::operator=(BST&& bst){
  if (this == &bst) return *this;
  root = bst.root;
  bst.root = nullptr;
  return *this;
}

BST::~BST()
{
	std::vector<BST::Node*> nodes;
	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
	for(auto node: nodes)
		delete node;

  root = nullptr;
}
