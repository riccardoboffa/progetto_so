#define _GNU_SOURCE
#include "conf.h"
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
#define TEST_ERROR if (errno) {dprintf(STDERR_FILENO, \
                        "%s:%d: PID=%5d: Error %d (%s)\n", \
                        FILE, \
                        LINE, \
                        getpid(), \
                        errno, \
                        strerror(errno));}

typedef struct cell{
char value;
int sem_num;
char score;
int x;
int y;
}cell;

typedef struct pawn{
    pid_t player_id;
    pid_t pawn_id;
    int x;
    int y;
}pawn;

typedef struct player{
    pid_t player_id;
    int score;
}player;

typedef struct sp{
    int my_key;
    int shm_id;
}sp;

sp spchessboard;
sp spplayer;
sp sppawn;

cell chessboard[SO_BASE*SO_ALTEZZA];
cell *_chessboard[SO_BASE*SO_ALTEZZA];
player *_player[SO_NUM_G];
pawn *_pawn[SO_NUM_P];

void setShm();
void ciao();
void shm_print_stats(int fd,int m_id);
void setChessboard();
void printChessboard();
void modifica();
