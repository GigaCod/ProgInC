#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    if(argc<=1) {
        printf("Bitte übergeben sie mit dem Aufruf des Programms ein Argument");
        return 1;
    }
    int tmp = atoi(argv[1]);
    int result = 0;
    while (tmp != 0)
    {
        result += tmp % 10;
        tmp /= 10; 
    }
    printf("Das Ergebnis lautet %d \n" ,result);
    return 0;
}