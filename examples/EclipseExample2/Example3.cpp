#include <Arduino.h>
#include "../GSS-ArduTasks/Task.h"

class Task1: public Task
{
public:
	Task1()
	{

	}

	void setup()
	{
		pinMode(LED_BUILTIN, OUTPUT);
	}

	long loop(long currTime_ms)
	{
		digitalWrite(LED_BUILTIN, nextState);

		if (nextState != HIGH)
			nextState = HIGH;
		else
			nextState = LOW;

		return currTime_ms + 200;
	}

private:
	bool nextState = HIGH;
};

Task1 task1;

Task* tasks[] =
{ NullTask, &task1 };
const uint8_t numTasks = 2;
long nextTaskTime[numTasks];

#include "../GSS-ArduTasks/TaskFramework.h"
