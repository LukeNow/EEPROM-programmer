VERSION=-std=c++11
DEPEND=GPIO.cpp prog.cpp
HEADER=GPIO.h prog.h

prog: $(DEPEND) $(HEADER) driver.cpp
	g++ $(VERSION) $(DEPEND) driver.cpp -o drive

clean:
	@ rm drive
