#pragma once

#include <limits.h>

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

