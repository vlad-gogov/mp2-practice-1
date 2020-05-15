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
	int remove(BalanceTNode<TData>* BalanceTNode_, int key_);
};

template <typename TData>
BalanceBinaryTree<TData>::BalanceBinaryTree() : pRoot(nullptr) {}

template <typename TData>
BalanceBinaryTree<TData>::BalanceBinaryTree(int key_, TData* pData_, int balance_) : pRoot(key_, pData_) {}

template <typename TData>
BalanceBinaryTree<TData>::~BalanceBinaryTree()
{
	if (pRoot)
		delete pRoot;
}

template <typename TData>
int BalanceBinaryTree<TData>::insert(BalanceTNode<TData>* TNode_, int key_, TData* pData_)
{

}

template <typename TData>
int BalanceBinaryTree<TData>::leftTreeBalancing(BalanceTNode<TData>* BalanceTNode_)
{

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
int BalanceBinaryTree<TData>::remove(BalanceTNode<TData>* BalanceTNode_, int key_)
{

}

#endif //!_BALANCEBINARYTREE_H_