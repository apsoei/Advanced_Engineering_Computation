#include <stdio.h>
#include <cstddef>

#include <math.h>
#include <iostream>

template <class KeyClass,class ValueClass>
class BinaryTree
{
protected:
	class Node
	{
	public:
		KeyClass key;
		ValueClass value;
		Node *left,*right,*up;
		int height;
		Node() : left(nullptr),right(nullptr),up(nullptr),height(1)
		{
		}
	};
	
public:

	bool autoRebalancing;
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
			return this->ptr==hd.ptr;
		}
		inline bool operator!=(NodeHandle hd) const
		{
			return this->ptr!=hd.ptr;
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
		if(ndHd.IsNotNull())
		{
			return ndHd.ptr;
		}
		return nullptr;
	}
	const Node *GetNode(NodeHandle ndHd) const
	{
		if(ndHd.IsNotNull())
		{
			return ndHd.ptr;
		}
		return nullptr;
	}
	static NodeHandle MakeHandle(Node *nodePtr)
	{
		NodeHandle ndHd;
		ndHd.ptr=nodePtr;
		return ndHd;
	}
	bool UpdateHeight(Node *nodePtr)
	{
		int leftHeight=1,rightHeight=1;
		if(nullptr!=nodePtr->left)
		{
			leftHeight=nodePtr->left->height+1;
		}
		if(nullptr!=nodePtr->right)
		{
			rightHeight=nodePtr->right->height+1;
		}
		int newHeight=1;
		if(leftHeight>rightHeight)
		{
			newHeight=leftHeight;
		}
		else
		{
			newHeight=rightHeight;
		}
		if(newHeight!=nodePtr->height)
		{
			nodePtr->height=newHeight;
			return true;
		}
		return false;
	}
	void UpdateHeightCascade(Node *nodePtr)
	{
		bool first=true;
		while(nullptr!=nodePtr)
		{
			auto changed=UpdateHeight(nodePtr);
			if(true!=first && true!=changed)
			{
				break;
			}
			nodePtr=nodePtr->up;
			first=false;
		}
	}

private:
	Node *root;
	long long int nElem;

public:
	BinaryTree()
	{
		autoRebalancing = false;
		root=nullptr;
		nElem=0;
	}
	~BinaryTree()
	{
		CleanUp();
	}
	void CleanUp(void)
	{
		CleanUp(GetNode(RootNode()));
	}
private:
	void CleanUp(Node *nodePtr)
	{
		if(nullptr!=nodePtr)
		{
			CleanUp(nodePtr->left);
			CleanUp(nodePtr->right);
			delete nodePtr;
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
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return MakeHandle(nodePtr->left);
		}
		return Null();
	}
	NodeHandle Up(NodeHandle ndHd) const
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return MakeHandle(nodePtr->up);
		}
		return Null();
	}
	NodeHandle Right(NodeHandle ndHd) const
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return MakeHandle(nodePtr->right);
		}
		return Null();
	}

	long long int GetN(void) const
	{
		return nElem;
	}
	const KeyClass &GetKey(NodeHandle ndHd) const
	{
		// This will crash if ndHd==nullptr.  Therefore, ndHd must be non-null to use this function.
		return GetNode(ndHd)->key;
	}
	ValueClass &GetValue(NodeHandle ndHd)
	{
		// This will crash if ndHd==nullptr.  Therefore, ndHd must be non-null to use this function.
		return GetNode(ndHd)->value;
	}
	const ValueClass &GetValue(NodeHandle ndHd) const
	{
		// This will crash if ndHd==nullptr.  Therefore, ndHd must be non-null to use this function.
		return GetNode(ndHd)->value;
	}
	NodeHandle FindNode(const KeyClass &key) const
	{
		auto ndHd=RootNode();
		while(nullptr!=ndHd)
		{
			if(key==GetKey(ndHd))
			{
				return ndHd;
			}
			if(key<GetKey(ndHd))
			{
				ndHd=Left(ndHd);
			}
			else
			{
				ndHd=Right(ndHd);
			}
		}
		return Null();
	}
	bool IsKeyIncluded(const KeyClass &key) const
	{
		return FindNode(key).IsNotNull();
	}
	int GetHeight(NodeHandle ndHd) const
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return nodePtr->height;
		}
		return 0;
	}

	NodeHandle Insert(const KeyClass &key,const ValueClass &value)
	{
		auto newNode=new Node;
		newNode->key=key;
		newNode->value=value;

		auto ndHd=RootNode();
		if(ndHd.IsNull())
		{
			root=newNode;
		}
		else
		{
			while(ndHd.IsNotNull())
			{
				if(key<GetKey(ndHd))
				{
					if(Left(ndHd)!=nullptr)
					{
						ndHd=Left(ndHd);
					}
					else
					{
						GetNode(ndHd)->left=newNode;
						newNode->up=GetNode(ndHd);
						break;
					}
				}
				else
				{
					if(Right(ndHd)!=nullptr)
					{
						ndHd=Right(ndHd);
					}
					else
					{
						GetNode(ndHd)->right=newNode;
						newNode->up=GetNode(ndHd);
						break;
					}
				}
			}
		}
		UpdateHeightCascade(newNode);
		nElem++;

		// REBLANCE >>>>>>>>


		Rebalance(newNode->up);


		// <<<<<< REBLANCE 

		return MakeHandle(newNode);
	}

	NodeHandle First(void) const
	{
		auto ndHd=RootNode();
		while(Left(ndHd).IsNotNull())
		{
			ndHd=Left(ndHd);
		}
		return ndHd;
	}
	NodeHandle FindNext(NodeHandle ndHd) const
	{
		auto rightHd=Right(ndHd);
		if(rightHd.IsNotNull())
		{
			// Has a right sub-tree.
			// The next node is the left-most of the right sub-tree.
			ndHd=Right(ndHd);
			while(Left(ndHd).IsNotNull())
			{
				ndHd=Left(ndHd);
			}
			return ndHd;
		}
		else
		{
			// Does not have a right sub-tree.
			// Go up until it goes up from the left.
			while(ndHd.IsNotNull())
			{
				auto upHd=Up(ndHd);
				if(upHd.IsNotNull() && ndHd==Left(upHd))
				{
					return upHd;
				}
				ndHd=upHd;
			}
			return Null();
		}
	}
	NodeHandle Last(void) const  // Do it in the assignment.
	{
		auto ndHd = RootNode();
		while(Right(ndHd).IsNotNull())
		{
			ndHd = Right(ndHd);
		}
		return ndHd;
	}
	NodeHandle FindPrev(NodeHandle ndHd) const  // Do it in the assignment.
	{
		auto leftHd = Left(ndHd);
		if(leftHd.IsNotNull())
		{
			// Has left sub-tree.
			// The previous node is the right-most of the left sub-tree.
			ndHd = Left(ndHd);
			while(Right(ndHd).IsNotNull())
			{
				ndHd = Right(ndHd);
			}
			return ndHd;
		}
		else
		{
			// Does not have left sub-tree.
			// Go up until it goes up from the right.
			while(ndHd.IsNotNull())
			{
				auto upHd=Up(ndHd);
				if(upHd.IsNotNull() && ndHd==Right(upHd))
				{
					return upHd;
				}
				ndHd=upHd;
			}
			return Null();
		}
	}



private:
	NodeHandle RightMostOf(NodeHandle ndHd)
	{
		while(Right(ndHd).IsNotNull())
		{
			ndHd=Right(ndHd);
		}
		return ndHd;
	}
	bool SimpleDetach(NodeHandle ndHd)
	{
		if(ndHd.IsNotNull())
		{
			auto upHd=Up(ndHd);
			auto rightHd=Right(ndHd);
			auto leftHd=Left(ndHd);
			if(rightHd.IsNull() && leftHd.IsNull())
			{
				if(upHd.IsNull()) // ndHd is a root.
				{
					root=nullptr;
				}
				else
				{
					auto upPtr=GetNode(upHd);
					if(Left(upHd)==ndHd)
					{
						upPtr->left=nullptr;
						
					}
					else if(Right(upHd)==ndHd)
					{
						upPtr->right=nullptr;
						
					}
					else
					{
						fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
						return false;
					}

				}
				UpdateHeightCascade(GetNode(upHd));
				Rebalance(GetNode(upHd));

				return true;
			}
			else if(rightHd.IsNull())
			{
				if(upHd.IsNull())
				{
					root=GetNode(leftHd);
					root->up=nullptr;
// std::cout << __FUNCTION__ <<__LINE__ << std::endl;
					Rebalance(root);
// std::cout << __FUNCTION__ <<__LINE__ << std::endl;
					return true;
				}
				else
				{
					// Connect upHd and leftHd
					auto upPtr=GetNode(upHd);
					auto leftPtr=GetNode(leftHd);
					if(Left(upHd)==ndHd)
					{
						upPtr->left=leftPtr;
						leftPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						Rebalance(leftPtr);
						return true;
					}
					else if(Right(upHd)==ndHd)
					{
						upPtr->right=leftPtr;
						leftPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						Rebalance(leftPtr);
						return true;
					}
					else
					{
						fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
						return false;
					}
					// Rebalance(GetNode(upHd));
				}
				
			}
			else if(leftHd.IsNull())
			{
				if(upHd.IsNull())
				{
					root=GetNode(rightHd);
					root->up=nullptr;
// std::cout << __FUNCTION__ <<__LINE__ << std::endl;
// std::cout << root-> key << std::endl;
					Rebalance(root);
// std::cout << __FUNCTION__ <<__LINE__ << std::endl;
					return true;
				}
				else
				{
					// Connect upHd and rightHd
					auto upPtr=GetNode(upHd);
					auto rightPtr=GetNode(rightHd);
					if(Left(upHd)==ndHd)
					{
						upPtr->left=rightPtr;
						rightPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						// Rebalancing here >>

						Rebalance(rightPtr);

						// Rebalancing here <<
						return true;
					}
					else if(Right(upHd)==ndHd)
					{
						upPtr->right=rightPtr;
						rightPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						// Rebalancing here >>
						Rebalance(rightPtr);
						// Rebalancing here <<
						return true;
					}
					else
					{
						fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
						return false;
					}
				}
			}
			
			else
			{
				return false;
			}
			
		}
		return false;
	}
public:
	bool Delete(NodeHandle ndHd)
	{
		if(true==SimpleDetach(ndHd))
		{
			delete GetNode(ndHd);
			--nElem;
			
			return true;
		}
		else if(ndHd.IsNotNull())
		{
			// Right most of left. Always Simple-Detachable.
			// Also, since SimpleDetach of itself has failed, it must have a left sub-tree.
			auto RMOL=RightMostOf(Left(ndHd));
			if(true==SimpleDetach(RMOL))
			{
				// Now, RMOL needs to take position of ndHd.
				auto RMOLptr=GetNode(RMOL);
				// // cache
				auto tempPtr = GetNode(Up(RMOL));
				// // cache
				auto upPtr=GetNode(Up(ndHd));
				auto leftPtr=GetNode(Left(ndHd));
				auto rightPtr=GetNode(Right(ndHd));

				auto upOfRMOLptr=RMOLptr->up;
				if(upOfRMOLptr==GetNode(ndHd))
				{
					upOfRMOLptr=RMOLptr;	// Now it is correct.
					// Rebalance(upOfRMOLptr);
				}

				if(nullptr==upPtr)
				{
					root=RMOLptr;
					root->up=nullptr;
					
				}
				else if(upPtr->left==GetNode(ndHd))
				{
					upPtr->left=RMOLptr;
					RMOLptr->up=upPtr;
					
				}
				else if(upPtr->right==GetNode(ndHd))
				{
					upPtr->right=RMOLptr;
					RMOLptr->up=upPtr;
					
				}
				else
				{
					fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
					return false;
				}

				RMOLptr->left=leftPtr;
				if(nullptr!=leftPtr)
				{
					leftPtr->up=RMOLptr;
				}
				RMOLptr->right=rightPtr;
				if(nullptr!=rightPtr)
				{
					rightPtr->up=RMOLptr;
				}

				UpdateHeightCascade(RMOLptr);

				

				delete GetNode(ndHd);
				
				--nElem;
// std::cout << __FUNCTION__ <<__LINE__ << std::endl;
// 				// Rebalance(tempPtr);
// std::cout << __FUNCTION__ <<__LINE__ << std::endl;
				// ----------------------
				// Rebalance(tempPtr);
				// ----------------------
				// Rebalancing here >>
// std::cout <<__FUNCTION__<< __LINE__ <<std::endl;
// std::cout << "just deleted this: " << upPtr->key << std::endl;
// 				Rebalance(RMOLptr);
// std::cout <<__FUNCTION__<< __LINE__ <<std::endl;
				// Rebalancing here <<

				
				return true;
			}
		}
		return false; // Cannot delete a null node.
	}

	bool RotateLeft(NodeHandle ndHd)
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr && nullptr!=nodePtr->right)
		{
			auto rightPtr=nodePtr->right;
			auto leftOfRight=nodePtr->right->left;

			if(nullptr==nodePtr->up)
			{
				root=rightPtr;
				rightPtr->up=nullptr;
			}
			else
			{
				rightPtr->up=nodePtr->up;
				if(nodePtr->up->left==nodePtr)
				{
					nodePtr->up->left=rightPtr;
				}
				else
				{
					nodePtr->up->right=rightPtr;
				}
			}

			rightPtr->left=nodePtr;
			nodePtr->up=rightPtr;

			nodePtr->right=leftOfRight;
			if(nullptr!=leftOfRight)
			{
				leftOfRight->up=nodePtr;
			}
			UpdateHeight(nodePtr);
			UpdateHeightCascade(rightPtr);
			return true;
		}
		return false;
	}

	bool RotateRight(NodeHandle ndHd)
	{
		auto nodePtr = GetNode(ndHd);
		// CHECK selected node is not nullptr and it has left node
		if(nullptr!=nodePtr && nullptr!=nodePtr->left)
		{
			auto leftPtr = nodePtr->left;
			auto rightOfLeft = nodePtr->left->right;
			// CHECK current node's parent is nullptr
			if(nullptr == nodePtr->up)
			{
				root = leftPtr;
				leftPtr->up = nullptr;
			}
			else
			{
				// left goes in the place of current node
				leftPtr->up = nodePtr->up;
				if(nodePtr->up->left==nodePtr)
				{
					nodePtr->up->left = leftPtr;
				}
				else
				{
					nodePtr->up->right = leftPtr;
				}
			}
			leftPtr->right = nodePtr;
			nodePtr->up = leftPtr;

			nodePtr->left = rightOfLeft;
			if(nullptr!=rightOfLeft)
			{
				rightOfLeft->up = nodePtr;
			}
			UpdateHeight(nodePtr);
			UpdateHeightCascade(leftPtr);
			return true;
		}
		return false;
	}

	void TreeToVine(void)
	{
		auto vine_tail = root;
		auto remainder = root;

		int size = 0;
		int downCount = 1;
		int rotCount = 1;
		while(nullptr != remainder)
		{
			if(nullptr == remainder->left)
			{
				vine_tail = remainder;
				remainder = remainder->right;
				size+=1;

				downCount++;
			}
			else
			{
				auto temp = remainder -> left;
				RotateRight(MakeHandle(remainder));

				rotCount++;
				remainder = temp;
			}


			
		}
// std::cout << "tree to vine done" << std::endl;
	}
	void Compress(int N)
	{
		auto pivot = root;
		auto temp = root;

		while(N >0)
		{
// std::cout << " 0 " <<std::endl;	
			temp = pivot->right;

			
			RotateLeft(MakeHandle(pivot));

			
			pivot = temp->right;
			
			
// std::cout << " 3 " <<std::endl;
			N--;
			
		}
// std::cout << " 4 " <<std::endl;
	}

	void VineToTree(void)
	{
		int size = root->height;  // NODE COUNT
		int leafCount = 1 + size - pow(2,int(log2(size+1)));

		Compress(leafCount);
		size = size - leafCount;
		while( 1 < size)
		{
// std::cout << "size / 2 = " << size/2 <<std::endl;
			Compress(size/2);
// std::cout << "COMPRESSED . . " << std::endl;
			size/=2;
		}
		

// >>>>>>>>>>>>>>>>>>>>>>>>

		// int m = pow(2, int(log2(nodeCount+1))) - 1;
		// Compress(nodeCount - m);
		// for (m = m/2; m>0; m/=2)
		// {
		// 	Compress(m);
		// }

// <<<<<<<<<<<<<<<<<<<

	}


	// TreeNode* balanceBST(TreeNode *root) 
	// {
	// TreeNode grand;
	// grand.right = root;
	// auto cnt = makeVine(&grand);
	// int m = pow(2, int(log2(cnt + 1))) - 1;
	// compress(&grand, cnt - m);
	// for (m = m / 2; m > 0; m /= 2)
	// 		compress(&grand, m);
	// return grand.right;

protected:
	


// ps5_2 REBALANCE >>>>>>
void Rebalance(Node * nodePtr)
{

	if(true==autoRebalancing)
	{

		auto scanner = nodePtr;
		
		EXIT:
		while(nullptr!=scanner)
		{
			
			int scannerBalance = 0, childBalance = 0;

			// BALANCED >>>
			if(nullptr==scanner->left && nullptr==scanner->right)
			{

				scanner = scanner->up;
				goto EXIT;
			}
			// BALANCED <<<

			else if(nullptr!=scanner->left && nullptr==scanner->right)
			{

				scannerBalance = scanner->left->height;
			}
			else if(nullptr!=scanner->right && nullptr==scanner->left)
			{

				scannerBalance = - scanner->right->height;
			}
			else
			{

				scannerBalance = scanner->left->height - scanner->right->height;
			}

			// LEFT HEAVY
			if(scannerBalance > 1)
			{

				auto child = scanner->left;

				if(nullptr==child->left) childBalance = - child->right->height;
				else if(nullptr==child->right) childBalance = child->left->height;
				else childBalance = child->left->height - child->right->height;
				// L - L
				if(childBalance > 0)
				{
					RotateRight(MakeHandle(scanner));
					

					scanner = child;
				}
				else
				{
					RotateLeft(MakeHandle(child));
					RotateRight(MakeHandle(scanner));
					
					scanner = child;

				}
			}
			// RIGHT HEAVY
			else if(scannerBalance < -1)
			{

				auto child = scanner->right;

				if(nullptr==child->left) childBalance = - child->right->height;
				else if(nullptr==child->right) childBalance = child->left->height;
				else childBalance = child->left->height - child->right->height;
				// R - R
				if(childBalance < 0)
				{
					RotateLeft(MakeHandle(scanner));
					

					scanner = child;
				}
				else
				{
					RotateRight(MakeHandle(child));
					RotateLeft(MakeHandle(scanner));
					

					scanner = child;
				}
			}
			
			else
			{
				scanner = scanner->up;
			}


		}
	
			
			
		
	}
}
// <<<<<<<<<<<< ps5_2 REBALANCE 

public:

bool CheckBalance(void)
{
	NodeHandle ndHd = First();
	while(ndHd.IsNotNull())
	{
		int balance = 0;
		int L = 0, R = 0;
		if(Left(ndHd).IsNull()) L = 0;
		else L = GetHeight(Left(ndHd));
		if(Right(ndHd).IsNull()) R = 0;
		else R = GetHeight(Right(ndHd));
		balance = L - R;
		if(balance > 1 || balance < -1)
		{
			std::cout << "balance broken" << std::endl;
			std::cout << "this node: " <<GetKey(ndHd) << " has balance: " << balance <<std::endl;
			return false;
		}
		ndHd = FindNext(ndHd);
	}
	std::cout << "all tree balance maintained" <<std::endl;
	return true;
}

};