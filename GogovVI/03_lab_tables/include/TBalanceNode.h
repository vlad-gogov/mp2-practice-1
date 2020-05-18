#ifndef _BALANCETNODE_H_
#define _BALANCETNODE_H_
#include "../include/TNode.h"

template <typename TData>
class TBalanceNode : protected TNode<TData>
{
private:
	int balance;
public:
	TBalanceNode();
	TBalanceNode(int key_, TData* pData_, int balance_);
	~TBalanceNode();

	int GetBalance();
	void SetBalance(int balance_);
};

template <typename TData>
TBalanceNode<TData>::TBalanceNode() : TNode<TData>() {}

template <typename TData>
TBalanceNode<TData>::TBalanceNode(int key_, TData* pData_, int balance_) : TNode<TData>(key_, pData_), balance(balance_) {}

template <typename TData>
TBalanceNode<TData>::~TBalanceNode() 
{
	if (this->pLeft)
		delete this->pLeft;
	if (this->pRight)
		delete this->pRight;
	if (this->pParent)
		delete this->pParent;
	if (this->pData)
		delete this->pData;
}

template <typename TData>
int TBalanceNode<TData>::GetBalance()
{
	return balance;
}

template <typename TData>
void TBalanceNode<TData>::SetBalance(int balance_)
{
	balance = balance_;
}

#endif //!_BALANCETNODE_H_
