# makefiles work with TABS, not spaces
# definition of a variable, which is a string, always
OBJS := bld/printer.o bld/dog.o bld/animal.o

# also rules, the ":" reads "depends on"
# this rule relates to the file ./hello, which doesn't depend on anything
# in addition, before running commands, make will print them to screen

all : main

hello:
	echo "Hello World"

# compiles main from main.cpp, no linking whatsoever
main: main.cpp $(OBJS)
	g++ main.cpp bld/printer.o bld/dog.o -o main

# compilazione object file
bld/printer.o : src/printer.cc src/printer.hh
	g++ -c src/printer.cc -o bld/printer.o

bld/dog.o : src/dog.cc 
	g++ -c src/dog.cc -o bld/dog.o

bld/animal.o : src/animal.cc
	g++ -c src/animal.cc -o bld/animal.o

# cleans executable
clean:
	rm main
	rm bld/*
	rm ./*~
	rm ./src/*~
