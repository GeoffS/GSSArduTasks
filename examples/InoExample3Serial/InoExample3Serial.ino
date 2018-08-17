#include <GSSArduTasks.h>

class Task1 : public Task
{
  public:
    void setup() override
    {
      pinMode(LED_BUILTIN , OUTPUT);
    }
    long loop(long currTime_ms) override
    {
      digitalWrite(LED_BUILTIN, nextState);
      Serial.print("LED ");
      Serial.println(nextState != HIGH ? "Off" : "On");

      if (nextState != HIGH) nextState = HIGH;
      else                   nextState = LOW;

      return currTime_ms + 2000;
    }
    bool needsSerial() { return true; }

  private:
    uint8_t nextState = HIGH;
};

Task1 task1;

Task* tasks[] = {NullTask, &task1};
const uint8_t numTasks = 2;
long nextTaskTime[numTasks];

RUNTIME

