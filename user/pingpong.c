#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p1[2]; // child write parent read
    int p2[2]; // child read parent write
    char buf[1];
    pipe(p1);
    pipe(p2);
    int pid = fork();
    if( pid == 0) {
        int child = getpid();
        close(p2[1]);
        // read 
        if(read(p2[0], buf, 1) == 1)
            fprintf(0,"%d: received ping\n", child);
        close(p2[0]);
        // write
        close(p1[0]);
        write(p1[1], buf, 1);
        close(p1[1]);
        

    }else {
        int parent = getpid();
        // write
        close(p2[0]);
        write(p2[1], buf, 1);
        close(p2[1]);

        // read
        close(p1[1]);
        if( read(p1[0], buf , 1) == 1) 
            fprintf(0, "%d: received pong\n", parent);
        close(p1[0]);
        
    }
    exit(0);
}