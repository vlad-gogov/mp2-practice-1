#ifndef __BALANCEBINARYTREE_H_
#define _BALANCEBINARYTREE_H_
#include "../include/TBinaryTree.h"
#include "../include/BalanceTNode.h"

template <typename TData>
class BalanceBinaryTree : protected TBinaryTree<TData>
{
public:
	BalanceBinaryTree();
	BalanceBinaryTree(int key_, TData* pData_, int balance_);
	~BalanceBinaryTree();

	int insert(BalanceTNode<TData>* TNode_, int key_, TData* pData_);
	int leftTreeBalancing(BalanceTNode<TData>* BalanceTNode_);
	int rightTreeBalancing(BalanceTNode<TData>* BalanceTNode_);
	void remove(BalanceTNode<TData>* BalanceTNode_, int key_);
};

template <typename TData>
BalanceBinaryTree<TData>::BalanceBinaryTree() : TBinaryTree<TData>()
{
	this->pRoot = dynamic_cast<BalanceTNode<TData>*>(this->pRoot);
	this->pRoot->balance = 0;
}

template <typename TData>
BalanceBinaryTree<TData>::BalanceBinaryTree(int key_, TData* pData_, int balance_) : TBinaryTree<TData>(key_, pData_) 
{
	this->pRoot = dynamic_cast<BalanceBinaryTree<TData>*>(this->pRoot);
	this->pRoot->balance = balance_;
}

template <typename TData>
BalanceBinaryTree<TData>::~BalanceBinaryTree()
{
	if (this->pRoot)
		delete this->pRoot;
}

template <typename TData>
int BalanceBinaryTree<TData>::insert(BalanceTNode<TData>* TNode_, int key_, TData* pData_)
{
	if (this->pRoot == nullptr)
	{
		this->pRoot = new BalanceBinaryTree<TData>(TNode_, key_, pData_);
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
int BalanceBinaryTree<TData>::leftTreeBalancing(BalanceTNode<TData>* BalanceTNode_)
{
	int height = 0;
	switch (BalanceTNode_->GetBalance())
	{
	case -1:
	{
		BalanceTNode<TData>* right = (BalanceTNode<TData>*)(BalanceTNode_->pRight);
		if (right->GetBalance() == -1)
		{
			BalanceTNode_->pRight = right->pLeft;
			right->pLeft = BalanceTNode_;
			BalanceTNode_->SetBalance(0);
			BalanceTNode_ = right;
		}
		else
		{
			BalanceTNode<TData>* left = (BalanceTNode<TData>*)(right->left);
			right->left = left->right;
			left->right = right;
			BalanceTNode_->right = left->left;
			left->left = BalanceTNode_;
			if (left->GetBalance() == -1)
				BalanceTNode_->SetBalance(1);
			else
				BalanceTNode_->SetBalance(0);
			if (left->GetBalance() == 1)
				BalanceTNode_->SetBalance(-1);
			else BalanceTNode_->SetBalance(0);
			BalanceTNode_ = left;
			BalanceTNode_->SetBalance(0);
		}
		height = 0;
		break;
	}
	}
	case 0:
	{
		BalanceTNode_->SetBalance(-1);
		height = 1;
		break;
	}
	case 1:
	{
		BalanceTNode_->SetBalance(0);
		height = 0;
		break;
	}
	return height;
}

template <typename TData>
int BalanceBinaryTree<TData>::rightTreeBalancing(BalanceTNode<TData>* BalanceTNode_)
{
	int height = 0;
	switch (BalanceTNode_->GetBalance())
	{
	case -1:
	{
		BalanceTNode<TData>* left = (BalanceTNode<TData>*)(BalanceTNode_->pLeft);
		if (left->GetBalance() == -1)
		{
			BalanceTNode_->pLeft = left->pRight();
			left->pRight = BalanceTNode_;
			BalanceTNode_->SetBalance(0);
			BalanceTNode_ = left;
		}
		else
		{
			BalanceTNode<TData>* right = (BalanceTNode<TData>*)(left->right);
			left->right = right->left;
			right->left = left;
			BalanceTNode_->left = right->right;
			right->right = BalanceTNode_;
			if (right->GetBalance() == -1) 
				BalanceTNode_->SetBalance(1);
			else 
				BalanceTNode_->SetBalance(0);
			if (right->GetBalance() == 1) 
				BalanceTNode_->SetBalance(-1);
			else BalanceTNode_->SetBalance(0); 
			BalanceTNode_ = right;
			BalanceTNode_->SetBalance(0);
		}
		height = 0;
		break;
		}
	}
	case 0:
	{
		BalanceTNode_->SetBalance(-1);
		height = 1;
		break;
	}
	case 1:
	{
		BalanceTNode_->SetBalance(0);
		height = 0;
		break;
	}
	return height;
}

template <typename TData>
void BalanceBinaryTree<TData>::remove(BalanceTNode<TData>* BalanceTNode_, int key_)
{
	if (this->pRoot == nullptr)
	{
		return;
	}
	else
	{
		if (key_ > this->pRoot->GetKey())
		{
			this->pRoot->GetRight()->remove(BalanceTNode_, key_);
		}
		if (key_ < this->pRoot->GetKey())
		{
			this->pRoot->GetLeft()->remove(BalanceTNode_, key_);
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