#include <stdio.h>
#include <stdlib.h>
int total_depth=0;//'d' in depth, 's' in depth
//definition of tree
// p is all_trees now
struct node
{
	struct node *left;
	int data;
	int visit;
	struct node *right;
};
void insert(struct node **, int);
void swap(int *,int *);
void permute(int *, int, int, int **);
int fact(int);
void depth(struct node **);

int main()
{
	struct node **all_trees;
	int **permutations_of_numbers;
	int nodes_in_tree, *input_numbers;
	int i,j,s;
	int number_of_permutations;
	float k, depth_by_formula=0; // k is required to be float

	printf("enter the number of nodes \n");
	scanf("%d", &nodes_in_tree);
	number_of_permutations = fact(nodes_in_tree);
	permutations_of_numbers=(int **) calloc(number_of_permutations, sizeof(int *));
	for(i=0; i<number_of_permutations; i++)
		permutations_of_numbers[i]=(int *) calloc(nodes_in_tree, sizeof(int));
	
	input_numbers=calloc(nodes_in_tree,sizeof(int));
	printf("enter the %d numbers to make tree\n",nodes_in_tree);
	for(i=0; i<nodes_in_tree; i++)
		scanf(" %d", input_numbers+i);

	//making space for all the permutations
	all_trees = calloc(number_of_permutations, sizeof(struct node *));
	permute(input_numbers, 0, nodes_in_tree, permutations_of_numbers);

	//inserting elements in trees
	for(i=0; i<number_of_permutations; i++)
	{
		for(j=0; j<nodes_in_tree; j++)
			insert(&all_trees[i], permutations_of_numbers[i][j]);
	}

	// print permutations
	printf("permutations are:\n");
	for(i=0; i<number_of_permutations; i++)
	{
		for(j=0;j<nodes_in_tree;j++)
			printf(" %d",permutations_of_numbers[i][j]);
		printf("\n");
	}
	
	//calculating depths of the trees
	for(s=0; s<number_of_permutations; s++)
		depth(&all_trees[s]);
	printf(" %d\n",total_depth);
	k=(float) total_depth/number_of_permutations;
	printf(" Obtained average total depth is %f\n",k);
	for(k=1; k<=nodes_in_tree; k++)
		depth_by_formula=depth_by_formula+1/k;
	depth_by_formula=2*(nodes_in_tree+1)*depth_by_formula-3*nodes_in_tree;
	printf(" Expected average total depth is %f\n",depth_by_formula);
	
}

//function for genrating permutations
void permute(int *input_numbers, int left, int right, int **permutations_of_numbers)
{
   int i;
   int static z = 0;
   if ( left == right)
	{
		for(i=0;i<right;i++)	
			permutations_of_numbers[z][i] = input_numbers[i];
		z++;
	}
   else
   {
       for (i = left; i < right; i++)
       {
          swap(input_numbers + left, input_numbers+i);
          permute(input_numbers, left+1, right, permutations_of_numbers);
          swap(input_numbers + left, input_numbers+i);
       }
   }
}

//functions to swap values at two locations
void swap(int *r, int *s)
{
	int t;
	t=*s;
	*s=*r;
	*r=t;
}
int fact(int t)
{
	int f=1;
	if(t==0||t==1)
		return f;
	else
		f=t*fact(t-1);
	return f;
}
//function to insert nodes in a tree
void insert( struct node **j,int t)
{
	if(*j==NULL)
	{
		*j=(struct node *)malloc(sizeof(struct node));
		(*j)->left=NULL;
		(*j)->data=t;
		(*j)->visit=0;
		(*j)->right=NULL;
	}
	else if(t<(*j)->data)
		insert(&((*j)->left),t);
	else
		insert(&((*j)->right),t);
}


//function to calculate the total depth of a tree
void depth(struct node **j)
{
	int i;
	if((*j)->left==NULL && (*j)->right==NULL)
	 {
	 	if((*j)->visit==1)
	 	;
	 	else
		{
			total_depth++;
			(*j)->visit=1;
		}
	}
	else if((*j)->left==NULL && (*j)->right!=NULL)
	{
		if((*j)->right->visit==1 && (*j)->visit==0)
		{
			total_depth++;
			(*j)->visit=1;
		}
		else if((*j)->right->visit==0)
		{
			total_depth++;
	 		depth(&((*j)->right));
			depth(&j);
		}
	}
	else if((*j)->right==NULL && (*j)->left!=NULL)
	{
		if((*j)->left->visit==1 && (*j)->visit==0)
		{
			total_depth++;
			(*j)->visit=1;
		}
		else if((*j)->left->visit==0)
		{
			total_depth++;
	 		depth(&((*j)->left));
			depth(&j);
		}
	}
	else if((*j)->right!=NULL && (*j)->left!=NULL)
	{
		if((*j)->left->visit==1 && (*j)->right->visit==1)
		{
			if((*j)->visit==1);
			else
			{
				total_depth++;
				(*j)->visit=1;
			}
		}
		else if((*j)->left->visit==0 && (*j)->right->visit==1)
		{
			total_depth++;
	 		depth(&((*j)->left));
			depth(&j);
		}
		else if((*j)->left->visit==1 && (*j)->right->visit==0)
		{
			total_depth++;
	 		depth(&((*j)->right));
			depth(&j);
		}
		else if((*j)->left->visit==0 && (*j)->right->visit==0)
		{
			total_depth++;
			depth(&((*j)->left));
				depth(&j);
			depth(&((*j)->right));
				depth(&j);
		}
	}
	return;	
}
