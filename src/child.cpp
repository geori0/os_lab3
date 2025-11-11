#include <fstream>
#include <iostream>
#include <semaphore.h>
#include <unistd.h>

#include "os.h"
#include "prime.h"

void childProcess(SharedData *shared_memory) {
  SemaphoreWait(&shared_memory->sem_file);
  std::ofstream out(shared_memory->file, std::ios::app);
  if (!out.is_open()) {
    std::cerr << "Ошибка открытия файла" << std::endl;
    return;
  }
  while (true) {
    SemaphoreWait(&shared_memory->sem_child);
    if (!Prime(shared_memory->number) && (shared_memory->number > 1)) {
      out << shared_memory->number << std::endl;
      shared_memory->signal = 0;
      SemaphorePost(&shared_memory->sem_parent);
    } else {
      shared_memory->signal = 1;
      SemaphorePost(&shared_memory->sem_parent);
      break;
    }
  }
  out.close();
  return;
}
