#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>

#include "prog.h"

Prog::Prog(int clockPin, int clearPin, int dataPin, int bits, int holdTime) {
    clock = new GPIO(clockPin, holdTime);
    clear = new GPIO(clearPin, holdTime);
    data = new GPIO(dataPin, holdTime);
    bitNum = bits;
    initialize();
}

void Prog::write(int data) {
    int maskOffset = 16 - bitNum;
    unsigned short int mask = 0x8000;
    unsigned short int setValue = 0;

    mask >>= maskOffset;

    for(int i = 0; i < bitNum; i++) {
        setValue = mask & data;

        if (setValue != 0x0000) {
            setBit(HIGH);
        }
        else {
            setBit(LOW);
        }
        mask >>= 1;
    }
}

Prog::~Prog() {
    delete(clock);
    delete(clear);
    delete(data);
}

void Prog::status() {
    std::cout << "CLOCK -- ";
    clock->status();
    std::cout << "CLEAR -- ";
    clear->status();
    std::cout << "DATA -- ";
    data->status();
}

void Prog::initialize() {
    clock->setDirection(OUT);
    data->setDirection(OUT);
    clear->setDirection(OUT);
    
    clock->setValue(LOW);
    data->setValue(LOW);
    clear->setValue(HIGH);
}

void Prog::setBit(GPIO_VALUE val) {
    data->setValue(val);

    clock->setValue(LOW);
    usleep(holdTime);
    clock->setValue(HIGH);
    usleep(holdTime);
    clock->setValue(LOW);
}

void Prog::clearReg() {
    clear->setValue(LOW);
    usleep(holdTime);
    clear->setValue(HIGH); //active low
}
