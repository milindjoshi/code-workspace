CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = task_manager
SRC = task_manager.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

debug: CXXFLAGS += -g
debug: $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

