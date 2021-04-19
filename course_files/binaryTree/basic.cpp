#include <iostream>
#include <set>
#include <stdlib.h> // #include <cstdlib>
#include <time.h>



class TreeNode
{
public:
	int key;
	TreeNode *parent=nullptr,*left=nullptr,*right=nullptr;
	static int count;

	TreeNode()
	{
		++count;
	}
	~TreeNode()
	{
		--count;
	}
};

int TreeNode::count=0;

void Print(const TreeNode *ptr)
{
	if(nullptr!=ptr)
	{
		Print(ptr->left);
		std::cout << ptr->key << std::endl;
		Print(ptr->right);
	}
}

void Clear(TreeNode *ptr)
{
	if(nullptr!=ptr)
	{
		Clear(ptr->left);
		delete ptr;
		Clear(ptr->right);
	}
}

int main(void)
{
	srand((int)time(nullptr));

	TreeNode *root=nullptr;
	for(int i=0; i<20; ++i)
	{
		auto r=rand()%20;
		TreeNode *newNode=new TreeNode;
		newNode->key=r;

		if(nullptr==root)
		{
			root=newNode;
		}
		else
		{
			auto ptr=root;
			for(;;)
			{
				if(newNode->key<ptr->key)
				{
					if(nullptr!=ptr->left)
					{
						// Already something on the left.  Keep searching.
						ptr=ptr->left;
					}
					else
					{
						// Found a location to attach.
						// Make it bi-directional connection.
						ptr->left=newNode;
						newNode->parent=ptr;
						break;
					}
				}
				else
				{
					if(nullptr!=ptr->right)
					{
						// Already something on the right.  Keep searching.
						ptr=ptr->right;
					}
					else
					{
						// Found a location to attach.
						// Make it bi-directional connection.
						ptr->right=newNode;
						newNode->parent=ptr;
						break;
					}
				}
			}
		}
	}

	std::cout << "Created " << TreeNode::count << std::endl;

	Print(root);
	Clear(root);

	std::cout << "Remaining " << TreeNode::count << std::endl;

	return 0;
}
