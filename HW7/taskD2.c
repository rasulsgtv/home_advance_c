#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct tree {
datatype key;
struct tree *left, *right;
struct tree *parent; //ссылка на родителя
} tree;


tree * findBrother(tree *root, int key)
{
	
	tree *find=root;
	
	while (find && find->key != key)
	{
		if (key < find->key)
		{
			find = find->left;
		}
		else
		{
			find = find->right;
		}
	}

	if (find == NULL)
	{
		return 0;
	}
	
	if (find->parent == NULL)
	{
		return 0;
	}
	if(find->parent->left == find)
	{
		return find->parent->right;
	}
	else
	{
		return find->parent->left;
	}
	
}


int main(int argc, char **argv)
{
	


	
    return 0;
}

