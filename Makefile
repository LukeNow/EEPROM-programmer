VERSION=-std=c++11
DEPEND=GPIO.cpp prog.cpp
HEADER=GPIO.h prog.h

prog: $(DEPEND) $(HEADER) main.cpp
	g++ $(VERSION) $(DEPEND) main.cpp -o EEPROM-Prog

clean:
	@ rm EEPROM-Prog
