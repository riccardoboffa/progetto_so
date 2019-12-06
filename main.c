#include "header.h"

/* MAIN */


int main(int argc, char * argv[]){
    if(argc > 1){
        setMode(*argv[1]);
    }else{
        printf("Inserire la modalita' di gioco (e oppure h)\n");
        exit(-1);
    }
    setChessboard();
    setShm();
    printf("N° giocatori: %d\n", mode.SO_NUM_G);
	createProcPlayer();
}
