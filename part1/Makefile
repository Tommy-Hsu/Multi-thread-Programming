TARGET := pi.out
SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)
CXX := g++ -m64
CXXFLAGS := -O3 -std=c++17 -Wall -pthread

.PHONY: default clean

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
