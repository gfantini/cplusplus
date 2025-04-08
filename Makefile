# makefiles work with TABS, not spaces
# definition of a variable, which is a string, always
OBJS := bld/printer.o bld/dog.o bld/animal.o
CC	:= g++
CC_OPTS	:= -Wc++11-extensions

# also rules, the ":" reads "depends on"
# this rule relates to the file ./hello, which doesn't depend on anything
# in addition, before running commands, make will print them to screen

all : main
	echo "[make all]"
	echo $@

hello:
	echo "Hello World"

# compiles main from main.cpp
# $@ gets substituted by the target (i.e. whatever comes before :)
# $^ gets substituted by the dependancies (i.e. whatever comes after :)
# $< gets substituted by the first dependancy (i.e. first string after :)
main: main.cpp $(OBJS)
	echo "building $<"
	$(CC) $(CC_OPTS) $^ -o $@

# compilazione object file
bld/printer.o : src/printer.cc src/printer.hh
	$(CC) $(CC_OPTS) -c src/printer.cc -o bld/printer.o

bld/dog.o : src/dog.cc 
	$(CC) $(CC_OPTS) -c src/dog.cc -o bld/dog.o

bld/animal.o : src/animal.cc
	$(CC) $(CC_OPTS) -c src/animal.cc -o bld/animal.o

# cleans executable
clean:
	rm main
	rm bld/*
	rm ./*~
	rm ./src/*~
