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

	void insert(TNode<TKey, TData>* node);
	void remove(TNode<TKey, TData>* node);
public:
	TBinaryTreeTable();
	TBinaryTreeTable(int key_, TData* pData_);
	~TBinaryTreeTable();

	TNode<TKey, TData>* search(const int key_) const;
	TNode<TKey, TData>* searchMax(TNode<TKey, TData>* root) const;
	TNode<TKey, TData>* searchMin(TNode<TKey, TData>* root) const;
	TNode<TKey, TData>* searchNext(TNode<TKey, TData>* pTnode) const;
	TNode<TKey, TData>* searchPrev(TNode<TKey, TData>* pTnode) const;

	virtual TTabRecord<TKey, TData>* FindRecord(TKey key);
	virtual void InsertRecord(TKey key, TData* data);
	virtual void RemoveRecord(const TKey key);

	virtual bool Reset();
	virtual bool GetNext();
	virtual bool IsTabEnded() const;
	virtual bool IsFull() const;

	virtual TTabRecord<TKey, TData>* GetRecord() const;
	virtual TKey GetKey() const;
	virtual TData* GetData() const;
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

template <typename TKey, typename TData>
TTabRecord<TKey, TData>* TBinaryTreeTable<TKey, TData>::FindRecord(TKey key)
{
	return search(key);
}

template <typename TKey, typename TData>
void TBinaryTreeTable<TKey, TData>::InsertRecord(TKey key, TData* data)
{
	if (this->IsFull())
		throw "Binary Tree Table is full.\n";
	TNode<TKey, TData>* newTNode = new TNode<TKey, TData>(key, data);
	insert(newTNode);
	this->dataCount++;
}

template <typename TKey, typename TData>
void TBinaryTreeTable<TKey, TData>::RemoveRecord(const TKey key)
{
	if (this->IsEmpty())
		throw "Binary Tree Table is empty.\n";
	TNode<TKey, TData>* newTNode = search(key);
	remove(newTNode);
	this->dataCount--;
}

template <typename TKey, typename TData>
TTabRecord<TKey,TData>* TBinaryTreeTable<TKey, TData>::GetRecord() const
{
	return pCurrent;
}

template <typename TKey, typename TData>
TKey TBinaryTreeTable<TKey, TData>::GetKey() const
{
	return pCurrent->GetKey();
}

template <typename TKey, typename TData>
TData* TBinaryTreeTable<TKey, TData>::GetData() const
{
	return pCurrent->GetData();
}

template <typename TKey, typename TData>
bool TBinaryTreeTable<TKey, TData>::Reset()
{
	pCurrent = pRoot;
	this->currPos = 0;
	return IsTabEnded();
}

template <typename TKey, typename TData>
bool TBinaryTreeTable<TKey, TData>::GetNext()
{
	if (!this->IsTabEnded())
	{
			TTabRecord<TKey, TData>* node = searchNext(pCurrent);
			pCurrent = node;
			this->currPoss++;
	}
	return IsTabEnded();
}

template <typename TKey, typename TData>
bool TBinaryTreeTable<TKey, TData>::IsTabEnded() const
{
	return this->currPos >= this->dataCount;
}

template <typename TKey, typename TData>
bool TBinaryTreeTable<TKey, TData>::IsFull() const
{
	TTabRecord<TKey, TData>* node = new TTabRecord<TKey, TData>;
	if (node)
	{
		delete node;
		return false;
	}
	return true;
}
#endif //!_TBINARYTREE_H_
