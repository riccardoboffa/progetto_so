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
#define LUNG 0

#define TEST_ERROR    if (errno) {dprintf(STDERR_FILENO,		\
					  "%s:%d: PID=%5d: Error %d (%s)\n", \
					  __FILE__,			\
					  __LINE__,			\
					  getpid(),			\
					  errno,			\
					  strerror(errno));}

/*DICHIARAZIONE STRUTTURE*/
struct str_mode {        /*struct con i parametri per il livello del gioco (easy,hard)*/
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
	char value;		//valore da stampare
	int sem_num;	//numero del semaforo corrispondente nel set di semafori
	int score;		//punteggio della bandierina
	int x;			//posizione [x][y]
	int y;			//posizione [x][y]
}cell;


/*DICHIARAZIONE FUNZIONI*/
static void setMode(char fileName);
static void setShm();
static void shm_print_stats(int fd, int m_id);
//static void setChessboard();
