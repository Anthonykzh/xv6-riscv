#include "user/memory_management.h"

//pointer to first free block
static Node* root = NULL;

// find first free node of size
Node *findFNode(Node *sNode, int size){
    if(sNode == NULL){
        return NULL;
    }
    else if(size > sNode->size){
        return findFNode(sNode->next, size);
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
                nNode->next = NULL;
            }
            else{
                rNode->prev->next = nNode;
                nNode->next = NULL;
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
                rNode->next->prev = NULL;
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
            //printf("\nrepNode add %p, repnode prev %p, rep node prev next %p, next prev %p\n",repBlock,repBlock->prev,repBlock->prev->next,repBlock->next->prev);
            if(repBlock->size <= reqsize){
                remNode(repBlock,NULL);
                //printf("here\n");
            }
            else{
                newBlock = (Node *)((char*)repBlock + reqsize);
                newBlock->size = repBlock->size - reqsize;
                repBlock->size = newSize;
                remNode(repBlock,newBlock);
                //printf("split node prev %p, next %p\n",newBlock->prev,newBlock->next);
            }
            //printf("repNode add %p, rep node prev next %p, next prev %p\n\n",repBlock,repBlock->prev->next,repBlock->next->prev);
            repBlock->next = NULL;
            repBlock->prev = NULL;

            address = (char *)repBlock + sizeof(Node);
            return address;
        }
        else{
        newBlock = (Node *) sbrk(reqsize);
        newBlock->size = newSize;
        address = (char *)newBlock + sizeof(Node);
        return address;
        }
    }
}

void _free(void *ptr){
    if(ptr != NULL){
        Node *block = ptr - sizeof(Node);
        //printf("freeblock address %p\n",block);
        if (root!=NULL){
            root->prev = block;
            block->next = root;
            block->prev = NULL;
            root = block;
        }
        else{
            root = block;
            block->prev = NULL;
            block->next = NULL;
        }
    }
}