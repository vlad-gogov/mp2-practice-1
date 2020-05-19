#ifndef _TBALANCEBINARYTREE_H_
#define _TBALANCEBINARYTREE_H_
#include "../include/TBinaryTree.h"
#include "../include/TBalanceNode.h"

template <typename TKey, typename TData>
class TBalanceBinaryTree : protected TBinaryTree<TKey, TData>
{
private:
	int leftTreeBalancing(TBalanceNode<TKey, TData>** BalanceNode);
	int rightTreeBalancing(TBalanceNode<TKey, TData>** BalanceNode);

public:
	TBalanceBinaryTree();
	TBalanceBinaryTree(int key_, TData* pData_, int balance_);
	~TBalanceBinaryTree();

	int insert(TBalanceNode<TKey, TData>** TNode_, int key_, TData* pData_);
	void remove(TBalanceNode<TKey, TData>* BalanceNode, int key_);
};

template <typename TKey, typename TData>
TBalanceBinaryTree<TKey, TData>::TBalanceBinaryTree() : TBinaryTree<TKey, TData>()
{
	this->pRoot = dynamic_cast<TBalanceNode<TKey, TData>*>(this->pRoot);
	this->pRoot->balance = 0;
}

template <typename TKey, typename TData>
TBalanceBinaryTree<TKey, TData>::TBalanceBinaryTree(int key_, TData* pData_, int balance_) : TBinaryTree<TKey, TData>(key_, pData_) 
{
	this->pRoot = dynamic_cast<TBalanceNode<TKey, TData>*>(this->pRoot);
	this->pRoot->balance = balance_;
}

template <typename TKey, typename TData>
TBalanceBinaryTree<TKey, TData>::~TBalanceBinaryTree()
{
	if (this->pRoot)
		delete this->pRoot;
}

template <typename TKey, typename TData>
int TBalanceBinaryTree<TKey, TData>::insert(TBalanceNode<TKey, TData>** TNode_, int key_, TData* pData_)
{
	int height = 0;
	if ((*TNode_) == nullptr)
	{
		(*TNode_) = new TBalanceNode<TKey, TData>(key_, pData_);
		height = 1;
		return height;
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

template <typename TKey, typename TData>
int TBalanceBinaryTree<TKey, TData>::leftTreeBalancing(TBalanceNode<TKey, TData>** BalanceNode)
{
	int height = 0;
	switch ((*BalanceNode)->GetBalance())
	{
	case 1:
	{
		TBalanceNode<TKey, TData>* right = (TBalanceNode<TKey, TData>*)((*BalanceNode)->pRight);
		if (right->GetBalance() == 1)
		{
			(*BalanceNode)->pRight = right->pLeft;
			right->pLeft = (*BalanceNode);
			(*BalanceNode)->SetBalance(0);
			(*BalanceNode) = right;
		}
		else
		{
			TBalanceNode<TKey, TData>* left = (TBalanceNode<TKey, TData>*)(right->pLeft);
			right->pLeft = left->pRight;
			left->pRight = right;
			(*BalanceNode)->pRight = left->pLeft;
			left->pLeft = (*BalanceNode);
			if (left->GetBalance() == -1) 
				(*BalanceNode)->SetBalance(-1);
			else 
				(*BalanceNode)->SetBalance(0);
			if (left->GetBalance() == 1) 
				(*BalanceNode)->SetBalance(1);
			else 
				(*BalanceNode)->SetBalance(0);
			(*BalanceNode) = left;
			(*BalanceNode)->SetBalance(0);
		}
		height = 0;
		break;
	}
	case 0:
	{
		(*BalanceNode)->SetBalance(1);
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
}

template <typename TKey, typename TData>
int TBalanceBinaryTree<TKey, TData>::rightTreeBalancing(TBalanceNode<TKey, TData>** BalanceNode)
{
	int height = 0;
	switch ((*BalanceNode)->GetBalance())
	{
	case -1:
	{
		TBalanceNode<TKey, TData>* left = (TBalanceNode<TKey, TData>*)((*BalanceNode)->pLeft);
		if (left->GetBalance() == -1)
		{
			(*BalanceNode)->pLeft = left->pRight;
			left->pRight = (*BalanceNode);
			(*BalanceNode)->SetBalance(0);
			(*BalanceNode) = left;
		}
		else
		{
			TBalanceNode<TKey, TData>* right = (TBalanceNode<TKey, TData>*)(left->right);
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
	case 1:
	{
		(*BalanceNode)->SetBalance(0);
		height = 0;
		break;
	}
	return height;
}

template <typename TKey, typename TData>
void TBalanceBinaryTree<TKey, TData>::remove(TBalanceNode<TKey, TData>* BalanceNode, int key_)
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
					TBalanceNode<TKey, TData>* temp = this->pRoot->GetLeft();
					delete this->pRoot;
					this->pRoot = temp;
				}
				else
				{
					TBalanceNode<TKey, TData>* temp = this->pRoot->GetRight();
					delete this->pRoot;
					this->pRoot = temp;
				}
			}
			else
			{
				TBalanceNode<TKey, TData>* root = this->pRoot;
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