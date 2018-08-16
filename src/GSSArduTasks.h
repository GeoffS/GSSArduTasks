#pragma once
/*
 * GSSArduTasks.h
 *
 *  Created on: Aug 16, 2018
 *      Author: Geoff
 */

#include <limits.h>
#include <stdint.h>

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

#define RUNTIME \
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
