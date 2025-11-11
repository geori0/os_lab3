#include "os.h"

#include <cstdlib>
#include <iostream>
#include <semaphore.h>
#include <sys/mman.h>
#include <unistd.h>

ProcessRole ProcessCreate() {
  pid_t pid = fork();
  if (pid == -1) {
    std::cerr << "Ошибка создания process" << std::endl;
    exit(-1);
  }

  if (pid > 0) {
    return IS_PARENT;
  } else {
    return IS_CHILD;
  }
}

SharedData *CreateSharedMemory() {
  SharedData *shared_memory = static_cast<SharedData *>(
      mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE,
           MAP_SHARED | MAP_ANONYMOUS, -1, 0));
  if (shared_memory == MAP_FAILED) {
    std::cerr << "Ошибка создания общей памяти" << std::endl;
    exit(-1);
  }

  sem_init(&shared_memory->sem_parent, 1, 0);
  sem_init(&shared_memory->sem_child, 1, 0);
  sem_init(&shared_memory->sem_file, 1, 0);
  shared_memory->number = 0;
  shared_memory->signal = 0;
  shared_memory->file[0] = '\0';

  return shared_memory;
}

void DestroySharedMemory(SharedData *data) {
  if (data) {
    munmap(data, sizeof(SharedData));
    sem_destroy(&data->sem_child);
    sem_destroy(&data->sem_parent);
    sem_destroy(&data->sem_file);
  }
}

int SemaphoreWait(sem_cross_t* sem) {
    return sem_wait(sem);
}

int SemaphorePost(sem_cross_t* sem) {
    return sem_post(sem);
}
