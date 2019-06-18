/* DFS */
    unordered_map<Node*,Node*>bin;
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        Node * res=NULL;
        if(bin.find(head)==bin.end()){
            res = new Node(head->val, NULL, NULL);
            bin[head]=res;
        }else{
            return bin[head];
        }
        if(head->next!=NULL)res->next=copyRandomList(head->next);
        if(head->random!=NULL)res->random=copyRandomList(head->random);
        return res;
    }
/*
// Definition for a Node. and BFS solution
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        unordered_map<Node*,Node*>bin;
        Node dummy(0,NULL,NULL);
        Node * p = &dummy;
        while(head!=NULL){
            if(bin.find(head)==bin.end()){
                Node * tmp= new Node(head->val,NULL,NULL);
                p->next=tmp;
                bin[head]=tmp;
            }else{
                p->next=bin[head];
            }
            p=p->next;
            if(head->random!=NULL){
                if(bin.find(head->random)==bin.end()){
                    Node * tmp2 = new Node(head->random->val,NULL,NULL);
                    p->random=tmp2;
                    bin[head->random]=tmp2;
                }else{
                    p->random=bin[head->random];
                }
            }
            head=head->next;
        }
        return dummy.next;
    }
};
*/
