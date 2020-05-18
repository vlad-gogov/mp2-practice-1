#ifndef __BALANCEBINARYTREE_H_
#define _BALANCEBINARYTREE_H_
#include "../include/TBinaryTree.h"
#include "../include/TBalanceNode.h"

template <typename TData>
class TBalanceBinaryTree : protected TBinaryTree<TData>
{
private:
	int leftTreeBalancing(TBalanceNode<TData>** BalanceNode);
	int rightTreeBalancing(TBalanceNode<TData>** BalanceNode);

public:
	TBalanceBinaryTree();
	TBalanceBinaryTree(int key_, TData* pData_, int balance_);
	~TBalanceBinaryTree();

	int insert(TBalanceNode<TData>* TNode_, int key_, TData* pData_);
	void remove(TBalanceNode<TData>* BalanceNode, int key_);
};

template <typename TData>
TBalanceBinaryTree<TData>::TBalanceBinaryTree() : TBinaryTree<TData>()
{
	this->pRoot = dynamic_cast<BalanceTNode<TData>*>(this->pRoot);
	this->pRoot->balance = 0;
}

template <typename TData>
TBalanceBinaryTree<TData>::TBalanceBinaryTree(int key_, TData* pData_, int balance_) : TBinaryTree<TData>(key_, pData_) 
{
	this->pRoot = dynamic_cast<TBalanceBinaryTree<TData>*>(this->pRoot);
	this->pRoot->balance = balance_;
}

template <typename TData>
TBalanceBinaryTree<TData>::~TBalanceBinaryTree()
{
	if (this->pRoot)
		delete this->pRoot;
}

template <typename TData>
int TBalanceBinaryTree<TData>::insert(TBalanceNode<TData>* TNode_, int key_, TData* pData_)
{
	if (this->pRoot == nullptr)
	{
		this->pRoot = new TBalanceBinaryTree<TData>(TNode_, key_, pData_);
		return 0;
	}
	else
	{
		if (key_ >= this->pRoot->GetKey())
		{
			this->pRoot->GetRight()->insert(TNode_, key_, pData_);
		}
		if (key_ < this->pRoot->GetKey())
		{
			this->pRoot->GetLeft()->insert(TNode_, key_, pData_);
		}
	}
}

template <typename TData>
int TBalanceBinaryTree<TData>::leftTreeBalancing(TBalanceNode<TData>** BalanceNode)
{
	int height = 0;
	switch ((*BalanceNode)->GetBalance())
	{
	case -1:
	{
		TBalanceNode<TKey, TData>
		break;
	}
	case 0:
	{
		(*BalanceNode)->SetBalance(-1);
		height = 1;
		break;
	}
	case 1:
	{
		(*BalanceNode)->SetBalance(0);
		height = 0;
		break;
	}
	return height;
	}
}

template <typename TData>
int TBalanceBinaryTree<TData>::rightTreeBalancing(TBalanceNode<TData>** BalanceNode)
{
	int height = 0;
	switch ((*BalanceNode)->GetBalance())
	{
	case 1:
	{
		BalanceTNode<TData>* left = (BalanceTNode<TData>*)((*BalanceNode)->pLeft);
		if (left->GetBalance() == -1)
		{
			(*BalanceNode)->pLeft = left->pRight();
			left->pRight = (*BalanceNode);
			(*BalanceNode)->SetBalance(0);
			(*BalanceNode) = left;
		}
		else
		{
			BalanceTNode<TData>* right = (BalanceTNode<TData>*)(left->right);
			left->right = right->left;
			right->left = left;
			(*BalanceNode)->left = right->right;
			right->right = (*BalanceNode);
			if (right->GetBalance() == -1) 
				(*BalanceNode)->SetBalance(1);
			else 
				(*BalanceNode)->SetBalance(0);
			if (right->GetBalance() == 1) 
				(*BalanceNode)->SetBalance(-1);
			else (*BalanceNode)->SetBalance(0);
			(*BalanceNode) = right;
			(*BalanceNode)->SetBalance(0);
		}
		height = 0;
		break;
		}
	}
	case 0:
	{
		(*BalanceNode)->SetBalance(-1);
		height = 1;
		break;
	}
	case -1:
	{
		(*BalanceNode)->SetBalance(0);
		height = 0;
		break;
	}
	return height;
}

template <typename TData>
void TBalanceBinaryTree<TData>::remove(TBalanceNode<TData>* BalanceNode, int key_)
{
	if (this->pRoot == nullptr)
	{
		return;
	}
	else
	{
		if (key_ > this->pRoot->GetKey())
		{
			this->pRoot->GetRight()->remove(BalanceNode, key_);
		}
		if (key_ < this->pRoot->GetKey())
		{
			this->pRoot->GetLeft()->remove(BalanceNode, key_);
		}
		if (key_ == this->pRoot->GetKey())
		{
			if ((this->pRoot->GetLeft() == nullptr) && (this->pRoot->GetRight()))
			{
				if (this->pRoot->GetParent()->GetLeft() == this->pRoot)
				{
					delete this->pRoot;
					this->pRoot->GetParent()->GetLeft() = nullptr;
				}
				else
				{
					delete this->pRoot;
					this->pRoot->GetParent()->GetRight() = nullptr;
				}
			}
			else if ((this->pRoot->GetLeft() == nullptr) || (this->pRoot->GetRight()))
			{
				if (this->pRoot->GetLeft())
				{
					BalanceTNode<TData>* temp = this->pRoot->GetLeft();
					delete this->pRoot;
					this->pRoot = temp;
				}
				else
				{
					BalanceTNode<TData>* temp = this->pRoot->GetRight();
					delete this->pRoot;
					this->pRoot = temp;
				}
			}
			else
			{
				BalanceTNode<TData>* root = this->pRoot;
				this->pRoot = this->pRoot->GetRight();
				while (this->pRoot->GetLeft() != nullptr)
					this->pRoot = this->pRoot->GetLeft();
				root->key = this->pRoot->GetKey();
				root->pData = this->pRoot->GetData();
				remove(this->pRoot, this->pRoot->GetKey());
			}
		}
	}
}

#endif //!_BALANCEBINARYTREE_H_