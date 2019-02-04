#include<iostream>
#include<stdlib.h>
#include<stdio.h>
//structure for node of tree
struct node
{
	struct node *left;
	struct node *parent;
	int key;
	char color;
	struct node *right;
};

//global variable for nil node
struct node *t_nil;

//global variable for tree
struct node *t;

//global variable used in check bst
struct node *prev;

struct node * find(struct node *,int);
void insert(struct node *,int,char,int,char);
void check_color(struct node *);
void check_bst(struct node *);
void check_b_height(struct node *);
int bh(struct node *);
void check_r(struct node *);
void check_color(struct node *);
void check(struct node *);
void preorder(struct node *);
void rb_delete(struct node *,struct node *);
void rb_transplant(struct node *,struct node *, struct node *);
void rb_fixup(struct node *,struct node *);
void left_rotate(struct node *,struct node *);
void right_rotate(struct node *,struct node *);
struct node * rb_minimum(struct node *);
//***** main begins*******
int main()
{
	//intialization of tnil and t
	t_nil=(struct node *)malloc(sizeof(struct node));
	t_nil->left=NULL;
	t_nil->parent=NULL;
	t_nil->key=-2147483648;
	t_nil->color='b';
	t_nil->right=NULL;
	t=(struct node *)malloc(sizeof(struct node));
	t->left=t_nil;
	t->parent=t_nil;
	t->key=-2147483648;
	t->color='b';
	t->right=t_nil;
	
	freopen("red-black-tree/i.txt", "r", stdin);//input from file
	
	int n,k,i,d,pt;
	struct node *z;
	char col,loc,del;
	//cout<<"Enter the no. of nodes in the node: \n";
	std::cin>>n;
	for(i=0;i<n;i++)
	{
		//cout<<"enter the number, color(intial only i.e r or b) of the node, parent value and r or l for right or left child of parent respectively \n";
		std::cin>>k>>col>>pt>>loc;
		insert(t,k,col,pt,loc);
	}
	check(t);
	preorder(t);
	std::cout<<"\n";
	//cout<<"enter the node to be deleted :\n";
	//for deleting one or more nodes
	std::cin>>del;
	while(del=='y')
	{
		std::cin>>d;
		z=find(t,d);
		rb_delete(t,z);
		check(t);
		preorder(t);
		std::cout<<"\n";
		std::cin>>del;
	}
	return 0;
}

//function to find the pointer of a given node value
struct node * find(struct node *r,int d)
{
	struct node *temp=NULL;
	if(r->key==d)
		return r;
	if(r->left==t_nil && r->right==t_nil)
		return NULL;
	else 
	{
		if(r->left!=t_nil)
			temp=find(r->left,d);
		if(temp!=NULL)
			return temp;
		if(r->right!=t_nil)
			temp=find(r->right,d);
		if(temp!=NULL)
			return temp;
	}
}


//fuction for insertion of node
void insert(struct node *r,int k,char col,int pt, char loc)
{
	struct node *s;
	struct node *temp;
	s=(struct node *)malloc(sizeof(struct node));
	if(r->key==-2147483648 && pt==0 && loc=='n')
	{
		r->left=t_nil;
		r->parent=t_nil;
		r->key=k;
		r->color=col;
		r->right=t_nil;
	}
	else
	{
		temp=find(r,pt);
		if(loc=='l')
		{
			temp->left=s;
			s->parent=temp;
			s->left=t_nil;
			s->right=t_nil;
			s->key=k;
			s->color=col;
		}
		else if(loc=='r')
		{
			temp->right=s;
			s->parent=temp;
			s->left=t_nil;
			s->right=t_nil;
			s->key=k;
			s->color=col;
		}
		else
		{
			std::cout<<"invalid location entry. exiting\n";
			exit (0);
		}
	
	}
}

//function to check whether the given tree is valid bst or not & also eliminate the nodes having equal values
void check_bst(struct node *r)
{
	if(r->left!=t_nil)
		check_bst(r->left);
	if(r->key<prev->key)
	{
			std::cout<<"\nexiting because not a bst or equal values\n";
			exit(0);
	}
	prev=r;
	if(r->right!=t_nil)
		check_bst(r->right);
}

//function to check whether all nodes have red or black color
void check_color(struct node *r)
{
	if(r!=t_nil)
	{
		if(r->color=='b' || r->color=='r')
		{
			check_color(r->left);
			check_color(r->right);
		}
		else
		{
			std::cout<<"\ncolor of node:"<<r->key<<" is not red or black\n";
			exit(0);
		}
	}
}

//function to check whether two red nodes have parent-child relation
void check_r(struct node *r)
{
	if (r->color=='r')
	{
		if ((r->left)->color=='b' && (r->right)->color=='b')
		{
			check_r(r->left);
			check_r(r->right);
		}
		else
		{
			std::cout<<"check the child of red node:"<<r->key<<"\n exiting.\n";
			exit (0);
		}
	}
	else if (r!=t_nil)
	{
		check_r(r->left);
		check_r(r->right);
	}
}

//function to calculate the black height of a given node used in function check_b_height
int bh(struct node *r)
{
	if(r!=t_nil)
	{
		if (r->color=='b')
			return (bh(r->left) + 1);
		else
			return bh(r->left);
	}
}

//function to check blackheight property of rb-tree
void check_b_height(struct node *r)
{
	if(r!=t_nil)
	{
		if(bh(r->left)==bh(r->right))
		{
			check_b_height(r->left);
			check_b_height(r->right);
		}
		else
		{
			std::cout<<"check black height of the node:"<<r->key<<"\n exiting.\n";
			exit (0);
		}
	}
}

//function to check the properties of rb-tree 
void check(struct node *r)
{
	prev=t_nil;
	check_bst(r);
	if (r->color=='b')//for checking whether root is black or not
	{
		check_color(r);
		check_r(r);
		check_b_height(r);
	}
	else
	{
		std::cout<<"check root color. exiting\n";
		exit (0);
	}
}

//function to print preorder of a given tree with colors
void preorder(struct node *r)
{
	if(r!=t_nil)
	{
		std::cout<<"key:"<<(r->key)<<"     ";
		std::cout<<"color:"<<(r->color)<<"\n";
		preorder(r->left);	
		preorder(r->right);
	}
}

//function for left rotation about a node
void left_rotate(struct node *r,struct node *x)
{
	struct node *y;
	y=x->right;
	x->right=y->left;
	if (y->left!=t_nil)
		(y->left)->parent=x;
	y->parent=x->parent;
	if (x->parent==t_nil)
		t=y;
	else if(x==((x->parent)->left))
		(x->parent)->left=y;
	else (x->parent)->right=y;
	y->left=x;
	x->parent=y;
}

//function for right rotation about a node
void right_rotate(struct node *r,struct node *x)
{
	struct node *y;
	y=x->left;
	x->left=y->right;
	if (y->right!=t_nil)
		(y->right)->parent=x;
	y->parent=x->parent;
	if (x->parent==t_nil)
		t=y;
	if (x==(x->parent)->right)
		(x->parent)->right=y;
	else (x->parent)->left=y;
	y->right=x;
	x->parent=y;
}

//transplant function used in r-b deletion
void rb_transplant(struct node *r,struct node *u,struct node *v)
{
	if (u->parent==t_nil)
		t=v;
	else if (u==(u->parent)->left)
		(u->parent)->left=v;
	else (u->parent)->right=v;
	v->parent=u->parent;
}

//function helping to find the successor of a node
struct node * rb_minimum(struct node *r)
{
	if((r->left)!=t_nil)
		return rb_minimum(r->left);
	else return r;
}

//function to delete a node
void rb_delete(struct node *r,struct node *z)
{
	struct node *y,*x;
	char y_o_c;
	y=z;
	y_o_c=y->color;
	if (z->left==t_nil)
	{
		x=z->right;
		rb_transplant(r,z,z->right);
	}
	else if (z->right==t_nil)
	{
		x=z->left;
		rb_transplant(r,z,z->left);
	}
	else
	{	
		y=rb_minimum(z->right);
		y_o_c=y->color;
		x=y->right;
		if (y->parent==z)
			x->parent=y;
		else
		{
			rb_transplant(r,y,y->right);
			y->right=z->right;
			(y->right)->parent=y;
		}
		rb_transplant(r,z,y);
		y->left=z->left;
		(y->left)->parent=y;
		y->color=z->color;
	}
	if (y_o_c=='b')
		rb_fixup(r,x);
}

//function used for rb-delete fixup
void rb_fixup(struct node *r,struct node *x)
{
	struct node *w;
	while((x!=t) && (x->color=='b'))
	{
		if (x==(x->parent)->left)
		{
			w=(x->parent)->right;
			if (w->color=='r')
			{
				w->color='b';
				(x->parent)->color='r';
				left_rotate(r,x->parent);
				w=(x->parent)->right;
				preorder(t);
				std::cout<<"\n";
			}
			if ((w->left)->color=='b' && (w->right)->color=='b')
			{
				w->color='r';
				x=x->parent;
				preorder(t);
				std::cout<<"\n";
			}
			else if ((w->right)->color=='b')
			{
				(w->left)->color='b';
				w->color='r';
				right_rotate(r,w);
				w=(x->parent)->right;
				preorder(t);
				std::cout<<"\n";
			}
			else
			{
				
				w->color=(x->parent)->color;
				(x->parent)->color='b';
				(w->right)->color='b';
				left_rotate(r,x->parent);
				x=t;
				preorder(t);
				std::cout<<"\n";
			}
		}
		else
		{
			w=(x->parent)->left;
			if(w->color=='r')
			{
				w->color='b';
				(x->parent)->color='r';
				right_rotate(r,x->parent);
				w=(x->parent)->left;
				preorder(t);
				std::cout<<"\n";
			}
			if ((w->right)->color=='b' && (w->left)->color=='b')
			{
				w->color='r';
				x=x->parent;
				preorder(t);
				std::cout<<"\n";
			}
			else if ((w->left)->color=='b')
			{
				(w->right)->color='b';
				w->color='r';
				left_rotate(r,w);
				w=(x->parent)->left;
				preorder(t);
				std::cout<<"\n";
			}
			else
			{
				w->color=(x->parent)->color;
				(x->parent)->color='b';
				(w->left)->color='b';
				right_rotate(r,x->parent);
				x=t;
				preorder(t);
				std::cout<<"\n";
			}
		}
	}
	x->color='b';
}

