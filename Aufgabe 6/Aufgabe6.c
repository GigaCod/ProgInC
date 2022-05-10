#include <stdio.h> //fuer printf()
#include <stdlib.h> //fuer malloc()
#include <errno.h> //fuer errno
enum op {
    NOP,VALUEINT,VALUESHORT,VALUECHAR,PLUS,MINUS,GETEILT,MAL,SHORT2INT,CHAR2INT,
};

union value {
    int valuei;
    short values;
    char valuec;
};

struct bb {
    struct bb *op1;
    struct bb *op2;
    enum op op;
    union value value;
};
//Beispieldatensatz (statisch)
struct bb operand1= {NULL      ,NULL     ,VALUEINT  ,{10}};
struct bb operand2= {NULL      ,NULL     ,VALUEINT  ,{20}};
struct bb operand3a={NULL      ,NULL     ,VALUESHORT,.value.valuei=30};
struct bb operand3b={&operand3a,NULL     ,SHORT2INT ,{0}};
struct bb op1=      {&operand1 ,&operand2,PLUS      ,{0}};
struct bb op2=      {&op1    ,&operand3b,PLUS     ,{0}};
enum leftright {ND,LEFT,RIGHT};

void bb_debug(struct bb *root,enum leftright lr)
{
    if((root->op == SHORT2INT) || (root->op == CHAR2INT))
        printf("(int)(");
    else if((root->op == PLUS) || (root->op == MINUS) ||
        (root->op == MAL) || (root->op == GETEILT ))
        printf("[");
    //Rekursives durchlaufen
    if(root->op1 != NULL)
        bb_debug(root->op1,LEFT);
    else {
    if((root->op==VALUEINT) && ((lr==LEFT)||(lr==ND)))
        printf("i%d",root->value.valuei);
    else if((root->op==VALUESHORT) && ((lr==LEFT)||(lr==ND)))
        printf("s%d",root->value.values);
    }
    if(root->op == PLUS)
        printf(" + ");
    else if(root->op == MINUS)
        printf(" - ");
    else if(root->op == GETEILT)
        printf(" / ");
    else if(root->op == MAL)
        printf(" * ");
    //Rekursives durchlaufen
    if(root->op2 != NULL)
        bb_debug(root->op2,RIGHT);
    else {
    if((root->op==VALUEINT) && (lr==RIGHT))
        printf("i%d",root->value.valuei);
    else if((root->op==VALUESHORT) && (lr==RIGHT))
        printf("s%d",root->value.values);
    }
    if((root->op == SHORT2INT) || (root->op == CHAR2INT))
        printf(")");
    else if((root->op == PLUS) || (root->op == MINUS) ||
        (root->op == MAL) || (root->op == GETEILT ))
        printf("]");
}
    //Aufgabe 1
int bb_solve(struct bb *root)
{
    switch(root->op) {
    case NOP:
    break;
    }
    return -1;
}
    //Aufgabe 3
struct bb* bb_add(enum op op,union value value,
struct bb *topl,struct bb *topr)
{
}
    //Aufgabe 4
void bb_free(struct bb *root)
{
}
int main(void)
{
bb_debug(&op2,ND);
printf("\nSolve=%d\n",bb_solve(&op2));
//Aufgabe 2
//Statischer Baum für: '9‐5*6*(7+8)‐9'
//bb_debug(&new,ND);
//printf("\nsolve=%d\n",bb_solve(&new));
//Aufgabe 3
//Dynamischer Baum für: '2+3*7'
//struct bb *root=bb_add(PLUS ,(union value){0},NULL,NULL);
//bb_debug(root,ND);
//printf("\nsolve=%d\n",bb_solve(root));
//Aufgabe 4
//db_free(root);
return 0;
}