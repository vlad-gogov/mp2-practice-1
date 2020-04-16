#ifndef _BALANCETNODE_H_
#define _BALANCETNODE_H_
#include "../include/TNode.h"

template <typename TData>
class BalanceTNode : protected TNode<TData>
{
private:
	int balance;
public:
	BalanceTNode();
	BalanceTNode(int key_, TData* pData_, int balance_);
	~BalanceTNode();

	int GetBalance();
	void SetBalance(int balance_);
};

template <typename TData>
BalanceTNode<TData>::BalanceTNode() : TNode<TData>(), balance(NULL) {}

template <typename TData>
BalanceTNode<TData>::BalanceTNode(int key_, TData* pData_, int balance_) : TNode<TData>(key_, pData_), balance(balance_) {}

template <typename TData>
BalanceTNode<TData>::~BalanceTNode() 
{
	if (pLeft)
		delete pLeft;
	if (pRight)
		delete pRight;
	if (pParent)
		delete pParent;
	if (pData)
		delete pData;
}

template <typename TData>
int BalanceTNode<TData>::GetBalance()
{
	return balance;
}

template <typename TData>
void BalanceTNode<TData>::SetBalance(int balance_)
{
	balance = balance_;
}

#endif //!_BALANCETNODE_H_
