#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<unistd.h>
#include <omp.h>

int SOMA = 0;

int NUM_THREADS_CLIENTS = 4;

void client(int id){
    while (1){
        int local = SOMA;     /*******************/
        sleep(rand()%2);      /***Seção Crítica***/
        SOMA = local + 1;     /*******************/
        printf("%d\n", SOMA); /*******************/
    }
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
    return 0;
}