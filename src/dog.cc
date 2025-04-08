#include "dog.hh"
#include <string>
#include <iostream>

// overriding base class
void Dog::Speak()
{
  std::cout << "Bark!" << std::endl;
}
