#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    int tmp = 0;
    int result = 0;

    if(argv[1])
    {
        tmp = atoi(argv[1]);
    }else{
        char input[100];
        printf(">>");
        fgets(input,100,stdin);
        tmp = atoi(input);
    }
    while (tmp)
    {
        result += tmp % 10;
        tmp /= 10; 
    }
    printf("Die Quersumme lautet= %d\n",result);
    return 0;
}