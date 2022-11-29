#include "kernel/types.h"
#include "user/user.h"
#define NULL 0

//Node structure for segmenting blocks
typedef struct Node {
    //if allocated af will be 1 else 0
    int af;
    //block size
    int size;
    //pointer to prev allocated or free
    struct Node* prev;
    //pointer to next allocated or free
    struct Node* next;
} Node;

//pointer to first free block
static Node* root = NULL;

//prototypes
Node* findFNode(Node *sNode, int size);
void *splitblock(Node *sBlock, int size);
void* _malloc(int size);
void _free(void *ptr);