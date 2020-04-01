#ifndef _TNODE_H_
#define _TNODE_H_

template <typename TData>
class TNode
{
private:
	int key;
	TNode* pLeft;
	TNode* pRight;
	TNode* pParent;
	TData* pData;
public:
	TNode();
	TNode(int, TData*);
	TNode<TData>* GetLeft();
	TNode<TData>* GetRight();
};

template <typename TData>
TNode<TData>::TNode() : pParent(nullptr), pData(nullptr), pLeft(nullptr), pRight(nullptr) {}

template <typename TData>
TNode<TData>::TNode(int key_, TData* pData_) : key(key_), pData(pData_), pLeft(nullptr), pRight(nullptr), pParent(nullptr) {}

template <typename TData>
TNode<TData>* TNode<TData>::GetLeft()
{
	return pLeft;
}

template <typename TData>
TNode<TData>* TNode<TData>::GetLeft()
{
	return pLeft;
}

template <typename TData>
TNode<TData>* TNode<TData>::GetRight()
{
	return pRight;
}

#endif //!_TNODE_H_