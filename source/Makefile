##
## Configuration
##

TARGET = videoeq-toolbox.exe
LIBS = SDK/libVideoEq.a SDK/SiUSBXp.lib

CXX = g++
CXXFLAGS = -static -Wall -Wextra

##
## Rules
##

SRCS = $(shell find . -name '*.cpp')
OBJS = $(SRCS:%.cpp=%.o)

default: all

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.exe: $(OBJS) $(LIBS)
	$(CXX) $(CXXFLAGS) $^ -o $@