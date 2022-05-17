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
//Aufgabe 2 //Statischer Baum für: '9‐5*6*(7+8)‐9'
struct bb neun=     {NULL        ,NULL     ,VALUEINT  ,{9}};
struct bb sieben=   {NULL        ,NULL     ,VALUEINT  ,{7}};
struct bb acht=     {NULL        ,NULL     ,VALUEINT  ,{8}};
struct bb fuenf=    {NULL        ,NULL     ,VALUEINT  ,{5}};
struct bb sechs=    {NULL        ,NULL     ,VALUEINT  ,{6}};

struct bb nebenMul1= {&fuenf      ,&sechs     , MAL  ,{0}};
struct bb nebenPlus1= {&sieben      ,&acht      , PLUS  ,{0}};
struct bb hauptMul= {&nebenMul1  ,&nebenPlus1,  MAL  ,{0}};
struct bb erstesMinus= {&neun      ,&hauptMul      , MINUS  ,{0}};
struct bb new= {&erstesMinus      ,&neun      , MINUS  ,{0}};


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
    return 0;
    case VALUEINT:
    return root -> value.valuei;
    case VALUESHORT:
    return root -> value.values;
    case VALUECHAR:
    return root -> value.valuec;
    case PLUS:
    return bb_solve(root -> op1) + bb_solve(root -> op2);
    case MINUS:
    return bb_solve(root -> op1) - bb_solve(root -> op2);
    case GETEILT:
    return bb_solve(root -> op1) / bb_solve(root -> op2);
    case MAL:
    return bb_solve(root -> op1) * bb_solve(root -> op2);
    case SHORT2INT:
    return (int) bb_solve(root -> op1);
    case CHAR2INT:
    return (int) bb_solve(root -> op1);
    }
    return -1;
}
    //Aufgabe 3
struct bb* bb_add(enum op op,union value value,struct bb *topl,struct bb *topr){
    
    struct bb *result = (struct bb *) malloc(sizeof(struct bb));

    if(result == NULL){
        return NULL;
    }
    result->op1 = topl; 
    result->op2 = topr;
    result->op = op;
    result->value = value;
    
    return result;
}
    //Aufgabe 4
void bb_free(struct bb *root)
{
    if(root->op1 != NULL){
        bb_free(root->op1);    
    }
    if(root->op2 != NULL){
        bb_free(root->op2);
    }
    free(root);
}
int main(void)
{
bb_debug(&op2,ND);
printf("\nSolve=%d\n",bb_solve(&op2));
//Aufgabe 2
//Statischer Baum für: '9‐5*6*(7+8)‐9'
bb_debug(&new,ND);
printf("\nsolve=%d\n",bb_solve(&new));
//Aufgabe 3
//Dynamischer Baum für: '2+3*7'
struct bb *two=bb_add(VALUEINT ,(union value){2},NULL,NULL);
struct bb *three=bb_add(VALUEINT ,(union value){3},NULL,NULL);
struct bb *seven=bb_add(VALUEINT ,(union value){7},NULL,NULL);

struct bb *multi=bb_add(MAL ,(union value){0},three,seven);
struct bb *root=bb_add(PLUS ,(union value){0},two,multi);
bb_debug(root,ND);
printf("\nsolve=%d\n",bb_solve(root));
//Aufgabe 4
bb_free(root);
return 0;
}