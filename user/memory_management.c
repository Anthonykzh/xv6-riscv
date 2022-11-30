#include "user/memory_management.h"

//pointer to first free block
static Node* root = NULL;

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

//remove Node from free linked list
int remNode(Node *rNode, Node *nNode){
    if(nNode != NULL){
        if(rNode->next == NULL){
            if(rNode->prev == NULL){
                root = nNode;
                nNode->prev = NULL;
            }
            else{
                rNode->prev->next = nNode;
            }
        }
        else{
            if(rNode->prev == NULL){
                root = nNode;
                nNode->next = rNode->next;
                rNode->next->prev = nNode;
            }
            else{
                rNode->next->prev=nNode;
                rNode->prev->next=nNode;
                nNode->next=rNode->next;
                nNode->prev=rNode->prev;
            }
        }
    }
    else if(nNode == NULL){
        if(rNode->next == NULL){
            if(rNode->prev == NULL){
                root = NULL;
            }
            else{
                rNode->prev->next = NULL;
            }
        }
        else{
            if(rNode->prev == NULL){
                root = rNode->next;
                rNode->prev = NULL;
            }
            else{
                rNode->next->prev=rNode->prev;
                rNode->prev->next=rNode->next;
            }
        }
    }
    return 0;
}

void *_malloc(int size){
    if(size <= 0){
        return NULL;
    }
    else{
        void *address;
        int newSize;
        int reqsize;
        Node * newBlock;
        Node * repBlock;

        newSize = (8-(size%8))+size;
        reqsize = newSize + sizeof(Node);
        repBlock = findFNode(root,newSize);
        if(repBlock != NULL){

            if(repBlock->size <= reqsize){
                remNode(repBlock,NULL);
            }
            else{
                newBlock = (Node *)((char *)repBlock + newSize);
                newBlock->size = repBlock->size - reqsize;
                repBlock->size = newSize;
                remNode(repBlock,newBlock);
            }

            address = (char *)repBlock + sizeof(Node);
            return address;
        }
        else{
        newBlock = (Node *) sbrk(reqsize);
        address = (char *)newBlock + sizeof(Node);
        return address;
        }
    }
}

void _free(void *ptr){
    if(ptr != NULL){
        Node *block = (Node *)((char *)ptr - sizeof(Node));
        if (root!=NULL){
            root->prev = block;
            block->next = root;
            root = block;
        }
        else{
            root = block;
            block->prev = NULL;
            block->next = NULL;
        }
    }
}