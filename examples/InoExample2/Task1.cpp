#include "Task1.h"

Task1::Task1()
{
  
}

void Task1::setup()
{
  pinMode(LED_BUILTIN , OUTPUT);
}

long Task1::loop(long currTime_ms)
{
  digitalWrite(LED_BUILTIN, nextState);
  
  if(nextState != HIGH) nextState = HIGH;
  else                  nextState = LOW;
  
  return currTime_ms + 200;
}
