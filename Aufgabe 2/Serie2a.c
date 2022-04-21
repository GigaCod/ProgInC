#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    char str1[]="HalloWelt";
    char str2[]="Ich";
    char str3[]="?";
    int  var=4711;
    char str4[]="1234";
    char str5[]="Der String %s hat keine Bedeutung";

//1--------------------------------------------------------------------------------------------
    int firstLength = strlen(str1);
    int secondLength = strlen(str2);
    char str11[firstLength + secondLength + 1];

    int j = 0;
    for(int i = 0; str1[i] != '\0'; i++ ){
        str11[j] = str1[i];
        j++;
    };
    for(int i = 0; str2[i] != '\0'; i++ ){
        str11[j] = str2[i];
        j++;
    };
    str11[j] = '\0';
    printf("Ich bin str11: %s\n", str11);

//2--------------------------------------------------------------------------------------------
    char str12[firstLength + secondLength + 1];
    strcpy(str12, str1);
    strcpy(str12 + firstLength, str2);

    printf("Ich bin str12: %s\n", str12);
//3--------------------------------------------------------------------------------------------
    int size = firstLength + secondLength + 1;
    char str13[size];
    	
    memset(str13, '\0', size);

    strcat(str13, str1);
    strcat(str13 , str2);

    printf("Ich bin str13: %s\n", str13);
//4-------------------------------------------------------------------------------------------- 
    char str14[10];

    memset(str14, '\0', 10);  

    strncpy(str14, str1 , 3);
    printf("Ich bin str14: %s\n", str14);
    strncpy(str14, str1, 10);
    printf("Ich bin str14: %s\n", str14 );
    //strncpy(str14, str1, 12); //wirft einen Fehler, 
    //printf("%s\n", str14 ); 

//5--------------------------------------------------------------------------------------------
    char str15[10];
    char str155[10];

    memset(str15, '\0', 10);
    memset(str155, '\0', 10);

    strncat(str15, str1 , 3);
    printf("Ich bin str15: %s\n", str15);
    strncat(str155, str1, 12); // macht keine Probleme 
    printf("Ich bin str155: %s\n", str155);
    //strncpy(str15, str1, 12); //wirft einen Fehler, da er mehr Buchtaben einfügen will als Platz ist. 
    //printf("%s\n", str15 ); 
//6---------------------------------------------------------------------------------------------
    char str16[6];

    memset(str16, '\0', 6);

    sprintf(str16, "%i\n" , var);
    printf("Ich bin str16: %s", str16);
//7----------------------------------------------------------------------------------------------

    int aufgabe7 = atoi(str4);
    printf("Ich bin Aufgabe 7: %i\n", aufgabe7);
//8----------------------------------------------------------------------------------------------
    int fithLength = strlen(str5);
    char str18[size + fithLength - 1];

    memset(str18, '\0', size + fithLength - 1);

    int index = 0;
    for(int i = 0; str5[i] != '%';  i ++){
        str18[index] = str5[i];
        index++;
    }
    int indexStr5 = index + 2;

    strcat(str18, str1);
    index += firstLength;
    strcat(str18, str2);
    index += secondLength;
    strcat(str18, str3);
    index += 1;

    for(int i = indexStr5; str5[i] != '\0';  i ++){
        str18[index] = str5[i];
        index++;
    }

    printf("%s\n" , str18);
//9--------------------------------------------------------------------------------------------
   
    switch (1)
    {
    case 1:
        
        break;
    
    default: printf("Error");
    }
    return 0;
}