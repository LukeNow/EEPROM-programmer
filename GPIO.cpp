#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>

#include "GPIO.h"

GPIO::GPIO(int num, int hold) {
    number = num;
    holdTime = hold;
    name = "gpio" + std::to_string(number);
    path = GPIO_PATH + name;
    
    this->exportGPIO();
}

GPIO::~GPIO() {
    this->unexportGPIO();
}

void GPIO::status() {
    std::cout << "Status of " << name << "\n";
    if (getDirection() == 0) {
        std::cout << "\tDirection: IN\n";
    }
    else {
        std::cout << "\tDirection: OUT\n";
    }

    if (getValue() == 0) {
        std::cout << "\tValue: LOW\n";
    }
    else {
        std::cout << "\tValue: HIGH\n";
    }
}

void GPIO::setDirection(GPIO_DIRECTION dir) {
    std::ofstream fs;
    std::string dirPath = path + "/direction";
    fs.open(dirPath);

    if (dir == 0) {
        fs << "in";
    }
    else {
        fs << "out";
    }

    fs.close();
}

GPIO_DIRECTION GPIO::getDirection() {
    std::ifstream fs;
    std::string dirPath = path + "/direction";
    fs.open(dirPath);

    std::string dirVal;
    fs >> dirVal;
    fs.close();
    if (dirVal == "in") {
        return IN;
    }
    else {
        return OUT;
    }
}

void GPIO::setValue(GPIO_VALUE val) {
    std::ofstream fs;
    std::string valPath = path + "/value";
    fs.open(valPath);

    fs << val;
    fs.close();
}

GPIO_VALUE GPIO::getValue() {
    std::ifstream fs;
    std::string valPath = path + "/value";
    fs.open(valPath);
    
    GPIO_VALUE val;
    int svalue;
    fs >> svalue;

    if (svalue == 1) {
        val = HIGH;
    }
    else {
        val = LOW;
    }
    fs.close();
    return val;
}

void GPIO::pulse(GPIO_VALUE pulseVal) {
    if (pulseVal == 0) {
        setValue(HIGH);
        usleep(holdTime);
        setValue(LOW);
        usleep(holdTime);
        setValue(HIGH);
    }
    else {
        setValue(LOW);
        usleep(holdTime);
        setValue(HIGH);
        usleep(holdTime);
        setValue(LOW);
    }
}


void GPIO::exportGPIO() {
    std::ofstream fs;
    std::string exportPath = GPIO_PATH + "export";
    fs.open(exportPath);
    
    std::string val = std::to_string(number);
    fs << val;
    fs.close();
}

void GPIO::unexportGPIO() {
    std::ofstream fs;
    std::string unexportPath = GPIO_PATH + "unexport";
    fs.open(unexportPath);
    
    std::string val = std::to_string(number);
    fs << val;
    fs.close();
}
