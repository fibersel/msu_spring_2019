#Установим используемый компилятор
CC=g++


#Установим используемые флаги
CFLAGS=-c -Wall -std=c++11


SOURCES_MAIN=main.cpp
OBJECTS_MAIN=$(SOURCES_MAIN:.cpp=.o)
EXECUTABLE_MAIN=test

all: $(EXECUTABLE_MAIN)

$(EXECUTABLE_MAIN): $(OBJECTS_MAIN) 	
	$(CC) $(OBJECTS_MAIN) -o $(EXECUTABLE_MAIN) -pthread


.cpp.o: 
	$(CC) $(CFLAGS)  $< -o $@ 


clean:
	rm -rf *.o $(EXECUTABLE_MAIN)
