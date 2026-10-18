##
## Configuration
##

TARGET = test-toolbox.exe
CXX = g++
CXXFLAGS = -Wall -Wextra

##
## Rules
##

default: all

all: $(TARGET)

$(TARGET): test-toolbox.cpp ../source/cms.cpp ../source/info.cpp ../source/lut.cpp ../source/profile.cpp ../source/parse.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

FMT_SRCS = test-toolbox.cpp

fmt:
	clang-format -i $(FMT_SRCS)

lint:
	clang-format --dry-run -Werror $(FMT_SRCS)