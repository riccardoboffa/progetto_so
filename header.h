#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h> /*Memoria Condivisa*/
#include <sys/msg.h> /*Messaggi*/
#include <sys/sem.h> /*Semafori*/


/*#define TEST_ERROR if (errno) {dprintf(STDERR_FILENO, \
                        "%s:%d: PID=%5d: Error %d (%s)\n", \
                        FILE, \
                        LINE, \
                        getpid(), \
                        errno, \
                        strerror(errno));}*/


/* DICHIARAZIONE VARIABILI*/
int shm_id; /*id shared memory*/
int my_key; /*chiave per shared memory*/
int length; /*lunghezza scacchiera SO_BASE * SO_ALTEZZA*/

/*DICHIARAZIONE STRUTTURE*/
struct str_mode { /*struct con i parametri per il livello del gioco (easy,hard)*/
int SO_NUM_G;
int SO_NUM_P;
int SO_MAX_TIME;
int SO_BASE;
int SO_ALTEZZA;
int SO_FLAG_MIN;
int SO_FLAG_MAX;
int SO_ROUND_SCORE;
int SO_N_MOVES;
int SO_MIN_HOLD_SEC;
}mode;

typedef struct cell{
char value; //valore da stampare
int sem_num; //numero del semaforo corrispondente nel set di semafori
char score; //punteggio della bandierina
int x; //posizione [x][y]
char y; //posizione [x][y]
}cell;


/*DICHIARAZIONE FUNZIONI*/
void setMode(char fileName);
void setShm();
void shm_print_stats(int fd, int m_id);
void setChessboard();
void createProcPlayer();
void createProcPawn(int player);
int casuale(int a);
void printChessboard();