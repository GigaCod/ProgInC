#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    char input[100];
    printf(">>");
    fgets(input,100,stdin);

    int tmp = atoi(input);
    int result = 0;
    while (tmp != 0)
    {
        result += tmp % 10;
        tmp /= 10; 
    }
    printf("Result= %d\n",result);
    return 0;
}