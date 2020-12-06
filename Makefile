EXENAME = finalproj
OBJS = read_from_file.o graph.o graph_algorithms.o main.o 

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

graph.o:  main.cpp graph.cpp
	$(CXX) $(CXXFLAGS) main.cpp graph.cpp

graph_algorithms.o:  main.cpp graph_algorithms.cpp
	$(CXX) $(CXXFLAGS) main.cpp graph_algorithms.cpp

read_from_file.o: main.cpp read_from_file.cpp
	$(CXX) $(CXXFLAGS) main.cpp read_from_file.cpp

test: output_msg catch/catchmain.cpp tests/tests.cpp read_from_file.cpp graph_algorithms.cpp graph.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp read_from_file.cpp graph_algorithms.cpp graph.cpp $(LDFLAGS) -o test
	
drawmap: output_msg drawmap.o PNG.o HSLAPixel.o lodepng.o graph.o graph_algorithms.o read_from_file.o
	$(LD) drawmap.o PNG.o HSLAPixel.o lodepng.o graph.o graph_algorithms.o read_from_file.o $(LDFLAGS) -o drawmap

drwamap.o: drawmap.cpp drawmap.h
	$(CXX) $(CXXFLAGS) drawmap.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp

#main.o : main.cpp
	#$(CXX) $(CXXFLAGS) main.cpp

clean:
	-rm -f *.o $(EXENAME) test

#for drawmap testing




