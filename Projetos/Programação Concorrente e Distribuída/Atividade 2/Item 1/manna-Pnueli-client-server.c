#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<unistd.h>
#include <omp.h>

int request = 0;
int respond = 0;
int SOMA = 0;


int NUM_THREADS_SERVER = 1;

void server(){
    while(1){
        if(request != 0)
            respond = request;
        if(respond == 0)
            request = 0;
    } 
}

void client(int id){
    while (1){
        while(respond != id)
            request = id;
        int local = SOMA;     /*******************/
        sleep(rand()%2);      /***Seção Crítica***/
        SOMA = local + 1;     /*******************/
        printf("%d\n", SOMA); /*******************/
        respond = 0;
    }
}

void triggers_server(){
    omp_set_num_threads(NUM_THREADS_SERVER);
    #pragma omp parallel
    {
        server();
    }
    return;
}

void triggers_clients(){
    int id;

    omp_set_num_threads(NUM_THREADS_CLIENTS);
    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        client(id);
    }
    return;
}

int main(){
    triggers_clients();
    triggers_server();
    return 0;
}