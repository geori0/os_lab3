#pragma once

#ifdef WIN32
#include <"windows.h">
typedef HANDLE sem_cross_t;
#else
#include <semaphore.h>
typedef sem_t sem_cross_t;
#endif



struct SharedData {
    int number;
    int signal;
    char file[256];
    sem_cross_t sem_parent;
    sem_cross_t sem_child;
    sem_cross_t sem_file;
};