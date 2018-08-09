/***********************************************************/
/*    Search Tree
/*
/*    Aidan Clyens
/*    August 8, 2018
/***********************************************************/
#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

// #include "Arduino.h"

template <typename Type>
class SearchTree {
  public:
    SearchTree(); //  Done
    ~SearchTree();  //  Done

    //  Size
    bool empty() const; //  Done
    int size() const; //  Done
    int height() const; //  Done

    //  Modifiers
    bool insert( Type const & );  //  Done
    bool erase( Type const & ); //  Done, implement
    void clear(); //  Done, implement

    //  Misc.
    void print(); //  Done

  private:
    class SearchNode {
      public:
        SearchNode( Type const & ); //  Done

        //  Size
        int height() const; //  Done

        //  Modifers
        bool insert( Type const & ); //  Done
        bool erase( Type const & );  //  Done, implement

        //  Misc.
        bool is_leaf() const; //  Done
        void print( int = 0 );  //  Done
        int max( int, int ) const;  //  Done

        Type node_value;
        SearchNode* left_tree;
        SearchNode* right_tree;
        int tree_height;
    };


    SearchNode* root_node;
    int tree_size;
};

/***********************************************/
/***************   SearchTree    ***************/
/***********************************************/
/***************************************
*           Constructors
****************************************/
/*
 * Search Tree Constructor
 */
template <typename Type>
SearchTree<Type>::SearchTree():
root_node( nullptr ),
tree_size( 0 )
{
  //  Empty Constructor
}

/*
 * Search Tree Destructor
 */
template <typename Type>
SearchTree<Type>::~SearchTree() {
  clear();
}

/***************************************
*        Public Size Functions
****************************************/
/*
 * empty
 */
template <typename Type>
bool SearchTree<Type>::empty() const {
  return (tree_size == 0);
}

/*
 * size
 */
template <typename Type>
int SearchTree<Type>::size() const {
  return tree_size;
}

/*
 * height
 */
template <typename Type>
int SearchTree<Type>::height() const {
  return root_node->height();
}

/***************************************
*       Public Modifier Functions
****************************************/
/*
 * insert
 */
template <typename Type>
bool SearchTree<Type>::insert(Type const &obj) {
  if (empty()) {
    root_node = new SearchTree::SearchNode(obj);
    tree_size = 1;

    return true;
  } else if (root_node->insert(obj)) {
    ++tree_size;
    return true;
  } else {
    return false;
  }
}

/*
 * erase
 */
template <typename Type>
bool SearchTree<Type>::erase(Type const &obj) {
  return false;
}

/*
 * clear
 */
template <typename Type>
void SearchTree<Type>::clear() {

}

/***************************************
*         Public Misc. Functions
****************************************/
/*
 * print
 */
template <typename Type>
void SearchTree<Type>::print() {
  root_node->print(6*height());
}

/***********************************************/
/***************   SearchNode    ***************/
/***********************************************/
/***************************************
*           Constructors
****************************************/
/*
 * SearchNode Constructor
 */
template <typename Type>
SearchTree<Type>::SearchNode::SearchNode(Type const &obj):
node_value( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
tree_height( 0 )
{
  //  Empty Constructor
}

/***************************************
*        Public Size Functions
****************************************/
/*
 * height
 */
template <typename Type>
int SearchTree<Type>::SearchNode::height() const {
  return (this == nullptr) ? -1 : tree_height;
}

/***************************************
*       Public Modifier Functions
****************************************/
/*
 * insert
 */
template <typename Type>
bool SearchTree<Type>::SearchNode::insert(Type const &obj) {
  //  If the new object is less than the current value, attempt to insert into the left tree
  if (obj < node_value) {
    //  If there is no left tree, create a new node
    if (left_tree == nullptr) {
      left_tree = new SearchTree::SearchNode(obj);
      tree_height = max(left_tree->height(), right_tree->height()) + 1;

      return true;
    //  If there is a left tree, attempt to insert into it
    } else {
      if (left_tree->insert(obj)) {
        tree_height = max(left_tree->height(), right_tree->height()) + 1;

        return true;
      //  If the new object could not be inserted into the left tree, return false
      } else {
        return false;
      }
    }
  //  If the new object is greater than the current value, attempt to insert into the right tree
  } else if (obj > node_value) {
    //  If there is no right tree, create a new node
    if (right_tree == nullptr) {
      right_tree = new SearchTree::SearchNode(obj);
      tree_height = max(left_tree->height(), right_tree->height()) + 1;

      return true;
    //  If there is a right tree, attempt to insert into it
    } else if (right_tree->insert(obj)) {
      tree_height = max(left_tree->height(), right_tree->height()) + 1;

      return true;
    //  If the new object could not be inserted into the right tree, return false
    } else {
      return false;
    }

  //  If the object is equal to the current value, do nothing and return false
  } else {
    return false;
  }
}

/*
 * erase
 */
template <typename Type>
bool SearchTree<Type>::SearchNode::erase(Type const &obj) {
  return false;
}

/***************************************
*         Public Misc. Functions
****************************************/
/*
 * is_leaf
 */
template <typename Type>
bool SearchTree<Type>::SearchNode::is_leaf() const {
  return (left_tree == nullptr && right_tree == nullptr);
}

/*
 * print
 */
template <typename Type>
void SearchTree<Type>::SearchNode::print(int indent) {
  if (this != nullptr) {
    if (indent) {
      for (int i = 0; i < indent; ++i) {
        std::cout << " ";
      }
    }
    std::cout << node_value << "\n ";
    if (left_tree != nullptr) left_tree->print(indent-5);
    if (right_tree != nullptr) right_tree->print(indent+5);
  }
}

/*
 * max
 */
template <typename Type>
int SearchTree<Type>::SearchNode::max(int lhs, int rhs) const {
  return (lhs > rhs) ? lhs : rhs;
}

#endif
