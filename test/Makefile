CC=g++
CFLAGS=-c
LDFLAGS=-lgtest
INCLUDES=/usr/local/include/
LIBS=/usr/local/lib/
SOURCES=$(wildcard gtest*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=mystl_test
DEBUG=-g

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	    $(CC) $(DEBUG) -L$(LIBS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	    $(CC) $(DEBUG) $(CFLAGS) -I $(INCLUDES) $< -o $@

.PHONY: clean

clean:
	    @rm -f $(TARGET) $(OBJECTS)
