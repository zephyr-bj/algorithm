#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <list>
//remove the duplicated characters in a string without using any additional buffer. 
//if 2 strings are anagrams
//rotate a N by N image by 90 degree
//check if str1 is rotation of str2, given a issubstring routine (only need to use once).  
//trie

//implement c subtring function. write the code, along with error checks and some basic testing
//Write code for Strlen(char *).
//find all possible substrings 


void rmdup(char * str){
	int L = sizeof(str)/sizeof(str[0]);
	int tail = 1;
	for(int i = 1; i<L; i++){
		int j;
		for(j=0; j<tail; j++){
			if(str[j] == str[i])
				break;
		}
		if(tail == j){
			tail++;
			str[tail] = str[i];
		}
	}
	str[tail+1] = 0;
}
void rotate90(int ** mat, int N){
	int L = floor(N/2);
	for(int i = 0; i<L; i++){
		for(int j = i; j<L; j++){
			int tmp = mat[i][j];
			mat[i][j] = mat[i][N-j-1];
			mat[i][N-j-1] = mat[N-i-1][N-j-1];
			mat[N-i-1][N-j-1] = mat[N-i-1][j];
			mat[N-i-1][j] = tmp;
		}
	}
}
class TrieNode{
public:
	std::list<TrieNode *> * childNodes;// The children of this node in the trie.   
    char character;	// The character stored in this node as data.
    // Constructs an empty trie node and initializes the list of its
    // children to an empty list. Used only to construct the root node of the trie.
    TrieNode(){
        childNodes = new std::list<TrieNode*>;
    }
    // Constructs a trie node and stores in the node the char passed in
    // as the argument. Initializes the list of child nodes of this node to an empty list. 
    TrieNode(char c){
        TrieNode();
        character = c;
    }
    // Getter for the character data stored in this node. 
    char getChar(){
        return character;
    }
	void addWord(std::string word);
	TrieNode* getNode(char c);
};

void TrieNode::addWord(std::string word)
{
    char firstChar = word[0];
    TrieNode * next = getNode(firstChar);
    if (next == NULL) {
        next = new TrieNode(firstChar);
        childNodes->push_back(next);
    }
	if (word.length() > 1) {
		next->addWord(word.substr(1));
    } 
}

TrieNode * TrieNode::getNode(char c)
{
	std::list<TrieNode*>::iterator it;
    for(it = childNodes->begin(); it != childNodes->end(); it++)
        if((*it)->getChar() == c)
            return *it;
    return NULL;
}


class Trie{   
private: 
	TrieNode * root;// The root of this trie.
    // The only constructor for the Trie class. Takes a list of strings
    // as an argument, and constructs a trie that stores these strings.
public:
	Trie(std::list<std::string> slist);
    // Checks whether this trie contains a string with the prefix passed
    // in as argument.
    bool contains (std::string prefix);
	inline void insertWord(std::string s){root->addWord(s);};
};

Trie::Trie(std::list<std::string> slist)
{
    root = new TrieNode();
	std::list<std::string>::iterator it;
    for (it=slist.begin(); it!= slist.end(); it++) 
        root->addWord(*it);
}
bool Trie::contains(std::string prefix)
{
    TrieNode *lastNode = root;
    for(int i = 0; i< prefix.length(); i++){
        lastNode = lastNode->getNode(prefix[i]);
        if(lastNode == NULL) 
            return false;	 
    }
    return true;
}

Trie prefixtree;
char *allSubstr(char * str){
	char out[1000];
	int pos = 0;
	int N = strlen(str);
	int L = 1;
	while(L <= N){
		for(int i = 0; i+L-1<N; i++){
			char * tmp = new char[L+1];
			for(int k = 0; k<L;k++){
				tmp[k] = str[i+k];
			}
			if(!prefixtree.contains(tmp)){
				prefixtree.insertWord(tmp);
				for(int k = 0; k<L;k++){
					out[pos++] = tmp[i+k];
				}
				out[pos++] = ',';
			}
		}
	}
	out[pos] = '0';
	return out;
}

// compute all permutation of a string
// write a function to return all possible alphanumberic words that can be formed with a phone number.
	/*For a given US based phone number, write a function to return all possible alphanumberic words that can be formed with that number, 
	based on the keypad of a standard phone. For example, one possible value for 1-800-623-6537 could be 1-800-MCDNLDS*/

typedef std::vector<std::string> vs;
vs permu(std::string s){
    vs result;
    if(s == ""){
        return result;
    }
    std::string c = s.substr(0, 1);
    vs res = permu(s.substr(1));
    for(int i=0; i<res.size(); ++i){
        std::string t = res[i];
        for(int j=0; j<=t.length(); ++j){
            std::string u = t;
            u.insert(j, c);
            result.push_back(u);
        }
    }
    return result; 
}

//if 2 strings are anagrams

static int LETTERS_LEN = 256;	
static bool isAnagram(char * s1, char * s2) {
		if (s1 == NULL || s2 == NULL)
			return false;
		int len = sizeof(s1)/sizeof(s1[0]);
		if (len != sizeof(s2)/sizeof(s2) || len < 2)
			return false;

		int * letters = new int[LETTERS_LEN];

		for (int i = 0; i < len; i++) {
			letters[s1[i]]++;
			letters[s2[i]]--;
		}

		for (int i = 0; i < LETTERS_LEN; i++) {
			if (letters[i] != 0) {
				return false;
			}
		}
		return true;
	}


