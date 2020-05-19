#ifndef _TNODE_H_
#define _TNODE_H_
#include <iostream>
#include "../include/TTabRecord.h"
template <typename TKey,typename TData>
class TNode : protected TTabRecord<TKey, TData>
{
protected:
	int key;
	TNode* pLeft;
	TNode* pRight;
	TNode* pParent;
public:
	TNode();
	TNode(int, TData*);
	TNode(const TNode<TKey, TData>& temp);
	~TNode();
	TNode* GetLeft();
	TNode* GetRight();
	TNode* GetParent();
	int GetKey();

	friend std::ostream& operator<<(std::ostream& out, const TTabRecord<TKey, TData>& temp)
	{
		out << "Key: " << temp.key << "\t Data: " << *(temp.pData);
		return out;
	}
};

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode() : TTabRecord<TKey, TData>(), pParent(nullptr), pLeft(nullptr), pRight(nullptr) {}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(int key_, TData* pData_) : TTabRecord<TKey, TData>(key_, pData_),  pLeft(nullptr), pRight(nullptr), pParent(nullptr) {}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& temp) : TTabRecord<TKey, TData>(temp.key, temp.pData), pLeft(nullptr), pRight(nullptr), pParent(nullptr) {}

template <typename TKey, typename TData>
TNode<TKey, TData>::~TNode() 
{
	if (pLeft)
		delete pLeft;
	if (pRight)
		delete pRight;
	if (pParent)
		delete pParent;
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TNode<TKey, TData>::GetLeft()
{
	return pLeft;
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TNode<TKey, TData>::GetRight()
{
	return pRight;
}

template <typename TKey, typename TData>
TNode<TKey, TData>* TNode<TKey, TData>::GetParent()
{
	return pParent;
}

template <typename TKey, typename TData>
int TNode<TKey, TData>::GetKey()
{
	return key;
}
#endif //!_TNODE_H_