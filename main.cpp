#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

#include "prog.h"

const std::string USAGE = "USAGE: ./EEPROM-Prog [input filename]\n";

int main(int argc, char** argv) {
    int lineNum = 1;
    std::string line;
    std::fstream infile;   

    if (argc != 2) {
        std::cout << USAGE;
        return 1;
    }

    infile.open(argv[1]);
    
    if (!infile.is_open()) {
        std::cout << "Couldnt open input File\n";
        return 1;
    }
    
    /* FILE CHECKING.
     * Checks if within Paramaters
     * -- Two Values per line
     * -- Values are within specified range, 11 bits for addr 8 for data
     * -- Prints error report of which line it occurred and what value was invalid
     */

    while(getline(infile, line)) {
        std::stringstream ss(line);
        short int data[4];
        int wordCount = 0;
        

        while (ss >> std::hex >> data[wordCount]) {
            if(wordCount > 1) {
                std::cout << "More than 2 number found on line " << lineNum << "\n";
                return 1;
            }
            wordCount++;
        }
        
        if (wordCount < 2) {
            std::cout << "Less than 2 numbers found on line " << lineNum << "\n";
            return 1;
        }
        
        if (data[0] > MAX_ADDR || data[0] < 0) {
            std::cout << "Address value " << data[0] << " on line " << lineNum << " is invalid.\n";
            return 1;
        }
        if (data[1] > MAX_DATA || data[1] < 0) {
            std::cout << "Data value " << data[1] << " on line " << lineNum << " is invalid.\n";
            return 1;
        }
        
        lineNum++;
    }
    
    /* Back to beginning of file to start writing data. */
    infile.clear();
    infile.seekg(0, std::ios::beg);
    
    std::cout << "Beginning write . . .\n ";

    /* Clock, clear, and data respectively. Numbers are GPIO pin numbers. */
    Prog addr(45, 69, 66);
    Prog data(26, 44, 68);
    
    /* WE pin is used to pulse the EEPROM to write values from addr and data. */
    GPIO WE(67, 5000);
    WE.setDirection(OUT); 
    WE.setValue(HIGH);   
    
    /* Data writing. */
    while(getline(infile, line)) {
        short int addrVal;
        short int dataVal;
        std::stringstream ss(line);
        
        addr.clearReg();
        data.clearReg();

        ss >> std::hex >> addrVal;
        ss >> std::hex >> dataVal;
        
        std::cout << "addr: " << addrVal;
        std::cout << " data: " << dataVal << "\n";

        addr.write(addrVal, 11);
        data.write(dataVal, 8);
        
        WE.pulse(LOW); 
    }
    
    data.status();
    addr.status();
    WE.status();


    std::cout << "Done!\n";
    
    return 0;
}


