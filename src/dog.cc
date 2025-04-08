#include "dog.hh"
#include <string>
#include <iostream>

// dog constructor just calls base class constructor through initializer list
Dog::Dog(std::string name): Animal(name) {}

// overriding base class
void Dog::Speak()
{
  std::cout << "Bark!" << std::endl;
}
