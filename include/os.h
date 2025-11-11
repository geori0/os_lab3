#pragma once

#include "shared_data.h"


enum ProcessRole {
    IS_PARENT,
    IS_CHILD
};

ProcessRole ProcessCreate();

SharedData* CreateSharedMemory();
void DestroySharedMemory(SharedData * data);
void childProcess(SharedData *shared_memory);
int SemaphoreWait(sem_cross_t* sem);
int SemaphorePost(sem_cross_t* sem);