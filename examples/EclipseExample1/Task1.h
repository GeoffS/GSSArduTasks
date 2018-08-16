#pragma once

#include "../GSS-ArduTasks/Task.h"
#include <stdint.h>
#include <Arduino.h>

class Task1 : public Task
{
  public:
    Task1();
    void setup() override;
    long loop(long currTime_ms) override;

  private:
    uint8_t nextState = HIGH;
};

