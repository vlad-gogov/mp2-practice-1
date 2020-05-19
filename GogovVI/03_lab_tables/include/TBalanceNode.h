#ifndef _TBALANCENODE_H_
#define _TBALANCENODE_H_
#include "../include/TNode.h"
#include <iostream>

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

	template<typename TKey, class TData> 
	friend std::ostream& operator<<(std::ostream& out, const TBalanceNode& temp)
	{
		out << "Key: " << temp.GetKey() << "\t Data: " << temp.GetData() << "\t Balance: " << temp.GetBalance();

		return out;
	}
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
