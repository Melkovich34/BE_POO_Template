#ifndef DEVICE_H
#define DEVICE_H

class Device {
public:
    virtual ~Device() {}
    virtual void begin() = 0; 
};

#endif