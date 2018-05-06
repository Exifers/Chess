CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -I src/

fls = $(shell find src/ -type f -name "*.cc")

debug : CXXFLAGS += -g

all:
	$(CXX) $(CXXFLAGS) $(fls) -o main
debug:
	$(CXX) $(CXXFLAGS) $(fls) -o main
