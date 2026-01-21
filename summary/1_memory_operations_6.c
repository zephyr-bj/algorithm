//[1]aligned malloc and free
//[1]allocate a two dimension array
//[1]memory copy between overlapping buffers
//[1]my_sizeof
//[1]my_offset
//[1]big endian or small endian

//implementation of the sizeof operator
#define my_sizeof(x) (char *)(&x+1)-(char*)(&x)
//Is sizeof() a macro or a function? I said macro... asked why not a function (leave alone the inline advantage of a macro)
 /*Ans: In C there is no overloading. We send various 'Types' of parameters to sizeof. Macros dont do type checking. Hence Macros!*/

//write a macro to give offset of particular field in structure.Like struct abc { int a,int b,char c}. 
//Write a macro like offset(abc , c) to find offset of c from top.
#define offset(abc,c) ((char*)(&(abc.c)) - (char*)(&(abc)))
//Write a macro to which you can pass a name of a structure and a name of one of its fields and get a relative offset of this field within the structure. 
#define my_offsetof(type, f) (&(((type *) 0)->f))
//Say a function takes a pointer and allocates it some memory. How would the function 'Prototype' be? 
void memallocate (size_t size, void ** p); 


//aligned malloc and free (hits:x)
void *aligned_malloc(size_t size, size_t alignment) {
    assert((alignment & (alignment - 1)) == 0);
    void * p = malloc(size + alignment - 1 + sizeof(void*));
    if (p == NULL) {
        return NULL;
    }
    uintptr_t aligned_addr = ((uintptr_t)p + sizeof(void*) + alignment - 1) & (~(alignment - 1));
    *((void**)(aligned_addr - sizeof(void*))) = p;
    return (void*)aligned_addr;
}

void aligned_free( void* p ) {
    if (p == NULL) {
        return;
    }
    void* p1 = *((void**)((uintptr_t)p - sizeof(void*)));
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
	  for(int i=0; i<rows; i++){
		    rowptr[i] = buf+i*cols;
	  }
	  return rowptr;
}

// memmov: memcpy for overlapping cases
void memmove(void *dest, void *src, int size){
    int i;
    if (dest < src) {
        for (i = 0; i < size; i++) {
            ((char *)dest)[i] = ((char *)src)[i];
        }
    } else {
        for (i = size - 1; i >= 0; i--) {
            ((char *)dest)[i] = ((char *)src)[i];
        }
    }
} 

//find whether a machine is big endian or little endian
bool isSmall_endian(){
    short int word = 0x0001;
    char * byte = (char *)&word;
    if(*byte == 1) return true;
    else return false;
}

