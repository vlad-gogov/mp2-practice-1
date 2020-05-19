#ifndef _TBINARYTREE_H_
#define _TBINARYTREE_H_
#include "../include/TNode.h"
#include <stack>

template <typename TData>
class TBinaryTree
{
protected:
	TNode<TData>* pRoot;
public:
	TBinaryTree();
	TBinaryTree(int, TData*);
	~TBinaryTree();

	TNode<TData>* search(const int key_) const;
	TNode<TData>* searchMax(TNode<TData>* root) const;
	TNode<TData>* searchMin(TNode<TData>* root) const;
	TNode<TData>* searchNext(TNode<TData>* pTnode) const;
	TNode<TData>* searchPrev(TNode<TData>* pTnode) const;
	void insert(TNode<TData>*);
	void remove(TNode<TData>* node);
};

template <typename TData>
TBinaryTree<TData>::TBinaryTree()
{
	pRoot = nullptr;
}

template <typename TData>
TBinaryTree<TData>::TBinaryTree(int key_, TData* pData_)
{
	pRoot = new TNode<TData>(key_, pData_);
}

template <typename TData>
TBinaryTree<TData>::~TBinaryTree()
{
	if (pRoot)
	{
		std::stack<TNode<TData>*> stack1, stack2;
		stack2.push(pRoot);

		while (!stack2.empty())
		{
			TNode<TData>* node = stack2.top();
			stack2.pop();

			if (!node->pLeft)
				stack2.push(node->pLeft);
			if (!node->pRight)
				stack2.push(node->pRight);

			stack1.push(node);
		}

		while (!stack1.empty())
		{
			TNode<TData>* node = stack1.top();
			stack1.pop();
			delete node;
		}

		pRoot = nullptr;
	}
}

template <typename TData>
TNode<TData>* TBinaryTree<TData>::search(const int key_)  const
{
	TNode<TData>* current = pRoot;
	while ((current != nullptr) && (current->key != key_))
	{
		if (key_ < current->key)
			current = current->pLeft;
		else
			current = current->pRight;
	}
	return current;
}

template <typename TData>
TNode<TData>* TBinaryTree<TData>::searchMax(TNode<TData>* root)  const
{
	TNode<TData>* current = root;
	while (current->pRight != nullptr)
		current = current->pRight;
	return current;
}

template <typename TData>
TNode<TData>* TBinaryTree<TData>::searchMin(TNode<TData>* root) const
{
	TNode<TData>* current = root;
	while (current->pLeft != nullptr)
		current = current->pLeft;
	return current;
}

template <typename TData>
TNode<TData>* TBinaryTree<TData>::searchNext(TNode<TData>* pTNode) const
{
	TNode<TData>* result = nullptr;
	if (pTNode->pRigt != nullptr)
	{
		result = searchMin(pTNode);
		return result;
	}
	result = pTNode->pParent;
	TNode<TData>* temp = TNode;
	while ((result != nullptr) && (temp == result->pRight))
	{
		temp = result;
		result = result->pParent;
	}
	return result;
}

template <typename TData>
TNode<TData>* TBinaryTree<TData>::searchPrev(TNode<TData>* pTNode) const
{
	TNode<TData>* result = nullptr;
	if (pTNode->pLeft != nullptr)
	{
		result = searchMax(pTNode);
		return result;
	}
	result = pTNode->pParent;
	TNode<TData>* temp = TNode;
	while ((result != nullptr) && (temp == result->pLeft))
	{
		temp = result;
		result = result->pParent;
	}
	return result;
}

template <typename TData>
void TBinaryTree<TData>::insert(TNode<TData>* node)
{
	if (pRoot == nullptr)
	{
		pRoot = node;
		return;
	}
	TNode<TData>* x = pRoot, *y;
	while(x != nullptr)
	{
		y = x;
		if (node->key < x->key)
			x = x->pLeft;
		else
			x = x->pRight;
	}
	node->pParent = y;
	if (node->key < y->key)
		y->pLeft = node;
	else
		y->pRight = node;
}

template <typename TData>
void TBinaryTree<TData>::remove(TNode<TData>* z)
{
	TNode<TData>* y = nullptr, * x = nullptr;
	if (!(z->pLeft) && !(z->pRight))
		y = searchNext(z);
	else
		y = z;
	if (!y)
		x = y->pLeft;
	else
		x = y->pRight;
	if (!x)
		x->pParanet = y->pParanet;
	if (!(y->pParent))
	{
		if (y == y->pParent->pLeft)
			y->pParent->pLeft = x;
		else
			y->pParent->pRight = x;
	}
	if (y != z)
	{
		z->key = y->key;
		delete z->pData;
		z->pData = y->pData;
	}
}
#endif //!_TBINARYTREE_H_
