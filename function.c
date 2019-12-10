#include "header.h"

void setShm(){
    /*
    shm_parameters_array[0] --> chessboard
    shm_parameters_array[1] --> players
    shm_parameters_array[2] --> pawns
    */
    spchessboard.my_key = 1234;
    spplayer.my_key = 1235;
    sppawn.my_key = 1236;
    spchessboard.shm_id = shmget(spchessboard.my_key,sizeof(cell) * SO_ALTEZZA * SO_BASE, IPC_CREAT | 0600);
    spplayer.shm_id = shmget(spplayer.my_key,sizeof(player) , IPC_CREAT | 0600);
    sppawn.shm_id = shmget(sppawn.my_key,sizeof(pawn), IPC_CREAT | 0600);
    _chessboard[SO_BASE*SO_ALTEZZA] = (cell*)shmat(spchessboard.shm_id,NULL,0);
    _player[SO_NUM_G] = (player*)shmat(spplayer.shm_id,NULL,0);
    _pawn[SO_NUM_P] = (pawn*) shmat(sppawn.shm_id,NULL,0);
}

void ciao(int i, pid_t pid){
     _player[i]->score = 0;
     _player[i]->player_id = pid;
}

void setChessboard(){
    int i, y, sem_num,c, score, offset;
    sem_num, c, offset=0 , y= 0;

    for(i=0;i<SO_BASE*SO_ALTEZZA;i++){
            chessboard[i].x = offset;
            chessboard[i].y = y;
            chessboard[i].value = '0';
            chessboard[i].sem_num = sem_num;
            chessboard[i].score = score; 
        offset++;
        if(offset % SO_BASE == 0){
            y++;
        }
    }
    printf("\n");
}

void printChessboard(){
    int i ,offset, y;
    offset = 0;
    for(i=0;i<SO_BASE*SO_ALTEZZA;i++){
        printf("|");
        printf("%c", chessboard[i].value);
        printf("| ");
        offset++;
        if(offset % SO_BASE == 0){
            printf("\n");
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("\n");
}

void shm_print_stats(int fd, int m_id) {
    struct shmid_ds my_m_data;
    int ret_val;

    while (ret_val = shmctl(m_id, IPC_STAT, &my_m_data)) {
        }
    dprintf(fd, "--- IPC Shared Memory ID: %8d, START ---\n", m_id);
    dprintf(fd, "---------------------- Memory size: %ld\n",
    my_m_data.shm_segsz);
    dprintf(fd, "---------------------- Time of last attach: %ld\n",
    my_m_data.shm_atime);
    dprintf(fd, "---------------------- Time of last detach: %ld\n",
    my_m_data.shm_dtime);
    dprintf(fd, "---------------------- Time of last change: %ld\n",
    my_m_data.shm_ctime);
    dprintf(fd, "---------- Number of attached processes: %ld\n",
    my_m_data.shm_nattch);
    dprintf(fd, "----------------------- PID of creator: %d\n",
    my_m_data.shm_cpid);
    dprintf(fd, "----------------------- PID of last shmat/shmdt: %d\n",
    my_m_data.shm_lpid);
    dprintf(fd, "--- IPC Shared Memory ID: %8d, END -----\n", m_id);
}

