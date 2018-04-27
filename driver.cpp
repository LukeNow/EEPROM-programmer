#include "prog.h"
#include <sstream>

const string USAGE = "USAGE: ./EEPROM_Prog [input filename]";

int main(int argc, char** argv) {
    int lineNum = 1;
    string line;
    fstream infile;   

    if (argc != 2) {
        cout << USAGE << endl;
        return 1;
    }

    infile.open(argv[1]);
    
    if (!infile.is_open()) {
        cout << "Couldnt open input File" << endl;
        return 1;
    }
    
    /* FILE CHECKING.
     * Checks if within Paramaters
     * -- Two Values per line
     * -- Values are within specified range, 11 bits for addr 8 for data
     * -- Prints error report of which line it occurred and what value was invalid
     */

    while(getline(infile, line)) {
        stringstream ss(line);
        short int data[4];
        int wordCount = 0;
        

        while (ss >> hex >> data[wordCount]) {
            if(wordCount > 1) {
                cout << "More than 2 number found on line " << lineNum << endl;
                return 1;
            }
            wordCount++;
        }
        
        if (wordCount < 2) {
            cout << "Less than 2 numbers found on line " << lineNum << endl;
            return 1;
        }
        
        if (data[0] > MAX_ADDR || data[0] < 0) {
            cout << "Address value " << data[0] << " on line " << lineNum << " is invalid." << endl;
            return 1;
        }
        if (data[1] > MAX_DATA || data[1] < 0) {
            cout << "Data value " << data[1] << " on line " << lineNum << " is invalid." << endl;
            return 1;
        }
        
        lineNum++;
    }
    
    /* Back to beginning of file to start writing data. */
    infile.clear();
    infile.seekg(0, ios::beg);
    
    cout << "Beginning write . . . " << endl;

    /* Clock, clear, and data respectively. Numbers are GPIO pin numbers. */
    Prog addr(80, 79, 78);
    Prog data(88, 87, 86);
    
    /* WE pin is used to pulse the EEPROM to write values from addr and data. */
    GPIO WE(76);
    WE.setDirection(OUT);
    WE.setValue(HIGH);
    
    /* Data writing. */
    while(getline(infile, line)) {
        short int addrVal;
        short int dataVal;
        stringstream ss(line);
        
        addr.clearReg();
        data.clearReg();

        ss >> hex >> addrVal;
        ss >> hex >> dataVal;
        
        cout << "addr: " << addrVal;
        cout << " data: " << dataVal << endl;

        addr.write(addrVal, 11);
        data.write(dataVal, 8);
        
        WE.pulse(LOW);
    }
    
    cout << "Done!" << endl;
    
    return 0;
}


