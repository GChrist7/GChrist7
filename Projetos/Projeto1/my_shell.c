#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>

#define BLEN 4096

int main(int argc, char **argv) {

	char **cmd = &argv[1];
	char buffer[BLEN];
	int fd[2], ret, n;
	pid_t p;
	pipe(fd);
	p = fork();

	if (p == 0) { // filho
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execvp(cmd[0], cmd);
	} else { // pai
		close(fd[1]);
		printf("Pai espera filho %d\n", (int)p);
		waitpid(-1, &ret, 0);

		do {
			bzero(buffer, BLEN);
			n = read(fd[0], buffer, BLEN);
			printf("%s", buffer);
		}while(n > 0);
		close(fd[0]);
	}

	return 0;
}