#include "GPIO.h"

#ifndef PROG_H
#define PROG_H

class Prog {
    private:
        GPIO* clock;
        GPIO* clear;
        GPIO* data;
        int bitNum;
        int holdTime;

    public:
        Prog(int clockPin, int clearPin, int dataPin, int bitNum, int holdTime);
        virtual void write(int data);
        virtual ~Prog();
        virtual void clearReg();
        void status();

    private: 
        void initialize();
        void setBit(GPIO_VALUE val);
};
#endif
