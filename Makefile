CXX=g++

OBJS=\
	usbdriver.o \
	rs232driver.o \

all: main

main: $(OBJS) main.o
	$(CXX) -o grue-usb-avr main.o $(OBJS)

clean:
	rm -f *.o grue-usb-avr 

.cc.o:
	$(CXX) -c $< 
