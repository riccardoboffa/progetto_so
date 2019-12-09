#include "header.h"

cell chessboard[1200];

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

/*funzione scelta modalità (easy o hard)*/

void setMode(char fileName){

    FILE *fp;
    int j;
    int arrayMode[10];

    if(fileName == 'e' || fileName == 'h'){
        if(fileName == 'e'){
            if((fp = fopen("e.conf","r")) == NULL){
                printf("Errore apertura file %c.conf\n", fileName);
                exit(-1);
                }
            }else{
                if((fp = fopen("h.conf","r")) == NULL){
                    printf("Errore apertura file %c.conf\n", fileName);
                    exit(-1);
                }
            }

            for(j=0; j < 10; j++){
                fscanf(fp, "%d", &arrayMode[j]);
            }
            fclose(fp);

            mode.SO_NUM_G = arrayMode[0];
            mode.SO_NUM_P = arrayMode[1];
            mode.SO_MAX_TIME = arrayMode[2];
            mode.SO_BASE = arrayMode[3];
            mode.SO_ALTEZZA = arrayMode[4];
            mode.SO_FLAG_MIN = arrayMode[5];
            mode.SO_FLAG_MAX = arrayMode[6];
            mode.SO_ROUND_SCORE = arrayMode[7];
            mode.SO_N_MOVES = arrayMode[8];
            mode.SO_MIN_HOLD_SEC = arrayMode[9];
    }else{
        printf("Carattere non valido\n");
        exit(-1);
        }
}

/*funzione set shared memory*/
void setShm(){

    cell *chessboard[length];
    int board_pointer;
    my_key = 1234;
    /* Creo un segmento in memoria condivisa di grandezza cella * base * altezza */
    shm_id = shmget(my_key, sizeof(cell) * mode.SO_BASE * mode.SO_ALTEZZA, IPC_CREAT | 0600);

    chessboard [length] = (cell*)shmat(shm_id, NULL, 0);
    
}

/*funzione inizializzazione scacchiera*/
void setChessboard(){
    int i, y, sem_num,c, length, score, offset;
    sem_num, c, offset=0 , y= 0;
    length = (mode.SO_ALTEZZA * mode.SO_BASE);

        //cell chessboard[length];

    for(i=0;i<length;i++){
            chessboard[i].x = offset;
            chessboard[i].y = y;
            chessboard[i].value = '0';
            chessboard[i].sem_num = sem_num;
            chessboard[i].score = score; 
        offset++;
        printf("|");
        printf("%d", chessboard[i].x);
        printf("| ");
        if(y>=0 && y<10){
            printf(" ");
        }
        if(offset % mode.SO_BASE == 0){
            y++;
            printf("\n");
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("\n");
}

void printChessboard(){
    int i ,offset, y;
    printf("PORCO DIO \n\n\n ");
    for(i=0;i<length;i++){
        offset++;
        printf("|");
        printf("%c", chessboard[i].value);
        printf("| ");
        if(y>=0 && y<10){
            printf(" ");
        }
        if(offset % mode.SO_BASE == 0){
            y++;
            printf("\n");
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("\n");

}

void createProcPlayer(){

    int i, value, status;

    for(i=0; i < mode.SO_NUM_G; i++){
		value = fork();
        switch (value)
        {
            case -1:
            fprintf(stderr,"Error #%03d: %s\n", errno, strerror(errno));
                break;

            case 0:
            sleep(1);
                printf("# - Giocatore %d\n", getpid());
                createProcPawn(getpid());
                wait(&status);
                exit(EXIT_SUCCESS);
                break;
            
            default:
                wait(&status);
                break;
        }
	}

    while (wait(NULL) > 0);
}

void createProcPawn(int player){

    int j, value, i, cont = 0;             
                    
    for(j = 0; j < mode.SO_NUM_P; j++){
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

int casuale(int a){
    srand(time(NULL));
    int casuale = rand()%(a+1);
    printf("%d\n", casuale);
    return casuale;
}
