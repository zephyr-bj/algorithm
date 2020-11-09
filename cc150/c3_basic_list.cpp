# include <stdio.h>

//(hits:2) delete a particular node in a linked list given a pointer to that node: copy the key, and delte the next.
//Delete the last node of a linked list 
//link list search;
//link list insert after;
//link list delete; (delete the given node without known the previous)
//link list reverse; (hits:3)
//link list isCyclic;

//link lists intersection; 

struct node{
	int key;
	node * next;
};

int _getIntesectionNode(int d, node* head1, node* head2)
{
  int i;
  node* current1 = head1;
  node* current2 = head2;
 
  for(i = 0; i < d; i++){
    if(current1 == NULL)
    {  return -1; }
    current1 = current1->next;
  }
 
  while(current1 !=  NULL && current2 != NULL){
    if(current1 == current2)
      return current1->key;
    current1= current1->next;
    current2= current2->next;
  }
  return -1;
}
int getCount(struct node* head)
{
  node* current = head;
  int count = 0;
 
  while (current != NULL){
    count++;
    current = current->next;
  }
  return count;
}
int getIntesectionNode(node* head1, node* head2)
{
  int c1 = getCount(head1);
  int c2 = getCount(head2);
  int d;
 
  if(c1 > c2){
    d = c1 - c2;
    return _getIntesectionNode(d, head1, head2);
  }
  else{
    d = c2 - c1;
    return _getIntesectionNode(d, head2, head1);
  }
}


//reverse a linked list
void reverse(node **head){
	node *revHead = *head;
	node *curHead;
	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return;
	curHead = revHead->next;
	revHead->next = NULL;
	while (curHead != NULL) {
		node * tmp = curHead->next;
		curHead->next = revHead;
		revHead = curHead;
		curHead = tmp;
	}
	*head = revHead;
}

//Is there a loop in a list
bool isCyclic(node * first) {
    if(first == NULL) // list does not exist..so no loop either.
        return false;
    node* slow, *fast; // create two references.
    slow = first; // make both refer to the start of the list.
	fast = first;
    while(true) {
        slow = slow->next;          // 1 hop.
        if(fast->next != NULL)
            fast = fast->next->next; // 2 hops.
        else
            return false;          // next node null => no loop.
        if(slow == NULL || fast == NULL) // if either hits null..no loop.
            return false;
        if(slow == fast) // if the two ever meet...we must have a loop.
            return true;
    }
}

node * list_search(node * head, int k){
	node *x = head;
	while(x != NULL){
		if(x->key == k){
			return x;
		}
	}
	return x;
}

bool list_insert_after(node **head, node ** tail, node * flag, int k)
{
	node * newNode = new node;
	if(!newNode) return false;
		newNode->key = k;   // build a new node

	if(flag == NULL){		// insert in the beginning
		newNode->next = *head;
		*head = newNode;
		if(*tail == NULL){  // special case for a empty list
			*tail = newNode;
		}
		return true;
	}
	node * cp = *head;
	while(cp != NULL){
		if(cp == flag){
			if(cp->next != NULL)
				newNode->next = cp->next->next;
			else
				newNode->next = NULL;
			cp->next = newNode;
			if(newNode->next == NULL){ //special case for inserting at the end of the list
				*tail = newNode;
			}
			return true;
		}
		cp = cp->next;
	}
	delete newNode; 
	return false;
}

bool list_remove(node **head, node **tail, node * z){
	node *cp = *head;
	
	if(z == *head){
		*head = cp->next;//delete the beginning
		delete z;
		if(*head == NULL){//delete the only node
			*tail = NULL;
		}
		return true;
	}

	while(cp != NULL){
		if(cp->next == z){
			cp->next = z->next;
			delete z;
			if(cp->next == NULL){
				*tail = cp;
			}
			return true;
		}
		cp = cp->next;
	}
	return false;		
}


node * head, *tail;
void push(int k){
	node * newNode = new node;
	newNode->key = k;
	newNode->next = head;
	head = newNode;
}

node * pop(){
	node * tmp = head;
	head = head->next;
	return tmp;
}

void enqueue(int k){
	node * newNode = new node;
	newNode->key = k;
	newNode->next = NULL;
	if(tail == NULL){
		tail = newNode;
		head = newNode;
	}
	else{
		tail->next = newNode;
	}
}

node * dequeue(){
	return pop();
}
