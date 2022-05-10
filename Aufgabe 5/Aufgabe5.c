#include <stdio.h>
#include <string.h>

struct sub1struct {
    int integer;
    char str[40];
};

struct mainstruct {
    int a;
    int b[10];
    struct sub1struct c[3];
    struct sub2struct {
        int d;
        int e;
        struct sub1struct f;
    } g;
}h,i[2];

void debugMain(struct mainstruct c);

int main(int argc,char *argv[])
{
    struct {
        int x;
        int y;
        int z;
    };

    struct xyz2 {
        int x;
        int y;
        int z;
    };

    struct {
        int x;
        int y;
        int z;
    } xyz3;

    struct xyz4 {
        int x;
        int y;
        int z;
    } xyz4;

//------------------------------ 1 --------------------------------
// a
    //Erster Aufruf keine Variable möglich, da anonyme Deklaration

    struct xyz2 var2; // Variable für Datentypen angelegt,

    //Dritter aufruf nur auf Variablen Zugreifbar 
    xyz3.x = 4; // z.B.

    struct xyz4 var4; 
    xyz4.x = 4; // geht hierbei auch, weil bereits Variable erstellt wurde.

// b
    //1. Nur Sinvoll bei innerer Deklartion und Verwendung
    //2. Normale Deklaration überall nutzbar
    //3. Weiß nicht wo das sinnvoll sein kann
    //4. Normale Deklaration überall nutzbar, sowie direkte Variable deklariert.

// c/d 
    struct xyz2 test1;
    test1.x = 1;
    test1.y = 2;
    test1.z = 3;
    struct xyz2 test2;
    test2 = test1;
    printf("Zahl = %i \n",test2.x ); // Gleich geht
    //Unterschiedlich: var2 = xyz4; führt zu Fehlern geht nicht

// e
    struct xyz4 init1 = {1,2,3};
    struct xyz4 init2 = {.z=1, .x=2, .y=3};
    struct xyz4 init3 = {};
    struct xyz4 init4 = {};
    init4 = (struct xyz4) {1,2,3};

//------------------------------ 2 --------------------------------

struct mainstruct initStruct = {
    1,
    {2,3,4,5,6,7,8,9,10,11}, 
    12, "Test1", 13, "Test2", 14, "Test3",
    15, 16,
    17, "Test4"
};

struct mainstruct k = {
    .a = 1,
    .b = {2,3,4,5,6,7,8,9,10,11}, 
    .c = 
    {
        {.integer = 12, .str = "Test1"},
        {.integer = 13, .str = "Test2"},
        {.integer = 14, .str = "Test3"},
    },
    .g = 
    {
        .d = 15, .e = 16, .f = {.integer = 17, .str = "Test4"}
    }

};

debugMain(initStruct);
debugMain(k);

/*
struct sub1struct {
    int integer;
    char str[40];
};

struct mainstruct {
    int a;
    int b[10];
    struct sub1struct c[3];
    struct sub2struct {
        int d;
        int e;
        struct sub1struct f;
    } g;
}h,i[2];
*/
}

void debugMain(struct mainstruct ms){
    printf("---------ANFANG--------\n");
    printf("---------Mainstruct--------\n");
    printf("Mainstruct a: %i \n", ms.a);
    printf("Mainstruct b: ");
    for(int i = 0; i < 10; i++){
        if(i < 9){
            printf("%i, ", ms.b[i]);
        }else{
            printf("%i ", ms.b[i]);
        }
    };
    printf("\n-----------Substruct1----------- \n");
    for(int i = 0; i < 3; i++){
        printf("\tc[%i]=  Integer:  %i, ", i , ms.c[i].integer);
        printf("String: %s \n", ms.c[i].str);
    };
    printf("-----------Substruct2----------- \n");
    printf("\tSubstruct2 d: %i \n", ms.g.d);
    printf("\tSubstruct2 e: %i \n", ms.g.e);
    printf("\tSubstruct2 Substruct1= Integer: %i, String: %s \n", ms.g.f.integer,ms.g.f.str );
    printf("---------ENDE--------\n\n");
}




