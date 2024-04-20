#pragma once
#include<utility>
#include<iostream>
#include<vector>  //used for constructing the tree from an initialization vector

template <typename KeyType, typename ValueType>
class RBT
{
	struct TreeNode
	{
		std::pair<KeyType, ValueType> KeyValuePair;
		bool isRed;
		TreeNode* leftNode;
		TreeNode* rightNode;
		TreeNode* parentNode;

		TreeNode(const std::pair<KeyType, ValueType>& KeyValue = std::make_pair(KeyType(), ValueType()), bool red = true, TreeNode* left = nullptr, TreeNode* right = nullptr, TreeNode* parent = nullptr)
			: KeyValuePair(KeyValue), isRed(red), leftNode(left), rightNode(right), parentNode(parent) {}
	};

	TreeNode* root;
	TreeNode* sentinelNode;

	void RotateLeft(TreeNode* node)
	{
		TreeNode* rightChild = node->rightNode;

		node->rightNode = rightChild->leftNode;

		if (rightChild->leftNode != sentinelNode)
			rightChild->leftNode->parentNode = node;

		rightChild->parentNode = node->parentNode;

		if (node->parentNode == sentinelNode)
		{
			root = rightChild;
			root->parentNode = sentinelNode;
		}
		else
		{
			if (node == node->parentNode->leftNode)  //if the node is on the left of the parent
				node->parentNode->leftNode = rightChild;  //the right child of the node takes the node's place
			else                                    //if the node is on the right of the parent
				node->parentNode->rightNode = rightChild; //the right child of the node takes the node's place
		}
		rightChild->leftNode = node;
		node->parentNode = rightChild;
	}

	void RotateRight(TreeNode* node)
	{
		TreeNode* leftChild = node->leftNode;

		node->leftNode = leftChild->rightNode;

		if (leftChild->rightNode != sentinelNode)
			leftChild->rightNode->parentNode = node;

		leftChild->parentNode = node->parentNode;

		if (node->parentNode == sentinelNode)
		{
			root = leftChild;
			root->parentNode = sentinelNode;
		}
		else
		{
			if (node == node->parentNode->rightNode)
				node->parentNode->rightNode = leftChild;
			else
				node->parentNode->leftNode = leftChild;
		}
		leftChild->rightNode = node;
		node->parentNode = leftChild;
	}

	void InsertRepair(TreeNode* node) //the function takes the node that was inserted as a parameter and if it is needed rebalances the tree
	{
		if (node == root)
		{
			node->isRed = false;
			return;
		}
		if (node->parentNode == sentinelNode || node->parentNode->parentNode == sentinelNode)
		{
			node->parentNode->isRed = false; // the parent becomes black if the grandparent is sentinelNode because it means the parent is the root
			return;
		}

		if (node->parentNode->isRed != true) // if the parent is black,the tree is still balanced
			return;

		TreeNode* uncle;
		TreeNode* parent = node->parentNode;
		TreeNode* grandparent = parent->parentNode;
		if (grandparent->leftNode == parent) //if the parent is on the left of the grandparent,the uncle is on the right of the grandparent
			uncle = grandparent->rightNode;
		else  //if the parent is on the right of the grandparent,the uncle is on the left of the grandparent
			uncle = grandparent->leftNode;

		if (node->isRed && parent->isRed && uncle->isRed)  //if the parent and the uncle are red,then the parent,the grandparent and the uncle are recolored and the process starts again at the grandparent
		{
			parent->isRed = false; //make the parent black
			uncle->isRed = false;  //make the uncle black
			grandparent->isRed = true; //make the grandparent red and recheck if the tree is balanced
			InsertRepair(grandparent);
		}
		else if (node->isRed && parent->isRed && !uncle->isRed)  //if the parent is red and the uncle is black
		{
			if (grandparent->rightNode == parent && parent->leftNode == node)
			{
				RotateRight(parent);
				InsertRepair(parent);
			}
			else if (grandparent->leftNode == parent && parent->rightNode == node)
			{
				RotateLeft(parent);
				InsertRepair(parent);
			}

			if (grandparent->rightNode == parent && parent->rightNode == node)
			{
				parent->isRed = false;
				grandparent->isRed = true;
				RotateLeft(grandparent);
				InsertRepair(parent);
			}
			else if (grandparent->leftNode == parent && parent->leftNode == node)
			{
				parent->isRed = false;
				grandparent->isRed = true;
				RotateRight(grandparent);
				InsertRepair(parent);
			}
		}
	}

	void EraseRepair(TreeNode* node)  //fixes the problems that can appear after erasing a node
	{
		while (node != root && !node->isRed)
		{
			if (node == node->parentNode->leftNode)  //if the node is on the left of the parent
			{
				TreeNode* sibling = node->parentNode->rightNode;
				if (sibling->isRed)  //case 1: the sibling is red
				{
					sibling->isRed = false;
					node->parentNode->isRed = true;
					RotateLeft(node->parentNode);
					sibling = node->parentNode->rightNode;
				}
				else if (!sibling->leftNode->isRed && !sibling->rightNode->isRed) //case 2: if the sibling and the sibling's children are all black
				{
					sibling->isRed = true;
					node = node->parentNode;
				}
				else
				{
					if (!sibling->rightNode->isRed)//case 3: if the sibling is black and the left child of the sibling is red and the right child of the sibling is black
					{
						sibling->leftNode->isRed = false;
						sibling->isRed = true;
						RotateRight(sibling);
					}
					else  //case 4: if the sibling is black and the right child of the sibling is red
					{
						sibling->isRed = node->parentNode->isRed;
						node->parentNode->isRed = false;
						sibling->rightNode->isRed = false;
						RotateLeft(node->parentNode);
						node = root;
					}
				}
			}
			else  //if the node is on the right of the parent,it is the same algorithm but simetrically,so right becomes left and left becomes right
			{
				TreeNode* sibling = node->parentNode->leftNode;
				if (sibling->isRed)  //case 1: the sibling is red
				{
					sibling->isRed = false;
					node->parentNode->isRed = true;
					RotateRight(node->parentNode);
					sibling = node->parentNode->leftNode;
				}
				else if (!sibling->rightNode->isRed && !sibling->leftNode->isRed) //case 2
				{
					sibling->isRed = true;
					node = node->parentNode;
				}
				else
				{
					if (!sibling->leftNode->isRed)//case 3
					{
						sibling->rightNode->isRed = false;
						sibling->isRed = true;
						RotateLeft(sibling);
					}
					else  //case 4
					{
						sibling->isRed = node->parentNode->isRed;
						node->parentNode->isRed = false;
						sibling->leftNode->isRed = false;
						RotateRight(node->parentNode);
						node = root;
					}
				}
			}
		}
		node->isRed = false; //case 0
	}

	void TransplantRBT(TreeNode* node1, TreeNode* node2)  //replaces node1 with node2
	{
		if (node1->parentNode == sentinelNode)
			root = node2;
		else
		{
			if (node1 == node1->parentNode->leftNode)
				node1->parentNode->leftNode = node2;
			else
				node1->parentNode->rightNode = node2;
		}
		node2->parentNode = node1->parentNode;
	}

	void clear(TreeNode* node)  //clears the tree using postOrder traversal,which is the most efficient way
	{
		if (node == nullptr || node == sentinelNode)
			return;

		clear(node->leftNode);

		clear(node->rightNode);

		delete node;
	}

	void displayPreOrder(TreeNode* node)
	{
		if (node != sentinelNode)
		{
			std::cout << "(" << node->KeyValuePair.first << "," << node->KeyValuePair.second << ")->";
			if (node->isRed)
				std::cout << "red ";
			else
				std::cout << "black ";
			displayPreOrder(node->leftNode);
			displayPreOrder(node->rightNode);
		}
	}

	void displayInOrder(TreeNode* node)
	{
		if (node != sentinelNode)
		{
			displayInOrder(node->leftNode);
			std::cout << "(" << node->KeyValuePair.first << "," << node->KeyValuePair.second << ")->";
			if (node->isRed)
				std::cout << "red ";
			else
				std::cout << "black ";
			displayInOrder(node->rightNode);
		}
	}

	void displayPostOrder(TreeNode* node)
	{
		if (node != sentinelNode)
		{
			displayPostOrder(node->leftNode);
			displayPostOrder(node->rightNode);
			std::cout << "(" << node->KeyValuePair.first << "," << node->KeyValuePair.second << ")->";
			if (node->isRed)
				std::cout << "red ";
			else
				std::cout << "black ";
		}
	}

public:
	RBT()  //constructor with no parameters
	{
		sentinelNode = new TreeNode(std::make_pair(KeyType(), ValueType()), false, nullptr, nullptr, nullptr);
		root = sentinelNode;
	}

	RBT(const std::vector<std::pair<KeyType, ValueType>>& vector)  //constructor using a vector
	{
		clear(root);
		delete sentinelNode;

		sentinelNode = new TreeNode(std::make_pair(KeyType(), ValueType()), false, nullptr, nullptr, nullptr);
		root = sentinelNode;

		for (const std::pair<KeyType, ValueType>& pair : vector)
			insert(pair);
	}

	~RBT()
	{
		clear();
		delete sentinelNode;
	}

	void insert(const std::pair<KeyType, ValueType>& KeyValue)
	{
		if (root == sentinelNode)  //if the tree is empty,the keyvalue pair inserted becomes the root
		{
			TreeNode* node = new TreeNode();
			node->KeyValuePair = KeyValue;
			node->isRed = false;
			node->rightNode = sentinelNode;
			node->leftNode = sentinelNode;
			node->parentNode = sentinelNode;
			root = node;
			return;
		}

		TreeNode* node = root;
		while (node != sentinelNode)  //searches the tree for the right spot to insert the KeyValue
		{
			if (KeyValue.first == node->KeyValuePair.first)  //if the key already exists,the value is updated
			{
				node->KeyValuePair.second = KeyValue.second;
				break;
			}

			if (KeyValue.first > node->KeyValuePair.first)  //if the key inserted is higher than the node key,it will be inserted in the right subtree
			{
				if (node->rightNode == sentinelNode)  //if the right child of the current node is the sentinelNode,then the new node will be inserted as the right child of the current node
				{
					TreeNode* newNode = new TreeNode;
					newNode->KeyValuePair = KeyValue;
					newNode->parentNode = node;
					newNode->leftNode = sentinelNode;
					newNode->rightNode = sentinelNode;
					node->rightNode = newNode;
					InsertRepair(newNode); //the function takes the node that was inserted as a parameter and if it is needed rebalances the tree
					break;
				}
				else  //if the node doesn't reach the sentinelNode,then it keeps searching for the correct spot to insert the value in the right subtree
					node = node->rightNode;
			}
			else  //if the key inserted is lower than the node key,it will be inserted in the left subtree
			{
				if (node->leftNode == sentinelNode)  //if the left child of the current node is the sentinelNode,then the new node will be inserted as the left child of the current node
				{
					TreeNode* newNode = new TreeNode;
					newNode->KeyValuePair = KeyValue;
					newNode->parentNode = node;
					newNode->leftNode = sentinelNode;
					newNode->rightNode = sentinelNode;
					node->leftNode = newNode;
					InsertRepair(newNode); //the function takes the node that was inserted as a parameter and if it is needed rebalances the tree
					break;
				}
				else  //if the node doesn't reach the sentinelNode,then it keeps searching for the correct spot to insert the value in the left subtree
					node = node->leftNode;
			}
		}
	}

	TreeNode* max(TreeNode* node)  //returns a pointer to the node with the maximum key from the subtree rooted in the parameter node
	{
		if (node == sentinelNode)
			return nullptr;

		while (node->rightNode != sentinelNode)
			node = node->rightNode;
		return node;
	}

	TreeNode* min(TreeNode* node)
	{
		if (node == sentinelNode)
			return nullptr;

		while (node->leftNode != sentinelNode)
			node = node->leftNode;

		return node;
	}

	TreeNode* successor(TreeNode* node)  //returns a pointer to the successor of the node
	{
		if (node->rightNode != sentinelNode)  //if the node has a right child,the successor is the minimum from the right subtree
			return min(node->rightNode);
		else  //if the node doesn't have a right child,the successor is the first parent node that has contains the node in the left subtree
		{
			while (node != sentinelNode)
			{
				if (node->parentNode->leftNode == node)
					return node->parentNode;
				node = node->parentNode;
			}
			return nullptr;
		}
	}

	TreeNode* predecessor(TreeNode* node)  //returns a pointer to the predecessor of the node
	{
		if (node->leftNode != sentinelNode)  //if the node has a left child,the predecessor is the maximum from the left subtree
			return max(node->leftNode);
		else   //if the node doesn't have a left child,the predecessor is the first parent node that has contains the node in the right subtree
		{
			while (node != sentinelNode)
			{
				if (node->parentNode->rightNode == node)
					return node->parentNode;
				node = node->parentNode;
			}
			return nullptr;
		}
	}

	TreeNode* find(const KeyType& keySearch)
	{
		TreeNode* node = root;
		while (node != sentinelNode)
		{
			if (keySearch == node->KeyValuePair.first)
				return node;

			if (keySearch > node->KeyValuePair.first)  //if the value is higher than the node key,it will search in the right subtree
			{
				if (node == sentinelNode)
					return nullptr;
				else  //if the node is not the sentinelNode,then it keeps searching in the right subtree
					node = node->rightNode;
			}
			else  //if the value is lower than the node key,it will search in the left subtree
			{
				if (node == sentinelNode)
					return nullptr;
				else  //if the node is not a leaf node,then it keeps searching in the left subtree
					node = node->leftNode;
			}
		}
		return nullptr;
	}

	void erase(TreeNode* nodeDeleted)
	{
		if (nodeDeleted == sentinelNode)
			return;

		bool isRed = nodeDeleted->isRed;
		TreeNode* node;

		if (nodeDeleted->leftNode == sentinelNode)
		{
			node = nodeDeleted->rightNode;
			TransplantRBT(nodeDeleted, node);
		}
		else
		{
			if (nodeDeleted->rightNode == sentinelNode)
			{
				node = nodeDeleted->leftNode;
				TransplantRBT(nodeDeleted, node);
			}
			else
			{
				TreeNode* successorNode = successor(nodeDeleted);
				isRed = successorNode->isRed;
				node = successorNode->rightNode;
				if (successorNode->parentNode == nodeDeleted)
					node->parentNode = successorNode;
				else
				{
					TransplantRBT(successorNode, node);
					successorNode->rightNode = nodeDeleted->rightNode;
					nodeDeleted->rightNode->parentNode = successorNode;
				}
				TransplantRBT(nodeDeleted, successorNode);
				successorNode->leftNode = nodeDeleted->leftNode;
				nodeDeleted->leftNode->parentNode = successorNode;
				successorNode->isRed = nodeDeleted->isRed;
			}
		}
		if (!isRed)
			EraseRepair(node);
	}

	void deleteKey(const KeyType& keyDeleted)
	{
		TreeNode* nodeDeleted = find(keyDeleted);

		if (nodeDeleted)  //if the key is found,the node with that key is erased,otherwise nothing happens
			erase(nodeDeleted);
	}

	void clear()
	{
		clear(root);
		root = sentinelNode;
	}

	bool empty()
	{
		return root == sentinelNode;
	}

	void displayPreOrder()
	{
		displayPreOrder(root);
	}

	void displayInOrder()
	{
		displayInOrder(root);
	}

	void displayPostOrder()
	{
		displayPostOrder(root);
	}
};