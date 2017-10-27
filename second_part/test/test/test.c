#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
    while(1){
        if(!fork()){
        }
        usleep(1000000);
    }
    return 0;
}

