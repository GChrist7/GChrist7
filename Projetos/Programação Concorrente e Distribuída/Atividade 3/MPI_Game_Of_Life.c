/****************************************/
/****************************************/
/*                                      */
/*             Atividade 3              */
/*        Bruno Maciel Rotondaro        */
/*        Guilherme Aguiar Christ       */
/*          Luiza Peres Viana           */
/*                                      */
/****************************************/
/****************************************/


#include <stdio.h>
#include <stdlib.h>   
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

#define N 2048 //Tamanho do tabuleiro NxN
#define EXECUTIONS 2000 //Número de gerações 

//Aloca uma matriz dinamicamente
float **alocarMatriz(int division, int WorldSize) { 
    float **matriz;
    
    if(WorldSize == 1){ //Trata o caso da execução em serial
        matriz = (float **)malloc((division) * sizeof(*matriz));
        
        for (int i = 0; i < (division); i++) {
            matriz[i] = (float *)malloc(N * sizeof(*matriz[i]));
        }
    }

    else{
        matriz = (float **)malloc((division + 2) * sizeof(*matriz));
        
        for (int i = 0; i < (division + 2); i++) {
            matriz[i] = (float *)malloc(N * sizeof(*matriz[i]));
        }
    }
    
    return matriz;
}

//Retorna a diferença de tempo entre "start" e "end"
float get_time_taken(struct timespec *start, struct timespec *end){ 
    float time_taken;
    time_taken = (end->tv_sec - start->tv_sec) + 1e-9*(end->tv_nsec - start->tv_nsec);
    return time_taken;
}

//Imprime a Matriz 50x50 usando ■ para células vivas e □ para células mortas
void PrintBoard_50x50(float** grid){ 
    int i, j;

    for(i=0 ; i<50 ; i++){
        for(j=0 ; j<50 ; j++){
            if(grid[i][j] == 1)
                printf("■ ");
            else
                printf("□ ");
        }
        printf("\n");
    }
}

//Retorna no número de células vivas no tabuleiro
int getAliveCells(float** grid, int division, int WorldSize){ 
    int alive=0;
    int i, j;
    if(WorldSize == 1){ // Trata a contagem para execução serial
        for(i=0 ; i<division ; i++){
            for(j=0 ; j<N ; j++){
                if(grid[i][j] == 1)
                    alive++;
            }
        }
    }
    else{
        for(i=1 ; i<(division-1) ; i++){
            for(j=0 ; j<N ; j++){
                if(grid[i][j] == 1)
                    alive++;
            }
        }
    }

    return alive;

}

int Reduce(int MyAliveCells){
    int WorldAliveCells;
    //Utiliza-se a função de Reduce do MPI para calcular o total de células vivas em todas as grids
    MPI_Reduce(&MyAliveCells, &WorldAliveCells, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return WorldAliveCells;
}

//Retorna no número de células vizinhas vivas da célula (i, j)
int getNeighbors(float** grid, int i, int j){ 
    int count = 0;
    int newi, newj;
    int x, y;

    for(x=-1 ; x<=1 ; x++){
        for(y=-1 ; y<=1 ; y++){

            if (x == 0 && y == 0) { //Ignora a célula atual
                continue;
            }

            newi = (i + x + N) % N;
            newj = (j + y + N) % N; // Tratamento mundo infinito
            if (grid[newi][newj] == 1) {
                count++;
            }
            
        }
    }

    return count;
}


//Atualiza o tabuleiro matando e revivendo as células
void UpdateGrid(float **grid, float **newgrid, int lines, int j){ 
    int neighbors;
    neighbors = getNeighbors(grid, lines, j);
    if (grid[lines][j] == 1) {
        if (neighbors == 2 || neighbors == 3) {
            newgrid[lines][j] = 1;
        } else {
            newgrid[lines][j] = 0;
        }
    } else {
        if (neighbors == 3) {
            newgrid[lines][j] = 1;
        } else {
            newgrid[lines][j] = 0;
        }
    }
}

//Função para executar a troca das linhas nas bordas, com os processos responsáveis
//pelas linhas de cima e de baixo
void SendReceiveNeighbors(float** grid, int rank, int UpRank, int DownRank, int division){
    MPI_Request UpRequest, DownRequest;
    UpRequest = MPI_REQUEST_NULL;
    DownRequest = MPI_REQUEST_NULL;
    MPI_Status status;

    //A primeira linha de uma division de um processo é a linha 1, sendo a linha 0 a última linha do processo de cima
    //Já a última linha é dada por division-2 e a linha division-1 é a primeira linha do processo de baixo

    //Envia as suas primeira e última linhas para os processos "vizinhos"
    MPI_Isend(grid[1], N, MPI_FLOAT, UpRank, 0, MPI_COMM_WORLD, &UpRequest);
    MPI_Isend(grid[division-2], N, MPI_FLOAT, DownRank, 0, MPI_COMM_WORLD, &DownRequest);

    //Aguarda o recebimento de dados do processo de cima
    MPI_Irecv(grid[0], N, MPI_FLOAT, UpRank, 0, MPI_COMM_WORLD, &UpRequest);
    MPI_Wait(&UpRequest, &status);

    //Aguarda o recebimento de dados do processo de baixo
    MPI_Irecv(grid[division-1], N, MPI_FLOAT, DownRank, 0, MPI_COMM_WORLD, &DownRequest);
    MPI_Wait(&DownRequest, &status);

    //Ao fim do da troca, as linhas 0 e division-1 do grid estão atualizadas com as linhas do processos "vizinhos"
}


//Executa uma rodada do Game Of Life
void play_one_round(float** grid, float** newgrid, int rank, int WorldSize, int UpRank, int DownRank, int division){
    int i, j;

    if(WorldSize == 1){
        for(i=0 ; i<division ; i++){
            for(j=0 ; j<N ; j++){
                UpdateGrid(grid, newgrid, i, j);
            }
        }
    }
    else{
        for(i=1 ; i<(division - 1) ; i++){

            if(WorldSize > 1)
                SendReceiveNeighbors(grid, rank, UpRank, DownRank, division);

            //Atualiza a grid baseada nas linhas recebidas dos processos "vizinhos"
            for(j=0 ; j<N ; j++){
                UpdateGrid(grid, newgrid, i, j);
            }
        }
    }

    //Espera todos os processos terminarem de atualizar suas grid
    MPI_Barrier(MPI_COMM_WORLD);

    //Atualiza a grid anterior
    for(i=0 ; i<division ; i++){
        for(j=0 ; j<N ; j++){
            grid[i][j] = newgrid[i][j]; 
        }
    }

    //Espera todos os processos terminarem suas atualizações
    MPI_Barrier(MPI_COMM_WORLD);
}

//Inicia o Game Of Life 
void play_GameOfLife(float** grid, float** newgrid, int rank, int WorldSize, int UpRank, int DownRank, int division){
    int i;
    float time_taken;

    struct timespec start;
    struct timespec end;

    //clock_gettime(CLOCK_REALTIME, &start);

    for(i=0 ; i<EXECUTIONS ; i++)
        play_one_round(grid, newgrid, rank, WorldSize, UpRank, DownRank, division);

    //clock_gettime(CLOCK_REALTIME, &end);

    //time_taken = get_time_taken(&start, &end);

    ///printf("O tempo que as gerações tomaram foi: %0.3fs\n", time_taken);

}


//Inseri a configuração inicial do R-Pentomino
void init_RPentomino(float** grid){ 
    int lin =10, col = 30;
    grid[lin  ][col+1] = 1.0;
    grid[lin  ][col+2] = 1.0;
    grid[lin+1][col  ] = 1.0;
    grid[lin+1][col+1] = 1.0;
    grid[lin+2][col+1] = 1.0;
}


//Inseri a configuração inicial do Glider
void init_glider(float** grid){ 
    int lin = 1, col = 1;
    grid[lin  ][col+1] = 1.0;
    grid[lin+1][col+2] = 1.0;
    grid[lin+2][col  ] = 1.0;
    grid[lin+2][col+1] = 1.0;
    grid[lin+2][col+2] = 1.0;

}

//Função main
int main(int argc, char *argv[]){
    float **grid, **newgrid;
    int rank, WorldSize, UpRank, DownRank;
    int division, MyAliveCells, WorldAliveCells;

    // Inicialiação MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &WorldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Divisão do número de linhas por processo
    division = N / WorldSize;
    
    //Alocação grid
    grid = alocarMatriz(division, WorldSize);

    //Alocação newgrid
    newgrid = alocarMatriz(division, WorldSize);

    //Congiurações inicias tratadas apenas pelo processo de rank 0
    //Para qualquer número de processos 1, 2, 4 e 8 o glider e RPentomino
    //são inciados em suas linhas
    if(rank == 0){
        init_glider(grid);
        init_RPentomino(grid);
    }

    //Definição dos processos próximos e anteriores
    UpRank = (rank - 1 + WorldSize) % WorldSize;
    DownRank = (rank + 1 + WorldSize) % WorldSize;

    //Inicia o jogo
    play_GameOfLife(grid, newgrid, rank, WorldSize, UpRank, DownRank, division);

    //Cada processo calcula o número de células vivas em seu grid
    MyAliveCells = getAliveCells(grid, division, WorldSize);

    //Exceuta a operação de soma de todas as variáveis "MyAliveCells"
    WorldAliveCells = Reduce(MyAliveCells);

    //Aguarda a sincronização de todas os processos
    MPI_Barrier(MPI_COMM_WORLD);

    //Por fim, o processo 0 imprimi o número total de células vivas
    if(rank == 0)
        printf("Número de células vivas: %d\n", WorldAliveCells);

    //Imprimi o tabuleiro
    //if(rank==0)PrintBoard_50x50(grid); //Descomente essa linha para ver o tabuleiro

    MPI_Finalize();

    return 0;
}


