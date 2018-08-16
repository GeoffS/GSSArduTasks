#include "Task1.h"

Task1 task1;

Task* tasks[] = {NullTask, &task1};
const uint8_t numTasks = 2;
long nextTaskTime[numTasks];

RUNTIME

