#include "user/memory_management.h"

Node *findFNode(Node *sNode, int size){
    if(sNode == NULL){
        return NULL;
    }
    else if(size > sNode->size){
        findFNode(sNode->next, size);
    }
    else{
        return sNode;
    }
}

void *_malloc(int size){
    void *address;
    int reqsize;
    Node * newBlock;

    reqsize = size + sizeof(Node);
    newBlock = (Node *) sbrk(reqsize);
    newBlock->af = 1;
    newBlock->size = size;
    address = (char *)newBlock + sizeof(Node);
    return address;
}

void _free(void *ptr){
    Node *block = ptr - sizeof(Node);
    block->af = 0;
}