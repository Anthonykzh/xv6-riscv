#include "user/memory_management.h"

// find first free node of size
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
    return NULL;
}

// split block
void *splitblock(Node *sBlock, int size){

}

void *_malloc(int size){
    void *address;
    int newSize;
    int reqsize;
    Node * newBlock;
    Node * repBlock;

    newSize = (8-(size%8))+size;
    reqsize = newSize + sizeof(Node);
    repBlock = findFNode(root,reqsize);
    if(repBlock != NULL){
        if(root == repBlock){
            root = NULL;
        }
        repBlock->af = 1;
        repBlock->size = newSize;

        newBlock = repBlock + newSize;
        newBlock->af = 0;
        newBlock->size = repBlock->size - reqsize;
        newBlock->next = repBlock->next;
        newBlock->prev = repBlock->prev;
        
        repBlock->next->prev = newBlock;
        repBlock->prev->next = newBlock;

        return repBlock;
    }
    else{
    newBlock = (Node *) sbrk(reqsize);
    newBlock->af = 1;
    newBlock->size = size;
    address = (char *)newBlock + sizeof(Node);
    return address;
    }
}

void _free(void *ptr){
    Node *block = ptr - sizeof(Node);
    block->af = 0;
    if (root!=NULL){
        root->prev = block;
        block->next = root;
        root = block;
    }
}