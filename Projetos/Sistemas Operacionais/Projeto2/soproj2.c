#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <unistd.h>
#include <malloc.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define SIZE 1024
#define NP 5
#define NC 5
FILE *arquivo;

struct thread_t {
	pthread_t t;
	int id;
};

typedef struct thread_t thread_t;

int w, r, split_finished = 0, items_to_map = 0, items_to_reduce = 0;
sem_t mutex_map; // mutex para RC entre mapeadores
sem_t mutex_reds; // mutex para RC entre redutores
sem_t full; // indica qtd posicoes cheias no buffer
sem_t empty; // indica qtd de posicoes vazias no buffer
char f[SIZE][SIZE];

struct HashItem {
    char *name;
    int num;
    int key;
};
typedef struct HashItem HashItem;

HashItem* hashArray[SIZE];

int hashCode (char *name) {
    int code;
    int key = 0;
    int i;
    for (i = 0; name[i] != '\0'; i++) {
        key = key + name[i];
    }
    code = key % SIZE;
    return code;
}

HashItem *searchHash(char *name) {
    int attempts = 0;
    int hashIndex = hashCode(name);
    while (hashArray[hashIndex] != NULL && attempts < SIZE) {
        if (strcmp(hashArray[hashIndex]->name, name) == 0) {
            return hashArray[hashIndex];
        }
        hashIndex++;
        attempts++;
        hashIndex = hashIndex % SIZE;
    }
    return NULL;
}

int insertHash(char *name, int num) {
    int attempts = 0;
    int hashIndex = hashCode(name);
    HashItem *item = (HashItem*) malloc(sizeof(HashItem));
    item->name = name;
    item->num = num;
    while (hashArray[hashIndex] != NULL && attempts < SIZE) {
        if (strcmp(hashArray[hashIndex]->name, name) == 0) {
            break;
        }
        hashIndex++;
        hashIndex = hashIndex % SIZE;
    }
    if (attempts >= SIZE) {
        return 0;
    }
    if (hashArray[hashIndex] != NULL) {
        if (strcmp(hashArray[hashIndex]->name, name) == 0) {
            hashArray[hashIndex]->num = hashArray[hashIndex]->num + num;
            return 1;
        }
    }
    hashArray[hashIndex] = item;
    items_to_reduce++;
    return 1;
}

void print() {
    int i;
    for (i = 0; i < SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("%s: %d\n", hashArray[i]->name, hashArray[i]->num);
        }
    }
}

struct{
	char palavra;
	int qtd;
} words[10000];

void init(void) {
	w = 0;
	r = 0;
	sem_init(&mutex_map, 0, 1);
	sem_init(&mutex_reds, 0, 0);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, SIZE);
	srand(time(NULL));
}

void map_item() {
    char* part_string;
    part_string = strtok(f[w], " \t\r\n\v\f");
    while (part_string != NULL) {
        insertHash(part_string, 1);
        part_string = strtok(NULL, " \t\r\n\v\f");
    }
    w = (w + 1) % SIZE;
    items_to_map--;
}

void *mapper(void *args) {
	while(1) {
		sem_wait(&full);
		sem_wait(&mutex_map);
        if (items_to_map > 0) {
            map_item();
        }
        if (split_finished && !items_to_map) {
            sem_post(&mutex_map);
            sem_post(&full);
            pthread_exit(0);
        }
		sem_post(&mutex_map);
		sem_post(&empty);
	}
}

void reduce_item(FILE *arquivo) {
    HashItem *item = hashArray[r];
    if (item != NULL) {
        fflush(arquivo);
        fprintf(arquivo, "%s %d\n", item->name, item->num);
        items_to_reduce--;
    }
    r = (r + 1) % SIZE;
}

void *reducer(void *args) {
	int id = *(int *)args;
    char file_name[SIZE];
    sprintf(file_name, "reducer%d.txt", id);
    FILE *reducer_file = fopen(file_name, "a");
	while(1) {
		sem_wait(&mutex_reds);
		if (split_finished && !items_to_map && items_to_reduce > 0) {
            reduce_item(reducer_file);
        }
        else if (split_finished && !items_to_map && items_to_reduce <= 0) {
            sem_post(&mutex_reds);
            fclose(reducer_file);
            pthread_exit(0);
        }
		sem_post(&mutex_reds);
	}
}

void *master(void *args) {
    int i = 0;
    char next_string[SIZE];
    while (1) {
        if (!split_finished){
            if (fgets(next_string, sizeof next_string, arquivo) != NULL) {
                sem_wait(&empty);
                strcpy(f[i], next_string);
                i = (i + 1) % SIZE;
                items_to_map++;
                sem_post(&full);
            }
            else {
                split_finished = 1;
                sem_post(&mutex_reds);
                pthread_exit(0);
            }
        }
    }
}


void create_threads(thread_t *th, int n, void *(*func)(void*)){
	int i;
	for (i=0; i<n; i++) {
		th[i].id = i;
		pthread_create(&th[i].t, NULL, func, &th[i].id);
	}
}

void join_threads(thread_t *th, int n) {
	int i;
        for (i=0; i<n; i++) {
		pthread_join(th[i].t, NULL);
	}
}

int main(int argc, char **argv) {
    thread_t master_t, tp[NP], tc[NC];
	arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
	init();
    pthread_create(&master_t.t, NULL, master, &master_t.id);
	create_threads(tp, NP, mapper);
	create_threads(tc, NC, reducer);
    pthread_join(master_t.t, NULL);
	join_threads(tp, NP);
	join_threads(tc, NC);
    print();
	return 0;
}

