#ifndef BST_H
#define BST_H

#include <iostream>
#include "Date.h"

using namespace std;

    /**
     * @class BST
	 * @brief My custom-made BST class
	 *
	 * @author Melvin Sim
	 * @version 01
	 * @date 14 November 2020
     *
     * @bug Hopefully this program has no bugs
	 */

template <class T>
struct Node
{
    T key;
    Node* left;
    Node* right;
};

template <class T>
class BST
{
    public:
        /**
		 * @brief A function pointer that is used in the print-traversing methods
		 *
         * @param &data
		 *
         * @return void
		 */
        typedef void (*functionPtr)(T &data);

        /**
         * @brief Default constructor
         *
         * Constructs a BST
         */
        BST();

        /**
         * @brief Copy constructor
         *
         * @param &tree
         *
         * Constructs a copy of a BST from another BST
         */
        BST(const BST &tree);

        /**
         * @brief Destructor
         *
         * Destroys the BST when the function ends
         */
        ~BST();

        /**
		 * @brief Returns the smallest value in the BST
		 *
         * @return T
		 */
        T SmallestValue();

        /**
		 * @brief Returns the largest value in the BST
		 *
         * @return T
		 */
        T LargestValue();

        /**
		 * @brief Inserts a node
		 *
         * @param data
		 *
         * @return void
		 */
        void Insert(T data);

        /**
		 * @brief Removes a node
		 *
         * @param data
		 *
         * @return void
		 */
        void Remove(T data);

        /**
		 * @brief Searches for data in the BST
		 *
         * @param data
		 *
         * @return bool
		 */
        bool Search(T data);

        /**
		 * @brief Prints the BST in ascending order
		 *
         * @param processNode
		 *
         * @return void
		 */
        void PrintInOrder(functionPtr processNode);

        /**
		 * @brief Prints the BST in pre-order
		 *
         * @param processNode
		 *
         * @return void
		 */
        void PrintPreOrder(functionPtr processNode);

        /**
		 * @brief Prints the BST in post-order
		 *
         * @param processNode
		 *
         * @return void
		 */
        void PrintPostOrder(functionPtr processNode);

        /**
		 * @brief Adds the value of all nodes
		 *
         * @param processNode
		 *
         * @return void
		 */
        void AddAllNodes(functionPtr processNode);

    private:
        /**
         * @brief A pointer to the root of the BST
         */
        Node<T>* m_root;

        /**
		 * @brief Copies the data from a BST to another BST
		 *
         * @param node
		 *
         * @return Node<T>*
		 */
        Node<T>* Copy(Node<T>* node);

        /**
		 * @brief Clears the BST in post-order traversal
		 *
         * @param node
		 *
         * @return Node<T>*
		 */
        Node<T>* Clear(Node<T>* node);

        /**
		 * @brief Creates a new node and inserts the data
		 *
         * @param data
		 *
         * @return Node<T>*
		 */
        Node<T>* NewNode(T data);

        /**
		 * @brief Returns the node containing the smallest value in the BST
		 *
         * @param node
		 *
         * @return Node<T>*
		 */
        Node<T>* SmallestValuePrivate(Node<T>* node);

        /**
		 * @brief Returns the node containing the largest value in the BST
		 *
         * @param node
		 *
         * @return Node<T>*
		 */
        Node<T>* LargestValuePrivate(Node<T>* node);

        /**
		 * @brief Inserts a node
		 *
         * @param node
         * @param data
		 *
         * @return Node<T>*
		 */
        Node<T>* InsertPrivate(Node<T>* node, T data);

        /**
		 * @brief Removes a node
		 *
         * @param node
         * @param data
		 *
         * @return Node<T>*
		 */
        Node<T>* RemovePrivate(Node<T>* node, T data);

        /**
		 * @brief Searches for data in the BST
		 *
         * @param node
         * @param data
		 *
         * @return bool
		 */
        bool SearchPrivate(Node<T>* node, T data);

        /**
		 * @brief Prints the BST in ascending order
		 *
         * @param node
         * @param processNode
		 *
         * @return void
		 */
        void PrintInOrderPrivate(Node<T>* node, functionPtr processNode);

        /**
		 * @brief Prints the BST in pre-order. Pre-order traversal is used to create a copy of the BST
		 *
         * @param node
         * @param processNode
		 *
         * @return void
		 */
        void PrintPreOrderPrivate(Node<T>* node, functionPtr processNode);

        /**
		 * @brief Prints the BST in post-order. Post-order traversal is used to delete the BST
		 *
         * @param node
         * @param processNode
		 *
         * @return void
		 */
        void PrintPostOrderPrivate(Node<T>* node, functionPtr processNode);
};

template <class T>
BST<T>::BST()
{
    m_root = NULL;
}

template <class T>
BST<T>::BST(const BST &tree)
{
    m_root = Copy(tree.m_root);
}

template <class T>
Node<T>* BST<T>::Copy(Node<T>* node)
{
    Node<T>* temp = new Node<T>;
    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        temp->key = node->key;
        temp->left = Copy(node->left);
        temp->right = Copy(node->right);
    }
    return temp;
}

template <class T>
BST<T>::~BST()
{
    m_root = Clear(m_root);
}

template <class T>
Node<T>* BST<T>::Clear(Node<T>* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
    return NULL;
}

template <class T>
Node<T>* BST<T>::NewNode(T data)
{
    Node<T>* temp = new Node<T>;
    temp->key = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

template <class T>
T BST<T>::SmallestValue()
{
    Node<T>* temp = SmallestValuePrivate(m_root);
    return temp->key;
}

template <class T>
Node<T>* BST<T>::SmallestValuePrivate(Node<T>* node)
{
    if(node == NULL)
    {
        cout << "The tree is empty, unable to find the smallest value!" << endl;
        return NULL;
    }
    else if(node->left == NULL)
    {
        return node;
    }
    else
    {
        return SmallestValuePrivate(node->left); //Traverse left recursively until node->left == NULL
    }
}

template <class T>
T BST<T>::LargestValue()
{
    Node<T>* temp = LargestValuePrivate(m_root);
    return temp->key;
}

template <class T>
Node<T>* BST<T>::LargestValuePrivate(Node<T>* node)
{
    if(node == NULL)
    {
        cout << "The tree is empty, unable to find the largest value!" << endl;
        return NULL;
    }
    else if(node->right == NULL)
    {
        return node;
    }
    else
    {
        return LargestValuePrivate(node->right); //Traverse right recursively until node->right == NULL
    }
}

template <class T>
void BST<T>::Insert(T data)
{
    m_root = InsertPrivate(m_root, data);
}

template <class T>
Node<T>* BST<T>::InsertPrivate(Node<T>* node, T data)
{
    //If tree is empty, create a new node and insert the data
    if(node == NULL)
    {
        node = new Node<T>;
        node->key = data;
        node->left = NULL;
        node->right = NULL;
    }
    //If tree is not empty
    //Traverse left
    else if(data < node->key)
    {
        node->left = InsertPrivate(node->left, data);
    }
    //Traverse right
    else //if(data >= node->key)
    {
        node->right = InsertPrivate(node->right, data);
    }
    return node;
}

template <class T>
void BST<T>::Remove(T data)
{
    m_root = RemovePrivate(m_root, data);
}

template <class T>
Node<T>* BST<T>::RemovePrivate(Node<T>* node, T data)
{
    Node<T>* temp;
    if(node == NULL)
    {
        cout << "The tree is empty, nothing to delete!" << endl;
        return NULL;
    }
    //Traverse left
    else if(data < node->key)
    {
        node->left = RemovePrivate(node->left, data);
    }
    //Traverse right
    else if(data > node->key)
    {
        node->right = RemovePrivate(node->right, data);
    }
    //Node to be deleted has two children
    else if(node->left && node->right)
    {
        temp = SmallestValuePrivate(node->right);
        node->key = temp->key; //Overwrite the key in the parent node with the smallest value
        node->right = RemovePrivate(node->right, node->key); //Delete smallest value from the right subtree
    }
    //Node to be deleted has only one child
    else
    {
        temp = node;
        if(node->left == NULL) //If only have right child
        {
            node = node->right; //Overwrite the key in the parent node with the value of the right child
        }
        else if(node->right == NULL) //If only have left child
        {
            node = node->left; //Overwrite the key in the parent node with the value of the left child
        }
        delete temp;
    }
    return node;
}

template <class T>
bool BST<T>::Search(T data)
{
    return SearchPrivate(m_root, data);
}

//Using depth first search
template <class T>
bool BST<T>::SearchPrivate(Node<T>* node, T data)
{
    if(node == NULL)
    {
        return false;
    }
    else if(data == node->key)
    {
        return true;
    }
    else if(data < node->key)
    {
        return SearchPrivate(node->left, data);
    }
    else //If data > node->key
    {
        return SearchPrivate(node->right, data);
    }
}

template <class T>
void BST<T>::PrintInOrder(functionPtr processNode)
{
    PrintInOrderPrivate(m_root, processNode);
    cout << endl;
}

//Left subtree is visited first, then the root, then the right subtree
template <class T>
void BST<T>::PrintInOrderPrivate(Node<T>* node, functionPtr processNode)
{
    if(node != NULL)
    {
        if(node->left != NULL)
        {
            PrintInOrderPrivate(node->left, processNode);
        }
        processNode(node->key); //Uses the functionPtr to call another function here
        if(node->right != NULL)
        {
            PrintInOrderPrivate(node->right, processNode);
        }
    }
    else
    {
        cout << "The tree is empty!";
    }
}

template <class T>
void BST<T>::PrintPreOrder(functionPtr processNode)
{
    PrintPreOrderPrivate(m_root, processNode);
    cout << endl;
}

//Root node is visited first, then the left subtree, then the right subtree
template <class T>
void BST<T>::PrintPreOrderPrivate(Node<T>* node, functionPtr processNode)
{
    if(node != NULL)
    {
        processNode(node->key);
        if(node->left != NULL)
        {
            PrintPreOrderPrivate(node->left, processNode);
        }
        if(node->right != NULL)
        {
            PrintPreOrderPrivate(node->right, processNode);
        }
    }
    else
    {
        cout << "The tree is empty!";
    }
}

template <class T>
void BST<T>::PrintPostOrder(functionPtr processNode)
{
    PrintPostOrderPrivate(m_root, processNode);
    cout << endl;
}

//Left subtree is visited first, then the right subtree, then the root node
template <class T>
void BST<T>::PrintPostOrderPrivate(Node<T>* node, functionPtr processNode)
{
    if(node != NULL)
    {
        if(node->left != NULL)
        {
            PrintPostOrderPrivate(node->left, processNode);
        }
        if(node->right != NULL)
        {
            PrintPostOrderPrivate(node->right, processNode);
        }
        processNode(node->key);
    }
    else
    {
        cout << "The tree is empty!";
    }
}

//This should not be part of the BST minimal class but it is included in order to find the sum of all nodes
//I can actually use one of the Print Traversal methods but I decided not to because I do not want the cout << endl to be there
template <class T>
void BST<T>::AddAllNodes(functionPtr processNode)
{
    PrintPostOrderPrivate(m_root, processNode);
}

#endif // BST_H
