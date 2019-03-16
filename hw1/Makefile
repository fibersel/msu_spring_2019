#Установим используемый компилятор
CC=g++


#Установим используемые флаги
CFLAGS=-c -Wall -O2

SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 	
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

.cpp.o: 
	$(CC) $(CFLAGS)  $< -o $@ 


clean:
	rm -rf *.o $(EXECUTABLE)
