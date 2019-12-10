#include "header.h"

/*MAIN*/

void main(){
    setShm();
    ciao();
    shm_print_stats(2,spchessboard.shm_id);
    shm_print_stats(2,spplayer.shm_id);
    shm_print_stats(2,sppawn.shm_id);
    setChessboard();
    }
