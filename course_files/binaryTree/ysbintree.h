#ifndef YSBINTREE_IS_INCLUDED
#define YSBINTREE_IS_INCLUDED



#include <iostream>
#include <algorithm>

template <class KeyClass,class ValueClass>
class BinaryTree
{
private:
	const BinaryTree <KeyClass,ValueClass> &operator=(const BinaryTree <KeyClass,ValueClass> &);
	BinaryTree(const BinaryTree <KeyClass,ValueClass> &);
	const BinaryTree <KeyClass,ValueClass> &operator=(const BinaryTree <KeyClass,ValueClass> &&);
	BinaryTree(const BinaryTree <KeyClass,ValueClass> &&);

protected:
    class Node
    {
	public:
		KeyClass key;
		ValueClass value;
		int height=1;
		Node *left=nullptr,*right=nullptr,*up=nullptr;
	};
public:
    class NodeHandle
    {
    friend BinaryTree <KeyClass,ValueClass>;
    private:
        Node *ptr;
    public:
        inline void Nullify(void)
        {
			ptr=nullptr;
		}
        inline bool IsNull(void) const
        {
			return ptr==nullptr;
		}
        inline bool IsNotNull(void) const
        {
			return ptr!=nullptr;
		}
        inline bool operator==(NodeHandle hd) const
        {
			return ptr==hd.ptr;
		}
        inline bool operator!=(NodeHandle hd) const
        {
			return ptr!=hd.ptr;
		}
        inline bool operator==(std::nullptr_t) const
        {
			return ptr==nullptr;
		}
        inline bool operator!=(std::nullptr_t) const
        {
			return ptr!=nullptr;
		}
    };
protected:
    Node *GetNode(NodeHandle ndHd)
    {
		return ndHd.ptr;
	}
    const Node *GetNode(NodeHandle ndHd) const
    {
		return ndHd.ptr;
	}
    static NodeHandle MakeHandle(Node *nodePtr)
    {
		NodeHandle ndHd;
		ndHd.ptr=nodePtr;
		return ndHd;
	}
private:
    Node *root=nullptr;
    long long int nElem=0;
public:
    BinaryTree()
    {
	}
	~BinaryTree()
	{
		CleanUp();
	}
	void CleanUp(void)
	{
		Free(root);
	}
private:
	void Free(Node *ptr)
	{
		if(nullptr!=ptr)
		{
			Free(ptr->left);
			Free(ptr->right);
			delete ptr;
		}
	}
	void UpdateHeight(Node *ptr)
	{
		if(nullptr!=ptr)
		{
			if(nullptr==ptr->left && nullptr==ptr->right)
			{
				ptr->height=1;
				UpdateHeight(ptr->up);
			}
			else if(nullptr==ptr->left)
			{
				ptr->height=ptr->right->height+1;
				UpdateHeight(ptr->up);
			}
			else if(nullptr==ptr->right)
			{
				ptr->height=ptr->left->height+1;
				UpdateHeight(ptr->up);
			}
			else
			{
				ptr->height=1+std::max(ptr->left->height,ptr->right->height);
				UpdateHeight(ptr->up);
			}
		}
	}
public:
    static NodeHandle Null(void)
    {
		NodeHandle ndHd;
		ndHd.ptr=nullptr;
		return ndHd;
	}
    NodeHandle RootNode(void) const
    {
		return MakeHandle(root);
	}
    NodeHandle Left(NodeHandle ndHd) const
    {
		return MakeHandle(ndHd.ptr->left);
	}
    NodeHandle Up(NodeHandle ndHd) const
    {
		return MakeHandle(ndHd.ptr->up);
	}
    NodeHandle Right(NodeHandle ndHd) const
    {
		return MakeHandle(ndHd.ptr->right);
	}
    long long int Size(void) const
    {
		return nElem;
	}
    const KeyClass &GetKey(NodeHandle ndHd) const
    {
		return ndHd.ptr->key;
	}
    ValueClass &GetValue(NodeHandle ndHd)
    {
		return ndHd.ptr->value;
	}
    const ValueClass &GetValue(NodeHandle ndHd) const
    {
		return ndHd.ptr->value;
	}
	int GetHeight(NodeHandle ndHd) const
	{
		if(Null()!=ndHd)
		{
			return ndHd.ptr->height;
		}
		return 0;
	}
    NodeHandle FindNode(const KeyClass &key) const
    {
		for(auto ptr=root; nullptr!=ptr; )
		{
			if(key==ptr->key)
			{
				return MakeHandle(ptr);
			}
			else if(key<ptr->key)
			{
				ptr=ptr->left;
			}
			else
			{
				ptr=ptr->right;
			}
		}
		return Null();
	}
    bool IsKeyIncluded(const KeyClass &key) const
    {
		for(auto ptr=root; nullptr!=ptr; )
		{
			if(key==ptr->key)
			{
				return true;
			}
			else if(key<ptr->key)
			{
				ptr=ptr->left;
			}
			else
			{
				ptr=ptr->right;
			}
		}
		return false;
	}
    NodeHandle Insert(const KeyClass &key,const ValueClass &value)
    {
		if(nullptr==root)
		{
			root=new Node;
			root->key=key;
			root->value=value;
			return MakeHandle(root);
		}
		else
		{
			auto newNode=new Node;
			newNode->key=key;
			newNode->value=value;

			// WHere to add?
			auto ptr=root;
			for(;;)
			{
				if(key<ptr->key)
				{
					if(ptr->left!=nullptr)
					{
						// There is something to the left.
						ptr=ptr->left;
					}
					else
					{
						// Found a location to add.
						// Make bi-directional connection.
						ptr->left=newNode;
						newNode->up=ptr;
						break;  // You don't have to keep searching.
					}
				}
				else
				{
					if(ptr->right!=nullptr)
					{
						// There is something to the right.
						ptr=ptr->right;
					}
					else
					{
						// Found a location to add.
						// Make bi-directional connection.
						ptr->right=newNode;
						newNode->up=ptr;
						break;
					}
				}
			}

			UpdateHeight(newNode->up);

			return MakeHandle(newNode);
		}
	}

	NodeHandle First(void) const
	{
		if(nullptr!=root)
		{
			auto ptr=root;
			for(; nullptr!=ptr->left; ptr=ptr->left)
			{
			}
			return MakeHandle(ptr);
		}
		else
		{
			return Null();
		}
	}
	NodeHandle FindNext(NodeHandle ndHd) const
	{
		if(ndHd!=nullptr)
		{
			if(nullptr!=ndHd.ptr->right)
			{
				// Starting from right subtree,
				// GO down to the left as long as there is still something to the left.
				auto ptr=ndHd.ptr->right;
				for(; nullptr!=ptr->left; ptr=ptr->left)
				{
				}
				return MakeHandle(ptr);
			}
			else
			{
				for(;;)
				{
					auto prev=ndHd;
					ndHd=Up(ndHd);
					if(ndHd==nullptr)
					{
						return Null();
					}
					else if(Left(ndHd)==prev)
					{
						return ndHd;
					}
				}
			}
		}
		else
		{
			return Null();
		}
	}

	void Delete(NodeHandle ndHd)
	{
		auto nodePtr=GetNode(ndHd);
		if(true==DeleteSimpleCase(nodePtr))
		{
		}
		else
		{
			// General Case
			auto rmol=RMOL(nodePtr);
			if(true!=DetachSimpleCase(rmol))
			{
				std::cout << __FUNCTION__ << " " << __LINE__ << "Data Structure Broken." << std::endl;
				return;
			}

			auto affected=rmol->up;
			if(rmol->up==nodePtr)
			{
				affected=rmol;
			}

			if(nodePtr->left!=nullptr)
			{
				nodePtr->left->up=rmol;
				rmol->left=nodePtr->left;
			}
			if(nodePtr->right!=nullptr)
			{
				nodePtr->right->up=rmol;
				rmol->right=nodePtr->right;
			}
			else
			{
				std::cout << __FUNCTION__ << " " << __LINE__ << "Data Structure Broken." << std::endl;
				return;
			}

			if(nullptr!=nodePtr->up) // If nodePtr has a parent (or up) node.
			{
				if(nodePtr->up->right==nodePtr)
				{
					nodePtr->up->right=rmol;
					rmol->up=nodePtr->up;
				}
				else if(nodePtr->up->left==nodePtr)
				{
					nodePtr->up->left=rmol;
					rmol->up=nodePtr->up;
				}
				else
				{
					std::cout << __FUNCTION__ << " " << __LINE__ << "Data Structure Broken." << std::endl;
					return;
				}
			}
			else // nodePtr is the root node.
			{
				root=rmol;
			}
			delete nodePtr;

			UpdateHeight(affected);
		}
	};
private:
	bool DeleteSimpleCase(Node *ptr)
	{
		if(true==DetachSimpleCase(ptr))
		{
			delete ptr;
			return true;
		}
		return false;
	}
	bool DetachSimpleCase(Node *ptr)
	{
		if(nullptr==ptr->left || nullptr==ptr->right)
		{
			auto affected=ptr->up;
			Node *subtree=(nullptr==ptr->left ? ptr->right : ptr->left);
			if(nullptr!=ptr->up) // If the one you are detaching has a parent node.
			{
				if(ptr->up->left==ptr)
				{
					ptr->up->left=subtree;
				}
				else if(ptr->up->right==ptr)
				{
					ptr->up->right=subtree;
				}
				else
				{
					std::cout << __FUNCTION__ << " " << __LINE__ << "Data Structure Broken." << std::endl;
				}
			}
			else // The one you are detaching is the root node.
			{
				root=subtree;
			}

			if(nullptr!=subtree)
			{
				subtree->up=ptr->up;
			}

			ptr->up=nullptr;
			ptr->left=nullptr;
			ptr->right=nullptr;

			UpdateHeight(affected);

			return true;
		}
		else
		{
			return false;
		}
	}

	Node *RMOL(Node *ptr)  // Right Most of Left
	{
		if(nullptr!=ptr->left)
		{
			ptr=ptr->left;
			while(nullptr!=ptr->right)
			{
				ptr=ptr->right;
			}
			return ptr;
		}
		return nullptr;
	}

public:
	void RotateLeft(NodeHandle ndHd)
	{
		auto nodeA=GetNode(ndHd);
		if(nullptr!=nodeA)
		{
			auto nodeB=nodeA->right;
			if(nullptr!=nodeB)
			{
				auto nodeC=nodeB->left;

				if(nullptr!=nodeA->up)
				{
					if(nodeA==nodeA->up->left)
					{
						nodeA->up->left=nodeB;
					}
					else
					{
						nodeA->up->right=nodeB;
					}
					nodeB->up=nodeA->up;
				}
				else
				{
					root=nodeB;
					nodeB->up=nullptr;
				}

				nodeA->right=nodeC;
				if(nullptr!=nodeC)
				{
					nodeC->up=nodeA;
				}

				nodeB->left=nodeA;
				nodeA->up=nodeB;

				UpdateHeight(nodeA);
			}
		}
	}
};



#endif
