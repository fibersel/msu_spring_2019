#Установим используемый компилятор
CC=g++


#Установим используемые флаги
CFLAGS=-c -Wall -std=c++11

SOURCES_TEST=test.cpp
OBJECTS_TEST=$(SOURCES_TEST:.cpp=.o)
EXECUTABLE_TEST=test

SOURCES_MAIN=main.cpp
OBJECTS_MAIN=$(SOURCES_MAIN:.cpp=.o)
EXECUTABLE_MAIN=main

all: $(EXECUTABLE_MAIN)

$(EXECUTABLE_MAIN): $(OBJECTS_MAIN) 	
	$(CC) $(OBJECTS_MAIN) -o $(EXECUTABLE_MAIN)

testing: $(EXECUTABLE_TEST)

$(EXECUTABLE_TEST): $(OBJECTS_TEST) 	
	$(CC) $(OBJECTS_TEST) -o $(EXECUTABLE_TEST)

.cpp.o: 
	$(CC) $(CFLAGS)  $< -o $@ 


clean:
	rm -rf *.o $(EXECUTABLE_TEST) $(EXECUTABLE_MAIN)
