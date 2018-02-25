##
## Configuration
##

TARGET = videoeq-toolbox.exe
LIBS = SDK/libVideoEq.a SDK/SiUSBXp.lib

CPP = g++
CPPFLAGS = -static

##
## Rules
##

SRCS = $(shell find . -name '*.cpp')
OBJS = $(SRCS:%.cpp=%.o)

default: all

all: $(TARGET)

clean:
	rm -f $(TARGET)

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.exe: $(OBJS) $(LIBS)
	$(CPP) $(CPPFLAGS) $^ -o $@
