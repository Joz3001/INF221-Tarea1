CXX = g++
CXXFLAGS = -Wall -O3
LIBS = -lpsapi
TARGET = sorting.exe

all: $(TARGET)

$(TARGET): sorting.cpp algorithms/quicksort.cpp algorithms/mergesort.cpp algorithms/patiencesort.cpp algorithms/sort.cpp
	$(CXX) $(CXXFLAGS) sorting.cpp algorithms/quicksort.cpp algorithms/mergesort.cpp algorithms/patiencesort.cpp algorithms/sort.cpp -o $(TARGET) $(LIBS)

clean:
	del $(TARGET)