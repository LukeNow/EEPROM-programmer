#include "GPIO.h"

#ifndef PROG_H
#define PROG_H

const short int MAX_ADDR = 0x07FF;
const short int MAX_DATA = 0x00FF;

class Prog {
    private:
        GPIO* clock;
        GPIO* clear;
        GPIO* data;
    
    public:
        Prog(int clockPin, int clearPin, int dataPin);
        virtual int write(int data, int bitNum);
        virtual ~Prog();
        virtual int status();
        int clearReg();

    private: 
        int initialize();
        int setBit(GPIO_VALUE val);
};
#endif
