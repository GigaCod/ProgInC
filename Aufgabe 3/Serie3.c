#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
//1----------------------------------------------
/*
strstr(haystack, needle)
Sucht nach einem Teilstring in einem String.
Wenn es findet, dann gibt er die Anfangsadresse des Teilstring wieder.
Wenn Needle leer ist = wird haystack wiedergegeben
Wenn nichts gefunden wird wird null wiedergegeben.
*/

//2----------------------------------------------

char src[]="hallo";
char *ptr1=strstr(src,"ll"); // Erwarte: das er es erfolgreich findet.
char *ptr2=strstr(src,"xy"); // Erwarte: NULL
char *ptr3=strstr(src,"hallo123"); // Erwarte: Fehler
char *ptr4=strstr(src,"l"); // Erwarte: erstes Vorkomniss
char *ptr5=strstr("ll",src); // Erwarte: Fehler 

printf("%p %p \n",src,ptr1);
printf("%p %p \n",src,ptr2);
printf("%p %p \n",src,ptr3);
printf("%p %p \n",src,ptr4);
printf("%p %p \n",src,ptr5);

}

//"abc_abcd1"  "abcd"
// |
// |
char *mystrstr(char *haystack, char *needle) {

    size_t haystackSize = strlen(haystack);
    size_t needleSize = strlen(needle);

    if(haystackSize < needleSize){
        return NULL;
    }
    if(needleSize == 0){
        return haystack;
    }
    int wordFound = 0;

    int needlePos = 0;

    for(int haystackPos = 0; haystackPos < haystackSize; haystackPos++){
        for(int needlePos = 0; needlePos < needleSize; needlePos++ ){

            if(haystack[haystackPos] == needle[needlePos]){
                
            }
        };

    };


}