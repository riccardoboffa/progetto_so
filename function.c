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

    p_chessboards = shmat(spchessboard.shm_id,NULL,0);
    p_players = shmat(spplayer.shm_id,NULL,0);
    p_pawns = shmat(sppawn.shm_id,NULL,0);

}

void setPlayer(int i, pid_t player_id){
    p_players[i]->score = 3;
    p_players[i]->player_id = player_id;
}

void setPawn(int i, pid_t player_id, pid_t pawn_id){
    p_pawns[i]->player_id = player_id;
    p_pawns[i]->pawn_id = pawn_id;
    printf("%d\n", p_pawns[i]->pawn_id);
}

void setChessboard(){
    printf("strabella");
    int i, y, sem_num,c, score, offset;
    sem_num, c, offset=0 , y= 0;
    for(i=0;i<SO_BASE*SO_ALTEZZA;i++){
            p_chessboards[i]->x = offset;
            p_chessboards[i]->y = y;
            p_chessboards[i]->value = '0';
            p_chessboards[i]->sem_num = sem_num;
            p_chessboards[i]->score = score; 
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
        printf("%c", p_chessboards[i]->value);
        printf("| ");
        offset++;
        if(offset % SO_BASE == 0){
            printf("\n");
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("\n");
}

void createProc(){
    int i, value, status;
    pid_t j=0;
    for(i=0; i < SO_NUM_G; i++){
		value = fork();
        switch (value)
        {
            case -1:
            fprintf(stderr,"Error #%03d: %s\n", errno, strerror(errno));
                break;

            case 0:
                printf("# - Giocatore %d (parent: %d)\n", getpid(), getppid());
                setPlayer(i,getpid());
                createProcPawn(getpid());
                wait(&status);
                exit(EXIT_SUCCESS);
                break;
            
            default:
                wait(&status);
                break;
        }
	}
    printf("ok\n");
    while (wait(NULL) > 0);
}

void createProcPawn(pid_t player){

    int j, value, i, cont = 0;             
                    
    for(j = 0; j < SO_NUM_P; j++){
        value = fork();
        cont++;
        switch (value){
            case -1:
                fprintf(stderr,"Error #%03d: %s\n", errno, strerror(errno));
                break;
            case 0:
                printf("giocatore (%d) pedina (%d)\n", getppid(), getpid());
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }
    while (wait(NULL) > 0); 
	printf("Tutte e %d le pedine del giocatore %d sono state create!\n\n",cont,  player);
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

