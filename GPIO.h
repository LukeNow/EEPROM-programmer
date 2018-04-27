#ifndef GPIO_H
#define GPIO_H
#include<iostream>
#include<unistd.h>
#include<string>
#include<fstream>

using namespace std;

const int HOLD = 1000; //microseconds

enum GPIO_DIRECTION { IN, OUT };
enum GPIO_VALUE { LOW=0, HIGH=1 };
using namespace std;
const string GPIO_PATH = "/sys/class/gpio/";

class GPIO {
    private:
        int number;
        string name, path;
    
    public: 
        GPIO(int number);
        
        virtual int setDirection(GPIO_DIRECTION);
        virtual GPIO_DIRECTION getDirection();
        virtual int setValue(GPIO_VALUE);
        virtual GPIO_VALUE getValue();
        virtual ~GPIO();
        int status();
        int pulse(GPIO_VALUE pulseVal);

    private:
        int exportGPIO();
        int unexportGPIO();

};
#endif
