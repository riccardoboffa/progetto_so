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

sp spchessboard, spplayer, sppawn;

typedef player players[SO_NUM_G];
typedef cell chessboards[SO_BASE+SO_ALTEZZA];
typedef pawn pawns[SO_NUM_P];

players *p_players;
pawns *p_pawns;
chessboards *p_chessboards;

void setShm();
void shm_print_stats(int fd,int m_id);
void setPlayer(int i, pid_t player_id);
void setPawn(int i, pid_t player_id, pid_t pawn_id);
void setChessboard();
void printChessboard();
void createProc();
void createProcPawn(pid_t player);