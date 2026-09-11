CXX = g++
CXXFLAGS = -Wall -O3
LIBS = -lpsapi
TARGET = matrix_multiplication.exe

all: $(TARGET)

$(TARGET): matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp
	$(CXX) $(CXXFLAGS) matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp -o $(TARGET) $(LIBS)

clean:
	del $(TARGET)