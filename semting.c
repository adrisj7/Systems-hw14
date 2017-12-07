#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<string.h>
#include<stdlib.h>

#define SEM_KEY 4646

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Error: Invalid number of arguments. ");
        printf("Expected at least 1, got %d\n", argc - 1);
        exit(1);
    }
    // if create new semaphore
    if (!strcmp(argv[1], "-c")) {
        if (argc != 3) {
            printf("Error: Unexpected number of arguments. ");
            printf("Expected 2, got %d\n", argc - 1);
            exit(1);
        }
        int sem = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
        if (sem == -1) {
            printf("Cannot create semaphore:");
            printf("Semaphore already exists!\n");
            exit(0);
        }
        printf("Created sem with set id %d\n", sem);
        int val = atoi(argv[2]);
        semctl(sem, 0, SETVAL, val);
        printf("Set value of sem to %d\n", val);
        exit(0);
    }

    // if viewing semaphore value
    if (!strcmp(argv[1], "-v")) {
        int sem = semget(SEM_KEY, 0, 0);
        if (sem == -1) {
            printf("No semaphore found!\n");
            exit(0);
        }
        int val = semctl(sem, 0, GETVAL);
        printf("Sem value: %d\n", val);
        exit(0);
    }

    // if removing semaphore
    if (!strcmp(argv[1], "-r")) {
        int sem = semget(SEM_KEY, 0, 0);
        if (sem == -1) {
            printf("No semaphore found!\n");
            exit(0);
        }
        semctl(sem, 0, IPC_RMID);
        printf("Semaphore removed!\n");
        exit(0);
    }
    return 0;
}
