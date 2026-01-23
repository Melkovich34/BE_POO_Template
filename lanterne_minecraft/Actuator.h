#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "Device.h"

class Actuator : public Device {
public:
    virtual void stop() = 0;
};

#endif