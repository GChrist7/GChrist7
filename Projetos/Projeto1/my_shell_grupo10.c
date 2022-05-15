#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

#define BLEN 4096
#define TRUE 1
#define FALSE 0

//Sala 106

/* Checklist

    1. Executar comandos unitarios com multiplos parametros - Ok

    Imagino que isto ja seja solucionado pelo codigo que o professor passou

    2. Executar comandos encadeados - Ok

    O programa consegue executar pipes encadeados, abrindo novos pipes e mantendo memoria de pipes anteriores a fim de executar comandos intermediarios

    3. Executar comandos condicionados - Ok

    Dividir e conquistar.

    4. Executar comandos em background - Ok

    A ideia aqui e ao inves de usarmos um waitpid com flag 0, usamos um waitpid com flag WNOHANG, pois isto causa o programa a nao esperar o termino imediato do filho

*/

void busca_obj(int argc, char **argv, int *resultado){
    int i;

    for(i=0 ; i<argc ; i++){
        //printf("i %d argc %d\n", i, argc);
        fflush(stdout);
        if(!strcmp(argv[i], "|")){
            resultado[i] = 1; //Pipe
            argv[i] = NULL;
        } else if(!strcmp(argv[i], "&&")){
            resultado[i] = 2; //And
            argv[i] = NULL;
        } else if(!strcmp(argv[i], "||")){
            resultado[i] = 3; //Or
            argv[i] = NULL;
        } 
    }
}

int contacomandos(int argc, char** argv, int *resultado, int start, int end){
    int i;
    int ncomandos = 1;
    for(i=start ; i < end ;i++){
        //printf("%d ", resultado[i]);
        if (resultado[i] == 1) {
            ncomandos++;
        }
    }
    return ncomandos;
}

int executa(int argc, char ** argv, int *resultado, int start, int end){
    int fd[2], fd_prev[2], ret, ncomandos, i, j = 1;
    int count = start;
    int background_flag = 0;
    char **cmd;
    pid_t p;
    ncomandos = contacomandos(argc, argv, resultado, start, end);
    pipe(fd);    
    while (count < end && count < argc) {
    	// lemos o comando atual a ser executado a partir da ultima posicao em que encontramos um pipe (atual posicao do count) + 1
        cmd = &argv[count+1];
        for (i = 0; cmd[i] != NULL; i++) {
            if (!strcmp(cmd[i], "&")) {
                cmd[i] = NULL;
                background_flag = 1;
            }
        }
        // ainda estamos no programa pai, entao realizamos um fork para criar um novo filho
        p = fork();
        // se o p atual for 0, estamos no programa filho, se for 1, estamos no programa pai
        if (p == 0) { // filho
            // para o primeiro comando, so precisamos reescrever a saida padrao dele como a entrada de escrita do pipe atual
            if (j == 1) {// primeiro comando
            	// so precisamos realizar este passo se tiver mais que um pipe
            if (ncomandos > 1) {
		    // fechamos a entrada de lida do pipe para o filho pois nao iremos utiliza-la e deixa-la aberta compromete a continuacao correta do programa
                    close(fd[0]);
                    // neste dup2, alteramos a saida padrao deste programa filho para a entrada de escrita do pipe atual, assim, quando ele executar, sua saida nao ira para tela do terminal, mas sim para o proximo programa a ser executado
                    dup2(fd[1], STDOUT_FILENO);
                    // uma vez que ja reescrevemos a saida padrao como o pipe, fechamos o pipe para permitir a continuacao do programa
                    close(fd[1]);
                }
            }
            // para o ultimo comando, so precisamos executar uma operacao de lida, reescrevendo a entrada padrao como a entrada de leitura do pipe anterior
            else if (j == ncomandos) {// ultimo comando
                // fechamos a entrada de escrita do pipe pois nao sera utilizada
                close(fd_prev[1]);
                // reescrevemos a entrada padrao do programa como a entrada de leitura do pipe anterior
                dup2(fd_prev[0], STDIN_FILENO);
                // fechamos a entrada de leitura do pipe anterior pois ja reescrevemos a entrada padrao do programa com ela
                close(fd_prev[0]);
            // comandos intermediarios apenas realizam ambas as acoes de reescrita da entrada e saida padrao 
            } else { // comandos intermediarios
                close(fd_prev[1]);
                dup2(fd_prev[0], STDIN_FILENO);
                close(fd_prev[0]);

                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            // depois que saimos dos ifs e elses, realizamos a execucao do programa atual com execvp
            execvp(cmd[0], cmd);
            // perror reportara qualquer problema que ocorrer no meio do programa
            perror(cmd[0]);
            // se chegarmos aqui, algum erro ocorreu, entao damos retorno na funcao como erro
            exit(EXIT_FAILURE);
        } else { // pai
            // o pai nao utilizara os pipes anteriores, entao fechamos eles neste momento para permitir o fluxo correto do programa
            // do contrario, funcoes que executam ate encontrarem um fim de programa, como grep, continuarao tentando executar por muito tempo
            close(fd_prev[0]);
            close(fd_prev[1]);
            // aqui, esperamos o filho retornar
            if (background_flag == 0) {
                waitpid(-1, &ret, 0);
            }
            else {
                waitpid(-1, &ret, WNOHANG);
            }
            // definimos o pipe atual como pipe anterior
            fd_prev[0] = fd[0];
            fd_prev[1] = fd[1];
            
            // abrimos um novo pipe, se ocorrer um erro, fechamos o programa
            if (pipe(fd) < 0) {
                return -1;
            }
            
            // atualizamos o contador de comandos executados
            j++;
	    
	    // se estivermos atualmente sobre um PIPE, AND ou OR, avancamos o programa em um
            if (resultado[count] != 0) {
                count++;
            }
            
	    // aqui, continuamos a avancar posicoes ate encontrarmos um PIPE, AND ou OR
            while (resultado[count] == 0 && count < argc && count < end) {
                count++;
            }
        }
    }
    if(ret == 0)
        return TRUE;
    else 
        return FALSE;
}

int ANDS(int argc, char **argv, int *resultado, int start, int end) {
    int flag;
    int i;
    // Como sabemos que o elemento 0 de cada AND sera ou a propria chamada do nosso shell ou um AND, podemos pular esse elemento para evitar conflitos no programa
    for (i = start + 1; i < end && i < argc; i++) {
        if (resultado[i] == 2) {
            // Chamamos os comandos a esquerda primeiro e verificamos se algum erro ocorre
            flag = ANDS(argc, argv, resultado, start, i-1);
            // Se o comando anterior funcionou corretamente, continuamos chamando o lado direito
            if (flag == TRUE) {
                return ANDS(argc, argv, resultado, i, end);
            }
            // Do contrario, retornamos falso para avisar a chamada anterior que um erro ocorreu
            else {
                return FALSE;
            }
        }
    }
    // Se chegarmos ate aqui, nao ha mais ANDs para escanearmos na string de start a end, o que significa que podemos executar os comandos desta string
    return executa(argc, argv, resultado, start, end);
}

int ORS(int argc, char **argv, int *resultado, int start, int end) {
    int flag;
    int i;
    // Como sabemos que o elemento 0 de cada OR sera ou a propria chamada do nosso shell ou um OR, podemos pular esse elemento para evitar conflitos no programa
    for (i = start + 1; i < end && i < argc; i++) {
        if (resultado[i] == 3) {
            // Chamamos os comandos da esquerda primeiro e verificamos se algum erro ocorre
            flag = ORS(argc, argv, resultado, start, i-1);
            // Se ocorreu erro na chamada anterior, chamamos o lado direito do OR
            if (flag != TRUE) {
                return ORS(argc, argv, resultado, i, end);
            }
            // Do contrario retornamos FALSE 
            else {
                return FALSE;
            }
        }
    }
    // Se chegarmos aqui, sabemos que nao existe nenhum OR na string que estamos escaneando e podemos comecar a escanear por ANDs
    return ANDS(argc, argv, resultado, start, end);
}

#define MAX_ARGS 256
int main(int argc, char **argv) {
    int i;
    int resultado[MAX_ARGS];
    // inicializar o vetor que armazena as posicoes dos pipes
    for (i = 0; i < argc; i++) {
        resultado[i] = 0;
    }
    busca_obj(argc, argv, resultado);
    // comecamos escaneando todos os ORs do vetor resultado
    ORS(argc, argv, resultado, 0, argc);
    return 0;
}