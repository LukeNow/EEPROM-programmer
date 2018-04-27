#include "GPIO.h"

GPIO::GPIO(int num) {
    number = num;
    name = "gpio" + to_string(number);
    path = GPIO_PATH + name;
    
    this->exportGPIO();
}

int GPIO::status() {
    cout << "Status of " << name << endl;
    if (getDirection() == 0) {
        cout << "\tDirection: IN\n";
    }
    else {
        cout << "\tDirection: OUT\n";
    }

    if (getValue() == 0) {
        cout << "\tValue: LOW" << endl;
    }
    else {
        cout << "\tValue: HIGH" << endl;
    }

    return 0;
}
int GPIO::setDirection(GPIO_DIRECTION dir) {
    ofstream fs;
    string dirPath = path + "/direction";
    fs.open(dirPath);

    if (dir == 0) {
        fs << "in";
    }
    else {
        fs << "out";
    }

    fs.close();
    return 0;
}

GPIO_DIRECTION GPIO::getDirection() {
    ifstream fs;
    string dirPath = path + "/direction";
    fs.open(dirPath);

    string dirVal;
    fs >> dirVal;
    fs.close();
    if (dirVal == "in") {
        return IN;
    }
    else {
        return OUT;
    }
    
}

int GPIO::setValue(GPIO_VALUE val) {
    ofstream fs;
    string valPath = path + "/value";
    fs.open(valPath);

    fs << val;
    fs.close();
    return 0;
}

GPIO_VALUE GPIO::getValue() {
    ifstream fs;
    string valPath = path + "/value";
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

int GPIO::pulse(GPIO_VALUE pulseVal) {
    if (pulseVal == 0) {
        setValue(HIGH);
        usleep(HOLD);
        setValue(LOW);
        usleep(HOLD);
        setValue(HIGH);
    }
    else {
        setValue(LOW);
        usleep(HOLD);
        setValue(HIGH);
        usleep(HOLD);
        setValue(LOW);
    }

    return 0;
}


int GPIO::exportGPIO() {
    ofstream fs;
    string exportPath = GPIO_PATH + "export";
    fs.open(exportPath);
    
    string val = to_string(number);
    fs << val;
    fs.close();
    return 0;
}

int GPIO::unexportGPIO() {
    ofstream fs;
    string unexportPath = GPIO_PATH + "unexport";
    fs.open(unexportPath);
    
    string val = to_string(number);
    fs << val;
    fs.close();
    return 0;
}
GPIO::~GPIO() {
    this->unexportGPIO();
}



