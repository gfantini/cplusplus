#include "add.hh"

/* compile me with
 * g++ -shared -fPIC -o libadd.so add.cc
 */ 

extern "C" int add(int a, int b) {
    return a + b;
}