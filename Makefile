#

CFLAGS = -g -Wall 

TARGET = getbits

all: $(TARGET)

getbits: getbits.c

clean:
	rm -rf $(TARGET) *.o *~
