#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    //не поміститься в int
    long long ll_val = 0x11221122aabbaabbLL;
    printf("Long long (%zuB): 0x%llx\n", sizeof(ll_val), ll_val);

    int *int_ptr = (int *)malloc(sizeof(int));
    if(int_ptr == NULL){
        perror("Not allocated\n");
        exit(1);
    }

    printf("Allocated long long as int (%zuB) at: %p\n", sizeof(int), (void *)int_ptr);
    //копіювання виходить з втратою частини початкового long long, бо копіюються
    //тільки молодші sizeof(int) байтів з ll_val в int_ptr. Замість long long неправильно
    //приведено тип int при копіюванні в heap, в який перший тип не влазить
    memcpy(int_ptr, &ll_val, sizeof(int));
    //читаємо як int
    int int_val = *int_ptr;
    printf("Allocated int: 0x%x\n", int_val);
    //має бути втрата даних, тобто з початкового long long 0x11221122aabbaabb тільки молодші половина байтів
    //aabbaabb зберіжуться, а старші 11221122 - втратяться (int = 4B, long long = 8B)
    free(int_ptr);
}
