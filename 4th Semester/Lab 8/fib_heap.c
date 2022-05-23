//FIBONACCI HEAP

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node{
	struct node* p;
	int key;
	int deg;
	int mark;
	struct node* left;
	struct node* right;
	struct node* child;
	int flag;

};
struct hnode{
	struct node* min;
	int n;
};
struct hnode* makeheap(){
	struct hnode* H = (struct hnode*)malloc(sizeof(struct hnode));
	H->min = NULL;
	H->n =0;
	return H;

}
struct node* newnode(int x){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = x;
	temp->p = NULL;
	temp->left = temp;
	temp->right = temp;
	temp->child = NULL;
	temp->deg = 0;
	temp->mark = 0;
	temp->flag = 0;
	return temp;

}
struct hnode* insert(struct hnode* H,int x){
	struct node* temp = newnode(x);
	if(H->min == NULL){
	H->min = temp;
	H->n++;
	return H;}
	H->min->left->right = temp;
	temp->right = H->min;
	temp->left = H->min->left;
	H->min->left = temp;
	if(H->min->key > temp->key){
	H->min = temp;
	}
	H->n++;
	return H;

}

struct node* minimum(struct hnode* H){
	return H->min;
}
struct hnode* fibheaplink(struct hnode* H,struct node* y,struct node* x){
	y->left->right = y->right;
	y->right->left = y->left;
	y->right = y;
	y->left = y;
	if(x->child == NULL){
		x->child = y;
	}
	else{
	y->right = x->child;
	y->left = x->child->left;
	x->child->left->right = y;
	x->child->left = y;
	if(x->child->key > y->key)x->child = y;
	}
	y->p = x;
	x->deg++;
	return H;
}
struct hnode* CONSOLIDATE(struct hnode* H){
	if(H->min == NULL)return H;
	double n = (double)H->n;
	n = log2(n);
	int len = (int)n;
	len++;
	struct node* A[len];
	for(int i = 0;i<len;i++){
		A[i] = NULL;
	}
	struct node* w = H->min;
	struct node* x = w;
	struct node* y;
	struct node* temp;
	do{
		x = w;
		int d = x->deg;
		while(A[d] != NULL){
			y = A[d];
			if(y->key < x->key){
				temp = y;
				y = x;
				x =temp;
				w = x;
			}
			H = fibheaplink(H,y,x);
			if(x->right == x)H->min = x;
			A[d] = NULL;
			d++;
		}
		A[d] = x;
		w = w->right;
	}while(w != H->min);
	H->min = NULL;
	for (int i = 0 ;i<len;i++){
		if(A[i] != NULL){
			A[i]->right = A[i];
			A[i]->left = A[i];
			if(H->min == NULL){
				H->min = A[i];
			}
			else{
				H->min->left->right = A[i];
				A[i]->left = H->min->left;
				A[i]->right = H->min;
				H->min->left = A[i];
				if(H->min->key > A[i]->key)H->min = A[i];				
			}
			if(A[i]->key < H->min->key)H->min = A[i];
			
		}
	}
	return H;
}
struct hnode* extractmin(struct hnode* H){
	struct node* z = H->min;
	if(z == NULL)return NULL;
	struct node* temp = z->child;
	if(temp != NULL){
		struct node* ptr = temp->right;
		do{
			ptr = temp->right;
			z->left->right = temp;
			temp->left = z->left;
			temp->right = z;
			z->left = temp;
			if(z->key > temp->key)H->min = temp;
			temp->p =NULL;
			temp = ptr;
			
		}
		while(ptr != z->child);
	}
	temp = z;
	temp->left->right = temp->right;
	temp->right->left = temp->left;
	if(temp == temp->right && temp->child == NULL)H->min = NULL;
	else{
		H->min = temp->right;
		temp->right = temp;
		temp->left = temp;
		free(temp);
		H = CONSOLIDATE(H);
	}
	H->n--;
	return H;
		
}
struct hnode* cut(struct hnode* H,struct node* x,struct node* y){
	if(x == x->right )y->child = NULL;
	x->left->right = x->right;
	x->right->left = x->right; 
	if(x == y->child)y->child = x->right; 
	y->deg--; 
	x->right = x; 
	x->left = x; 
	H->min->left->right = x; 
	x->right = H->min; 
	x->left = H->min->left; 
	H->min->left = x; 
	x->p = NULL;
	x->mark = 0;
	return H;
} 
struct hnode* cascadingcut(struct hnode* H,struct node* y){
	struct node* z = y->p;
	if(z!=NULL){
		if(y->mark == 0){
			y->mark = 1;
		}
		else{
			H= cut(H,y,z);
			H = cascadingcut(H,z);
		}
	}
	return H;
}
struct node* FIND(struct node* min,int p){
	struct node* temp = min;
	struct node* find = NULL;
	temp->flag = 1;
	if(temp->key == p){
	find = temp;
	temp->flag = 0;
	return find;
	}
	if(find == NULL){
	if(temp->child != NULL){
		find = FIND(temp->child,p);
	}
	if(temp->right->flag != 1){
		find = FIND(temp->right,p);
	}
	}
	temp->flag = 0;
	return find;
}

struct hnode* decreasekey(struct hnode* H,int p,int q){
	if(H->min == NULL)return H;
	struct node* x = FIND(H->min,p);
	struct node* y = x->p;
	x->key = p-q;
	if(y != NULL && x->key < y->key){
		H = cut(H,x,y);
		H = cascadingcut(H,y);
	}
	if(x->key < H->min->key)H->min = x;
	return H;
		

}
struct hnode* delete(struct hnode* H,int x){
	if(H->min == NULL)return H;
	H = decreasekey(H,x,x+1);
	H = extractmin(H);
	return H;

}
void printheap(struct node* head){
	if(head == NULL)return;
	struct node* temp = head;
	temp->flag = 1;
	printf("%d ",temp->key);
	temp= temp->right;
	while(temp->flag != 1){
	printf("%d ",temp->key);
	temp = temp->right;	
	}
	temp->flag = 0;
	return ;
	
}
void main(){
	struct hnode* H = makeheap();
	char x;
	int p,q;
	int array[]={5,3,21,9,1,13,2,7,10,12,4,8,19,42,20,29,56,31,11};
	int n = sizeof(array)/sizeof(array[0]);
	for(int i = 0;i<n;i++){
		H = insert(H,array[i]);
	}
	printf("Inserted all the elements: ");
	printheap(H->min);
	printf("\n");
	printf("Extracting minimum: ");
	extractmin(H);
	printheap(H->min);
	printf("\n");
	printf("Inserting 15,1,23\n");
	H = insert(H, 15);
	H = insert(H, 1);
	H = insert(H, 23);
	printheap(H->min);
	printf("\n");
	printf("Extracting minimum: ");
	extractmin(H);
	printheap(H->min);
}
