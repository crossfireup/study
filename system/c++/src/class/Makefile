# makefile to generate exe
#

CXX = g++
CXXFLAGS = -g

SRCS := string.cpp

OBJS := $(SRCS:.cpp=.o)

MAIN := string_ops

.PHONY: all

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXGLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	$(RM) *.o $(MAIN)
