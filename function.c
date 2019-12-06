#include "header.h"

cell chessboard[LUNG];
int my_key; /*chiave per shared memory*/
int shm_id; /*id shared memory*/

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
}
