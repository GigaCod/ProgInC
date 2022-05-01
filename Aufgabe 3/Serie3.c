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
/*
printf("%p %p \n",src,ptr1);
printf("%p %p \n",src,ptr2);
printf("%p %p \n",src,ptr3);
printf("%p %p \n",src,ptr4);
printf("%p %p \n",src,ptr5);
*/
printf("%p\n",mystrstr(src2, "absd"));


char str3[]="Hello World";
char *ptr6=strtok(str3," ");
char *ptr7=strtok(NULL," ");
char *ptr8=strtok(NULL," ");
char str4[]="hello,world ich";
char *ptr9=strtok(str4," ,");  //Zweites Argument beinhaltet
char *ptr10=strtok(NULL," ,");  //ein Leerzeichen und ein Komma
char *ptr11=strtok(str4," ,");
char *ptr12=strtok(NULL," ,");
/*
printf("%p %p \n",str3,ptr6);
printf("%p %p \n",str3,ptr7);
printf("%p %p \n",str3,ptr8);
printf("%p %p \n",str4,ptr9);
printf("%p %p \n",str4,ptr10);
printf("%p %p \n",str4,ptr11);
printf("%p %p \n",str4,ptr12);
*/
char globalString[]="Ich bin ein sos String";
char globalString2[]="Ich bin ein sos String";

printf("------------------ \n");
printf("%s \n", mystrtok(globalString, " "));
printf("%s \n", mystrtok(NULL, " "));
printf("%s \n", mystrtok(NULL, " "));
printf("%s \n", mystrtok(NULL, " "));
printf("%s \n", mystrtok(NULL, " "));
printf("%s \n", mystrtok(NULL, " "));
printf("%s \n", mystrtok(NULL, " "));

printf("------------------ \n");
printf("%s \n", strtok(globalString2, " "));
printf("%s \n", strtok(NULL, " "));
printf("%s \n", strtok(NULL, " "));
printf("%s \n", strtok(NULL, " "));
printf("%s \n", strtok(NULL, " "));
printf("%s \n", strtok(NULL, " "));
printf("%s \n", strtok(NULL, " "));


}

//3------------------------------------------------

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
    int tempHaystackPos = 0;

    for(int haystackPos = 0; haystackPos < haystackSize; haystackPos++){
        if(haystack[haystackPos] == needle[needlePos] && needleSize + haystackPos <= haystackSize){
            tempHaystackPos = haystackPos;
            for(int needleCounter = 0; needleCounter < needleSize; needleCounter++){
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
    return NULL;


}
//4------------------------------------------------

int checkDelimiter(char character, const char *delim){
    size_t delimSize = strlen(delim);

    for(int i = 0; i < delimSize; i++){
        //printf("Charakter: %c vs ",character);
        //printf("Charakter: %c \n",delim[i]);
        if(character == delim[i]){
            //printf("ALARM \n");
            return 1;
        }
    }
    return 0;  
}
char *global = NULL;

char *mystrtok(char *str, const char *delim){

    size_t delimSize = strlen(delim);
    int counter = 0;

    if( str != NULL){
        global = str;
    }else{
        str = global;
    }

    while(!checkDelimiter(global[counter], delim) && global[counter] != '\0') {
        counter++;
    }

    if(global[counter] != '\0'){
        global[counter] = '\0';
        counter++;
        global = global + counter;
        while(str[counter] != '\0') {
            str[counter] = '\0';
            counter++;
        }
        printf("String: %s \n",str);
        return str;
    }else{
        global = global + counter;
        if(strlen(str)){
            return str;
        } 
    }
    return NULL;

}





