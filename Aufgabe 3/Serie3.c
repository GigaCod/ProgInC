#include <stdio.h>
#include <string.h>

char *mystrstr(char *haystack, char *needle);
char *mystrtok(char *str, const char *delim);

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
char src2[]="abc_aaabd";
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
printf("%s\n",mystrstr(src2, "absd"));


char str3[]="Hello World";
char *ptr6=strtok(str3," ");
char *ptr7=strtok(NULL," ");
char *ptr8=strtok(NULL," ");
char str4[]="hello,world ich";
printf("%s \n",str4);
char *ptr9=strtok(str4," ,");  //Zweites Argument beinhaltet
printf("%s \n",str4);
char *ptr10=strtok(NULL," ,");  //ein Leerzeichen und ein Komma
printf(" \n"]);
char *ptr11=strtok(str4," ,");
char *ptr12=strtok(NULL," ,");

printf("%p %p \n",str3,ptr6);
printf("%p %p \n",str3,ptr7);
printf("%p %p \n",str3,ptr8);
printf("%p %p \n",str4,ptr9);
printf("%p %p \n",str4,ptr10);
printf("%p %p \n",str4,ptr11);
printf("%p %p \n",str4,ptr12);
}

//3------------------------------------------------

char *mystrstr(char *haystack, char *needle) {

    size_t haystackSize = strlen(haystack); // 5
    size_t needleSize = strlen(needle); // 1

    if(haystackSize < needleSize){
        return "NULL";
    }
    if(needleSize == 0){
        return haystack;
    }

    int wordFound = 0;
    int needlePos = 0;
    int tempHaystackPos = 0;

    for(int haystackPos = 0; haystackPos < haystackSize; haystackPos++){
        printf("%i:%c vs %c \n",haystackPos, haystack[haystackPos], needle[needlePos]);
        if(haystack[haystackPos] == needle[needlePos] && needleSize + haystackPos <= haystackSize){
            tempHaystackPos = haystackPos;
            for(int needleCounter = 0; needleCounter < needleSize; needleCounter++){
                printf("In der Schleife \n");
                if(haystack[tempHaystackPos] == needle[needlePos]){
                    wordFound++;
                    needlePos++;
                    tempHaystackPos++;
                    if(wordFound == needleSize){
                        return &haystack[tempHaystackPos-needleSize];
                    }
                }else{
                    wordFound = 0;
                    needlePos = 0;
                    needleCounter = needleSize;
                }
            }
        }else{
            wordFound = 0;
            needlePos = 0;
        } 

    };
    return "NULL";


}
//4------------------------------------------------

char *mystrtok(char *str, const char *delim){

}





