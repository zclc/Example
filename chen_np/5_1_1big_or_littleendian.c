/*
 * @Author: zclc 2451433436@qq.com
 * @Date: 2023-02-19 20:13:08
 * @LastEditors: zclc 2451433436@qq.com
 * @LastEditTime: 2023-02-19 21:32:36
 * @FilePath: /chen_np/example/chen_np/big_or_littleendian.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    union  
    {
        short value;
        char union_bytes[sizeof(short)];
    }test;
    
    test.value = 0x0102;

    if (test.union_bytes[0] == 0x01 && test.union_bytes[1] == 0x02)
    {
        printf("big endien\n");
    }
    else if (test.union_bytes[0] == 0x02 && test.union_bytes[1] == 0x01)
    {
        printf("little endien\n");
    }
    else
    {
        printf("unkown...\n");
    }

    printf("------------------------\n");
    short a = 0x0102;
    char* c = (char*)&a;
    printf("%d\n",*c);
    if (*c == 0x01)
    {
        printf("big endien\n");
    }
    else if (*c == 0x02)
    {
        printf("little endien\n");
    }
    else
    {
        printf("unkown...\n");
    }

    return 0;
}