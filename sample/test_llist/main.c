#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

// 定义llist_str的销毁回调函数
void dtor_str(void *user, void *ptr)
{
    (void)user;
    if (ptr)
        free(ptr);
    return;
}

int main(int argc, char *argv[])
{
    return 0;
}
