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
FMT_SRCS = $(shell find . \( -name '*.cpp' -o -name '*.h' \) -not -path './SDK/*')

default: all

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

fmt:
	clang-format -i $(FMT_SRCS)

lint:
	clang-format --dry-run -Werror $(FMT_SRCS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.exe: $(OBJS) $(LIBS)
	$(CXX) $(CXXFLAGS) $^ -o $@