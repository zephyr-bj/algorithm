#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//aligned malloc and free
//allocate a two dimension array
//Find a un-contained integer from a file with four billion integers, given 1GB memory
//Find a un-contained integer from a file with four billion integers, given 10MB memory

//implementation of the sizeof operator
#define my_sizeof(x) (char *)(&x+1)-(char*)(&x)
//write a macro to give offset of particular field in structure.Like struct abc { int a,int b,char c}. 
//Write a macro like offset(abc , c) to find offset of c from top.
#define offset(abc,c) ((char*)(&(abc.c)) - (char*)(&(abc)))
//Write a macro to which you can pass a name of a structure and a name of one of its fields and get a relative offset of this field within the structure. 
#define my_offsetof(type, f) (&(((type *) 0)->f))
//Say a function takes a pointer and allocates it some memory. How would the function 'Prototype' be? 
void memallocate (size_t size, void ** p); 
//Is sizeof() a macro or a function? I said macro... asked why not a function (leave alone the inline advantage of a macro) 
 /*Ans: In C there is no overloading. We send various 'Types' of parameters to sizeof. Macros dont do type checking. Hence Macros!*/


//aligned malloc and free (hits:x)
void *aligned_malloc(size_t required_bytes, size_t alignment) {
    void *p1;
    void **p2;
    int offset=alignment-1+sizeof(void*);
    p1 = malloc(required_bytes + offset);               // the line you are missing
    p2=(void**)(((size_t)(p1)+offset)&~(alignment-1));  //line 5
    p2[-1]=p1; //line 6
    return p2;
}

void aligned_free( void* p ) {
    void* p1 = ((void**)p)[-1];         // get the pointer to the buffer we allocated
    free( p1 );
}

int main(int argc , char* argv[]){
    //void *p = aligned_malloc(atoi(argv[1]), atoi(argv[2]));
	void *p = aligned_malloc(333, 32);
    aligned_free(p);
}

//allocates a two dimensional array
int ** My2DAlloc(int rows, int cols){
	int header = rows*sizeof(int *);
	int data = rows*cols*sizeof(int);
	int **rowptr = (int**)malloc(header+data);
	int *buf = (int*)(rowptr+rows);
	for(int i=0; i<cols; i++){
		rowptr[i] = buf+i*cols;
	}
	return rowptr;
}

		//int ** d = (int**)malloc(rows * sizeof(int*));
        //for(int i = 0; i < rows; ++i){
        //    d[i] = (int*)malloc(cols * sizeof(int));
        //    d[i][0] = i;//sub string in word1 range [0,i) edit to ""
        //}


//Find a un-contained integer from a file with four billion integers, given 1GB memory
int main(){
    // freopen("12.3.in", "w", stdout);
    // int miss = 12345;
    // for(int i=0; i<20000; ++i){
    //     if(i == miss) continue;
    //     cout<<i<<endl;
    // }
    // fclose(stdout);
    
    freopen("12.3.in", "r", stdin);
    
    int int_len = sizeof(int) * 8;
    int bit_len = 0xFFFFFFFF / int_len;
    int* bit = new int[bit_len];
    int v;
    while(scanf("%d", &v) != EOF){
        bit[v/int_len] |= 1<<(v%int_len);
    }
    bool found = false;
    for(int i=0; i<bit_len; ++i){
        for(int j=0; j<int_len; ++j){
            if((bit[i] & (1<<j)) == 0){
                cout<<i*int_len + j<<endl;
                found = true;
                break;
            }
    
        }
        if(found) break;
    }
    
    delete[] bit;
    fclose(stdin);
    return 0;
}

//Find a un-contained integer from a file with four billion integers, given 10MB memory
int main(){
    freopen("12.3.in", "r", stdin);// 20000 number
    int int_len = sizeof(int) * 8;
    int totalnum = 20000;
    int blocksize = 2000;
    int blocknum = totalnum / blocksize;
    int* block = new int[blocknum];
    int* bit = new int[blocksize/int_len+1];
    int v;
    while(scanf("%d", &v) != EOF){
        ++block[v/blocksize];
    }
    fclose(stdin);
    int start;
    for(int i=0; i<blocknum; ++i){
        if(block[i] < blocksize){
            start = i * blocksize;
            break;
        }
    }
    freopen("12.3.in", "r", stdin);
    while(scanf("%d", &v) != EOF){
        if(v>=start && v<start+blocksize){
            v -= start; // make v in [0, blocksize)
            bit[v/int_len] |= 1<<(v%int_len);
        }
    }

    bool found = false;
    for(int i=0; i<blocksize/int_len+1; ++i){
        for(int j=0; j<int_len; ++j){
            if((bit[i] & (1<<j)) == 0){
                cout<<i*int_len+j+start<<endl;
                found = true;
                break;
            }
        }
        if(found) break;
    }

    delete[] block;
    delete[] bit;
    fclose(stdin);
    return 0;
}
