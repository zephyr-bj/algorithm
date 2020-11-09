#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>

//get the depth of a tree
//fill a depth table. 
//keep a parent record
//nearest common ancestor
//print the path with leading to parcific sum. keep a parent record.


struct node{
	node * left;
	node * right;
	node * p;
	int key;
};

node * rec_bst_search(node * root, int k){
	node * x = root;
	if(x == NULL){
		return x;
	}
	if(x->key == k){
		return x;
	}
	if(k < x->key){
		return rec_bst_search(root->left,k);
	}
	else{
		return rec_bst_search(root->right,k);
	}
}

node * ite_bst_search(node * root, int k){
	node * x = root;
	while(x != NULL){
		if(x->key == k){
			return x;
		}
		if(k < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	return x;
}

node * bst_minimum(node * root){
	node * x = root;
	while(x != NULL){
		x=x->left;
	}
	return x;
}

node *bst_maximum(node * root){
	node * x = root;
	while(x != NULL){
		x=x->right;
	}
	return x;
}

node *bst_successor(node * x){
	if(x->right != NULL){
		return bst_minimum(x->right);
	}
	node * y = x->p;
	while(y != NULL){
		y = x->p;
		if(y->right == x){
			x = y;
			y = x->p;
		}
		else{
			return y;
		}
	}
	return y;
}

node *bst_predecessor(node *x){
	if(x->left != NULL){
		return bst_maximum(x->left);
	}
	node * y = x->p;
	while(y != NULL){
		if(y->left == x){
			x = y;
			y = x->p;
		}
		else{
			return y;
		}
	}
	return y;

}

void bst_insert(node ** root, node * z){
	node * x = *root;
	node * y = *root;
	while(x != NULL){
		y = x;
		if(z->key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	z->p = y;
	if(y == NULL){
		*root = z;
	}
	else if(z->key < y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}
}

void bst_delete(node ** root, node *z){
	node * y;
	if(z->left == NULL || z->right == NULL){
		y = z;
	}
	else{
		y = bst_successor(z);
	} //going to delete;
	node * x;
	if(y->left != NULL){
		x = y->left;
	}
	else{
		x = y->right;
	} //going to keep
	if(x != NULL){
		x->p = y->p;
	} //up connection;
	if(y->p == NULL){
		*root = x;
	} // special case
	else if(y==y->p->left){
		y->p->left = x;
	}
	else{
		y->p->right = x;
	} //down connection
	if(y!=z){
		z->key = y->key;
	} //change the key words when we are going to delete the successor 
	delete y;
}

void bst_pre_trvs(node * root){
	if(root == NULL) return;
	printf("%d \n",root->key);
	bst_pre_trvs(root->left);
	bst_pre_trvs(root->right);
}

void bst_in_trvs(node * root){
	if(root == NULL) return;
	bst_in_trvs(root->left);
	printf("%d\n",root->key;
	bst_in_trvs(root->right);
}

void bst_pos_trvs(node * root){
	if(root == NULL) return;
	bst_pos_trvs(root->left);
	bst_pos_trvs(root->right);
	printf("%d\n",root->key);
}


/*Inorder tree traversal non recursive.*/
void inorder_non_recursive(node* nodePtr)
{
    std::list<node*> nstack;

    while (!nstack.empty() || nodePtr){
        /*If nodePtr is NULL, we need to pop from top of the stack
        and print it's value. Then traverse the right sub-tree*/
        if (!nodePtr){
            nodePtr = nstack.back();
            std::cout << nodePtr->key << "\t";
            nodePtr = nodePtr->right;
            nstack.pop_back();
        }
        /*Keep traversing left unless nodePtr is NULL*/
        if (nodePtr){
            nstack.push_back(nodePtr);
            nodePtr = nodePtr->left;
        }
    }
    return;
}
/*Non recursive preorder tree traversal*/
void preorder_non_recursive(node* nodePtr)
{
    std::list<node *> nstack;
    /*Root is NULL, nothing to do.*/
    if (!nodePtr)
        return;
    /*Push root*/
    nstack.push_back(nodePtr);
    while (!nstack.empty()){
        /*Pop the top element*/
        node* tmpPtr = nstack.back();
        std::cout << tmpPtr->key << "\t";
        nstack.pop_back();
        /*Go right before going left as we are using a stack.*/
        if (tmpPtr->right)//right first 
            nstack.push_back(tmpPtr->right);
        if (tmpPtr->left)
            nstack.push_back(tmpPtr->left);
    }
    return;
}
/*Non recursive postorder tree traversal. This is perhaps the most
complicated one too. Let's look at an easier solution using two
stacks first.*/
void postorder_non_recursive(node* nodePtr)
{
    if (!nodePtr)
        return;
    std::list<node*> s1;
    std::list<node*> s2;
    /*Push root into stack s1*/
    s1.push_back(nodePtr);
    while (!s1.empty()){
        /*Pop fropm sack s1 and push it to stack s2*/
        node * tmpPtr = s1.back();
        s2.push_back(tmpPtr);
        s1.pop_back();
        /*Now push left child before right. Because when we push it back to
        stack s2, the order will be correct.*/
        if (tmpPtr->left)
            s1.push_back(tmpPtr->left);
        if (tmpPtr->right)
            s1.push_back(tmpPtr->right);
    }
    /*Now s2 has got all the nodes in postorder. We will just pop it one by
    one and print.*/
    while (!s2.empty()){
        node* tmpPtr = s2.back();
        s2.pop_back();
        std::cout << tmpPtr->key << "\t";
    }
    return;
}
/*Non recursive postorder tree trraversal using only one stack.*/
void postorder_non_recursive_1(node* nodePtr)
{
    if (!nodePtr)
        return;
    std::list<node *> nstack;
    /*We will need current poionter to the node we are currently
    traversing and the pointer to the node we traversed previously.*/
    node* current = nodePtr;
    node* previous = NULL;
    nstack.push_back(current);
    while (!nstack.empty()){
        current = nstack.back();
        /*Traverse the tree down*/
        if (!previous || previous->left == current || previous->right == current){
            if (current->left)
                nstack.push_back(current->left);
            else if (current->right)
                nstack.push_back(current->right);
            else{
                std::cout << current->key << "\t";
                nstack.pop_back();
            }
        }
        /*Traverse the tree up from the left*/
        else if (current->left == previous){
            if (current->right)
                nstack.push_back(current->right);
            else{
                std::cout << current->key << "\t";
                nstack.pop_back();
            }
        }
        else if (current->right == previous){
            std::cout << current->key << "\t";
            nstack.pop_back();
        }
        previous = current;
    }

    return;
}


//Create the mirror image of a binary tree.

//get depth of a tree
//Minimum Depth of Binary Tree (leetcode)
//is Balanced Binary Tree (leetcode)
int d = 0; 
std::list<int> dep;
void getdepth(node *root){
	if(root == NULL) return;
	d++; 
	if(root->left != NULL)
		getdepth(root->left);
	if(root->left == NULL && root->right == NULL)
		dep.push_back(d);
	if(root->right != NULL)
		getdepth(root->right);
	d--;
}
//
int H = dep.size();
std::vector<std::list<node*>> heighttable(H);
void filldeptab(node * root){
	if(root == NULL) return;
	d++;
	if(root->left != NULL) filldeptab(root->left);
	heighttable[d].push_back(root);
	if(root->right != NULL) filldeptab(root->right);
	d--;
}
std::list<std::list<node *>> table;
void filldeptab1(node * root){
	std::list<node *> tmp;
	tmp.push_back(root);
	table.push_back(tmp);
	int d = 0;
	while(true){
		std::list<node *> tmp = table.back();
		std::list<node *>::iterator it;
		std::list<node *> levellist;
		for(it = tmp.begin(); it!=tmp.end(); it++){
			levellist.push_back((*it)->left);
			levellist.push_back((*it)->right);
		}
		if(levellist.size()!=0)
			table.push_back(levellist);
		else
			return;
	}
}

//nearest common ancestor
bool father(node* n1, node* n2){
    if(n1 == NULL) return false;
    else if(n1 == n2) return true;
    else return father(n1->left, n2) || father(n1->right, n2);
}
void first_ancestor2(node* head, node* n1, node* n2, node* &ans){
    if(head==NULL || n1==NULL || n2==NULL) return;
    if(head && father(head, n1) && father(head, n2)){
        ans = head;
        first_ancestor2(head->left, n1, n2, ans);
        first_ancestor2(head->right, n1, n2, ans);
    }
}

//   Binary Tree Maximum Path Sum
int max(int a, int b){
	if(a >= b) return a;
	return b;
}
void maxPathSumHelper(node *root, int &csum, int &maxsum) {
    if (!root) {
        csum = 0;
        return;
    }
    int lsum = 0, rsum = 0;
    maxPathSumHelper(root->left, lsum, maxsum);
    maxPathSumHelper(root->right, rsum, maxsum);
    csum = max(root->key, max(root->key + lsum, root->key + rsum));
    maxsum = max(maxsum, max(csum, root->key + lsum + rsum));
}
int maxPathSum(node *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
    int csum;
    int maxsum = INT_MIN;
    maxPathSumHelper(root, csum, maxsum);
    return maxsum;
}

//print the path with leading to parcific sum. keep a parent record. 
//Path Sum II (leetcode)
void printpath(std::list<int> v, std::list<int>::iterator it){
	std::list<int>::iterator i;
    for(i=it; i!=v.begin(); i--)
        std::cout<<*it<<" ";
	std::cout<<*v.begin();
    std::cout<<std::endl;
}
void find_sum(node* root, int wanted, std::list<int> v){
    if(root == NULL) return;
    v.push_front(root->key);
    int tmp = 0;
	std::list<int>::iterator it = v.begin();
    for(;it!=v.end();it++){
        tmp += *it;
        if(tmp == wanted)
            printpath(v, it);
    }
    std::list<int> v1(v), v2(v);
    find_sum(root->left, wanted, v1);
    find_sum(root->right, wanted, v2);
}

//Convert Sorted List to Binary Search Tree (Leetcode)
//Binary Tree Level Order Traversal (Leetcode)
//Binary Tree Level Order Traversal II (Leetcode)
//Binary Tree Zigzag Level Order Traversal (Leetcode)

//Construct Binary Tree from Inorder and Postorder Traversal (Leetcode)
//Construct Binary Tree from Preorder and Inorder Traversal (Leetcode)

//Symmetric Tree
//Same Tree

//Construct All Unique Binary Search Trees II
//find the number of all Unique Binary Search Trees 

//Populating Next Right Pointers in Each Node 
//Populating Next Right Pointers in Each Node II (leetcode, I did good work, works for both cases)
