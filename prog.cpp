#include "prog.h"

Prog::Prog(int clockPin, int clearPin, int dataPin) {
    clock = new GPIO(clockPin);
    clear = new GPIO(clearPin);
    data = new GPIO(dataPin);
    initialize();
}

int Prog::write(int data, int bitNum) {
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
    
    return 0;
}

Prog::~Prog() {
    delete(clock);
    delete(clear);
    delete(data);
}

int Prog::status() {
    cout << "CLOCK -- ";
    clock->status();
    cout << "CLEAR -- ";
    clear->status();
    cout << "DATA -- ";
    data->status();

    return 0;
}
int Prog::initialize() {
    clock->setDirection(OUT);
    data->setDirection(OUT);
    clear->setDirection(OUT);
    
    clock->setValue(LOW);
    data->setValue(LOW);
    clear->setValue(HIGH);

    return 0;
}

int Prog::setBit(GPIO_VALUE val) {
    data->setValue(val);

    clock->setValue(LOW);
    usleep(HOLD);
    clock->setValue(HIGH);
    usleep(HOLD);
    clock->setValue(LOW);
    
    return 0;
}

int Prog::clearReg() {
    clear->setValue(LOW);
    usleep(HOLD);
    clear->setValue(HIGH); //active low
    
    return 0;
}
