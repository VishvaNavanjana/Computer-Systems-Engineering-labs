
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#define DATA_PORT 0x378 /* parallel port base address */
#define STATUS_PORT DATA_PORT+1 /* status port */
#define CONTROL_PORT DATA_PORT+2 /* control port */

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

unsigned char status, data;

void main(){
    unsigned char seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; //Array storing 0-9 for the seven segment display
    char x=0; //Initial value of the counter
    //unsigned int i;
    //unsigned char p1=0x00;
    unsigned char status, data;  //To store port values


    if (ioperm(DATA_PORT, 1, 1)){
        fprintf(stderr, "Access denied to %x\n", DATA_PORT), exit(1); //Check whether the data port is available
    }

    if (ioperm(STATUS_PORT, 1, 1)){
        fprintf(stderr, "Access denied to %x\n", STATUS_PORT), exit(1); //Check whether the status port is available
    }
    if (ioperm(CONTROL_PORT, 1, 1)){
        fprintf(stderr, "Access denied to %x\n", CONTROL_PORT), exit(1); //Check whether the control port is available
    }
    

    outb(seg[x], DATA_PORT); //Giving the initial counter value to the display

    while(1){ //Runs forever

        status = inb(STATUS_PORT); //Read the status port 
        status = (status & 0xC0);  //Isolate the last two MSBs from the status port reading
        printf("%x\n",status);
        
        if(x<10 && x>=0){   //Should run only if x is betwen 0 and 9
            if (status== 0xC0){//Up counter
                
                if(x<9){ //Cannot increase more than 9
                    x++;
                    outb(seg[x], DATA_PORT); //Send the output to the display
                }
                else{
                    //Nothing
                }
                
                printf("Up");
            }

            else if(status== 0x00){ //Down counter
                if(x>0){ //Cannot decrease more than 0
                    x--;
                    outb(seg[x], DATA_PORT); //Send the output to the display
                }
                else{
                    //Nothing 
                }

                printf("Down");
            }
            
        }
        
        printf("x = %i\n", x); //For testing
        sleep(3); //Sleep for 3 s
        
    }

}