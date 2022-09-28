/**
 * @file esercizio.c
 * @author Francesco Di Lena, classe 4F
 * @brief Scrivere il codice di un programma in C che esegui il comando cat file.txt | more
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    int p1p0[2];
    pid_t pid;
    printf("Benvenuto nel programma!\n");
    pipe(p1p0);
    pid = fork();
    if (pid == 0)
    {
        close(1);
        dup(p1p0[1]);
        close(p1p0[0]);
        close(p1p0[1]);
        execl("/usr/bin/cat", "cat", "file.txt", (char *)0);
        return -1;
    }
    else
    {
        close(0);
        dup(p1p0[0]);
        close(p1p0[0]);
        close(p1p0[1]);
        execl("/usr/bin/more", "more", (char *)0);
        return -1;
    }
    return 0;
}