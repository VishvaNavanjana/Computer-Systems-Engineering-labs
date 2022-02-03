
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
#include <time.h>

#define DATA_PORT 0x378         // Parallel port base addr
#define STATUS_PORT DATA_PORT+1 //Status port
#define CONTROL_PORT DATA_PORT+2 //Control port

/*
        a
       ---
     f| g |b        0 - (a, b, c, d, e, f) - 0011 1111 - 0x3F
       ---          1 - (b, c) - 0000 0110 - 0x06
     e|   |c        2 - (a, b, g, e, d) - 0101 1011 - 0x5B
       ---          3 - (a, b, c, g, d) - 0100 1111 - 0x4F
        d           4 - (b, c, f, g) - 0110 0110 - 0x66
                    5 - (a, f, g, c, d) - 0110 1101 - 0x6D
                    6 - (a, c, d, e, f, g) - 0111 1101 - 0x7D
                    7 - (a, b, c) - 0000 0111 - 0x07
                    8 - (a, b, c, d, e, f, g) - 0111 1111 - 0x7F
                    9 - (a, b, c, d, f, g) - 0110 1111 - 0x6F
*/


int main() {

    //Initialize counter to count from 0-9
    int count = 0;

    //Check whether the ports are accessible
    if (ioperm(DATA_PORT,1,1)){

        fprintf(stderr, "Access denied to %x\n", DATA_PORT);
        exit(1);
    }
    if (ioperm(STATUS_PORT,1,1)){

        fprintf(stderr, "Access denied to %x\n", STATUS_PORT);
        exit(1);
    }
    if (ioperm(CONTROL_PORT,1,1)){

        fprintf(stderr, "Access denied to %x\n", CONTROL_PORT);
        exit(1);
    }


    //Count from 0-9
   while(count <= 9){

        if(count == 0){
            outb(0x3F, DATA_PORT); //0
        }else if(count == 1){
            outb(0x06, DATA_PORT); //1
        }else if(count == 2){
            outb(0x5B, DATA_PORT); //2
        }else if(count == 3){
            outb(0x4F, DATA_PORT); //3
        }else if(count == 4){
            outb(0x66, DATA_PORT); //4
        }else if(count == 5){
            outb(0x6D, DATA_PORT); //5
        }else if(count == 6){
            outb(0x7D, DATA_PORT); //6
        }else if(count == 7){
            outb(0x07, DATA_PORT); //7
        }else if(count == 8){
            outb(0x7F, DATA_PORT); //8
        }else if(count == 9){
            outb(0x6F, DATA_PORT); //9
        }else{
            //Displays E for error
            outb(0x79, DATA_PORT); //E
        }



        //Sleep for 1 second
        sleep(1);

        //Increment counter
        if(count == 9){
            count = 0;
        }
        else{
            count++;
        }
    }
}