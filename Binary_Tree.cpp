#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *left, *right;
};

//initializing the root Node with a value of 0;
struct Node *root = 0;
//initializing a bool variable to be used in the BFS function
int found = 0;

void insert(int d, struct Node **node);
int calcheight(struct Node *root);
void traverse_tree(struct Node *node, int level, int d);
void BFS(struct Node *node, int data);
void DFS(struct Node *node, int data);

//Adds new nodes to the tree
void insert(int d, struct Node **node)
{
	//checks if the current node has no children
	if (*node == 0)
	{
		*node = (struct Node*) malloc(sizeof(struct Node));
		(*node)->data = d;
		//Initializing children nodes 
		(*node)->left = 0;
		(*node)->right = 0; 
	}
	//if the node already has children, keep traversing the tree
	else if (d < (*node)->data)
	{
		insert(d, &(*node)->left);
	}
	else if (d < (*node)->data)
	{
		insert(d, &(*node)->left);
	}
}


//Calculates the "depth" of the farthest node from the root.
int calcheight(struct Node *node)
{
	if (&(*node) == 0) return 0;
	else
	{
		//calculate the height of the left and right side of the tree
		int heightl = calcheight(node->left);
		int heightr = calcheight(node->right);
		
		//returns the highest of the two values
		if (heightl < heightr)
		{
			return heightr+1;
		}
		//true for (heightl > heightr) || heightl == heightr
		else	
		{
			return heightl+1;
		} 
	}
}

//Breadth First Search
void BFS(struct Node *root, int data)
{
	int height = calcheight(root);
	
	int i;
	for (i = 0; i<height; i++)
	{
		traverse_tree(root, i, data);
	}
	if (found == 0) printf("Number %d was not found on this tree.\n", data);
}

//Depth First Search
void DFS(struct Node* node, int d)
{
    if (node == 0) return;
 	
    // Left side first
    DFS(node->left, d);
 
    // then right
    DFS(node->right, d);
 
    // checking the node
    if (node->data == d)
	{
		found = 1;
		printf("Number %d found with DFS\n", d);
	}
}
 
//Used for the BFS function
void traverse_tree(struct Node *node, int level, int d)
{
	int currlvl;
	if (node == 0) return;
	if (level == 0)
	{
		if (node->data == d)
		{
			printf("Number %d found.\n", d, level);
			found = 1;
		}
	}
	else if(level > 0)
	{
		traverse_tree(node->left, level-1, d);
		traverse_tree(node->right, level-1, d);
	}
}

int main(int argc, char* argv[])
{
	//Creating the binary tree
	insert(1, &root);
	insert(2, &root->left);
	insert(4, &root->right);
	insert(6, &root->left->right);
	insert(5, &root->left->left);
	insert(10, &root->left->left->right);
	insert(9, &root->left->left->left);
	insert(8, &root->right->right);
	insert(7, &root->right->left);
	insert(12, &root->right->left->right);
	insert(11, &root->right->left->left);
	
	//initializing user input variables
	int input, search_type;
	// Originally used a char type variable but an int that functions as a bool produced less bugs.
	char exit = 'a'; 
	while (exit != 'e')
	{
		printf("Please enter the number you wish to search for\n");
		scanf("%d", &input);
		printf("Please select search method. Type 1 for BFS and 2 for DFS\n");
		scanf("%d", &search_type);
		if (search_type == 1)
		{
			found = 0;
			BFS(root, input);
		}
		if (search_type == 2)
		{
			found = 0;
			DFS(root, input);
			if (found == 0) printf("Number %d, was not found on this tree\n", input);
		}
		
		printf("Press e to exit, or anything else to continue\n");
  		scanf(" %c", &exit);
	}
	
	//Searching for the numbers 10 and 15
	//BFS(root, 10);
	//found = 0;		//resetting the boolean variable
	//BFS(root, 15);
	return 0;
}

