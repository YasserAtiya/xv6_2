/*
-------------------------------------------------------------
-------WORK DONE BY YASSER ATIYA AND RICARDO ROMERO----------
-------------------------------------------------------------
*/
#include "types.h"
#include "user.h"   // has functions we need
#include "mmu.h"    // contains declarations needed in proc.h
#include "param.h"  // contains declarations needed in proc.h
#include "proc.h"   // we need to know what `struct proc` is


// This is where we define our userspace program!
void
ptest1(void)
{

    int NUM_P = 5;

    printf(1,"Hello, world! \n");

    int pid;
    int i;
    int val = -1;


    for(i = (NUM_P * 10); i > 10 ; i-=10) {
        pid = fork();
        if(pid == 0) {
            val = i;
            setpriority(val);
            printf(1,"Starting process %d\n", val);
            break;
        }
    }

    if(pid == 0) {
        // sloow dooown
        for(i = 0; i < 17000000; i++) {}

        printf(1,"%d finished\n", val);
    } else {

        for(i = 0; i < NUM_P; i++) {
            wait();

        }
        printf(1,"%s\n", "parent complete");
    }

}

void
ptest2(void) {
    printf(1,"Hello, world! \n");
    setpriority(10);
    printf(1, "Goodbye! \n");
}

void ptest3(void){
    int i, j, pid;
    for(i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {
            setpriority(i * 10);
            for(j = 0; j < 10000000; j++){}
        }
    }
    wait();
    exit();
}


//Enters here, calls top when no arguements
int
main(int argc, char *argv[])
{

    ptest1();
    //return 0;
    exit();
}
