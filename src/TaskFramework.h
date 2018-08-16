#include "Task.h"

void setup()
{
	bool needsSerial = false;
	for (uint8_t i = 0; i < numTasks; i++)
	{
		tasks[i]->setup();
		nextTaskTime[i] = 0;
		needsSerial |= tasks[i]->needsSerial();
	}
	if (needsSerial)
	{
		Serial.begin(9600);
	}
}

long currTime_ms;
long nextTask1Time_ms = 0;
void loop()
{
	currTime_ms = millis();

	// The "zero task" is always run:
	tasks[0]->loop(currTime_ms);

	for (uint8_t i = 1; i < numTasks; i++)
	{
		if (currTime_ms >= nextTaskTime[i])
		{
			nextTaskTime[i] = tasks[i]->loop(currTime_ms);
		}
	}
}
