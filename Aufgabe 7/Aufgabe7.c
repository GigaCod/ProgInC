/*---------------------------------------------------------------------------------------------*/
/*                    H-Datei                                                                  */
/*---------------------------------------------------------------------------------------------*/
#ifndef H_DATEI_include
#define H_DATEI_include
//Header-Dateien, die zwingend hier im Header benötigt werden
#include <stdio.h>   //fuer printf() size_t stderr
//Deklaration von Public Makros
#define ERROR(text, arg... ) (fflush(stdout),fprintf(stderr,"\e[31m%s() Error:\e[30m "\
                                text"'\n",__func__,##arg) )
//Deklaration von Public Datentypen / Aliase
typedef enum {DUMP_8, DUMP_16, DUMP_32, 
                DUMP_8A,DUMP_16A,DUMP_32A,} DUMP_MODE;
//Deklarationen von Public Funktionen und Variablen 
int dump(void *start, size_t len, int width, DUMP_MODE mode);
void  vl_init(void);
void  vl_close(void);
int   vl_addfront(const char *value);
int   vl_addback(const char *value);
char *vl_getback(void);
#endif
/*---------------------------------------------------------------------------------------------*/
/*                    C-Datei                                                                  */
/*---------------------------------------------------------------------------------------------*/
//#include <stdio.h>   //fuer printf() size_t stderr
#include <string.h>    //fuer strcpy() memcpy() 
#include <stdint.h>    //fuer uintptr_t   uint32_t
#include <signal.h>    //fuer sigaction()
#include <stdlib.h>    //füer exit()
#include <errno.h>     //für errno
#include <limits.h>    //für LONG_MAX,LONG_MIN
//#include "main.h"
//Deklarationen von Datei'privaten' Funktionen und Variablen 
static int signal_init(void);
extern int signal_flag;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct vl {
	struct vl *next;
	char       data[];
} vl_t;
vl_t *head;
void vl_init(void)
{
    head=NULL;
}
void vl_close(void)
{
    //Liste durchgehen und allen Speicher löschen
}
static void vl_debug(void)
{
    printf("------------\n");
    printf("head=%p\n",head);
    if(head!=NULL)
        for(vl_t *ptr=head;ptr!=NULL;ptr=ptr->next)
            printf("%p: '%s'\n",ptr,ptr->data);
    
    //Größe des benötigten Speichers berechnen
}
int vl_addfront(const char *value)
{
        vl_t *newVl = (vl_t *) malloc(sizeof(vl_t)+strlen(value)+1);
        newVl -> next = head;
        strcpy(newVl -> data, value);
        head = newVl;
    return 0;
}
int vl_addback(const char *value)
{
    if(head == NULL){
        vl_addfront(value);
    }else{
        vl_t *temp = head;
        while(temp->next != NULL){
            temp = temp->next; 
        }
        vl_t *lastVl = (vl_t *) malloc(sizeof(vl_t)+strlen(value)+1);
        temp -> next = lastVl;
        lastVl -> next = NULL;
        strcpy(lastVl -> data, value);
    }
    return 0;
}
char *vl_getback(void)
{
    if(head == NULL){
        return NULL;
    }else if(head->next == NULL){
        char *copy = malloc(strlen(head->data) + 1);
        strcpy(copy,head->data);
        free(head);
        head = NULL;
        return copy;
    }else{
        vl_t *lastVl = head-> next;
        while(lastVl->next != NULL){
            lastVl = lastVl->next;
        }
        char *copy = malloc(strlen(lastVl->data)+1);
        strcpy(copy,lastVl->data );
        free(lastVl);
        lastVl = NULL;
        return copy;
    }

    return NULL;
}
 
const char help[]= "\n"
  "setf <value> - Fügt <value> am Anfang der Liste ein\n"
  "setb <value> - Fügt <value> am Ende der Liste ein\n"
  "getb         - Gibt das letzte Element zurück und \n"
  "               entfernt dieses aus der Liste\n"
  "\e[1mdebug\e[0m        - Gibt die gesamte Lite aus\n"
  "\e[1mdump\e[0m         - Gibt ein Speicherabbild der Liste aus\n"
  "help         - Führt alle Operationen auf.\n"
  "\e[1mquit\e[0m         - Beendet das Programm.\n";
int main(int argc, char const *argv[]) {
    //Konstruktoren 
    if(signal_init())
        return 1; 
    vl_init();
    printf("File:"__FILE__ " erstellt am "__DATE__" um "__TIME__ " gestartet\n");
    printf(help);
    while(signal_flag==0) {
        char input[100];
        fgets(input, 100, stdin);
        char *arg1 = strtok(input, " \n\r");
        char *arg2 = strtok(NULL, " \n\r");
        
        if(arg1==NULL) {
            continue;
        }
        else if((strcmp(arg1,"setf")==0) && (arg2!=NULL)) {
            if(vl_addfront(arg2) == -1)
                printf("Fehler: Element konnte nicht eingefügt werden");
        }
        else if((strcmp(arg1,"setb")==0) && (arg2!=NULL)) {
            if(vl_addback(arg2) == -1)
                printf("Fehler: Element konnte nicht eingefügt werden");
        }
        else if(strcmp(arg1,"getb")==0)  {
            char *ret=vl_getback();
            if(ret!=NULL) {
                printf("'%s'",ret);
                free(ret);
            }
        }
        else if(strcmp(arg1,"debug")==0) {
            vl_debug();
        }
        else if((strcmp(arg1,"dump")==0) && (head!=NULL)) {
            printf("-------------\n");
            printf("head=%p\n",head);
            void *start=head;
            for(vl_t *ptr=head;ptr!=NULL;ptr=ptr->next)
                if((void *)ptr<start)
                    start=ptr;
            dump(start,256,16,DUMP_8A);
        }
        else if(strcmp(arg1,"help")==0) {
            printf(help);
        }
        else if(strcmp(arg1,"quit")==0) {
            break;
        }
        else {
            printf("unbekanntes Kommando\n");
        }
    }
    vl_close();
    return 0;
}
/*---------------------------------------------------------------------------------------------*/
int signal_flag=0;
static void signal_handler( int  signo )
{
    signal_flag=signo;
    fflush(stdout);
    switch(signo)
    {
        case SIGTERM:
            ERROR( "Signal 'SIGTERM -> Termiantion, generated with kill()' called!\n\r");
            break;
        case SIGINT:
            ERROR( "Signal 'Program Interrrupt, generated by ctrl-c!' called!\n\r");
            break;
        case SIGQUIT:
            ERROR( "Signal 'SIGQUIT -> Program Quit, genated by ctrl-\\    with CoreDump!' called!\n\r");
            break;
        case SIGKILL:
            ERROR( "Signal 'SIGKILL -> Immediate Programm Termination (cannot be handled or ignored)' called!\n\r");
            break;
        case SIGABRT:
            ERROR( "Signal 'SIGABRT -> Indicate an error detected by the program itself and reported by calling abort().' called!\n\r");
            break;
        case SIGFPE:
            ERROR( "Signal 'SIGFPE -> FPU-Fehler' called\n\r");
            exit(1);
            break;
        case SIGSEGV:
            ERROR("Signal 'SIGSEGV' -> Illegaler Speicherzugriff");
            exit(1);
        default:
            ERROR( "Signal %d called!\n\r", signo );
            break;
    }
}
static int signal_init(void)
{
    struct sigaction   sigterm_action;
    sigterm_action.sa_handler = signal_handler;
    sigemptyset( & sigterm_action.sa_mask );
    sigterm_action.sa_flags = 0;
    if( sigaction( SIGSEGV , &sigterm_action, NULL ) != 0 )
        return ERROR("SIGSEGV failed"),1;
    if( sigaction( SIGINT , &sigterm_action, NULL ) != 0 )
        return ERROR("SIGABRT failed"),1;
    return 0;
}
/*---------------------------------------------------------------------------------------------*/
static char *dump_str[]={"8-Bit","16-Bit","32-Bit",
                    "8-Bit","16-Bit","32-Bit",};
//Bei Nutzung dieser Funktion darf der Compiler-Schalter -Fsanitze=address nicht genutzt werden
int dump(void *start, size_t len, int width, DUMP_MODE mode)
{
    void *ptr;
    uintptr_t size;
    switch(mode) {
        case DUMP_8: 
        case DUMP_8A:
            size=0x01;
            break;
        case DUMP_16:
        case DUMP_16A: 
            size=0x02;
            break;
        case DUMP_32:
        case DUMP_32A:
            size=0x04;
            break;
        default:
            ERROR("Illegal Mode");
            return -1;
    }
    ptr=(void *)((uintptr_t)start & ~(size-1));
//   printf("Adressbreite: %d Bytes von 0 .... %p\n",sizeof(char *),(uintptr_t)-1);
    printf("--- Dump %10p .. %10p Mode=%s ---",start,start+len-1,dump_str[mode]);
    while(ptr<start+len) {
        printf("\n%10p:",ptr);
        for(int lauf=0;lauf<width;lauf++) 
            switch(mode) {
                case DUMP_8:
                case DUMP_8A:
                    printf(" %02x",*(((unsigned char *)ptr)+lauf)&0xFF);
                    break;
                case DUMP_16:
                case DUMP_16A: 
                    printf(" %04x",*(((unsigned short *)ptr)+lauf)&0xFFFF);
                    break;
                case DUMP_32:
                case DUMP_32A:
                    printf(" %08x",*(((unsigned int *)ptr)+lauf));
                    break;
            }
        if((mode==DUMP_8A) || (mode==DUMP_16A) || (mode==DUMP_32A)) {
            printf(" - ");
            for(int lauf=0;lauf<(width*size);lauf++) 
                switch(mode) {
                    case DUMP_8A:
                    case DUMP_16A:
                    case DUMP_32A:
                        printf("%c",*(((unsigned char *)ptr)+lauf)&0xFF);
                        break;
                    case DUMP_8:
                    case DUMP_16:
                    case DUMP_32:
                        break;
                }
        }
        ptr+=width*size;
    }
    return 0;
}
