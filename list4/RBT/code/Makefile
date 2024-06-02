CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -I../../include

EXES = large_data small_data

all: $(EXES)

large_data: large_data.cpp ../../include/lib.cpp ../../include/lib.hpp rbt.hpp
	$(CXX) $(CXXFLAGS) -o large_data large_data.cpp ../../include/lib.cpp

small_data: small_data.cpp ../../include/lib.cpp ../../include/lib.hpp rbt.hpp
	$(CXX) $(CXXFLAGS) -o small_data small_data.cpp ../../include/lib.cpp

clean:
	rm -f $(EXES)

.PHONY: all clean