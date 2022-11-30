#include "kernel/types.h"
#include "user/user.h"
#define NULL 0

//Node structure for segmenting blocks
typedef struct Node {
    //block size
    int size;
    //pointer to prev allocated or free
    struct Node* prev;
    //pointer to next allocated or free
    struct Node* next;
} Node;



//prototypes
Node* findFNode(Node *sNode, int size);
int remNode(Node *rNode, Node *nNode);
void* _malloc(int size);
void _free(void *ptr);