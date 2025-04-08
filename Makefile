# makefiles work with TABS, not spaces
# definition of a variable, which is a string, always
CC	:= g++
CFLAGS	:= -Wc++11-extensions

# Trova tutti i file sorgenti con estensione .cc nella cartella src/
SRC_DIR := ./src
SRC_EXT := .cc
SRCS = $(wildcard $(SRC_DIR)/*$(SRC_EXT))

# Sostituisci 
# $(variabile:pattern=replacement)
# % -> viene lasciato così com'è
OBJ_DIR := ./bld
OBJ_EXT := .o
OBJS := $(SRCS:$(SRC_DIR)/%$(SRC_EXT)=$(OBJ_DIR)/%$(OBJ_EXT))


# also rules, the ":" reads "depends on"
# this rule relates to the file ./hello, which doesn't depend on anything
# in addition, before running commands, make will print them to screen

all : main
	echo "[make all]"
	echo $@

# compiles main (target) from main.cpp (dependancy)
# $@ gets substituted by the target (i.e. whatever comes before :)
# $^ gets substituted by the dependancies (i.e. whatever comes after :)
# $< gets substituted by the first dependancy (i.e. first string after :)
main: main.cpp $(OBJS)
	echo "building $<"
	$(CC) $(CFLAGS) $^ -o $@

# compilazione object file
# per ogni file che si chiama src/<file>.cc, crea una regola
bld/%.o : src/%.cc
	$(CC) $(CFLAGS) -c $^ -o $@ 

# debug
debug :
	echo $@
	echo $(SRCS)
	echo $(OBJS)

# cleans executable
clean:
	rm main
	rm bld/*
	rm ./*~
	rm ./src/*~
