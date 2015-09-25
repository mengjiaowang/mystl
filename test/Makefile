CC=g++
CFLAGS=-c
LDFLAGS=-lgtest
INCLUDES=/usr/local/include/
LIBS=/usr/local/lib/
SOURCES=gtest_main.cpp gtest_algo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=mystl_test

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	    $(CC) -L$(LIBS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	    $(CC) $(CFLAGS) -I $(INCLUDES) $< -o $@

.PHONY: clean

clean:
	    @rm -f $(TARGET) $(OBJECTS)
