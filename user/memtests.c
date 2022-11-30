#include "user/memory_management.c"

int main()
{
    int *int32 = _malloc(32);
    printf("int32 address %p\n",int32);

    int *int16 = _malloc(16);
    printf("int16 address %p\n",int16);
    

    int *int8 = _malloc(8);
    printf("int8 address %p\n",int8);

    _free(int32);
    Node * N32 = (Node *)((char*)int32 - sizeof(Node));
    printf("prev add %p, next add %p\n",N32->prev,N32->next);
    _free(int16);
    Node * N16 = (Node *)((char*)int16 - sizeof(Node));
    printf("prev add %p, next add %p\n",N16->prev,N16->next);
    _free(int8);
    Node * N8 = (Node *)((char*)int8 - sizeof(Node));
    printf("prev add %p, next add %p\n",N8->prev,N8->next);

    //int *int32_ = _malloc(32);
    //printf("int32_ address %p\n",int32_);
    int *int16_ = _malloc(16);
    printf("int16_ address %p\n",int16_);
    int *int8_1 = _malloc(8);
    printf("int8_1 address %p\n",int8_1);
    int *int4_ = _malloc(4);
    printf("int4_ address %p\n",int4_);
    int *int4_1 = _malloc(4);
    printf("int4_1 address %p\n",int4_1);
    //_free(int32_);
    _free(int16_);
    Node * N16_ = (Node *)((char*)int16_ - sizeof(Node));
    printf("prev add %p, next add %p\n",N16_->prev,N16_->next);
    _free(int8_1);
    Node * N8_1 = (Node *)((char*)int8_1 - sizeof(Node));
    printf("prev add %p, next add %p\n",N8_1->prev,N8_1->next);
    _free(int4_);   
    Node * N4_ = (Node *)((char *)int4_ - sizeof(Node));
    printf("prev add %p, next add %p\n",N4_->prev,N4_->next); 
    _free(int4_1);
    Node * N4_1 = (Node *)((char *)int4_1 - sizeof(Node));
    printf("prev add %p, next add %p\n",N4_1->prev,N4_1->next);
    return 0;
}
