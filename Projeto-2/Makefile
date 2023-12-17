CXX = g++
CXXFLAGS = -g -std=c++11 -O3 -Wall -lm
TARGET = proj.out
SRC = Projeto2.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.out

format:
	@which clang-format >/dev/null 2>&1 || echo "Please install clang-format to run this command"
	clang-format -i *.cpp 