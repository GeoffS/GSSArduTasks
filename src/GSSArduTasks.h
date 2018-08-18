#pragma once
/*
 * GSSArduTasks.h
 *
 *  Created on: Aug 16, 2018
 *      Author: Geoff
 */

#include <limits.h>
#include <stdint.h>

// Macro magic to determine the number of arguments in a variadic macro:
// From:
//   https://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5?pli=1
//   https://gist.github.com/aprell/3722962
//   https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
//
#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

class Task
{
  public:
    virtual void setup() = 0;
    virtual long loop(long currTime_ms) = 0;
    virtual bool needsSerial() { return false; }
};

class NullTaskClass : public Task
{
public:
    virtual void setup() {}
    virtual long loop(long currTime_ms) { return LONG_MAX; }
};

static NullTaskClass NullTaskInstance;
static Task* NullTask = &NullTaskInstance;

#define TASK_LIST(...)\
Task* tasks[] = { __VA_ARGS__ };\
const uint8_t numTasks = VA_NARGS(__VA_ARGS__);\
long nextTaskTime[numTasks];\
void setup()\
{\
	bool needsSerial = false;\
	for (uint8_t i = 0; i < numTasks; i++)\
	{\
		tasks[i]->setup();\
		nextTaskTime[i] = 0;\
		needsSerial |= tasks[i]->needsSerial();\
	}\
	if (needsSerial)\
	{\
		Serial.begin(9600);\
	}\
}\
\
long currTime_ms;\
long nextTask1Time_ms = 0;\
void loop()\
{\
	currTime_ms = millis();\
\
	tasks[0]->loop(currTime_ms);\
\
	for (uint8_t i = 1; i < numTasks; i++)\
	{\
		if (currTime_ms >= nextTaskTime[i])\
		{\
			nextTaskTime[i] = tasks[i]->loop(currTime_ms);\
		}\
	}\
}
