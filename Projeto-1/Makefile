CXX = g++
CXXFLAGS = -g -std=c++11 -O3 -Wall -lm
TARGET = proj.out
SRC = Projeto1.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.out *.in
