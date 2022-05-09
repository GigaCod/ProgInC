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

void stream_open (size_t alloc_size);
void stream_close(void);
int  stream_set  (char *str);
char *stream_get();

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

struct stream {
    char   *str;
    size_t  size_max;     //Größe des derzeit reservierten Speichers
    size_t  size_akt;     //Tatsächliche Größe
    size_t  alloc_size;   //Heap-Blöcke in vielfachen dieser Größe
} stream;

void stream_open(size_t alloc_size) {
    stream.str = NULL;
    stream.size_akt=0;  //Tatsächliche Größe
    stream.size_max=0;  //Reservierte Speichergröße
    stream.alloc_size=alloc_size;
}
void stream_close( void )
{
    free(stream.str);
    stream.str = NULL;
    stream.size_max = 0;
    stream.size_akt = 0;
    stream.alloc_size = 0;
    
}

void stream_debug(void)
{
    char *ptr_start=stream.str;
    char *ptr_end  =stream.str+stream.size_akt;
    printf("\n------------------------------------------\n");
    printf("size_max  =%8lu size_akt  =%8lu \n"
           "alloc_size=%8lu buffer    =%p\n",
           stream.size_max,stream.size_akt,
           stream.alloc_size,stream.str);
    for( ;ptr_start<ptr_end ; ptr_start++)
        printf("%c",*ptr_start);
    printf("\n------------------------------------------\n");
}

int stream_set(char *str)
{
    size_t extraStringSize = strlen(str); // 5
    int firstFlag = stream.str==NULL? 1 : 0;
    if(firstFlag || stream.size_akt + extraStringSize >= stream.size_max) {
        size_t newAlloc = (((extraStringSize + stream.size_akt ) /stream.alloc_size)+1)*stream.alloc_size; // 16
        stream.str = realloc(stream.str, newAlloc);
        stream.size_max = newAlloc;
        if(firstFlag){
            stream.str[0] = '\0';
        }
    
    }
    stream.size_akt += extraStringSize;
    strcat(stream.str, str);
    return 0;
}
    
char *stream_get()
{
    return stream.str;
}

const  char *HELP_STRING = 
    "Help\n"
    ">>help        --> Ohne Worte\n"
    ">>quit        --> Programm beenden\n"
    ">>set xxx     --> xxx an Stream anhängen\n"
    ">>get         --> Stream auslesen\n"
    ">>debug       --> Darstellung aller globalen Varialben\n";

int main(int argc, char *argv[]){
    //Konstruktoren 
    if(signal_init())
        return 1;
    
    printf("File:"__FILE__ " erstellt am "__DATE__" um "__TIME__ " gestartet\n");
    stream_open(16);
    while(1) {
        //scanf() bietet sich aufgrund der unterschiedlichen Anzahl von Eingabeparameter nicht an
        char input[100];
        char *arg1,*arg2;
        
        fgets(input,100,stdin);
        arg1=strtok(input," \n");
        
        if(arg1==NULL)
            continue;
        else if(!strcasecmp(arg1,"help"))
            printf("%s",HELP_STRING);
        else if(!strcasecmp(arg1,"quit"))
            break;
        else if(!strcasecmp(arg1,"debug"))
            stream_debug();
        else if(!strcasecmp(arg1,"set")) {
            arg2=strtok(NULL,"\n");
            if(arg2!=NULL) {
                if(stream_set(arg2)==-1)
                    fprintf(stderr,"\e[31mstream_set() Error:\e[30m Memory Failed\n");
            }
            else
                fprintf(stderr,"\e[31mstream_set() Error:\e[30m Missing Operand\n");
        }
        else if(!strcasecmp(arg1,"get")) {
            printf("%s \n", stream.str);
            printf("%s \n", stream_get());
        }
        else
            printf("Invalid Command\n");
    }
    stream_close();
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