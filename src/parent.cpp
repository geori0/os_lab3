#include "os.h"

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <semaphore.h>
#include <unistd.h>
#include <string>
#include<sys/wait.h>

int main() {
    SharedData *shared_memory = CreateSharedMemory();
    ProcessRole role = ProcessCreate();
    shared_memory->signal = 0;
    if (role == IS_CHILD) {
        childProcess(shared_memory);
        exit(0);
    }
    if (role == IS_PARENT) {
        std::string file_name;
        std::cin >> file_name;
        strncpy(shared_memory->file, file_name.c_str(), sizeof(shared_memory->file) - 1);
        shared_memory->file[sizeof(shared_memory->file) - 1] = '\0';
        SemaphorePost(&shared_memory->sem_file);

        int number;
        while (std::cin >> number) {
            shared_memory->number = number;
            SemaphorePost(&shared_memory->sem_child);

            SemaphoreWait(&shared_memory->sem_parent);

            if (shared_memory->signal == 1) {
                break;
            }
        }
        wait(NULL);
        DestroySharedMemory(shared_memory);
    }

    return 0;
}