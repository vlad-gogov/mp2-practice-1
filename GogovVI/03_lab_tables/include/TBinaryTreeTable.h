#ifndef _TBINARYTREETABLE_H_
#define _TBINARYTREETABLE_H_
#include "../include/TNode.h"
#include "../include/TTable.h"
#include <stack>

template <typename TKey, typename TData>
class TBinaryTreeTable
{
protected:
	TNode<TKey, TData>* pRoot;
	TNode<TKey, TData>* pCurrent;

public:
	TBinaryTreeTable();
	TBinaryTreeTable(int key_, TData* pData_);
	~TBinaryTreeTable();

	TNode<TKey, TData>* search(const int key_) const;
	TNode<TKey, TData>* searchMax(TNode<TKey, TData>* root) const;
	TNode<TKey, TData>* searchMin(TNode<TKey, TData>* root) const;
	TNode<TKey, TData>* searchNext(TNode<TKey, TData>* pTnode) const;
	TNode<TKey, TData>* searchPrev(TNode<TKey, TData>* pTnode) const;
	void insert(TNode<TKey, TData>*);
	void remove(TNode<TKey, TData>* node);


};

template <typename TKey, typename TData>
TBinaryTreeTable<TKey, TData>::TBinaryTreeTable()
{
	pRoot = nullptr;
}

template <typename TKey, typename TData>
TBinaryTreeTable<TKey, TData>::TBinaryTreeTable(int key_, TData* pData_)
{
	pRoot = new TNode<TKey, TData>(key_, pData_);
}

template <typename TKey, typename TData>
TBinaryTreeTable<TKey, TData>::~TBinaryTreeTable()
{
	if (pRoot)
	{
		std::stack<TNode<TKey, TData>*> stack1, stack2;
		stack2.push(pRoot);

		while (!stack2.empty())
		{
			TNode<TKey, TData>* node = stack2.top();
			stack2.pop();

			if (!node->pLeft)
				stack2.push(node->pLeft);
			if (!node->pRight)
				stack2.push(node->pRight);

			stack1.push(node);
		}

		while (!stack1.empty())
		{
			TNode<TKey, TData>* node = stack1.top();
			stack1.pop();
			delete node;
		}

		pRoot = nullptr;
	}
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTreeTable<TKey, TData>::search(const int key_)  const
{
	TNode<TKey, TData>* current = pRoot;
	while ((current != nullptr) && (current->key != key_))
	{
		if (key_ < current->key)
			current = current->pLeft;
		else
			current = current->pRight;
	}
	return current;
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTreeTable<TKey, TData>::searchMax(TNode<TKey, TData>* root)  const
{
	TNode<TKey, TData>* current = root;
	while (current->pRight != nullptr)
		current = current->pRight;
	return current;
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTreeTable<TKey, TData>::searchMin(TNode<TKey, TData>* root) const
{
	TNode<TKey, TData>* current = root;
	while (current->pLeft != nullptr)
		current = current->pLeft;
	return current;
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTreeTable<TKey, TData>::searchNext(TNode<TKey, TData>* pTNode) const
{
	TNode<TKey, TData>* result = nullptr;
	if (pTNode->pRigt != nullptr)
	{
		result = searchMin(pTNode);
		return result;
	}
	result = pTNode->pParent;
	TNode<TKey, TData>* temp = TNode;
	while ((result != nullptr) && (temp == result->pRight))
	{
		temp = result;
		result = result->pParent;
	}
	return result;
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTreeTable<TKey, TData>::searchPrev(TNode<TKey, TData>* pTNode) const
{
	TNode<TKey, TData>* result = nullptr;
	if (pTNode->pLeft != nullptr)
	{
		result = searchMax(pTNode);
		return result;
	}
	result = pTNode->pParent;
	TNode<TKey, TData>* temp = TNode;
	while ((result != nullptr) && (temp == result->pLeft))
	{
		temp = result;
		result = result->pParent;
	}
	return result;
}

template <typename TKey, typename TData>
void TBinaryTreeTable<TKey, TData>::insert(TNode<TKey, TData>* node)
{
	if (pRoot == nullptr)
	{
		pRoot = node;
		return;
	}
	TNode<TKey, TData>* x = pRoot, *y;
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

template <typename TKey, typename TData>
void TBinaryTreeTable<TKey, TData>::remove(TNode<TKey, TData>* z)
{
	TNode<TKey, TData>* y = nullptr, * x = nullptr;
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
