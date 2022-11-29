#include "user/user.h"
#define NULL 0

//
static Node* root = NULL;

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

//prototypes
void* _malloc(int size);
void _free(void *ptr);
Node* findFNode(Node *sNode, int size);