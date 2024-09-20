CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = 
TARGET = main

all: $(TARGET)
	./main

$(TARGET): main.o
	$(CXX) -o $(TARGET) main.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CXXFLAGS)

clean:
	rm -rf $(TARGET) main.o
