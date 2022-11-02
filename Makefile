src = $(wildcard *.cpp)
target = $(patsubst %.cpp, %, $(src))

CXXFLAGS = -std=c++17 \
	-O3

.PHONY: all
all: $(target)

$(target): % : %.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@
